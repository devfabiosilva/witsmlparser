#include <request_context.h>
#include <read1411_soap_req.h>
#include <write1411_soap_req.h>
#include <update1411_soap_req.h>
#include <delete1411_soap_req.h>
#include <cws_soap.h>
#include <cws_memory.h>
#include <base_msgs.h>
#include "../parser/w1411/read/read1411ns.nsmap"
#include "../parser/w1411/read/read1411H.h"
#include "../parser/w1411/write/write1411ns.nsmap"
#include "../parser/w1411/write/write1411H.h"
#include "../parser/w1411/update/update1411ns.nsmap"
#include "../parser/w1411/update/update1411H.h"
#include "../parser/w1411/delete/delete1411ns.nsmap"
#include "../parser/w1411/delete/delete1411H.h"

//gcc -c -O2 -o request_contextDEBUG.o request_context.c -I../include -I../parser/w1411/read/include -Wall -Wno-stringop-truncation -fsanitize=address,leak -DSOAP_DEBUG

#define VERSION_1411 "1.4.1.1"
#define VERSION_141 "1.4.1"
#define VERSION_1311 "1.3.1.1"
#define VERSION_131 "1.3.1"

const char *TYPE_IN_141X[]={
  CWS_CONST_ARRAY_VALUES(
    OBJ_ATTACHMENT, OBJ_BHA_RUN, OBJ_CEMENT_JOB, OBJ_CHANGE_LOG, OBJ_CONV_CORE, OBJ_COORDINATE_REFERENCE_SYSTEM, OBJ_DRILL_REPORT, OBJ_FLUID_REPORT,
    OBJ_FORMATION_MARKER, OBJ_LOG, OBJ_MESSAGE, OBJ_MUD_LOG, OBJ_OBJ_GROUP, OBJ_OPS_REPORT, OBJ_RIG, OBJ_RISK,
    OBJ_SIDEWALL_CORE, OBJ_STIM_JOB, OBJ_SURVEY_PROGRAM, OBJ_TARGET, OBJ_TOOL_ERROR_MODEL, OBJ_TOOL_ERROR_TERM_SET, OBJ_TRAJECTORY, OBJ_TUBULAR,
    OBJ_WB_GEOMETRY, OBJ_WELLBORE, OBJ_WELL
  )
};

const char *versions1_4_x[] = {
  CWS_CONST_ARRAY_VALUES(VERSION_1411, VERSION_141)
};

struct cws_action_t cws_action[] = {
  {
    ACTION_READ_141X, // 0 -> SAME AS cws_action INDEX
    "read",
    "GetFromStore",
    w1411read_namespaces,
    versions1_4_x,
    CWS_CONST_VALUE(READ1411_SOAP_START),
    CWS_CONST_VALUE(READ1411_SOAP_END),
    "rd1411:readObj1411",
    soap_serve_rd1411__readObj1411
  },
  {
    ACTION_WRITE_141X, // 1 -> SAME AS cws_action INDEX
    "write",
    "AddToStore",
    w1411write_namespaces,
    versions1_4_x,
    CWS_CONST_VALUE(WRITE1411_SOAP_START),
    CWS_CONST_VALUE(WRITE1411_SOAP_END),
    "wr1411:writeObj1411",
    soap_serve_wr1411__writeObj1411
  },
  {
    ACTION_UPDATE_141X, // 2 -> SAME AS cws_action INDEX
    "update",
    "UpdateInStore",
    w1411update_namespaces,
    versions1_4_x,
    CWS_CONST_VALUE(UPDATE1411_SOAP_START),
    CWS_CONST_VALUE(UPDATE1411_SOAP_END),
    "up1411:updateObj1411",
    soap_serve_up1411__updateObj1411
  },
  {
    ACTION_DELETE_141X, // 3 -> SAME AS cws_action INDEX
    "delete",
    "DeleteFromStore",
    w1411delete_namespaces,
    versions1_4_x,
    CWS_CONST_VALUE(DELETE1411_SOAP_START),
    CWS_CONST_VALUE(DELETE1411_SOAP_END),
    "dl1411:deleteObj1411",
    soap_serve_dl1411__deleteObj1411
  }
};

//_Static_assert()

const char *check_client_schema_version(struct soap *soap, const char *version)
{
// version can be NULL
  DECLARE_CONFIG(soap)
  const char **vers;

  if (version) {
    vers=config->action->versions;

    while ((*vers!=NULL)&&(strcmp(*vers, version)!=0))
      vers++;

    config->client_version=*vers;

  } else
    config->client_version=NULL;

  return config->client_version;
}

