//sáb 04 mai 2024 19:42:22 

#include <cws_soap.h>
#include <cws_utils.h>
#include <base_msgs.h>

#include <stdio.h>

#include <jni.h>

#define HAS_ERROR (config->internal_soap_error!=0)||(config->base_msg.code < 0)||(config->object==NULL)
#define TREE_MAP_CLASS "Ljava/util/TreeMap;"
#define INTEGER_CLASS "Ljava/lang/Integer;"
#define JNI_EXCEPTION_CLASS "java/lang/Exception"
#define WITSML_CLASS_EXCEPTION "org/jwitsmlparser14x/exception/JWitsmlException"
#define WITSML_CLASS "org/jwitsmlparser14x/JWitsmlParserLoader"
#define throwCWitsmlException(msg) cWitsmlParserException(env, JNI_EXCEPTION_CLASS, msg, 0, NULL, NULL, NULL, 0, NULL)
#define throwCWitsmlError(msg) cWitsmlParserException(env, JNI_EXCEPTION_CLASS, msg, 0, NULL, NULL, c_soap_internal_instance_name, 0, NULL)
#define JNI_INIT_THROWABLE_WITH_CODE(class) \
  (*env)->GetMethodID(env, class, "<init>", "(Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;)V")

CWS_CONFIG *code=(void *)0;

// CODE crc32 algorithm extracted from https://opensource.apple.com/source/xnu/xnu-1456.1.26/bsd/libkern/crc32.c
static uint32_t crc32_tab[] = {
	0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f,
	0xe963a535, 0x9e6495a3,	0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988,
	0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91, 0x1db71064, 0x6ab020f2,
	0xf3b97148, 0x84be41de,	0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
	0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec,	0x14015c4f, 0x63066cd9,
	0xfa0f3d63, 0x8d080df5,	0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172,
	0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,	0x35b5a8fa, 0x42b2986c,
	0xdbbbc9d6, 0xacbcf940,	0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
	0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423,
	0xcfba9599, 0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
	0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,	0x76dc4190, 0x01db7106,
	0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
	0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d,
	0x91646c97, 0xe6635c01, 0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e,
	0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
	0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
	0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7,
	0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0,
	0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa,
	0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
	0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81,
	0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a,
	0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683, 0xe3630b12, 0x94643b84,
	0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
	0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
	0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc,
	0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5, 0xd6d6a3e8, 0xa1d1937e,
	0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
	0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55,
	0x316e8eef, 0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
	0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe, 0xb2bd0b28,
	0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
	0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f,
	0x72076785, 0x05005713, 0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38,
	0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
	0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
	0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69,
	0x616bffd3, 0x166ccf45, 0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2,
	0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc,
	0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
	0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693,
	0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94,
	0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d
};

uint32_t crc32(uint32_t crc, const void *buf, size_t size)
{
  const uint8_t *p;
  p = buf;
  crc = crc ^ ~0U;

  while (size--)
    crc = crc32_tab[(crc ^ *p++) & 0xFF] ^ (crc >> 8);

  return crc ^ ~0U;
}

// END

struct c_handler_t {
  CWS_CONFIG *cfg_encoded;
  uint32_t crc32;
  uint32_t initial;
};

_Static_assert(sizeof(struct c_handler_t)==16, "c_handler_t align error");

