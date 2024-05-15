#define _GNU_SOURCE
#include <sys/resource.h>
#include <signal.h>
#include <cws_memory.h>
#include <base_msgs.h>
#include <cws_soap.h>
#include <cws_bson_utils.h>
#include "../plugin/threads.h"
#include <stdsoap2.h>
/*
static long int getResourceSize() {
  struct rusage r_usage;

  if (getrusage(RUSAGE_THREAD, &r_usage)==0)
    return (long int)r_usage.ru_maxrss;

  return -1;
}
*/

int cws_internal_serve1(struct soap *soap_internal)
{
  int errCode, errType;
  const char *str;

  if (soap_serve(soap_internal)==SOAP_OK)
    return 0;

  errType=0;
  if ((str=soap_fault_subcode(soap_internal)))
    if (strcmp("SOAP-ENV:Client", str))
      errType=-1;

//errType=0;
  #define CWS_ERR_INTERNAL_GSOAP_SERVE -7002
  #define CWS_ERR_INTERNAL_GSOAP_FAULTSTRING -7003
  #define UNKNOWN_SOAP_INTERNAL_FAULTSTR "Unknown faultstring in SOAP internal. Err. CWS_ERR_INTERNAL_GSOAP_FAULTSTRING"
  #define UNKNOWN_SOAP_INTERNAL_FAULTSTR_LEN sizeof(UNKNOWN_SOAP_INTERNAL_FAULTSTR)-1
  if ((str=soap_fault_string(soap_internal))) {
    if (errType)
      cws_set_soap_fault_util(soap_internal, errCode=CWS_ERR_INTERNAL_GSOAP_SERVE, (char *)str, strlen(str), errType);
    else {
      errCode=-7004;
      cws_set_custom_base_msg(soap_internal, BM_CLIENT_VALIDATION_ERROR_CODE, BM_CLIENT_VALIDATION_ERROR, str);
    }
  } else
    cws_set_soap_fault_util(soap_internal, errCode=CWS_ERR_INTERNAL_GSOAP_FAULTSTRING, UNKNOWN_SOAP_INTERNAL_FAULTSTR, UNKNOWN_SOAP_INTERNAL_FAULTSTR_LEN, errType);
  #undef UNKNOWN_SOAP_INTERNAL_FAULTSTR_LEN
  #undef UNKNOWN_SOAP_INTERNAL_FAULTSTR
  #undef CWS_ERR_INTERNAL_GSOAP_FAULTSTRING
  #undef CWS_ERR_INTERNAL_GSOAP_SERVE

  return errCode;
}

inline int cws_internal_serve(CWS_CONFIG *config) {
  return cws_internal_serve1(config->soap_internal);
}

//-1 -> Server; 0-> Client
#define CWITSML_FAULT_DETAIL "<CWitsmlStoreError type=\"CWITSML_SOAP_INTERNAL\" errorCode=\"%d\">%.*s</CWitsmlStoreError>"
#define CWITSML_SET_FAULT_STRING(soap_ptr) \
if ((config->cws_soap_fault.XMLfaultdetail_len=asprintf( \
     &config->cws_soap_fault.XMLfaultdetail, CWITSML_FAULT_DETAIL, error_code, (int)faultstring_len, faultstring))<0) { \
  config->cws_soap_fault.XMLfaultdetail=NULL; \
  config->cws_soap_fault.XMLfaultdetail_len=0; \
} \
\
if ((config->cws_soap_fault.faultstring=cws_malloc((size_t)(faultstring_len+1)))) { \
  config->cws_soap_fault.faultstring_len=faultstring_len; \
  strcpy(config->cws_soap_fault.faultstring, faultstring); \
  if (type) \
    soap_receiver_fault(soap_ptr, (const char *)config->cws_soap_fault.faultstring, (const char *)config->cws_soap_fault.XMLfaultdetail); \
  else \
    soap_sender_fault(soap_ptr, (const char *)config->cws_soap_fault.faultstring, (const char *)config->cws_soap_fault.XMLfaultdetail); \
}

void cws_set_soap_fault_util(struct soap *soap, int error_code, char *faultstring, size_t faultstring_len, int type)
{
  DECLARE_CONFIG(soap)

  if ((config->internal_soap_error!=0)||(error_code==0))
    return; // Doesn't overlap last error;

  CWITSML_SET_FAULT_STRING(config->soap_internal)
}