#undef VERSION_131
#undef VERSION_1311
#undef VERSION_141
#undef VERSION_1411

#define CWS_INTERNAL_SOAP_FREE2(ptr) \
    (ptr)->is=NULL; \
    soap_destroy(ptr); \
    soap_end(ptr); \
    soap_free(ptr); \
    ptr=NULL;

#define M_CONFIG_DESTROY2(cfg) \
  if ((cfg->base_msg.is_allocable!=0)&&(cfg->base_msg.message!=NULL)) \
    free((void *)cfg->base_msg.message); \
\
  cfg->base_msg.is_allocable=0;\
  cfg->base_msg.code=0;\
  cfg->base_msg.message_len=0;\
  cfg->base_msg.message=NULL;\
\
  if (cfg->cws_soap_fault.faultstring) {\
    free((void *)cfg->cws_soap_fault.faultstring);\
    cfg->cws_soap_fault.faultstring=NULL;\
    cfg->cws_soap_fault.faultstring_len=0;\
  }\
\
  if (cfg->cws_soap_fault.XMLfaultdetail) {\
    free((void *)cfg->cws_soap_fault.XMLfaultdetail);\
    cfg->cws_soap_fault.XMLfaultdetail=NULL;\
    cfg->cws_soap_fault.XMLfaultdetail_len=0;\
  } \
\
  if (cfg->c_bson_serialized.bson) { \
    bson_free((void *)cfg->c_bson_serialized.bson); \
    cfg->c_bson_serialized.bson=NULL; \
    cfg->c_bson_serialized.bson_size=0; \
  }\
\
  if (cfg->c_json_str.json) {\
    bson_free((void *)cfg->c_json_str.json);\
    cfg->c_json_str.json=NULL;\
    cfg->c_json_str.json_len=0;\
  }\
\
  cws_bson_free(&cfg->object);

#define M_CONFIG_XML_SOAP_FREE2(cfg) \
  if (cfg->xmlSoap) {\
    free((void *)cfg->xmlSoap);\
    cfg->xmlSoap=NULL;\
  }

int cws_recycle_config(CWS_CONFIG *config)
{
  int err=-1;

  if (config->xmlSoap==NULL) {
    M_CONFIG_DESTROY2(config)
    err=0;
  } else if (config->soap_internal_master) {

    soap_destroy(config->soap_internal);
    soap_end(config->soap_internal);
    soap_copy_stream(config->soap_internal, config->soap_internal_master);

    config->soap_internal->user=(void *)config;

    config->internal_os=NULL;

    config->soap_internal->is=NULL;
    config->soap_internal->os=&config->internal_os;

    M_CONFIG_DESTROY2(config)

    //if (config->xmlSoap) { // Config is AWAYS NON NULL
    config->xmlSoapLen=0;
    config->xmlSoap[0]=0;
    //}

    config->internal_soap_error=0;
    config->witsmlObject=NULL;
    config->xmlIn="";
    config->xmlLen=0;
    config->objectName=NULL;

    err=0;
  }

  return err;
}