jint cWitsmlParserException(
  JNIEnv *env,
  const char *class,
  const char *message,
  int cwitsmlError,
  const char *faultstring,
  const char *XMLfaultdetail,
  const char *c_soap_internal_instance_name,
  int baseMsgCode,
  const char *baseMsg
)
{
  jint err;
  jclass exClass;
  jmethodID methodId;
  jobject jErrObj;
  jstring
    errMsg, jFaultString, jXMLfaultdetail, jSoapInternalInstanceName, jBaseMsg;
  const char *err_msg;

  if (!(exClass=(*env)->FindClass(env, class))) {
    if ((void *)class==(void *)JNI_EXCEPTION_CLASS)
      return 1; // PANIC (It should never happen)

    if (!(exClass=(*env)->FindClass(env, JNI_EXCEPTION_CLASS)))
      return 2; // PANIC (It should never happen)

    err_msg="cWitsmlParserException: Class not found WITSML_CLASS_EXCEPTION = \""WITSML_CLASS_EXCEPTION"\"";

  } else if (cwitsmlError) {

    if (baseMsgCode < 0)
      cwitsmlError=0;

    err_msg=(message)?message:"cWitsmlParserException: CWitsml Soap Internal error or WITSML error. Please, see faultstring or XMLfaultdetail for details";

    if (!(errMsg=(*env)->NewStringUTF(env, err_msg))) {
      throwCWitsmlError("cWitsmlParserException: Cannot set message error 3");
      return 3;
    }

    if (!(jFaultString=(*env)->NewStringUTF(env, (faultstring)?faultstring:""))) {
      err=4;
      throwCWitsmlError("cWitsmlParserException: Cannot set faultstring error 4");
      goto cWitsmlParserException_EXIT1;
    }

    if (!(jXMLfaultdetail=(*env)->NewStringUTF(env, (XMLfaultdetail)?XMLfaultdetail:""))) {
      err=5;
      throwCWitsmlError("cWitsmlParserException: Cannot set XMLfaultdetail error 5");
      goto cWitsmlParserException_EXIT2;
    }

    if (!(jSoapInternalInstanceName=(*env)->NewStringUTF(env, (c_soap_internal_instance_name)?c_soap_internal_instance_name:""))) {
      err=6;
      throwCWitsmlError("cWitsmlParserException: Cannot set soapInternalInstanceName error 6");
      goto cWitsmlParserException_EXIT3;
    }

    if (!(jBaseMsg=(*env)->NewStringUTF(env, (baseMsg)?baseMsg:""))) {
      err=7;
      throwCWitsmlError("cWitsmlParserException: Cannot set baseMsgError error 7");
      goto cWitsmlParserException_EXIT4;
    }

    if (!(methodId=JNI_INIT_THROWABLE_WITH_CODE(exClass))) {
      err=8;
      throwCWitsmlError("cWitsmlParserException: Cannot initialize throwable class \""WITSML_CLASS_EXCEPTION"\". Error 8");
      goto cWitsmlParserException_EXIT5;
    }

    if (!(jErrObj=(*env)->NewObject(
      env, exClass, methodId, errMsg, (jint)cwitsmlError, jFaultString, jXMLfaultdetail, (jint)baseMsgCode, jBaseMsg, jSoapInternalInstanceName))) {
      err=9;
      throwCWitsmlError("cWitsmlParserException: Cannot create throwable class \""WITSML_CLASS_EXCEPTION"\". Error 9");
      goto cWitsmlParserException_EXIT5;
    } else if ((err=(*env)->Throw(env, jErrObj))) {
      throwCWitsmlError("cWitsmlParserException: Can't throw jErrObj");
      goto cWitsmlParserException_EXIT6;
    }

    return 0;

cWitsmlParserException_EXIT6:
  (*env)->DeleteLocalRef(env, jErrObj);

cWitsmlParserException_EXIT5:
  (*env)->DeleteLocalRef(env, jBaseMsg);

cWitsmlParserException_EXIT4:
  (*env)->DeleteLocalRef(env, jSoapInternalInstanceName);

cWitsmlParserException_EXIT3:
  (*env)->DeleteLocalRef(env, jXMLfaultdetail);

cWitsmlParserException_EXIT2:
  (*env)->DeleteLocalRef(env, jFaultString);

cWitsmlParserException_EXIT1:
  (*env)->DeleteLocalRef(env, errMsg); // NEVER will be NULL

   return err;
  } else
    err_msg=message;

  return (*env)->ThrowNew(env, exClass, err_msg);
}



/* Header for class org_jwitsmlparser14x_JWitsmlParserLoader */

//Utilities

static int read_random(uint8_t *rnd, size_t rnd_sz)
{
  int fd=open("/dev/urandom", O_RDONLY), err;

  err=(((size_t)(read(fd, (void *)rnd, rnd_sz)))!=rnd_sz);

  close(fd);
  return err;
}
//uint32_t crc32(uint32_t crc, const void *buf, size_t size)
static struct c_handler_t *encodeHandler(struct c_handler_t *handler)
{
  if (!read_random((uint8_t *)&handler->initial, sizeof(handler->initial))) {
    handler->crc32=crc32(handler->initial, (const void *)&handler->cfg_encoded, sizeof(handler->cfg_encoded));
_Static_assert(sizeof(size_t)==sizeof(CWS_CONFIG *), "Invalid CWS_CONFIG * size");
    handler->cfg_encoded=(CWS_CONFIG *)(((size_t)code)^((size_t)handler->cfg_encoded));
    return handler;
  }

  return NULL;
}

static CWS_CONFIG *decodeHandler(CWS_CONFIG **cfg, struct c_handler_t *handler)
{
  if ((handler->initial!=0)&&(code!=NULL)) {
    *cfg=(CWS_CONFIG *)(((size_t)handler->cfg_encoded)^((size_t)code));

    if (crc32(handler->initial, (const void *)cfg, sizeof(*cfg))==handler->crc32)
      return *cfg;
  }

  return NULL;
}

