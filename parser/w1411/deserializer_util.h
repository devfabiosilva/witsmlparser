#ifndef DESERIALIZER_UTIL_H
 #define DESERIALIZER_UTIL_H

#define SET_MULTIPLE_ATTRIBUTES(...) __VA_ARGS__, NULL, 0, NULL

#define KEY_USCORE_ATTRIBUTES (const char *)"#attributes", (int)(sizeof("#attributes")-1)

#define CWS_KEY_ANY "#any"

#define CWS_CONSTRUCT_BSON(nameObj) \
  if (!(config->object=CWS_BSON_NEW)) { \
    CWS_SET_SOAP_FAULT("Could not create new BSON at " #nameObj) \
    return SOAP_FAULT; \
  }

#define KEY_USCORE_VALUE (const char *)"#value", (int)(sizeof("#value")-1)

int bson_put_single_attribute_if_exists(bson_t *, const char *, int, char *, int);
int bson_put_multiple_attributes_if_they_exist(bson_t *, ...);
int bson_put_multiple_attributes_if_they_exist_typed(bson_t *, ...);

#define CWS_DETECT_OBJ(object) \
  if (witsmlObject->object##s) { \
    config->objectName=#object; \
    fn=bson_read_##object##s1411; \
    n++; \
  }

#define KEY_USCORE_ATTRIBUTES (const char *)"#attributes", (int)(sizeof("#attributes")-1)

#define _CWS_NULLABLE_XSD_STR (1<<0)
#define _CWS_NULLABLE_XSD_SIGNED_SHORT (1<<1)
#define _CWS_NULLABLE_DATE_TIME (1<<2)
#define _CWS_NULLABLE_DOUBLE (1<<3)

#define ATTR_ENUM_KEY_NULLABLE_1411(parent, key, enumType) CWS_CONST_VALUE(#key), parent->key?soap_rd1witsml__##enumType##2s(soap_internal, *(parent->key)):NULL
#define ATTR_KEY_1411(parent, key) CWS_CONST_VALUE(#key), parent->key
#define ATTR_KEY_TYPED_1411(parent, type, key) CWS_CONST_VALUE(#key), type, parent->key

#endif