CWS_CONFIG *cws_config_new(const char *config_name, int *soap_options, int flag, int action_type)
{
  CWS_CONFIG *ret=(CWS_CONFIG *)malloc(CWS_CONFIG_SZ);

  if (!ret)
    return NULL;

  memset((void *)ret, 0, CWS_CONFIG_SZ);

  ret->flag=flag;
  ret->action=&cws_action[(size_t)action_type];

  if (soap_options)
    ret->internalInitFlag=(*soap_options);
  else {
#ifndef SOAP_DEBUG
    ret->internalInitFlag=SOAP_C_UTFSTRING|SOAP_XML_IGNORENS|SOAP_XML_STRICT|SOAP_ENC_PLAIN;
#else
//(SOAP_XML_DEFAULTNS|WITH_NOEMPTYNAMESPACES)
    ret->internalInitFlag=SOAP_C_UTFSTRING|SOAP_XML_INDENT|SOAP_XML_IGNORENS|SOAP_XML_STRICT;//|SOAP_ENC_PLAIN;
#endif
  }

  if (!(ret->soap_internal = soap_new1(ret->internalInitFlag)))
    goto cws_config_new_exit1;

  if ((soap_set_namespaces(ret->soap_internal, ret->action->namespaces))!=SOAP_OK)
    goto cws_config_new_exit1;

  if (ret->flag&CWS_FLAG_RECYCLABLE) {
    if (!(ret->soap_internal_master = soap_new1(ret->internalInitFlag)))
      goto cws_config_new_exit2;
    
    if ((soap_set_namespaces(ret->soap_internal_master, ret->action->namespaces))!=SOAP_OK)
      goto cws_config_new_exit3;

    soap_clr_mode(ret->soap_internal_master, SOAP_XML_GRAPH);
    soap_clr_mode(ret->soap_internal_master, SOAP_XML_TREE);

    ret->soap_internal_master->user=NULL;// user master is aways NULL

    ret->soap_internal_master->sendfd=-1;
    ret->soap_internal_master->recvfd=-1;

    ret->soap_internal_master->is=NULL; //Is never used
    ret->soap_internal_master->os=&ret->internal_master_os;
  }

  soap_clr_mode(ret->soap_internal, SOAP_XML_GRAPH);
  soap_clr_mode(ret->soap_internal, SOAP_XML_TREE);

  ret->soap_internal->user=(void *)ret;

  ret->soap_internal->sendfd=-1;
  ret->soap_internal->recvfd=-1;

  ret->internal_os=NULL;

  ret->soap_internal->is=(const char *)ret->xmlSoap;
  ret->soap_internal->os=&ret->internal_os;

  snprintf(ret->instance_name, sizeof(ret->instance_name), "%s - (%p)", (config_name)?config_name:"CWS_CONFIG_INIT", (void *)ret);

  return ret;

cws_config_new_exit3:
  CWS_INTERNAL_SOAP_FREE2(ret->soap_internal_master)

cws_config_new_exit2:
  CWS_INTERNAL_SOAP_FREE2(ret->soap_internal)

cws_config_new_exit1:

  free((void *)ret);

  return NULL;
}

void cws_config_free(CWS_CONFIG **cws_config)
{
  if (*cws_config) {

    if ((*cws_config)->soap_internal_master) {
#ifdef SOAP_DEBUG
      printf(
        "\nBegin free soap internal (MASTER) instance %p ...\n",
        (*cws_config)->soap_internal_master
      );
#endif
      CWS_INTERNAL_SOAP_FREE2((*cws_config)->soap_internal_master)
      (*cws_config)->soap_internal_master=NULL;

#ifdef SOAP_DEBUG
      printf("\nFinished freeing soap_internal (MASTER)\n");
#endif
    }


    if ((*cws_config)->soap_internal) {
#ifdef SOAP_DEBUG
      printf(
        "\nBegin free soap internal instance %p ...\n",
        (*cws_config)->soap_internal
      );
#endif
      CWS_INTERNAL_SOAP_FREE2((*cws_config)->soap_internal)
      (*cws_config)->soap_internal=NULL;
#ifdef SOAP_DEBUG
      printf("\nFinished freeing soap_internal\n");
#endif
    }

#ifdef SOAP_DEBUG
    printf(
      "\nDestroying config instance %s ...\n",
      (*cws_config)->instance_name
    );
#endif

  M_CONFIG_DESTROY2((*cws_config))

#ifdef SOAP_DEBUG
    printf(
      "\nDestroyed instance ...\n");
#endif

#ifdef SOAP_DEBUG
    printf(
      "\nDestroying XML soap enveloper of size %lu ...\n",
      (*cws_config)->xmlSoapSize
    );
#endif

  M_CONFIG_XML_SOAP_FREE2((*cws_config))

#ifdef SOAP_DEBUG
    printf(
      "\nDestroying XML soap enveloper ...\n");
#endif


#ifdef SOAP_DEBUG
    printf(
      "\nBegin freeing config instance %s ...\n",
      (*cws_config)->instance_name
    );
#endif

    free((void *)*cws_config);
    *cws_config=NULL;

#ifdef SOAP_DEBUG
    printf("\nFinished freeing cws_config\n");
#endif
  }
}