static jbyteArray cNewByteArray(
  JNIEnv *env,
  uint8_t *buf,
  size_t buf_sz,
  const char *fnName
)
{
  char msg[256];
  jbyteArray arr=(*env)->NewByteArray(env, (jsize)buf_sz);

  if (!arr) {
    if (fnName) {
      snprintf(msg, sizeof(msg), "%s: Could not create byte array in object", fnName);
      throwCWitsmlException(msg);
    }
    return NULL;
  }

  (*env)->SetByteArrayRegion(env, arr, 0, (jsize)buf_sz, (const jbyte *)buf);

  if (!(*env)->ExceptionCheck(env))
    return arr;

  (*env)->DeleteLocalRef(env, arr);

  if (fnName) {
    snprintf(msg, sizeof(msg), "%s: Could not copy Binary data to object", fnName);
    throwCWitsmlException(msg);
  }

  return NULL;
}

static int cGetObjectField
(
  JNIEnv *env,
  void **result,
  jclass *classResult,
  jfieldID *fieldIdResult,
  jobject object,
  const char *className,
  const char *field,
  const char *fieldSig,
  const char *fName
)
{
  char msg[512];
  jclass classTmp, *p_classTmp;
  jfieldID jfieldIdTmp, *p_jfieldIdTmp;

  *result=NULL;

  if (classResult)
    p_classTmp=classResult;
  else
    p_classTmp=&classTmp;

  if (fieldIdResult)
    p_jfieldIdTmp=fieldIdResult;
  else
    p_jfieldIdTmp=&jfieldIdTmp;

  (*p_classTmp)=(*env)->FindClass(env, className);
  if (!(*p_classTmp)) {
    if (fName) {
      snprintf(msg, sizeof(msg), "%s: Could not find class \"%s\"", fName, className);
      throwCWitsmlException(msg);
    }
    return -1;
  }

  (*p_jfieldIdTmp)=(*env)->GetFieldID(env, *p_classTmp, field, fieldSig);
  if (!(*p_jfieldIdTmp)) {
    (*p_classTmp)=NULL;
    if (fName) {
      snprintf(msg, sizeof(msg), "%s: Could not find field \"%s\" with signature \"%s\"", fName, field, fieldSig);
      throwCWitsmlException(msg);
    }
    return -2;
  }

  *result=(void *)(*env)->GetObjectField(env, object, *p_jfieldIdTmp);
  if (!(*env)->ExceptionCheck(env))
    return 0;

  (*p_jfieldIdTmp)=NULL;
  (*p_classTmp)=NULL;

  if (fName) {
    snprintf(msg, sizeof(msg), "%s: Could not get field \"%s\" with sig \"%s\" in object pointer %p", fName, field, fieldSig, (void *)object);
    throwCWitsmlException(msg);
  }

  return -3;
}

#define STR(s) (const char *)#s
#define ACTION_READ_141X_STR STR(ACTION_READ_141X)
#define ACTION_WRITE_141X_STR STR(ACTION_WRITE_141X)
#define ACTION_UPDATE_141X_STR STR(ACTION_UPDATE_141X)
#define ACTION_DELETE_141X_STR STR(ACTION_DELETE_141X)
#define ACTION_UNKNOWN "Unknown_ACTION"

const char *check_rules(int rule) {
  switch (rule) {
    case ACTION_READ_141X:
      return ACTION_READ_141X_STR;
    case ACTION_WRITE_141X:
      return ACTION_WRITE_141X_STR;
    case ACTION_UPDATE_141X:
      return ACTION_UPDATE_141X_STR;
    case ACTION_DELETE_141X:
      return ACTION_DELETE_141X_STR;
    default:
      return ACTION_UNKNOWN;
  }
}

static int cGetCWS_CONFIG(
  CWS_CONFIG **config,
  JNIEnv *env,
  jobject thisObject,
  const char *fName
)
{
  struct c_handler_t *c_handler_p;
  void *jHandler;
  jfieldID fieldID;
  char msg[256];

  *config=NULL;
  if (cGetObjectField(env, &jHandler, NULL, &fieldID, thisObject, WITSML_CLASS, "handler", "[B", NULL)) {
    if (fName) {
      snprintf(msg, sizeof(msg), "%s: Could not get config from WITSML class instance", fName);
      throwCWitsmlException(msg);
    }
    return -1;
  }

  if (jHandler==NULL) {
    if (fName) {
      snprintf(msg, sizeof(msg), "%s: Instance not initialized", fName);
      throwCWitsmlException(msg);
    }
    return -2;
  }

  if (((size_t)(*env)->GetArrayLength(env, (jbyteArray)jHandler))!=sizeof(*c_handler_p)) {
    if (fName) {
      snprintf(msg, sizeof(msg), "%s: Wrong Java byte array size. Could not get CWS_CONFIG", fName);
      throwCWitsmlException(msg);
    }
    return -3;
  }

  if (!(c_handler_p=(struct c_handler_t *)(*env)->GetByteArrayElements(env, (jbyteArray)jHandler, NULL))) {
    if (fName) {
      snprintf(msg, sizeof(msg), "%s: Could not get byte array elements. Could not get CWS_CONFIG", fName);
      throwCWitsmlException(msg);
    }
    return -4;
  }

  if (!decodeHandler(config, c_handler_p)) {
    if (fName) {
      snprintf(msg, sizeof(msg), "%s: Invalid C handler pointer", fName);
      throwCWitsmlException(msg);
    }
    (*env)->ReleaseByteArrayElements(env, (jbyteArray)jHandler, (jbyte *)c_handler_p, JNI_ABORT);
    return -5;
  }

  (*env)->ReleaseByteArrayElements(env, (jbyteArray)jHandler, (jbyte *)c_handler_p, JNI_ABORT);

  if (*config)
    return 0;

  if (fName) {
    snprintf(msg, sizeof(msg), "%s: CWS_CONFIG pointer not initialized", fName);
    throwCWitsmlException(msg);
  }

  return -6;
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

//End Utilities

JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *vm, void *reserved)
{
  if (read_random((void *)&code, sizeof(code)))
    return -1;

  return JNI_VERSION_1_8;
}

