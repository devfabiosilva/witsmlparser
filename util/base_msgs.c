#define _GNU_SOURCE
#include <stdarg.h>
#include <base_msgs.h>

#define IS_ALLOC -1
#define NOT_ALLOC 0
#define SET_BASE_MSG(code, codeMsg) {code, NOT_ALLOC, (int)(sizeof(codeMsg)-1), codeMsg}
static struct cws_base_msg_t CWS_BASE_MSG14X[] = 
{
  SET_BASE_MSG(
    1, "Witsml Store SUCCESS"
  ),
  SET_BASE_MSG(
    -407, "A non-empty value must be defined for WMLtypeIn."    
  ),
  SET_BASE_MSG(
    -408, "A non-empty value must be defined for the input template."
  ),
  SET_BASE_MSG(
    -409, "The input template must conform to the appropriate derived schema."
  ),
  SET_BASE_MSG(
    -411, "The OptionsIn parameter string must be encoded utilizing a subset (semicolon separators and no whitespace) of the encoding rules for HTML form content type application/x-www-form-urlencoded."
  ),
  SET_BASE_MSG(
    -426, "The input template must conform to the appropriate derived schema after uncompressing the string"
  ),
  SET_BASE_MSG(
    -467, "The server does not support the API Version provided by the client."
  ),
  SET_BASE_MSG(
    -468, "A QueryIn template must include a version attribute in the plural data-object that defines the Data Schema Version of the data-object."
  ), // Pag 115
  SET_BASE_MSG(
    BM_MISSING_VERSION_ATTRIBUTE_ERROR_CODE, BM_MISSING_VERSION_ATTRIBUTE_ERROR_TEMPLATE
  ),
  SET_BASE_MSG(
    -1002, "GetFromStore missing parameter(s). Expected (in order): WMLtypeIn, QueryIn, OptionsIn and CapabilitiesIn"
  ),
  SET_BASE_MSG(
    -1003, "AddToStore missing parameter(s). Expected (in order): WMLtypeIn, XMLin, OptionsIn and CapabilitiesIn"
  ),
  SET_BASE_MSG(
    BM_CLIENT_VALIDATION_ERROR_CODE, BM_CLIENT_VALIDATION_ERROR_TEMPLATE
  ),
  SET_BASE_MSG(
    BM_CLIENT_MISSING_TYPE_IN_ERROR_CODE, BM_CLIENT_MISSING_TYPE_IN_ERROR_TEMPLATE
  ),
  {0}
};

struct cws_base_msg_t *get_base_msg_list()
{
  return CWS_BASE_MSG14X;
}

inline size_t get_base_msg_list_size() {
  return (sizeof(CWS_BASE_MSG14X)/sizeof(struct cws_base_msg_t)) - 1;
}

inline struct cws_base_msg_t *cws_has_base_msg14x(short code)
{
  struct cws_base_msg_t *q=CWS_BASE_MSG14X;

  while ((q->message!=NULL)&&(q->code!=code))
    q++;

  if (q->message)
    return q;

  return NULL;
}

struct cws_base_msg_t *cws_get_base_msg14x(short code)
{
  static struct cws_base_msg_t unknown_base_msg = SET_BASE_MSG(-2000, "Unknown base message code in C WITSML 1.4.x.x - 1.3.x.x parser");
  struct cws_base_msg_t *q=cws_has_base_msg14x(code);

  return (q)?(q):(&unknown_base_msg);
}

void cws_set_base_msg14x(struct soap *soap, short code)
{
  DECLARE_CONFIG(soap)

  if (config->internal_soap_error!=0)
    return; // Soap internal is imperative

  if (config->base_msg.message==NULL)
    memcpy((void *)&config->base_msg, (void *)cws_get_base_msg14x(code), sizeof(config->base_msg));
}

void catch_base_msg14x(CWS_CONFIG *config, short *code, char **codeMessage)
{
  if (config->internal_soap_error!=0) {
    *code=0;
    *codeMessage=NULL;
    return;
  }

  if ((*codeMessage=(char *)config->base_msg.message))
    *code=config->base_msg.code;
  else
    *codeMessage=(char *)cws_get_base_msg14x((*code)=1)->message;
}

void cws_set_custom_base_msg(struct soap *soap, short code, char *fmt, ...)
{
  DECLARE_CONFIG(soap)
  va_list args;

  if (config->internal_soap_error!=0)
    return; // Soap internal and external errors are imperatives

  if (config->base_msg.message)
    return;

  va_start(args, fmt);
  config->base_msg.message_len=vasprintf((char **)&config->base_msg.message, fmt, args);
  va_end(args);

  if (config->base_msg.message_len<0) {
    config->base_msg.message=NULL;
    config->base_msg.message_len=0;
    return;
  }

  config->base_msg.code=code;
  config->base_msg.is_allocable=IS_ALLOC;
}

#undef SET_BASE_MSG
#undef NOT_ALLOC
#undef IS_ALLOC

