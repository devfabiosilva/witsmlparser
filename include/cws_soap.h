#ifndef CWS_SOAP_H
 #define CWS_SOAP_H

#include <request_context.h>

int cws_internal_serve1(struct soap *);
int cws_internal_serve(CWS_CONFIG *);

void cws_set_soap_fault_util(struct soap *, int, char *, size_t, int);

#define CWS_CONST_LEN(val) (sizeof(val)-1)
#define CWS_CONST_VALUE(val) val, CWS_CONST_LEN(val)
#define CWS_CONST_ARRAY_VALUES(...) __VA_ARGS__, NULL
#define CWS_FAULTSTR(str) str, (sizeof(str)-1)
#define IS_SOAP_EXTERNAL ((config->soap_external)==soap)
#define IS_SERVICE_141X (config->service_protocol_version==VER_14X)
#define CWS_SET_SOAP_FAULT_ERR_CLIENT -2200
#define CWS_SET_SOAP_FAULT_CLIENT(msg) \
  cws_set_soap_fault_util(soap_internal, CWS_SET_SOAP_FAULT_ERR_CLIENT, CWS_FAULTSTR(msg), 0);
#define CWS_SET_SOAP_FAULT_ERR (int)-1234
#define CWS_SET_SOAP_FAULT(msg) \
  cws_set_soap_fault_util(soap_internal, CWS_SET_SOAP_FAULT_ERR, CWS_FAULTSTR(msg), -1);

#define CWS_RETURN(soap) return ((((CWS_CONFIG *)(soap->user))->internal_soap_error==0))?SOAP_OK:SOAP_FAULT;
#endif