JNIEXPORT void JNICALL
JNI_OnUnload(JavaVM *vm, void *reserved)
{
// DO NOTHING
}

/*
 * Class:     org_jwitsmlparser14x_JWitsmlParserLoader
 * Method:    init
 * Signature: (IZ)V
 */
JNIEXPORT void JNICALL Java_org_jwitsmlparser14x_JWitsmlParserLoader_init
(
  JNIEnv *env,
  jobject thisObject,
  jint rule,
  jboolean versionCheckDisable
)
{
  struct c_handler_t c_handler;
  CWS_CONFIG *cfg;
  jfieldID fieldID;
  void *jHandler;
  const char *rule_str;
  char msg[128];

  if ((void *)(rule_str=check_rules((int)rule))==(void *)ACTION_UNKNOWN) {
    throwCWitsmlException("init: Unknown action");
    return;
  }

  if ((void *)rule_str!=(void *)ACTION_READ_141X_STR) {
    snprintf(msg, sizeof(msg), "init: Rule %s not implemented yet", rule_str);
    throwCWitsmlException(msg);
    return;
  }

  if (cGetObjectField(env, (void **)&jHandler, NULL, &fieldID, thisObject, WITSML_CLASS, "handler", "[B", "init"))
    return;

  if (jHandler) {
    throwCWitsmlException("init: Instance is already in use");
    return;
  }

  if (!(cfg=cws_config_new(
    "JWITSML 1.3.X - 1.4.X BSON parser", NULL, CWS_FLAG_RECYCLABLE|((versionCheckDisable)?CWS_FLAG_CHECK_VERSION_DISABLE:0), rule
  ))) {
    throwCWitsmlException("init: Could not initialize JWITSML 1.3.X - 1.4.X BSON parser");
    return;
  }

  c_handler.cfg_encoded=cfg;
  if (!encodeHandler(&c_handler)) {
    cws_config_free(&cfg);
    throwCWitsmlException("init: Could not encode JWITSML 1.3.X - 1.4.X BSON parser C pointer");
    return;
  }

  if (!(jHandler=(void *)cNewByteArray(env, (uint8_t *)&c_handler, sizeof(c_handler), NULL))) {
    cws_config_free(&cfg);
    throwCWitsmlException("init: Could not move C WITSML config pointer to Java byte array");
    return;
  }

  (*env)->SetObjectField(env, thisObject, fieldID, (jobject)jHandler);

  if (!(*env)->ExceptionCheck(env))
    return;

  (*env)->DeleteLocalRef(env, (jobject)jHandler);
  cws_config_free(&cfg);
  throwCWitsmlException("init: Could not parse Java byte array handler to JWitsmlParserLoader() instance");
}

