#define NAPI_VERSION 8
#include <cws_soap.h>
#include <cws_utils.h>
#include <base_msgs.h>
#include <cws_memory.h>
#include <node_api.h>

//https://nodejs.org/api/n-api.html
//https://github.com/nodejs/nan/tree/HEAD/examples/

#ifndef WITH_NOIDREF
  #error "Error. Declare first line below in stdsoap2.h #define WITH_NOIDREF"
#endif

#ifdef JS_SOAP_DEBUG
 #define JS_WITSML21_DEBUG(...) \
    fprintf(stdout, "\nJSWITSML14x_PARSER DEBUG: ");\
    fprintf(stdout, __VA_ARGS__);
#else
 #define JS_WITSML21_DEBUG(std, ...)
#endif

#define JS_CWS_THROW(errFunc, errDesc, errCode) \
  cws_js_throw(env, &cws_js_err, errFunc, errDesc, errCode); \
  return NULL;

#define JS_CWS_THROW_GOTO(errFunc, errDesc, errCode, onErrorGoto) \
  cws_js_throw(env, &cws_js_err, errFunc, errDesc, errCode); \
  goto onErrorGoto;

#define JS_CWS_THROW_COND_GOTO(condT, errFunc, errDesc, errCode, onErrorGoto) \
  if (condT) { \
    JS_CWS_THROW_GOTO(errFunc, errDesc, errCode, onErrorGoto) \
  }

#define JS_CWS_THROW_COND(condT, errFunc, errDesc, errCode) \
  if (condT) { \
    JS_CWS_THROW(errFunc, errDesc, errCode) \
  }

#define JS_GET_INSTANCE_NAME (js_cws_instance->config)->instance_name

#define JS_GET_INTERNAL_SOAP_ERROR js_cws_instance->config->internal_soap_error
#define JS_GET_OBJECT_NAME js_cws_instance->config->objectName
#define JS_GET_BASEMSG_CODE (int)js_cws_instance->config->base_msg.code
#define JS_GET_FAULT_STRING js_cws_instance->config->cws_soap_fault.faultstring
#define JS_GET_FAULT_STRING_LEN js_cws_instance->config->cws_soap_fault.faultstring_len
#define JS_GET_XML_FAULT_DETAIL js_cws_instance->config->cws_soap_fault.XMLfaultdetail
#define JS_GET_XML_FAULT_DETAIL_LEN js_cws_instance->config->cws_soap_fault.XMLfaultdetail_len

#define ERR js_cws_instance->err

#define CHECK_HAS_ERROR(errFunc, errDesc, errCde) \
  if ((ERR!=0)||(JS_GET_INTERNAL_SOAP_ERROR!=0)||(JS_GET_BASEMSG_CODE<0)||(JS_GET_OBJECT_NAME==NULL)) {\
    JS_CWS_THROW(errFunc, errDesc, errCde) \
  }

#define JS_CWS_RETURN_NULL \
  JS_CWS_THROW_COND( \
    napi_get_null(env, &res)!=napi_ok, \
    "napi_get_null", \
    "Create JavaScript object 'null' error", \
    -15\
  )\
\
  return res;

#define JS_CWS_RETURN_UNDEFINED \
  JS_CWS_THROW_COND( \
    napi_get_undefined(env, &res)!=napi_ok, \
    "napi_get_undefined", \
    "Create JavaScript object 'undefined' error", \
    -16\
  )\
\
  return res;

/// UTILITIES
typedef napi_value (*cws_node_fn)(napi_env, napi_callback_info);
#define JS_CWS_GET_CONFIG(js_cws_cfg) js_cws_cfg->config
struct js_cws_config_t {
  CWS_CONFIG *config;
  int err;
  char *str; //Alloc'd draft text for manipulating string and data. Must be free
  size_t str_len; // Copied string length
  size_t str_size; // Alloc'd string size
};

struct cws_js_err_t {
  char buf[512];
  char err[16];
};

