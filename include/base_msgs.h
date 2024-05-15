#ifndef BASE_MSG_H
 #define BASE_MSG_H

#include <request_context.h>

#define BM_MISSING_VERSION_ATTRIBUTE_ERROR_TEMPLATE\
  "Missing version attribute. Supported versions=[\"1.4.1.1\", \"1.4.1\"] and namespace xmlns=\"http://www.witsml.org/schemas/1series\" only. Found: <MESSAGE>"
#define BM_MISSING_VERSION_ATTRIBUTE_ERROR\
  "Missing version attribute. Supported versions=[\"1.4.1.1\", \"1.4.1\"] and namespace xmlns=\"http://www.witsml.org/schemas/1series\" only. Found: \"%s\""
#define BM_MISSING_VERSION_ATTRIBUTE_ERROR_CODE -1001

#define BM_CLIENT_VALIDATION_ERROR_TEMPLATE "Client validation error: <VALIDATION ERROR MESSAGE>"
#define BM_CLIENT_VALIDATION_ERROR "Client validation error: %s"
#define BM_CLIENT_VALIDATION_ERROR_CODE -1004

#define BM_CLIENT_MISSING_TYPE_IN_ERROR_TEMPLATE "Wrong \"WMLtypeIn\". Found: <MESSAGE>"
#define BM_CLIENT_MISSING_TYPE_IN_ERROR "Wrong \"WMLtypeIn\". Found: \"%s\""
#define BM_CLIENT_MISSING_TYPE_IN_ERROR_CODE -1005

struct cws_base_msg_t *cws_get_base_msg14x(short);
void cws_set_base_msg14x(struct soap *, short);
struct cws_base_msg_t *cws_has_base_msg14x(short);
void catch_base_msg14x(CWS_CONFIG *, short *, char **);
void cws_set_custom_base_msg(struct soap *, short, char *, ...);
struct cws_base_msg_t *get_base_msg_list();
size_t get_base_msg_list_size();

#endif