/*
 * Class:     org_jwitsmlparser14x_JWitsmlParserLoader
 * Method:    parser
 * Signature: (ILjava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_jwitsmlparser14x_JWitsmlParserLoader_parser
(
  JNIEnv *env,
  jobject thisObject,
  jstring xml
)
{
  int err;
  const char *c_xml;
  char *errMsg, msg[256];
  CWS_CONFIG *config;
  struct c_bson_serialized_t *bson_ser;
  jsize c_xml_len;
  jbyteArray res;

  if (!xml) {
    throwCWitsmlException("parser: null xml string");
    return NULL;
  }

  c_xml_len=(*env)->GetStringUTFLength(env, xml);

  if (c_xml_len < 1) {
    throwCWitsmlException("parser: empty xml string");
    return NULL;
  }

  if (!(c_xml=(*env)->GetStringUTFChars(env, xml, NULL))) {
    throwCWitsmlException("parser: Cannot parse xml utf8 to C char");
    return NULL;
  }

  res=NULL;
  if (cGetCWS_CONFIG(&config, env, thisObject, "parser"))
    goto Java_org_jwitsmlparser14x_JWitsmlParserLoader_parser_EXIT1;

  if ((err=c_parse_util(config, (void **)&bson_ser, c_xml, (size_t)c_xml_len, IS_BSON, &errMsg, -1))) {
    snprintf(msg, sizeof(msg), "parser: %s", errMsg);
    cWitsmlParserException(
      env, WITSML_CLASS_EXCEPTION,
      (const char *)msg, err,
      (const char *)config->cws_soap_fault.faultstring,
      (const char *)config->cws_soap_fault.XMLfaultdetail,
      (const char *)config->instance_name,
      (int)config->base_msg.code,
      config->base_msg.message
    );
    goto Java_org_jwitsmlparser14x_JWitsmlParserLoader_parser_EXIT1;
  }

  res=cNewByteArray(env, bson_ser->bson, bson_ser->bson_size, "parser");

Java_org_jwitsmlparser14x_JWitsmlParserLoader_parser_EXIT1:
  (*env)->ReleaseStringUTFChars(env, xml, c_xml);

  return res;
}

/*
 * Class:     org_jwitsmlparser14x_JWitsmlParserLoader
 * Method:    parserJson
 * Signature: (Ljava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_jwitsmlparser14x_JWitsmlParserLoader_parserJson
(
  JNIEnv *env,
  jobject thisObject,
  jstring xml
)
{
  int err;
  const char *c_xml;
  char *errMsg, msg[256];
  CWS_CONFIG *config;
  struct c_json_str_t *json_ser;
  jsize c_xml_len;
  jbyteArray res;

  if (!xml) {
    throwCWitsmlException("parserJson: null xml string");
    return NULL;
  }

  c_xml_len=(*env)->GetStringUTFLength(env, xml);

  if (c_xml_len < 1) {
    throwCWitsmlException("parserJson: empty xml string");
    return NULL;
  }

  if (!(c_xml=(*env)->GetStringUTFChars(env, xml, NULL))) {
    throwCWitsmlException("parserJson: Cannot parse xml utf8 to C char");
    return NULL;
  }

  res=NULL;
  if (cGetCWS_CONFIG(&config, env, thisObject, "parserJson"))
    goto Java_org_jwitsmlparser14x_JWitsmlParserLoader_parserJson_EXIT1;

  if ((err=c_parse_util(config, (void **)&json_ser, c_xml, (size_t)c_xml_len, IS_JSON, &errMsg, -1))) {
    snprintf(msg, sizeof(msg), "parserJson: %s", errMsg);
    cWitsmlParserException(
      env, WITSML_CLASS_EXCEPTION,
      (const char *)msg, err,
      (const char *)config->cws_soap_fault.faultstring,
      (const char *)config->cws_soap_fault.XMLfaultdetail,
      (const char *)config->instance_name,
      (int)config->base_msg.code,
      config->base_msg.message
    );
    goto Java_org_jwitsmlparser14x_JWitsmlParserLoader_parserJson_EXIT1;
  }

  res=cNewByteArray(env, (uint8_t *)json_ser->json, json_ser->json_len, "parserJson");

Java_org_jwitsmlparser14x_JWitsmlParserLoader_parserJson_EXIT1:
  (*env)->ReleaseStringUTFChars(env, xml, c_xml);

  return res;
}

/*
 * Class:     org_jwitsmlparser14x_JWitsmlParserLoader
 * Method:    parserFromFile
 * Signature: (Ljava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_jwitsmlparser14x_JWitsmlParserLoader_parserFromFile
(
  JNIEnv *env,
  jobject thisObject,
  jstring filename
)
{
  int err;
  const char *c_filename;
  char *errMsg, msg[256];
  CWS_CONFIG *config;
  struct c_bson_serialized_t *bson_ser;
  jsize c_filename_len;
  jbyteArray res;

  if (!filename) {
    throwCWitsmlException("parserFromFile: null filename string");
    return NULL;
  }

  c_filename_len=(*env)->GetStringUTFLength(env, filename);

  if (c_filename_len < 1) {
    throwCWitsmlException("parserFromFile: empty filename string");
    return NULL;
  }

  if (!(c_filename=(*env)->GetStringUTFChars(env, filename, NULL))) {
    throwCWitsmlException("parserFromFile: Cannot parse filename utf8 to C char");
    return NULL;
  }

  res=NULL;
  if (cGetCWS_CONFIG(&config, env, thisObject, "parserFromFile"))
    goto Java_org_jwitsmlparser14x_JWitsmlParserLoader_parserFromFile_EXIT1;

  if ((err=c_parse_util(config, (void **)&bson_ser, c_filename, (size_t)c_filename_len, IS_BSON, &errMsg, 0))) {
    snprintf(msg, sizeof(msg), "parserFromFile: %s", errMsg);
    cWitsmlParserException(
      env, WITSML_CLASS_EXCEPTION,
      (const char *)msg, err,
      (const char *)config->cws_soap_fault.faultstring,
      (const char *)config->cws_soap_fault.XMLfaultdetail,
      (const char *)config->instance_name,
      (int)config->base_msg.code,
      config->base_msg.message
    );
    goto Java_org_jwitsmlparser14x_JWitsmlParserLoader_parserFromFile_EXIT1;
  }

  res=cNewByteArray(env, bson_ser->bson, bson_ser->bson_size, "parserFromFile");

Java_org_jwitsmlparser14x_JWitsmlParserLoader_parserFromFile_EXIT1:
  (*env)->ReleaseStringUTFChars(env, filename, c_filename);

  return res;
}

/*
 * Class:     org_jwitsmlparser14x_JWitsmlParserLoader
 * Method:    parserFromFileJson
 * Signature: (Ljava/lang/String;)[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_jwitsmlparser14x_JWitsmlParserLoader_parserFromFileJson
(
  JNIEnv *env,
  jobject thisObject,
  jstring filename
)
{
  int err;
  const char *c_filename;
  char *errMsg, msg[256];
  CWS_CONFIG *config;
  struct c_json_str_t *json_ser;
  jsize c_filename_len;
  jbyteArray res;

  if (!filename) {
    throwCWitsmlException("parserFromFileJson: null filename string");
    return NULL;
  }

  c_filename_len=(*env)->GetStringUTFLength(env, filename);

  if (c_filename_len < 1) {
    throwCWitsmlException("parserFromFileJson: empty filename string");
    return NULL;
  }

  if (!(c_filename=(*env)->GetStringUTFChars(env, filename, NULL))) {
    throwCWitsmlException("parserFromFileJson: Cannot parse filename utf8 to C char");
    return NULL;
  }

  res=NULL;
  if (cGetCWS_CONFIG(&config, env, thisObject, "parserFromFileJson"))
    goto Java_org_jwitsmlparser14x_JWitsmlParserLoader_parserFromFileJson_EXIT1;

  if ((err=c_parse_util(config, (void **)&json_ser, c_filename, (size_t)c_filename_len, IS_JSON, &errMsg, 0))) {
    snprintf(msg, sizeof(msg), "parserFromFileJson: %s", errMsg);
    cWitsmlParserException(
      env, WITSML_CLASS_EXCEPTION,
      (const char *)msg, err,
      (const char *)config->cws_soap_fault.faultstring,
      (const char *)config->cws_soap_fault.XMLfaultdetail,
      (const char *)config->instance_name,
      (int)config->base_msg.code,
      config->base_msg.message
    );
    goto Java_org_jwitsmlparser14x_JWitsmlParserLoader_parserFromFileJson_EXIT1;
  }

  res=cNewByteArray(env, (uint8_t *)json_ser->json, json_ser->json_len, "parserFromFileJson");

Java_org_jwitsmlparser14x_JWitsmlParserLoader_parserFromFileJson_EXIT1:
  (*env)->ReleaseStringUTFChars(env, filename, c_filename);

  return res;
}

#define WITSML_FILE_SAVER(fnName, c_caller)\
/*\
 * Class:     org_jwitsmlparser14x_JWitsmlParserLoader\
 * Method:    #fnName\
 * Signature: (Ljava/lang/String;)V\
 */\