#define SET_CONST_TYPE(val)\
  {#val, val}

struct cws_js_int32_t {
  const char *name;
  int32_t value;
} RULES_TYPE[]={
  SET_CONST_TYPE(ACTION_READ_141X),
  SET_CONST_TYPE(ACTION_WRITE_141X),
  SET_CONST_TYPE(ACTION_UPDATE_141X),
  SET_CONST_TYPE(ACTION_DELETE_141X),
  {NULL}
};

#define SET_JS_FN_CALL(fn) {#fn, c_##fn}
typedef struct cws_js_fn_call_t {
   const char *function_name;
   cws_node_fn fn;
} CWS_JS_FUNCTIONS_OBJ;

static char *textBufAlloc(size_t *sz, struct js_cws_config_t *js_cws_config, size_t len)
{
  char *str_tmp;
  size_t str_sz_tmp;

  if (len>0) {
    JS_WITSML21_DEBUG("textBufAlloc: Begin creation/realloc text buf of length %lu", len)
    if (js_cws_config->str) {
      if (js_cws_config->str_size>len) {
        *sz=js_cws_config->str_size;
        js_cws_config->str[len]=0;
        JS_WITSML21_DEBUG("textBufAlloc: Recycled buffer %p of size %lu", js_cws_config->str, js_cws_config->str_size)
        return js_cws_config->str;
      }

      JS_WITSML21_DEBUG("textBufAlloc: Try to realloc pointer %p of size %lu...", js_cws_config->str, js_cws_config->str_size)
      if ((str_tmp=(char *)cws_realloc((void *)js_cws_config->str, (str_sz_tmp=(len+1))))) {
        js_cws_config->str_len=len;
        *sz=js_cws_config->str_size=str_sz_tmp;
        JS_WITSML21_DEBUG("textBufAlloc: realloc'd pointer has changed? = %s", (str_tmp==js_cws_config->str)?"FALSE":"TRUE")
        (js_cws_config->str=str_tmp)[len]=0;
        JS_WITSML21_DEBUG("textBufAlloc: realloc'd pointer %p of new size %lu...", js_cws_config->str, js_cws_config->str_size)
        return js_cws_config->str;
      }
      
      *sz=js_cws_config->str_size; // Size <= len. Keep last size (realloc fail) and old pointer
      js_cws_config->str_len=0;
      js_cws_config->str[0]=0; // On realloc fail text buffer has empty string
      JS_WITSML21_DEBUG("textBufAlloc: Fail on realloc. Keep old pointer %p of size %lu", js_cws_config->str, js_cws_config->str_size)
    } else {
      JS_WITSML21_DEBUG("textBufAlloc: try to create new text buffer of length %lu", len)
      if ((js_cws_config->str=(char *)cws_malloc((js_cws_config->str_size=(len+1))))) {
        js_cws_config->str_len=len;
        *sz=js_cws_config->str_size;
        JS_WITSML21_DEBUG("textBufAlloc: try to create text buffer of length %lu. Success at %p with size %lu", len, js_cws_config->str, js_cws_config->str_size)
        return js_cws_config->str;
      }
      js_cws_config->str_len=0;
      *sz=js_cws_config->str_size=0;
      JS_WITSML21_DEBUG("textBufAlloc: Unable to alloc new text buffer.")
    }
  }

  return NULL;
}

static char *js_cws_get_value_string_utf8(size_t *len, napi_env env, napi_value value, struct js_cws_config_t *js_cws_config)
{
  char *res;
  size_t sz;

  if (napi_get_value_string_utf8(env, value, NULL, 0, len)!=napi_ok)
    return NULL;

  if (!(res=textBufAlloc(&sz, js_cws_config, *len)))
    return NULL;

  if (napi_get_value_string_utf8(env, value, res, sz, len)==napi_ok) {
    JS_WITSML21_DEBUG("js_cws_get_value_string_utf8: has NULL terminator: %d\n", res[*len]==0)
    JS_WITSML21_DEBUG("js_cws_get_value_string_utf8: value: %s\n", res)
    return res;
  }

  return NULL;
}

enum c_parse_util_e {
  IS_BSON=1,
  IS_JSON
};

static int c_parse_util(
  CWS_CONFIG *config, 
  void **v_ser,
  const char *c_xml,
  size_t c_xml_size,
  enum c_parse_util_e c_parse_util,
  char **errMsg,
  int fromMem
)
{

  short code;
  *v_ser=NULL;

  if ((fromMem!=0)&&(c_xml_size<1)) {
    *errMsg="Wrong xml size or empty xml string";
    return -498;
  }

  if (cws_recycle_config(config)) {
    *errMsg="Could not recycle instance";
    return -499;
  }

  if (fromMem) {
    if (!cws_parse_XML_soap_envelope(config, (char *)c_xml, (size_t)c_xml_size)) {
      *errMsg="Could not parse xml string. See xml errors for details";
      return -500;
    }
  } else if (!cws_parse_XML_soap_envelope_from_file(config, c_xml)) {
    *errMsg="Could not parse file. See xml errors for details";
    return -501;
  }

  if (cws_internal_serve(config)) {
    *errMsg="Could not deserialize xml string. See xml errors for details";
    return -502;
  }

  catch_base_msg14x(config, &code, (char **)errMsg);

  if (code<0)
    return (int)code;

  if (c_parse_util==IS_BSON) {
    if ((*v_ser=(void *)bsonSerialize(config))) {
      *errMsg="";
      return 0;
    }

    *errMsg="Could not serialize BSON";
  } else {
    if ((*v_ser=(void *)getJson(config))) {
      *errMsg="";
      return 0;
    }

    *errMsg="Could not serialize JSON";
  }

  return -503;
}

static void js_cws_config_free(struct js_cws_config_t **js_cws_config)
{

  JS_WITSML21_DEBUG("js_cws_config_free: Begin free if is NOT NULL %p", *js_cws_config)

  if (*js_cws_config) {

    JS_WITSML21_DEBUG("js_cws_config_free: Destroying config %p", JS_CWS_GET_CONFIG((*js_cws_config)))
    cws_config_free(&JS_CWS_GET_CONFIG((*js_cws_config)));

    if ((*js_cws_config)->str) {
      JS_WITSML21_DEBUG(
        "js_cws_config_free: Freeing draft string buffer %p of length %lu of size %lu",
        (*js_cws_config)->str, (*js_cws_config)->str_len, (*js_cws_config)->str_size
      )
      free((*js_cws_config)->str);
      (*js_cws_config)->str=NULL;
    }

    JS_WITSML21_DEBUG("js_cws_config_free: Destroying js_cws_config object %p", js_cws_config)
    free((void *)*js_cws_config);
    *js_cws_config=NULL;

    JS_WITSML21_DEBUG("js_cws_config_free: Destroyed")
  }

}

static struct js_cws_config_t *js_cws_config_init(int32_t rule, int versionCheckDisable)
{
  struct js_cws_config_t *js_cws_config;

  JS_WITSML21_DEBUG("js_cws_config_init: Initializing ...")
  if (!(js_cws_config=(struct js_cws_config_t *)malloc(sizeof(struct js_cws_config_t))))
    return NULL;

  if (versionCheckDisable)
    versionCheckDisable=CWS_FLAG_CHECK_VERSION_DISABLE;

  if (!(js_cws_config->config=cws_config_new("JSWITSML 1.4.x.x - 1.3.x.x BSON parser", NULL, CWS_FLAG_RECYCLABLE|versionCheckDisable, (int)rule)))
    goto js_cws_config_init_exit1;

  js_cws_config->err=0;
  js_cws_config->str=NULL;
  js_cws_config->str_len=0;
  js_cws_config->str_size=0;

  JS_WITSML21_DEBUG("js_cws_config_init: SUCCESS ... %p", js_cws_config)

  return js_cws_config;

js_cws_config_init_exit1:
  free((void *)js_cws_config);

  JS_WITSML21_DEBUG("\njs_cws_config_init: FAIL ...")

  return NULL;
}

//https://nodejs.org/api/n-api.html#napi_finalize
//typedef void (*napi_finalize)(napi_env env, void* finalize_data, void* finalize_hint);
static void cws_js_finalize(napi_env env, void *finalize_data, void *finalize_hint)
{
  void *data=finalize_data;
  JS_WITSML21_DEBUG("\ncws_js_finalize: Entering and perform cleanup %p", data)

  js_cws_config_free((struct js_cws_config_t **)&data);

}

static void cws_js_throw(napi_env env, struct cws_js_err_t *caster, const char *c_function_name, const char *errMessage, int err)
{
  snprintf(caster->buf, sizeof(caster->buf), "%s:Err.:%d %s", c_function_name, err, errMessage);
  snprintf(caster->err, sizeof(caster->err), "%d", err);
  napi_throw_error(env, caster->err, caster->buf);
}

static int cws_add_function_util(napi_env env, napi_value exports, CWS_JS_FUNCTIONS_OBJ *function, void *data)
{
  napi_value fn;

  while (function->function_name) {
    if (napi_create_function(env, NULL, 0, function->fn, data, &fn)!=napi_ok)
      return 300;

    if (napi_set_named_property(env, exports, function->function_name, fn)!=napi_ok)
      return 301;

    function++;
  }

  return 0;
}

static int cws_add_int32_list_util(napi_env env, napi_value exports, struct cws_js_int32_t *value)
{
  napi_value int32;

  while (value->name) {
    if (napi_create_int32(env, value->value, &int32)!=napi_ok)
      return 600;

    if (napi_set_named_property(env, exports, value->name, int32)!=napi_ok)
      return 601;

    value++;
  }

  return 0;
}

static int cws_add_int32_object_list_util(napi_value *int32_out, const char *objName, napi_env env, napi_value exports, struct cws_js_int32_t *value)
{
  napi_value obj, *objTmp;

  objTmp=(int32_out)?int32_out:&obj;

  if (napi_create_object(env, objTmp)!=napi_ok)
    return 602;

  if (napi_set_named_property(env, exports, objName, *objTmp)!=napi_ok)
    return 603;

  return cws_add_int32_list_util(env, *objTmp, value);
}

inline int js_cws_new_array_buffer(napi_value *dest, napi_env env, void *src, size_t src_sz)
{
  void *buf;

  if (napi_create_arraybuffer(env, src_sz, &buf, dest)==napi_ok) {
    memcpy(buf, src, src_sz);
    return 0;
  }

  return -1;
}

static int js_base_msg_util(napi_env env, napi_value *res, int32_t code, char *msg, size_t msg_len, char **errMsg)
{

  napi_value int32, str;

  if (napi_create_object(env, res)!=napi_ok) {
    *res=NULL;
    *errMsg="js_base_msg_util: Could not create object";
    return -900;
  }

  if (napi_create_int32(env, code, &int32)!=napi_ok) {
    *res=NULL;
    *errMsg="js_base_msg_util: Could not create int32 object";
    return -901;
  }

  if (napi_set_named_property(env, *res, "code", int32)!=napi_ok) {
    *res=NULL;
    *errMsg="js_base_msg_util: Could not set name property @ int32 object";
    return -902;
  }

  if (napi_create_string_utf8(env, msg, msg_len, &str)!=napi_ok) {
    *res=NULL;
    *errMsg="js_base_msg_util: Error on parsing XML fault detail string message";
    return -903;
  }

  if (napi_set_named_property(env, *res, "baseMessage", str)!=napi_ok) {
    *res=NULL;
    *errMsg="js_base_msg_util: Could not set name property @ string object";
    return -904;
  }

  *errMsg="";

  return 0;
}

///

napi_value c__witsml14xbsonInit_(napi_env env, napi_callback_info info)
{
  return NULL;
}

napi_value c_getBsonVersion(napi_env env, napi_callback_info info)
{
  napi_value argv, res;
  size_t argc=0;
  struct cws_js_err_t cws_js_err;
  struct cws_version_t version;

  JS_CWS_THROW_COND(napi_get_cb_info(env, info, &argc, &argv, NULL, NULL)!=napi_ok, "napi_get_cb_info", "Can't parse arguments", -19)

  JS_CWS_THROW_COND(argc, "c_getBsonVersion", "Too many arguments", -20)

  cws_version(&version);

  if (js_cws_new_array_buffer(&res, env, (void *)version.version, version.versionSize)==0)
    return res;

  JS_CWS_THROW("c_getBsonVersion", "Fail to create ArrayBuffer", -21);
}

napi_value c_parseFromFile(napi_env env, napi_callback_info info)
{
  napi_value argv=NULL, res;
  char *filename, *errMsg;
  size_t argc=1, filenameLen;
  struct cws_js_err_t cws_js_err;
  struct c_bson_serialized_t *bson_ser;
  struct js_cws_config_t *js_cws_instance;

  JS_CWS_THROW_COND(
    (ERR=(napi_get_cb_info(env, info, &argc, &argv, NULL, (void **)&js_cws_instance)!=napi_ok)),
    "napi_get_cb_info",
    "Can't parse arguments. Wrong argument at c_parseFromFile",
    120
  )

  JS_CWS_THROW_COND(
    (ERR=(js_cws_instance==NULL)),
    "c_parseFromFile",
    "Fatal: js_cws_instance. Was expected NOT NULL",
    121
  )

  JS_CWS_THROW_COND(
    (ERR=(argc==0)),
    "c_parseFromFile",
    "Missing argument. Was expected: file path/filename",
    122
  )

  JS_CWS_THROW_COND(
    (ERR=(argc>1)),
    "c_parseFromFile",
    "Too many arguments",
    123
  )

  JS_CWS_THROW_COND(
    (ERR=((filename=js_cws_get_value_string_utf8(&filenameLen, env, argv, js_cws_instance))==NULL)),
    "c_parseFromFile",
    "Could not parse filename. Wrong format or empty string or invalid utf-8 or no space in C string buffer",
    124
  )

  JS_CWS_THROW_COND(
    (ERR=c_parse_util(js_cws_instance->config, (void **)&bson_ser, filename, 0, IS_BSON, &errMsg, 0)),
    "c_parse_util", errMsg,
    ERR
  )

  JS_CWS_THROW_COND(
    (ERR=js_cws_new_array_buffer(&res, env, (void *)bson_ser->bson, bson_ser->bson_size)),
    "js_cws_new_array_buffer", "Could not copy BSON bytes to JavaScript array buffer @ c_parseFromFile",
    ERR
  )

  return res;
}

napi_value c_parse(napi_env env, napi_callback_info info)
{
  napi_value argv=NULL, res;
  char *text, *errMsg;
  size_t argc=1, textLen;
  struct cws_js_err_t cws_js_err;
  struct c_bson_serialized_t *bson_ser;
  struct js_cws_config_t *js_cws_instance;

  JS_CWS_THROW_COND(
    (ERR=(napi_get_cb_info(env, info, &argc, &argv, NULL, (void **)&js_cws_instance)!=napi_ok)),
    "napi_get_cb_info",
    "Can't parse arguments. Wrong argument at c_parse",
    100
  )

  JS_CWS_THROW_COND(
    (ERR=(js_cws_instance==NULL)),
    "c_parse",
    "Fatal: js_cws_instance. Was expected NOT NULL",
    101
  )

  JS_CWS_THROW_COND(
    (ERR=(argc==0)),
    "c_parse",
    "Missing argument. Was expected: xml text",
    102
  )

  JS_CWS_THROW_COND(
    (ERR=(argc>1)),
    "c_parse",
    "Too many arguments",
    103
  )

  JS_CWS_THROW_COND(
    (ERR=((text=js_cws_get_value_string_utf8(&textLen, env, argv, js_cws_instance))==NULL)),
    "js_cws_get_value_string_utf8",
    "Could not parse xml string. Wrong format or empty string or invalid utf-8 or no space in C string buffer",
    104
  )

  JS_CWS_THROW_COND(
    (ERR=c_parse_util(js_cws_instance->config, (void **)&bson_ser, text, textLen, IS_BSON, &errMsg, -1)),
    "c_parse_util", errMsg,
    ERR
  )

  JS_CWS_THROW_COND(
    (ERR=js_cws_new_array_buffer(&res, env, (void *)bson_ser->bson, bson_ser->bson_size)),
    "js_cws_new_array_buffer", "Could not copy BSON bytes to JavaScript array buffer @ c_parse",
    ERR
  )

  return res;
}

napi_value c_parseToJSON(napi_env env, napi_callback_info info)
{
  napi_value argv=NULL, res;
  char *text, *errMsg;
  size_t argc=1, textLen;
  struct cws_js_err_t cws_js_err;
  struct c_json_str_t *json_ser;
  struct js_cws_config_t *js_cws_instance;

  JS_CWS_THROW_COND(
    (ERR=(napi_get_cb_info(env, info, &argc, &argv, NULL, (void **)&js_cws_instance)!=napi_ok)),
    "napi_get_cb_info",
    "Can't parse arguments. Wrong argument at c_parseToJSON",
    200
  )

  JS_CWS_THROW_COND(
    (ERR=(js_cws_instance==NULL)),
    "c_parseToJSON",
    "Fatal: js_cws_instance. Was expected NOT NULL",
    201
  )

  JS_CWS_THROW_COND(
    (ERR=(argc==0)),
    "c_parseToJSON",
    "Missing argument. Was expected: xml text",
    202
  )

  JS_CWS_THROW_COND(
    (ERR=(argc>1)),
    "c_parseToJSON",
    "Too many arguments",
    203
  )

  JS_CWS_THROW_COND(
    (ERR=((text=js_cws_get_value_string_utf8(&textLen, env, argv, js_cws_instance))==NULL)),
    "js_cws_get_value_string_utf8",
    "Could not parse xml string. Wrong format or empty string or invalid utf-8 or no space in C string buffer",
    204
  )

  JS_CWS_THROW_COND(
    (ERR=c_parse_util(js_cws_instance->config, (void **)&json_ser, text, textLen, IS_JSON, &errMsg, -1)),
    "c_parse_util", errMsg,
    ERR
  )

  JS_CWS_THROW_COND(
    (ERR=(napi_create_string_utf8(env, json_ser->json, json_ser->json_len, &res)!=napi_ok)),
    "napi_create_string_utf8",
    "napi_create_string_utf8 @ c_parseToJSON. Error on parsing JSON string",
    205
  )

  return res;
}

napi_value c_parseFromFileJSON(napi_env env, napi_callback_info info)
{
  napi_value argv=NULL, res;
  char *filename, *errMsg;
  size_t argc=1, filenameLen;
  struct cws_js_err_t cws_js_err;
  struct c_json_str_t *json_ser;
  struct js_cws_config_t *js_cws_instance;

  JS_CWS_THROW_COND(
    (ERR=(napi_get_cb_info(env, info, &argc, &argv, NULL, (void **)&js_cws_instance)!=napi_ok)),
    "napi_get_cb_info",
    "Can't parse arguments. Wrong argument at c_parseFromFileJSON",
    140
  )

  JS_CWS_THROW_COND(
    (ERR=(js_cws_instance==NULL)),
    "c_parseFromFileJSON",
    "Fatal: js_cws_instance. Was expected NOT NULL",
    141
  )

  JS_CWS_THROW_COND(
    (ERR=(argc==0)),
    "c_parseFromFileJSON",
    "Missing argument. Was expected: file path/filename",
    142
  )

  JS_CWS_THROW_COND(
    (ERR=(argc>1)),
    "c_parseFromFileJSON",
    "Too many arguments",
    143
  )

  JS_CWS_THROW_COND(
    (ERR=((filename=js_cws_get_value_string_utf8(&filenameLen, env, argv, js_cws_instance))==NULL)),
    "c_parseFromFileJSON",
    "Could not parse filename. Wrong format or empty string or invalid utf-8 or no space in C string buffer",
    144
  )

  JS_CWS_THROW_COND(
    (ERR=c_parse_util(js_cws_instance->config, (void **)&json_ser, filename, 1, IS_JSON, &errMsg, 0)),
    "c_parse_util", errMsg,
    ERR
  )

  JS_CWS_THROW_COND(
    (ERR=(napi_create_string_utf8(env, json_ser->json, json_ser->json_len, &res)!=napi_ok)),
    "napi_create_string_utf8",
    "napi_create_string_utf8 @ c_parseFromFileJSON. Error on parsing JSON string",
    145
  )

  return res;
}

napi_value c_saveToFile(napi_env env, napi_callback_info info)
{
  int err;
  napi_value argv=NULL, res;
  size_t argc=1, filenameLen;
  char *filename;
  struct js_cws_config_t *js_cws_instance;
  struct cws_js_err_t cws_js_err;

  JS_CWS_THROW_COND(
    napi_get_cb_info(env, info, &argc, &argv, NULL, (void **)&js_cws_instance)!=napi_ok,
    "napi_get_cb_info",
    "Can't parse arguments. Wrong argument at c_saveToFile",
    150
  )

  JS_CWS_THROW_COND(argc==0, "c_saveToFile", "Missing arguments. Expected: Output filename", 151)

  JS_CWS_THROW_COND(argc>1, "c_saveToFile", "Too many arguments. Expected only one argument: output filename", 152)

  JS_CWS_THROW_COND(
    (js_cws_instance==NULL),
    "c_saveToFile",
    "Fatal: js_cws_instance @ c_saveToFile. Was expected NOT NULL",
    153
  )

  CHECK_HAS_ERROR("c_saveToFile", "Could not save BSON serialized to file for this object. Object not found or error on parsing", 154)

  JS_CWS_THROW_COND(
    (filename=js_cws_get_value_string_utf8(&filenameLen, env, argv, js_cws_instance))==NULL,
    "c_saveToFile",
    "Could not parse filename. Wrong format or empty string or invalid utf-8 or no space in C string buffer",
    155
  )

  JS_CWS_THROW_COND(
    (err=writeToFile(js_cws_instance->config, filename)),
    "writeToFile", "Could not save BSON file @ c_saveToFile",
    err
  )

  JS_CWS_RETURN_UNDEFINED
}

napi_value c_saveToFileJSON(napi_env env, napi_callback_info info)
{
  int err;
  napi_value argv=NULL, res;
  size_t argc=1, filenameLen;
  char *filename;
  struct js_cws_config_t *js_cws_instance;
  struct cws_js_err_t cws_js_err;

  JS_CWS_THROW_COND(
    napi_get_cb_info(env, info, &argc, &argv, NULL, (void **)&js_cws_instance)!=napi_ok,
    "napi_get_cb_info",
    "Can't parse arguments. Wrong argument at c_saveToFileJSON",
    160
  )

  JS_CWS_THROW_COND(argc==0, "c_saveToFileJSON", "Missing arguments. Expected: Output filename", 161)

  JS_CWS_THROW_COND(argc>1, "c_saveToFileJSON", "Too many arguments. Expected only one argument: output filename", 162)

  JS_CWS_THROW_COND(
    (js_cws_instance==NULL),
    "c_saveToFileJSON",
    "Fatal: js_cws_instance @ c_saveToFileJSON. Was expected NOT NULL",
    163
  )

  CHECK_HAS_ERROR("c_saveToFileJSON", "Could not save JSON serialized to file for this object. Object not found or error on parsing", 154)

  JS_CWS_THROW_COND(
    (filename=js_cws_get_value_string_utf8(&filenameLen, env, argv, js_cws_instance))==NULL,
    "c_saveToFileJSON",
    "Could not parse filename. Wrong format or empty string or invalid utf-8 or no space in C string buffer",
    165
  )

  JS_CWS_THROW_COND(
    (err=writeToFileJSON(js_cws_instance->config, filename)),
    "writeToFileJSON", "Could not save JSON file @ writeToFileJSON",
    err
  )

  JS_CWS_RETURN_UNDEFINED
}

napi_value c_getInstanceName(napi_env env, napi_callback_info info)
{
  napi_value argv=NULL, res;
  size_t argc=0;
  struct js_cws_config_t *js_cws_instance;
  struct cws_js_err_t cws_js_err;

  JS_CWS_THROW_COND(
    napi_get_cb_info(env, info, &argc, &argv, NULL, (void **)&js_cws_instance)!=napi_ok,
    "napi_get_cb_info",
    "Can't parse arguments. Wrong argument at c_getInstanceName",
    130
  )

  JS_CWS_THROW_COND(argc, "c_getInstanceName", "Too many arguments @ getInstanceName", 131)

  JS_CWS_THROW_COND(
    (js_cws_instance==NULL),
    "c_getInstanceName",
    "Fatal: js_cws_instance @ c_getInstanceName. Was expected NOT NULL",
    132
  )

  JS_CWS_THROW_COND(
    (napi_create_string_utf8(env, JS_GET_INSTANCE_NAME, NAPI_AUTO_LENGTH, &res)!=napi_ok),
    "napi_create_string_utf8",
    "napi_create_string_utf8 @ c_getInstanceName. Error on parsing instance name",
    133
  )

  return res;
}

napi_value c_getObjectName(napi_env env, napi_callback_info info)
{
  napi_value argv=NULL, res;
  size_t argc=0;
  struct js_cws_config_t *js_cws_instance;
  struct cws_js_err_t cws_js_err;

  JS_CWS_THROW_COND(
    napi_get_cb_info(env, info, &argc, &argv, NULL, (void **)&js_cws_instance)!=napi_ok,
    "napi_get_cb_info",
    "Can't parse arguments. Wrong argument at c_getObjectName",
    40
  )

  JS_CWS_THROW_COND(argc, "c_getObjectName", "Too many arguments @ c_getObjectName", 41)

  JS_CWS_THROW_COND(
    (js_cws_instance==NULL),
    "c_getObjectName",
    "Fatal: js_cws_instance @ c_getObjectName. Was expected NOT NULL",
    42
  )

  CHECK_HAS_ERROR("c_getObjectName", "Could not get object name. Object not parsed or internal error", 43)

  JS_CWS_THROW_COND(
    (napi_create_string_utf8(env, JS_GET_OBJECT_NAME, NAPI_AUTO_LENGTH, &res)!=napi_ok),
    "napi_create_string_utf8",
    "napi_create_string_utf8 @ c_getObjectName. Error on get object name",
    44
  )

  return res;
}

napi_value c_getError(napi_env env, napi_callback_info info)
{
  int err;
  napi_value argv=NULL, res;
  size_t argc=0;
  struct js_cws_config_t *js_cws_instance;
  struct cws_js_err_t cws_js_err;

  JS_CWS_THROW_COND(
    napi_get_cb_info(env, info, &argc, &argv, NULL, (void **)&js_cws_instance)!=napi_ok,
    "napi_get_cb_info",
    "Can't parse arguments. Wrong argument at c_getError",
    55
  )

  JS_CWS_THROW_COND(argc, "c_getError", "Too many arguments @ c_getError", 56)

  JS_CWS_THROW_COND(
    (js_cws_instance==NULL),
    "c_getError",
    "Fatal: js_cws_instance @ c_getError. Was expected NOT NULL",
    57
  )

  if (JS_GET_INTERNAL_SOAP_ERROR)
    err=JS_GET_INTERNAL_SOAP_ERROR;
  else if (ERR)
    err=ERR;
  else if (JS_GET_BASEMSG_CODE<0)
    err=JS_GET_BASEMSG_CODE;
  else
    err=0;

  JS_CWS_THROW_COND(
    (napi_create_int32(env, (int32_t)err, &res)!=napi_ok),
    "napi_create_int32",
    "napi_create_int32 @ c_getError. Unable to get Witsml 2.1 parser error",
    58
  )

  return res;
}

napi_value c_getBsonBytes(napi_env env, napi_callback_info info)
{
  napi_value argv=NULL, res;
  size_t argc=0;
  struct js_cws_config_t *js_cws_instance;
  struct cws_js_err_t cws_js_err;
  struct c_bson_serialized_t *bson_ser;

  JS_CWS_THROW_COND(
    napi_get_cb_info(env, info, &argc, &argv, NULL, (void **)&js_cws_instance)!=napi_ok,
    "napi_get_cb_info",
    "Can't parse arguments. Wrong argument at c_getBsonBytes",
    70
  )

  JS_CWS_THROW_COND(argc, "c_getBsonBytes", "Too many arguments @ c_getBsonBytes", 71)

  JS_CWS_THROW_COND(
    (js_cws_instance==NULL),
    "c_getBsonBytes",
    "Fatal: js_cws_instance @ c_getBsonBytes. Was expected NOT NULL",
    72
  )

  CHECK_HAS_ERROR("c_getBsonBytes", "Could not get BSON serialized. Object not parsed or internal error", 73)

  JS_CWS_THROW_COND(
    (bson_ser=bsonSerialize(js_cws_instance->config))==NULL,
    "bsonSerialize",
    "bsonSerialize @ c_getBsonBytes. Unable to load parsed BSON binary data",
    74
  )

  JS_CWS_THROW_COND(
    js_cws_new_array_buffer(&res, env, (void *)bson_ser->bson, bson_ser->bson_size),
    "napi_create_int32",
    "napi_create_int32 @ c_getBsonBytes. Unable to copy BSON to JavaScript ArrayBuffer",
    75
  )

  return res;
}

napi_value c_getJson(napi_env env, napi_callback_info info)
{
  napi_value argv=NULL, res;
  size_t argc=0;
  struct js_cws_config_t *js_cws_instance;
  struct cws_js_err_t cws_js_err;
  struct c_json_str_t *c_json;

  JS_CWS_THROW_COND(
    napi_get_cb_info(env, info, &argc, &argv, NULL, (void **)&js_cws_instance)!=napi_ok,
    "napi_get_cb_info",
    "Can't parse arguments. Wrong argument at c_getJson",
    80
  )

  JS_CWS_THROW_COND(argc, "c_getJson", "Too many arguments @ c_getJson", 81)

  JS_CWS_THROW_COND(
    (js_cws_instance==NULL),
    "c_getJson",
    "Fatal: js_cws_instance @ c_getJson. Was expected NOT NULL",
    82
  )

  CHECK_HAS_ERROR("c_getJson", "Could not get JSON string. Object not parsed or internal error", 83)

  JS_CWS_THROW_COND(
    (c_json=getJson(js_cws_instance->config))==NULL,
    "getJson",
    "getJson @ c_getJson. Unable to load parsed JSON string",
    84
  )

  JS_CWS_THROW_COND(
    (napi_create_string_utf8(env, c_json->json, c_json->json_len, &res)!=napi_ok),
    "napi_create_int32",
    "napi_create_int32 @ c_getJson. Unable to copy JSON string",
    85
  )

  return res;
}

napi_value c_getFaultString(napi_env env, napi_callback_info info)
{
  napi_value argv=NULL, res;
  size_t argc=0;
  struct js_cws_config_t *js_cws_instance;
  struct cws_js_err_t cws_js_err;

  JS_CWS_THROW_COND(
    napi_get_cb_info(env, info, &argc, &argv, NULL, (void **)&js_cws_instance)!=napi_ok,
    "napi_get_cb_info",
    "Can't parse arguments. Wrong argument at c_getFaultString",
    200
  )

  JS_CWS_THROW_COND(argc, "c_getFaultString", "Too many arguments @ c_getFaultString", 201)

  JS_CWS_THROW_COND(
    (js_cws_instance==NULL),
    "c_getFaultString",
    "Fatal: js_cws_instance @ c_getFaultString. Was expected NOT NULL",
    202
  )

  if (JS_GET_FAULT_STRING) {
    JS_CWS_THROW_COND(
      (napi_create_string_utf8(env, JS_GET_FAULT_STRING, JS_GET_FAULT_STRING_LEN, &res)!=napi_ok),
      "napi_create_string_utf8",
      "napi_create_string_utf8 @ c_getFaultString. Error on parsing fault string message",
      203
    )

    return res;
  }

  JS_CWS_RETURN_NULL
}

napi_value c_getXMLfaultdetail(napi_env env, napi_callback_info info)
{
  napi_value argv=NULL, res;
  size_t argc=0;
  struct js_cws_config_t *js_cws_instance;
  struct cws_js_err_t cws_js_err;

  JS_CWS_THROW_COND(
    napi_get_cb_info(env, info, &argc, &argv, NULL, (void **)&js_cws_instance)!=napi_ok,
    "napi_get_cb_info",
    "Can't parse arguments. Wrong argument at c_getXMLfaultdetail",
    210
  )

  JS_CWS_THROW_COND(argc, "c_getXMLfaultdetail", "Too many arguments @ c_getXMLfaultdetail", 211)

  JS_CWS_THROW_COND(
    (js_cws_instance==NULL),
    "c_getXMLfaultdetail",
    "Fatal: js_cws_instance @ c_getXMLfaultdetail. Was expected NOT NULL",
    212
  )

  if (JS_GET_XML_FAULT_DETAIL) {
    JS_CWS_THROW_COND(
      (napi_create_string_utf8(env, JS_GET_XML_FAULT_DETAIL, JS_GET_XML_FAULT_DETAIL_LEN, &res)!=napi_ok),
      "napi_create_string_utf8",
      "napi_create_string_utf8 @ c_getXMLfaultdetail. Error on parsing XML fault detail string message",
      213
    )

    return res;
  }

  JS_CWS_RETURN_NULL
}

napi_value c_getBaseMsgCode(napi_env env, napi_callback_info info)
{
  int code, err;
  char *baseMsg, *errMsg;
  int baseMsgLen;
  napi_value argv=NULL, res;
  size_t argc=0;
  struct js_cws_config_t *js_cws_instance;
  struct cws_js_err_t cws_js_err;

  JS_CWS_THROW_COND(
    napi_get_cb_info(env, info, &argc, &argv, NULL, (void **)&js_cws_instance)!=napi_ok,
    "napi_get_cb_info",
    "Can't parse arguments. Wrong argument at c_getBaseMsgCode",
    310
  )

  JS_CWS_THROW_COND(argc, "c_getBaseMsgCode", "Too many arguments @ c_getBaseMsgCode", 311)

  JS_CWS_THROW_COND(
    (js_cws_instance==NULL),
    "c_getBaseMsgCode",
    "Fatal: js_cws_instance @ c_getBaseMsgCode. Was expected NOT NULL",
    312
  )

  if (JS_GET_INTERNAL_SOAP_ERROR==0) {
    if ((code=js_cws_instance->config->base_msg.code)) {
      baseMsg=(char *)js_cws_instance->config->base_msg.message;
      baseMsgLen=js_cws_instance->config->base_msg.message_len;

c_getBaseMsgCode_ret:
      JS_CWS_THROW_COND((err=js_base_msg_util(env, &res, (int32_t)code, baseMsg, (size_t)baseMsgLen, &errMsg)),
        "js_base_msg_util",
        errMsg,
        err
      )

      return res;

    } else if ((ERR==0)&&(JS_GET_OBJECT_NAME!=NULL)) {
      code=1;
#define SUCCESS_MSG "Success"
      baseMsg=SUCCESS_MSG;
      baseMsgLen=(int)(sizeof(SUCCESS_MSG)-1);
#undef SUCCESS_MSG
      goto c_getBaseMsgCode_ret;
    }
  }

  JS_CWS_THROW(
    "c_getBaseMsgCode", "Could not get object name. Object not parsed or internal error",
    -318
  )
}

napi_value c_getBaseMessage(napi_env env, napi_callback_info info)
{
  napi_value argv=NULL, res;
  int err;
  int32_t code;
  size_t argc=1;
  struct cws_js_err_t cws_js_err;
  struct cws_base_msg_t *cws_has_base_msg;
  char *errMsg;

  JS_CWS_THROW_COND(
    napi_get_cb_info(env, info, &argc, &argv, NULL, NULL)!=napi_ok,
    "napi_get_cb_info",
    "Can't parse arguments. Wrong argument at c_getBaseMessage",
    810
  )

  JS_CWS_THROW_COND(argc>1, "c_getBaseMessage", "Too many arguments @ c_getBaseMessage", 811)

  JS_CWS_THROW_COND(argc==0, "c_getBaseMessage", "Was expected: code", 812)

  JS_CWS_THROW_COND(
    (napi_get_value_int32(env, argv, &code)!=napi_ok),
     "c_getBaseMessage",
     "Fatal: napi_get_value_int32 @ c_getBaseMessage. Could not get baseMsg code. Was expected an integer value",
     814
  )

  if ((cws_has_base_msg=cws_has_base_msg14x((short)code))) {

    JS_CWS_THROW_COND(
      (err=js_base_msg_util(env, &res, (int32_t)code, (char *)cws_has_base_msg->message, (size_t)cws_has_base_msg->message_len, &errMsg)),
      "c_getBaseMessage",
      errMsg,
      err
    )

    return res;
  }

  JS_CWS_RETURN_NULL
}

//
napi_value c_getBaseMessageList14x(napi_env env, napi_callback_info info)
{
  napi_value argv=NULL, obj, res;
  int err;
  int32_t index;
  size_t argc=0;
  struct cws_js_err_t cws_js_err;
  struct cws_base_msg_t *list;
  char *errMsg;

  JS_CWS_THROW_COND(
    napi_get_cb_info(env, info, &argc, &argv, NULL, NULL)!=napi_ok,
    "napi_get_cb_info",
    "Can't parse arguments. Wrong argument at c_getBaseMessageList14x",
    610
  )

  JS_CWS_THROW_COND(argc!=0, "c_getBaseMessageList14x", "Too many argumenys", 612)

  JS_CWS_THROW_COND(napi_create_array(env, &res)!=napi_ok,
    "c_getBaseMessageList14x",
    "Could not create JavaScript array",
    613
  )

  index=0;
  list=get_base_msg_list();

  while (list->message) {
    JS_CWS_THROW_COND(
      (err=js_base_msg_util(env, &obj, (int32_t)list->code, (char *)list->message, (size_t)list->message_len, &errMsg)),
      "c_getBaseMessageList14x",
      errMsg,
      err
    )

    JS_CWS_THROW_COND(
      napi_set_element(env, res, index++, obj)!=napi_ok,
      "c_getBaseMessageList14x",
      "Unable to add object to JavaScript array",
      614
    )

    list++;
  }

  return res;
}
//
CWS_JS_FUNCTIONS_OBJ CWS_JS_CREATE_FUNCTIONS[] = {
  SET_JS_FN_CALL(getInstanceName),
  SET_JS_FN_CALL(getObjectName),
  SET_JS_FN_CALL(getBsonBytes),
  SET_JS_FN_CALL(getJson),
/* #ifdef WITH_STATISTICS
  SET_JS_FN_CALL(getStatistics),
#endif */
  SET_JS_FN_CALL(getBaseMsgCode),
  SET_JS_FN_CALL(getFaultString),
  SET_JS_FN_CALL(getXMLfaultdetail),
  SET_JS_FN_CALL(getError),
  SET_JS_FN_CALL(parse),
  SET_JS_FN_CALL(parseToJSON),
  SET_JS_FN_CALL(parseFromFile),
  SET_JS_FN_CALL(parseFromFileJSON),
  SET_JS_FN_CALL(saveToFile),
  SET_JS_FN_CALL(saveToFileJSON),
  {NULL}
};


const char *js_cws_check_action(int32_t rule)
{
  struct cws_js_int32_t *c=RULES_TYPE;

  while ((c->value!=(int)rule)&&(c->name!=NULL))
    c++;

  return c->name;
}

napi_value c_create(napi_env env, napi_callback_info info)
{
  int err;
  int32_t rule=ACTION_READ_141X;
  bool versionCheckDisable=false;
  char msg[128];
  const char *act;
  napi_value constructor, argv[2]={NULL}, res;
  size_t argc=2;
  struct js_cws_config_t *js_cws_instance;
  struct cws_js_err_t cws_js_err;

  JS_CWS_THROW_COND(
    napi_get_cb_info(env, info, &argc, &argv[0], NULL, NULL)!=napi_ok,
    "napi_get_cb_info",
    "Can't parse arguments. Wrong argument at create",
    98
  )

  JS_CWS_THROW_COND(argc>2, "c_create", "Too many arguments", 98)

  JS_CWS_THROW_COND(argc==1, "c_create", "Expected rule => (default = ACTION_READ_141X) and version check disable => (default = false)", 99)

  JS_CWS_THROW_COND(
    napi_create_function(env, NULL, 0, c__witsml14xbsonInit_, NULL, &constructor)!=napi_ok,
    "napi_create_function",
    "Error on generating c__witsml14xbsonInit_",
    100
  )

  if (argc) {
    JS_CWS_THROW_COND(
      napi_get_value_int32(env, argv[0], &rule)!=napi_ok,
      "napi_get_value_int32",
      "Error on parsing int 32 value for rule",
      97
    )

    JS_CWS_THROW_COND(
      (act=js_cws_check_action(rule))==NULL,
      "js_cws_check_action",
      "Invalid rule.",
      96
    )

    if ((void *)act!=(void *)RULES_TYPE[0].name) {
      snprintf(msg, sizeof(msg), "Rule: %s not implemented yet", act);
      JS_CWS_THROW("c_create", msg, 99)
    }

    JS_CWS_THROW_COND(
      napi_get_value_bool(env, argv[1], &versionCheckDisable)!=napi_ok,
      "napi_get_value_bool",
      "Error on parsing boolean value for version check disable",
      95
    )
  }

  if (napi_new_instance(env, constructor, 0, NULL, &res)==napi_ok) {

    JS_CWS_THROW_COND(
      (js_cws_instance=js_cws_config_init(rule, versionCheckDisable))==NULL,
      "js_cws_config_init", "Could not alloc JSWITSML 1.4.x.x - 1.3.x.x C instance",
      101
   )

    if ((err=cws_add_function_util(env, res, CWS_JS_CREATE_FUNCTIONS, js_cws_instance))) {
      js_cws_config_free(&js_cws_instance);

      JS_CWS_THROW("cws_add_function_util", "Could add functions @ c_create constructor", err)
    }

    if (napi_add_finalizer(env, res, (void *)js_cws_instance, cws_js_finalize, NULL, NULL)!=napi_ok) {
      js_cws_config_free(&js_cws_instance);

      JS_CWS_THROW("napi_add_finalizer", "Could not add finalizer callback", 103)
    }

    return res;
  }

  JS_CWS_THROW("c_create", "Could not create new instance", 104)
}

CWS_JS_FUNCTIONS_OBJ CWS_JS_INIT_FUNCTIONS[] = {
  SET_JS_FN_CALL(create),
  SET_JS_FN_CALL(getBsonVersion),
  SET_JS_FN_CALL(getBaseMessage),
  SET_JS_FN_CALL(getBaseMessageList14x),
  {NULL}
};

napi_value Init(napi_env env, napi_value exports)
{

  int err;
  struct cws_js_err_t cws_js_err;

  JS_CWS_THROW_COND(
    (err=cws_add_function_util(env, exports, CWS_JS_INIT_FUNCTIONS, NULL)),
    "cws_add_function_util",
    "Could not initialize C functions",
    err
  )

  JS_CWS_THROW_COND(
    (err=cws_add_int32_object_list_util(NULL, "WITSML_RULES_TYPES", env, exports, RULES_TYPE)),
    "cws_add_int32_object_list_util",
    "Could not initialize C WITSML 1.4.x.x | 1.3.x.x const object",
    err
  )

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)

/////////////////////////////////////////////////////// C Witsml Parser ///////////////////////////////////////////////////////

CWS_BUILDER_14X_13X