#define SERVER_FAULT_OUT_OF_MEMORY_ERROR -5000
#define SERVER_FAULT_OUT_OF_MEMORY_ERROR_MESSAGE "Out of memory"
#define SERVER_FAULT_NAMESPACE_ERROR -5001
#define SERVER_FAULT_NAMESPACE_ERROR_MESSAGE "Could not set namespace"
//xmlIn NOT NULL
char *cws_parse_XML_soap_envelope(CWS_CONFIG *config, char *xmlIn, size_t xmlLen)
{
  char
    *p,
    *xmlSoap_tmp;
  size_t xmlSoapSize_tmp;

  if ((config->xmlLen=xmlLen)==0) {
    cws_set_base_msg14x(config->soap_internal, -407);
    return NULL;
  }

  config->xmlIn=xmlIn;

  config->xmlSoapLen=(config->action->soap_start_len + config->action->soap_end_len + config->xmlLen);

  if (config->soap_internal_master) {

    if (config->xmlSoap) {

      if (config->xmlSoapSize>config->xmlSoapLen)
        goto cws_parse_XML_soap_envelope_cpy;

      xmlSoapSize_tmp=config->xmlSoapLen+1;

      if ((xmlSoap_tmp=(char *)cws_realloc(config->xmlSoap, xmlSoapSize_tmp))) {

        config->xmlSoap=xmlSoap_tmp;
        config->xmlSoapSize=xmlSoapSize_tmp;
        goto cws_parse_XML_soap_envelope_cpy;

      }
    } else {

      config->xmlSoapSize=config->xmlSoapLen+1;
      if ((config->xmlSoap=(char *)cws_malloc(config->xmlSoapSize)))
        goto cws_parse_XML_soap_envelope_cpy;

      config->xmlSoapSize=0;
    }

  } else if ((config->xmlSoap=(char *)cws_malloc(config->xmlSoapSize=(config->xmlSoapLen+1)))) {

cws_parse_XML_soap_envelope_cpy:
    p=&((char *)memcpy(config->xmlSoap, config->action->soap_start, config->action->soap_start_len))[config->action->soap_start_len];
    p=&((char *)memcpy(p, config->xmlIn, config->xmlLen))[config->xmlLen];
    p=&((char *)memcpy(p, config->action->soap_end, config->action->soap_end_len))[config->action->soap_end_len];
    *p=0;

    config->soap_internal->is=(const char *)config->xmlSoap;

    return config->xmlSoap;

  } else
    config->xmlSoapSize=0;

  config->xmlLen=0;
  config->xmlIn=NULL;

  cws_set_soap_fault_util(
    config->soap_internal, SERVER_FAULT_OUT_OF_MEMORY_ERROR,
    CWS_CONST_VALUE(SERVER_FAULT_OUT_OF_MEMORY_ERROR_MESSAGE),
    -1
  );

  return NULL;
}

char *cws_parse_XML_soap_envelope_from_file(CWS_CONFIG *config, const char *filename)
{
  FILE *f;
  long l;
  char
    *xmlSoap_tmp,
    *p;
  size_t xmlSoapSize_tmp;

  if (!filename)
    return NULL;

  if (!(f=fopen(filename, "r")))
    return NULL;

  if (fseek(f, 0L, SEEK_END)<0) {
    fclose(f);
    return NULL;
  }

  if ((l=ftell(f))<0) {
    fclose(f);
    return NULL;
  }

  if ((config->xmlLen=(size_t)l)==0) {
    fclose(f);
    cws_set_base_msg14x(config->soap_internal, -407);
    return NULL;
  }

  config->xmlSoapLen=(config->action->soap_start_len + config->action->soap_end_len + config->xmlLen);

  if (config->soap_internal_master) {

    if (config->xmlSoap) {

      if (config->xmlSoapSize > config->xmlSoapLen)
        goto cws_parse_XML_soap_envelope_from_file_cpy;

      xmlSoapSize_tmp=config->xmlSoapLen+1;

      if ((xmlSoap_tmp=(char *)cws_realloc(config->xmlSoap, xmlSoapSize_tmp))) {

        config->xmlSoap=xmlSoap_tmp;
        config->xmlSoapSize=xmlSoapSize_tmp;
        goto cws_parse_XML_soap_envelope_from_file_cpy;

      }
    } else {

      config->xmlSoapSize=config->xmlSoapLen+1;
      if ((config->xmlSoap=(char *)cws_malloc(config->xmlSoapSize)))
        goto cws_parse_XML_soap_envelope_from_file_cpy;

      config->xmlSoapSize=0;
    }

  } else if ((config->xmlSoap=(char *)cws_malloc(config->xmlSoapSize=(config->xmlSoapLen+1)))) {

cws_parse_XML_soap_envelope_from_file_cpy:

    p=&((char *)memcpy((void *)config->xmlSoap, config->action->soap_start, config->action->soap_start_len))[config->action->soap_start_len];
    config->xmlIn=p;
    rewind(f);

    if (fread((void *)config->xmlIn, sizeof(char), config->xmlLen, f)==config->xmlLen) {
      p+=config->xmlLen;
      p=&((char *)memcpy((void *)p, config->action->soap_end, config->action->soap_end_len))[config->action->soap_end_len];
      *p=0;

      config->soap_internal->is=(const char *)config->xmlSoap;
      fclose(f);

      return config->xmlSoap;
    }

    config->xmlSoap[0]=0;
    config->xmlSoapLen=0;

#define SERVER_FAULT_READ_FILE_STREAM_ERROR -5001
#define SERVER_FAULT_READ_FILE_STREAM_ERROR_MESSAGE "Could not read file stream"
    cws_set_soap_fault_util(
      config->soap_internal, SERVER_FAULT_READ_FILE_STREAM_ERROR,
      CWS_CONST_VALUE(SERVER_FAULT_READ_FILE_STREAM_ERROR_MESSAGE),
      -1
    );
#undef SERVER_FAULT_READ_FILE_STREAM_ERROR_MESSAGE
#undef SERVER_FAULT_READ_FILE_STREAM_ERROR

  } else
    config->xmlSoapSize=0;

  config->xmlLen=0;
  config->xmlIn=NULL;
  config->soap_internal->is=NULL;
  fclose(f);

  cws_set_soap_fault_util(
    config->soap_internal, SERVER_FAULT_OUT_OF_MEMORY_ERROR,
    CWS_CONST_VALUE(SERVER_FAULT_OUT_OF_MEMORY_ERROR_MESSAGE),
    -1
  );

  return NULL;
}
//