JNIEXPORT void JNICALL Java_org_jwitsmlparser14x_JWitsmlParserLoader_##fnName\
(\
  JNIEnv *env,\
  jobject thisObject,\
  jstring filename\
)\
{\
  const char *c_filename;\
  CWS_CONFIG *config;\
\
  if (cGetCWS_CONFIG(&config, env, thisObject, #fnName))\
    return;\
\
  if (HAS_ERROR) {\
    throwCWitsmlException(#fnName": WITSML error or object not parsed");\
    return;\
  }\
\
  if (filename) {\
    if (!(c_filename=(*env)->GetStringUTFChars(env, filename, NULL))) {\
      throwCWitsmlException(#fnName": Cannot parse filename utf8 to C char");\
      return;\
    }\
  } else\
    c_filename=NULL;\
\
  if (c_caller(config, c_filename))\
    throwCWitsmlException(#fnName": Could not save BSON file. Check if file exists or I/O error");\
\
  (*env)->ReleaseStringUTFChars(env, filename, c_filename);\
}


WITSML_FILE_SAVER(saveToFile, writeToFile)
WITSML_FILE_SAVER(saveToFileJSON, writeToFileJSON)

/*
 * Class:     org_jwitsmlparser14x_JWitsmlParserLoader
 * Method:    getSerializedBson
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_jwitsmlparser14x_JWitsmlParserLoader_getSerializedBson
(
  JNIEnv *env,
  jobject thisObject
)
{
  CWS_CONFIG *config;
  struct c_bson_serialized_t *c_bson_serialized;

  if (cGetCWS_CONFIG(&config, env, thisObject, "getSerializedBson"))
    return NULL;

  if (HAS_ERROR) {
    throwCWitsmlException("getSerializedBson: WITSML error or object not parsed yet");
    return NULL;
  }

  if (!(c_bson_serialized=bsonSerialize(config))) {
    throwCWitsmlException("getSerializedBson: Could not get BSON serialized");
    return NULL;
  }

  return cNewByteArray(env, c_bson_serialized->bson, c_bson_serialized->bson_size, "getSerializedBson");
}

/*
 * Class:     org_jwitsmlparser14x_JWitsmlParserLoader
 * Method:    getError
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_jwitsmlparser14x_JWitsmlParserLoader_getError
(
  JNIEnv *env,
  jobject thisObject
)
{
  CWS_CONFIG *config;

  if (cGetCWS_CONFIG(&config, env, thisObject, "getError"))
    return 0;

  return (jint)(config->base_msg.code<0)?(config->base_msg.code):(config->internal_soap_error);
}

/*
 * Class:     org_jwitsmlparser14x_JWitsmlParserLoader
 * Method:    getBinaryBsonVersion
 * Signature: ()[B
 */
JNIEXPORT jbyteArray JNICALL Java_org_jwitsmlparser14x_JWitsmlParserLoader_getBinaryBsonVersion(
  JNIEnv *env,
  jobject thisObject
)
{
  struct cws_version_t version;

  cws_version(&version);

  return cNewByteArray(env, version.version, version.versionSize, "getBinaryBsonVersion");
}

/*
 * Class:     org_jwitsmlparser14x_JWitsmlParserLoader
 * Method:    baseMsgList
 * Signature: ()Ljava/util/TreeMap;
 */
JNIEXPORT jobject JNICALL Java_org_jwitsmlparser14x_JWitsmlParserLoader_baseMsgList(
  JNIEnv *env,
  jobject thisObject
)
{
  struct cws_base_msg_t *list;
  jobject
    intObj,
    map;
  jstring j_str;
  jmethodID
    init,
    put,
    integerInit;
//https://stackoverflow.com/questions/4844022/jni-create-hashmap

  jclass
    integerClass,
    mapClass=(*env)->FindClass(env, TREE_MAP_CLASS);

  if(!mapClass) {
    throwCWitsmlException("baseMsgList: Could not get "TREE_MAP_CLASS" class");
    return NULL;
  }

  integerClass=(*env)->FindClass(env, INTEGER_CLASS);
  if (!integerClass) {
    throwCWitsmlException("baseMsgList: Could not get "INTEGER_CLASS" class");
    return NULL;
  }

  integerInit=(*env)->GetMethodID(env, integerClass, "<init>", "(I)V");
  if(!integerInit) {
    throwCWitsmlException("baseMsgList: Could not init "INTEGER_CLASS" class");
    return NULL;
  }

  init=(*env)->GetMethodID(env, mapClass, "<init>", "()V");
  if(!init) {
    throwCWitsmlException("baseMsgList: Could not init "TREE_MAP_CLASS" class");
    return NULL;
  }

  put=(*env)->GetMethodID(env, mapClass, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
  if (!put) {
    throwCWitsmlException("baseMsgList: Could not find \"put\" method in "TREE_MAP_CLASS" class");
    return NULL;
  }

  map=(*env)->NewObject(env, mapClass, init);
  if(!map) {
    throwCWitsmlException("baseMsgList: Could not create "TREE_MAP_CLASS" instance");
    return NULL;
  }

  list=get_base_msg_list();

  while(list->message) {

    intObj=(*env)->NewObject(env, integerClass, integerInit, (jint)list->code);
    if(!intObj) {
      throwCWitsmlException("baseMsgList: Could not create "INTEGER_CLASS" instance");
      (*env)->DeleteLocalRef(env, map);
      return NULL;
    }

    if (!(j_str=(*env)->NewStringUTF(env, list->message))) {
      throwCWitsmlException("baseMsgList: Could not create Java string");
      (*env)->DeleteLocalRef(env, intObj);
      (*env)->DeleteLocalRef(env, map);
      return NULL;
    }

    (*env)->CallObjectMethod(env, map, put, intObj, j_str);

    if ((*env)->ExceptionCheck(env)) {
      (*env)->DeleteLocalRef(env, j_str);
      (*env)->DeleteLocalRef(env, intObj);
      (*env)->DeleteLocalRef(env, map);
      return NULL;
    }

    (*env)->DeleteLocalRef(env, j_str);
    (*env)->DeleteLocalRef(env, intObj);

    list++;
  }

  return map;
}

/*
 * Class:     org_jwitsmlparser14x_JWitsmlParserLoader
 * Method:    close
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_org_jwitsmlparser14x_JWitsmlParserLoader_close
(
  JNIEnv *env,
  jobject thisObject
)
{
  CWS_CONFIG *cfg;
  struct c_handler_t
    *c_handler_p,
    c_handler;
  void *jHandler;
  jfieldID fieldID;
  jboolean isCopy;

  if (cGetObjectField(env, &jHandler, NULL, &fieldID, thisObject, WITSML_CLASS, "handler", "[B", NULL)) {
    throwCWitsmlException("close: Critical. Could not get Java byte array handler. Memory may be leaked");
    return;
  }

  if (jHandler==NULL) {
    throwCWitsmlException("close: Instance not initialized");
    return;
  }

  if (((size_t)(*env)->GetArrayLength(env, (jbyteArray)jHandler))!=sizeof(c_handler)) {
    throwCWitsmlException("close: Critical. Wrong Java byte array size. Memory leaked");
    return;
  }

  if (!(c_handler_p=(struct c_handler_t *)(*env)->GetByteArrayElements(env, (jbyteArray)jHandler, &isCopy))) {
    throwCWitsmlException("close: Critical. Could not get byte array elements. Memory leaked");
    return;
  }

  if (!c_handler_p->cfg_encoded) {
    throwCWitsmlException("close: C Witsml instance already closed");
    (*env)->ReleaseByteArrayElements(env, (jbyteArray)jHandler, (jbyte *)c_handler_p, JNI_ABORT);
    return;
  }

  if (!decodeHandler(&cfg, c_handler_p)) {
    throwCWitsmlException("close: Critical. Invalid C pointer. Could not close. Memory leaked");
    (*env)->ReleaseByteArrayElements(env, (jbyteArray)jHandler, (jbyte *)c_handler_p, JNI_ABORT);
    return;
  }

  cws_config_free(&cfg);

  if (isCopy) {
    c_handler_p->cfg_encoded=NULL;
    c_handler_p->crc32=0;
    c_handler_p->initial=0;
    //https://docs.oracle.com/javase/8/docs/technotes/guides/jni/spec/functions.html#DeleteLocalRef
    (*env)->ReleaseByteArrayElements(env, (jbyteArray)jHandler, (jbyte *)c_handler_p, 0); //0->copy back the content and free the elems buffer
    return;
  }

  (*env)->ReleaseByteArrayElements(env, (jbyteArray)jHandler, (jbyte *)c_handler_p, JNI_ABORT);

  c_handler.cfg_encoded=NULL;
  c_handler.crc32=0;
  c_handler.initial=0;

  if ((jHandler=(void *)cNewByteArray(env, (uint8_t *)&c_handler, sizeof(c_handler), NULL))) {
    (*env)->SetObjectField(env, thisObject, fieldID, (jobject)jHandler);

    if (!(*env)->ExceptionCheck(env))
      return;
  }

  //THIS SHOULD NEVER HAPPEN
  throwCWitsmlException("close: Critical. Could not change C Witsml pointer state. Memory freed successfully \
 BUT it was not changed status in Java byte. Calling close method again will cause double free and crash your VM");

  (*env)->DeleteLocalRef(env, jHandler);
}

/*
 * Class:     org_jwitsmlparser14x_JWitsmlParserLoader
 * Method:    isClosed
 * Signature: ()Z
 */
JNIEXPORT jboolean JNICALL Java_org_jwitsmlparser14x_JWitsmlParserLoader_isClosed
(
  JNIEnv *env,
  jobject thisObject
)
{
  struct c_handler_t *c_handler_p;
  void *jHandler;
  jfieldID fieldID;
  jboolean res;

  if (cGetObjectField(env, &jHandler, NULL, &fieldID, thisObject, WITSML_CLASS, "handler", "[B", NULL)) {
    throwCWitsmlException("isClosed: Could not get Java byte array handler instance");
    return JNI_FALSE;
  }

  if (jHandler==NULL) {
    throwCWitsmlException("isClosed: Instance not initialized");
    return JNI_FALSE;
  }

  if (((size_t)(*env)->GetArrayLength(env, (jbyteArray)jHandler))!=sizeof(*c_handler_p)) {
    throwCWitsmlException("isClosed: Wrong Java byte array size");
    return JNI_FALSE;
  }

  if (!(c_handler_p=(struct c_handler_t *)(*env)->GetByteArrayElements(env, (jbyteArray)jHandler, NULL))) {
    throwCWitsmlException("isClosed: Could not get byte array elements.");
    return JNI_FALSE;
  }

  res=(c_handler_p->cfg_encoded==NULL)&&(c_handler_p->crc32==0);

  (*env)->ReleaseByteArrayElements(env, (jbyteArray)jHandler, (jbyte *)c_handler_p, JNI_ABORT);

  return res;
}

/////////////////////////////////////////////////////// C Witsml Parser ///////////////////////////////////////////////////////

CWS_BUILDER_14X_13X