struct c_json_str_t *getJson(CWS_CONFIG *config)
{

  struct c_json_str_t *c_json_str;

  c_json_str=&(config)->c_json_str;

  if (c_json_str->json)
    return c_json_str;

  if ((config->object!=NULL)&&((c_json_str->json=bson_as_relaxed_extended_json((const bson_t *)config->object, &c_json_str->json_len))!=NULL))
    return c_json_str;

  return NULL;
}

struct c_bson_serialized_t *bsonSerialize(CWS_CONFIG *config)
{
  struct c_bson_serialized_t *ptr;

  ptr=&config->c_bson_serialized;

  if (ptr->bson)
    return ptr;

  if (config->object)
    if (!bson_serialize(&(ptr->bson), &(ptr->bson_size), config->object))
      return ptr;

  return NULL;
}

static int file_exists(const char *filename)
{
  FILE *f;

  if ((f=fopen(filename, "r"))) {
    fclose(f);
    return -156;
  }

  return 0;
}

int writeToFile(CWS_CONFIG *config, const char *filename)
{
  int err;
  FILE *f;
  char fname[64];

  struct c_bson_serialized_t *ptr;

  if (!(ptr=bsonSerialize(config)))
    return -1;

  if (!filename)
    snprintf((char *)(filename=(const char *)fname), sizeof(fname), "%s.bson", config->objectName);

  if ((err=file_exists(filename)))
    return err;

  if (!(f=fopen(filename, "w")))
    return -2;

  err=(fwrite((void *)ptr->bson, sizeof(uint8_t), ptr->bson_size, f)==ptr->bson_size)?0:-3;

  fclose(f);

  return err;
}

int writeToFileJSON(CWS_CONFIG *config, const char *filename)
{
  int err;
  FILE *f;
  char fname[64];

  struct c_json_str_t *ptr;

  if (!(ptr=getJson(config)))
    return -4;

  if (!filename)
    snprintf((char *)(filename=(const char *)fname), sizeof(fname), "%s.json", config->objectName);

  if ((err=file_exists(filename)))
    return err;

  if (!(f=fopen(filename, "w")))
    return -5;

  err=(fwrite((void *)ptr->json, sizeof(uint8_t), ptr->json_len, f)==ptr->json_len)?0:-6;

  fclose(f);

  return err;
}
/*
inline int writeToFileJSON(CWS_CONFIG *config, const char *filename)
{
  return writeToFileJSON1(config->soap_internal, filename);
}
*/

#undef SERVER_FAULT_NAMESPACE_ERROR
#undef SERVER_FAULT_NAMESPACE_ERROR_MESSAGE
#undef SERVER_FAULT_OUT_OF_MEMORY_ERROR_MESSAGE
#undef SERVER_FAULT_OUT_OF_MEMORY_ERROR

