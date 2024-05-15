//qua 26 jul 2023 10:08:42 
//w2l -c -g -U -F -P -u  /home/fabiolinux/Documentos/GITHUB/PREPARO/cwitsml/api/PARSERS/witsml_v1.4.1.1_data/generated_read_schemas/* -o read1411.h -tread1411.dat
//scpp -c -S -s -t -2 -pread1411 read1411.h

//gcc -O2 -c read1411C.c -I../../include -Wall -fsanitize=address,leak -DSOAP_DEBUG -DWITH_NOGLOBAL -o read1411C.o

//TRY
//OK -> gcc -O2 -c read1411C.c -I../../include -Wall -fsanitize=address,leak -DSOAP_DEBUG -DWITH_NONAMESPACES -o read1411C.o
//OK -> int rd1411__readattachments(struct rd1witsml__obj_USCOREattachments *attachments, char **result);
// -DWITH_NOSERVEREQUEST
//OK -> gcc -O2 -c read1411ServerLib.c -I../../include -Wall -fsanitize=address,leak -DSOAP_DEBUG -DWITH_NONAMESPACES -o read1411ServerLib.o

//gcc -O2 -c read1411ServerLib.c -I../../../include -Wall -fsanitize=address,leak -DSOAP_DEBUG -DWITH_NONAMESPACES -DWITH_NOSERVEREQUEST -o read1411ServerLibDEBUG.o

//NO DEBUG:
//gcc -O2 -c read1411ServerLib.c -I../../../include -Wall -DWITH_NONAMESPACES -DWITH_NOSERVEREQUEST -o read1411ServerLib.o

//#include <cws_bson_utils.h>
#include <request_context.h>
#include <cws_soap.h>
#include <base_msgs.h>
#include <cws_bson_utils.h>
#include <cws_utils.h>
#include "read/read1411H.h"
#include "deserializer_util.h"
//#include "read/include/read_1411_deserializer.h"

#ifdef WITH_STATISTICS

#else

#endif

#define READ_W_OBJECT_1411_BEGIN(object) \
int bson_read_##object##s1411(struct soap *soap_internal) \
{\
  DECLARE_CONFIG(soap_internal)\
  struct rd1witsml__obj_USCORE##object##s *object##s=((struct rd1411__readObj1411_USCOREt *)config->witsmlObject)->object##s;\
\
  CWS_CONSTRUCT_BSON(object)

#define READ_W_OBJECT_1411_END(object) \
  printf("\nSoap internal %p " #object " %p", soap_internal, object##s); \
\
  return SOAP_OK;\
}
/*
READ_W_OBJECT_1411_BEGIN(attachment)
READ_W_OBJECT_1411_END(attachment)
*/

#define READ_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(objectParent, objectName) \
  if ((objectParent->objectName!=NULL)&&(!bson_append_utf8(bson, CWS_CONST_BSON_KEY(#objectName), (const char *)objectParent->objectName, -1))) { \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #objectName " of " #objectParent " object") \
    goto bson_read_##objectParent##1411_resume; \
  }

#define READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(objectParent, objectName) \
  READ_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(objectParent, objectName)

// into a simple sequence
#define READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(objectParent, objectName) \
  if ((objectParent##_sequence->objectName!=NULL)&&(!bson_append_utf8(&bson, CWS_CONST_BSON_KEY(#objectName), (const char *)objectParent##_sequence->objectName, -1))) { \
  CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #objectName " of " #objectParent " object") \
  goto bson_read_##objectParent##1411_resume1; \
}

#define READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B

#define READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_C(objectParent, objectName, suffix) \
  if ((__##objectParent##_sequence##suffix->objectName!=NULL)&&(!bson_append_utf8(bson, CWS_CONST_BSON_KEY(#objectName),\
    (const char *)__##objectParent##_sequence##suffix->objectName, -1))) { \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #objectName " of " #objectParent " object") \
    goto bson_read_##objectParent##_sequence##suffix##1411_resume1; \
  }

#define READ_O_UTF8_OBJECT_WITH_ALIAS_1411_OR_ELSE_GOTO_RESUME_B(objectParent, objectName, alias) \
  if ((objectParent##_sequence->objectName!=NULL)&&(!bson_append_utf8(&bson, CWS_CONST_BSON_KEY(#alias),\
    (const char *)objectParent##_sequence->objectName, -1))) { \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #alias " of " #objectParent " object") \
    goto bson_read_##objectParent##1411_resume1; \
  }

#define READ_O_UTF8_OBJECT_1411_VOID_B(objectParent, objectName) \
  if ((objectParent##_sequence->objectName!=NULL)&&(!bson_append_utf8(&bson,\
    CWS_CONST_BSON_KEY(#objectName), (const char *)objectParent##_sequence->objectName, -1)))\
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #objectName " of " #objectParent " object")

#define READ_A_UTF8_OBJECT_1411_VOID_B READ_O_UTF8_OBJECT_1411_VOID_B

#define READ_O_ARRAY_OF_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(objectParent, objectName) \
if (bson_read_array_of_string1411(soap_internal, &bson, CWS_CONST_BSON_KEY(#objectName), objectParent##_sequence->__size##objectName,\
  objectParent##_sequence->objectName)) { \
  CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read array of string" #objectName " of " #objectParent " object") \
  goto bson_read_##objectParent##1411_resume1; \
}

#define READ_A_ARRAY_OF_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B READ_O_ARRAY_OF_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B

#define READ_O_ARRAY_OF_ANY_OBJECT_1411_VOID_B(objectParent) \
if (bson_read_array_of_string1411(soap_internal, &bson, CWS_CONST_BSON_KEY(CWS_KEY_ANY), objectParent##_sequence->__size, objectParent##_sequence->__any))\
  CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read array of string (any)" CWS_KEY_ANY " of " #objectParent " object")

#define READ_ARRAY_OF_UTF8_OBJECT_1411_VOID_B(objectParent, objectName) \
if (bson_read_array_of_string1411(soap_internal, &bson, CWS_CONST_BSON_KEY(#objectName), objectParent##_sequence->__size##objectName, \
  objectParent##_sequence->objectName))\
  CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read array of string" #objectName " of " #objectParent " object")

#define READ_A_ARRAY_OF_UTF8_OBJECT_1411_VOID_B READ_ARRAY_OF_UTF8_OBJECT_1411_VOID_B

#define READ_ARRAY_OF_UTF8_OBJECT_1411_VOID(objectParent, objectName) \
if (bson_read_array_of_string1411(soap_internal, thisDocument, CWS_CONST_BSON_KEY(#objectName), objectParent##_sequence_->__size##objectName, \
  objectParent##_sequence_->objectName))\
  CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read array of string" #objectName " of " #objectParent " object")

#define READ_ARRAY_OF_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(objectParent, objectName) \
  if (bson_read_array_of_string1411(soap_internal, thisDocument, CWS_CONST_BSON_KEY(#objectName), objectParent##_sequence_->__size##objectName, \
    objectParent##_sequence_->objectName)) {\
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read array of string" #objectName " of " #objectParent " object")\
    goto bson_read_##objectParent##_sequence_1411_resume1;\
  }

#define READ_A_UTF8_OBJECT_WITH_ALIAS_1411_OR_ELSE_GOTO_RESUME_B(objectParent, objectName, alias) \
  if ((objectParent##_sequence->objectName!=NULL)&&(!bson_append_utf8(&bson, CWS_CONST_BSON_KEY(#alias), (const char *)objectParent##_sequence->objectName, -1))) { \
  CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #alias " of " #objectParent " object") \
  goto bson_read_##objectParent##1411_resume1; \
}

#define READ_S_ARRAY_OF_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME READ_ARRAY_OF_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME

#define READ_S_ARRAY_OF_UTF8_OBJECT_1411_VOID READ_ARRAY_OF_UTF8_OBJECT_1411_VOID

#define READ_O_ARRAY_OF_UTF8_OBJECT_1411_VOID_C(objectParent)\
if (bson_read_array_of_string1411(soap_internal, bson, key, key_len, objectParent##_sequence->__size, objectParent##_sequence->__any))\
  CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read array of string of " #objectParent " object")

#define READ_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(objectParent, objectName) \
  if ((objectParent##_sequence->objectName!=NULL)&&(!bson_append_bool(&bson, CWS_CONST_BSON_KEY(#objectName), (bool)*(objectParent##_sequence->objectName)))) { \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read boolean " #objectName " of " #objectParent " object") \
    goto bson_read_##objectParent##1411_resume1;\
  }

#define READ_BOOLEAN_NULLABLE_1411_VOID_B(objectParent, objectName) \
  if ((objectParent##_sequence->objectName!=NULL)&&(!bson_append_bool(&bson, CWS_CONST_BSON_KEY(#objectName), (bool)*(objectParent##_sequence->objectName))))\
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read boolean " #objectName " of " #objectParent " object")

#define READ_S_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME(objectParent, objectName) \
  if ((objectParent##_sequence_->objectName!=NULL)&&(!bson_append_bool(thisDocument, CWS_CONST_BSON_KEY(#objectName), (bool)*(objectParent##_sequence_->objectName)))) { \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read boolean " #objectName " of " #objectParent " object") \
    goto bson_read_##objectParent##_sequence_1411_resume1;\
  }

#define READ_S_BOOLEAN_NULLABLE_1411_VOID(objectParent, objectName) \
  if ((objectParent##_sequence_->objectName)&&(!bson_append_bool(thisDocument, CWS_CONST_BSON_KEY(#objectName), (bool)*(objectParent##_sequence_->objectName))))\
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read boolean " #objectName " of " #objectParent " object")

#define READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B READ_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B

#define READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B READ_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B

#define READ_A_BOOLEAN_NULLABLE_1411_VOID_B READ_BOOLEAN_NULLABLE_1411_VOID_B

#define READ_O_BOOLEAN_NULLABLE_1411_VOID_B READ_BOOLEAN_NULLABLE_1411_VOID_B

#define READ_O_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(objectParent, objectName, objectType) \
  if ((objectParent##_sequence->objectName!=NULL)&&(!bson_append_utf8(&bson, CWS_CONST_BSON_KEY(#objectName),\
  (const char *)soap_rd1witsml__##objectType##2s(soap_internal, *(objectParent##_sequence->objectName)), -1))) { \
  CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #objectName " of " #objectParent " object") \
  goto bson_read_##objectParent##1411_resume1; \
}

#define READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B READ_O_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B

#define READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(objectParent, objectName, objectType) \
  if ((objectParent##_sequence_->objectName!=NULL)&&(!bson_append_utf8(thisDocument, CWS_CONST_BSON_KEY(#objectName),\
    (const char *)soap_rd1witsml__##objectType##2s(soap_internal, *(objectParent##_sequence_->objectName)), -1))) { \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #objectName " of " #objectParent " object") \
    goto bson_read_##objectParent##_sequence_1411_resume1; \
  }

#define READ_S_OBJECT_ENUM_NULLABLE_1411_VOID(objectParent, objectName, objectType) \
  if ((objectParent##_sequence_->objectName!=NULL)&&(!bson_append_utf8(thisDocument, CWS_CONST_BSON_KEY(#objectName),\
    (const char *)soap_rd1witsml__##objectType##2s(soap_internal, *(objectParent##_sequence_->objectName)), -1))) \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #objectName " of " #objectParent " object")

#define READ_O_OBJECT_ENUM_NULLABLE_1411_VOID_B(objectParent, objectName, objectType) \
  if ((objectParent##_sequence->objectName!=NULL)&&(!bson_append_utf8(&bson, CWS_CONST_BSON_KEY(#objectName),\
    (const char *)soap_rd1witsml__##objectType##2s(soap_internal, *(objectParent##_sequence->objectName)), -1))) \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #objectName " of " #objectParent " object")

#define READ_W_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(objectParent, objectName) \
  if ((objectParent##_sequence->objectName!=NULL)&&(!bson_append_utf8(&bson,\
    CWS_CONST_BSON_KEY(#objectName), (const char *)objectParent##_sequence->objectName, -1))) { \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #objectName " of " #objectParent " object") \
    goto bson_read_##objectParent##1411_array_resume1; \
  }

#define READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(objectParent, objectName) \
  if ((objectParent##_sequence_->objectName!=NULL)&&(!bson_append_utf8(thisDocument,\
    CWS_CONST_BSON_KEY(#objectName), (const char *)objectParent##_sequence_->objectName, -1))) { \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #objectName " of " #objectParent " object") \
    goto bson_read_##objectParent##_sequence_1411_resume1; \
  }

#define READ_S_UTF8_OBJECT_ALIAS_1411_OR_ELSE_GOTO_RESUME(objectParent, objectName, alias) \
  if ((objectParent##_sequence_->objectName!=NULL)&&(!bson_append_utf8(thisDocument,\
    CWS_CONST_BSON_KEY(#alias), (const char *)objectParent##_sequence_->objectName, -1))) { \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #objectName "(" #alias ") of " #objectParent " object") \
    goto bson_read_##objectParent##_sequence_1411_resume1; \
  }

#define READ_S_UTF8_OBJECT_1411_VOID(objectParent, objectName) \
  if ((objectParent##_sequence_->objectName!=NULL)&&(!bson_append_utf8(thisDocument,\
    CWS_CONST_BSON_KEY(#objectName), (const char *)objectParent##_sequence_->objectName, -1)))\
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #objectName " of " #objectParent " object")

#define READ_PUT_MULTIPLE_ATTRIBUTES_1411_OR_ELSE_GOTO_RESUME(objectParent, ...) \
  if (bson_put_multiple_attributes_if_they_exist(&bson, __VA_ARGS__)) {\
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not set default attributes to #attribute") \
    goto bson_read_##objectParent##1411_resume1; \
  }

#define READ_PUT_SINGLE_ATTRIBUTE_1411_OR_ELSE_GOTO_RESUME(objectParent, objectName) \
  if (bson_put_single_attribute_if_exists(&bson, CWS_CONST_BSON_KEY(#objectName), objectParent->objectName, -1)) {\
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not set " #objectName " attribute to #attribute") \
    goto bson_read_##objectParent##1411_resume1; \
  }

#define READ_W_PUT_MULTIPLE_ATTRIBUTES_1411_OR_ELSE_GOTO_RESUME(objectParent, ...) \
  READ_PUT_MULTIPLE_ATTRIBUTES_1411_OR_ELSE_GOTO_RESUME(objectParent, __VA_ARGS__)

#define READ_O_PUT_MULTIPLE_ATTRIBUTES_1411_OR_ELSE_GOTO_RESUME(objectParent, ...) \
  READ_PUT_MULTIPLE_ATTRIBUTES_1411_OR_ELSE_GOTO_RESUME(objectParent, __VA_ARGS__)

#define READ_O_PUT_SINGLE_ATTRIBUTE_1411_OR_ELSE_GOTO_RESUME READ_PUT_SINGLE_ATTRIBUTE_1411_OR_ELSE_GOTO_RESUME
#define READ_A_PUT_SINGLE_ATTRIBUTE_1411_OR_ELSE_GOTO_RESUME READ_PUT_SINGLE_ATTRIBUTE_1411_OR_ELSE_GOTO_RESUME

#define READ_O_UTF8_OBJECT_ITEM_1411_OR_ELSE_GOTO_RESUME(objectParent) \
  if (objectParent->__item) { \
    if (!bson_append_utf8(&bson, KEY_USCORE_VALUE, (const char *)objectParent->__item, -1)) { \
      CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read #value of " #objectParent " object") \
      goto bson_read_##objectParent##1411_resume1; \
    } \
  }

#define READ_O_UTF8_OBJECT_ITEM_1411_VOID(objectParent) \
  if (objectParent->__item) { \
    if (!bson_append_utf8(&bson, KEY_USCORE_VALUE, (const char *)objectParent->__item, -1)) { \
      CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read #value of " #objectParent " object") \
    }\
  }

#define READ_A_UTF8_OBJECT_ITEM_1411_VOID READ_O_UTF8_OBJECT_ITEM_1411_VOID

#define READ_O_DOUBLE_NULLABLE_ITEM_1411_VOID(objectParent) \
  if ((objectParent->__item)&&(!bson_append_double(&bson, KEY_USCORE_VALUE, *(objectParent->__item))) \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read double #value of " #objectParent " object")

#define READ_O_DOUBLE_ITEM_1411_VOID(objectParent) \
  if (!bson_append_double(&bson, KEY_USCORE_VALUE, objectParent->__item)) \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read double #value of " #objectParent " object")

#define READ_O_SHORT_ITEM_1411_VOID(objectParent) \
  if (!bson_append_int32(&bson, KEY_USCORE_VALUE, (int32_t)objectParent->__item)) \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read short #value of " #objectParent " object")

#define READ_O_DOUBLE_NULLABLE_OBJECT_ITEM_1411_VOID(objectParent) \
  if (objectParent->__item) { \
    if (!bson_append_double(&bson, KEY_USCORE_VALUE, objectParent->__item)) { \
      CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read double #value of " #objectParent " object") \
    }\
  }

#define READ_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(objectParent, objectName)\
  if ((objectParent##_sequence->objectName!=NULL)&&(!bson_append_double(&bson, CWS_CONST_BSON_KEY(#objectName), *(objectParent##_sequence->objectName)))) { \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read double nullable" #objectName " of " #objectParent " object") \
    goto bson_read_##objectParent##1411_resume1;\
  }

#define READ_INT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(objectParent, objectName)\
  if ((objectParent##_sequence->objectName!=NULL)&&(!bson_append_int32(&bson, CWS_CONST_BSON_KEY(#objectName),\
    (int32_t)*((int32_t *)objectParent##_sequence->objectName)))) { \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read int nullable " #objectName " of " #objectParent " object") \
    goto bson_read_##objectParent##1411_resume1;\
  }

#define READ_A_INT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B READ_INT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B

#define READ_DOUBLE_NULLABLE_1411_VOID_B(objectParent, objectName)\
  if ((objectParent##_sequence->objectName!=NULL)&&(!bson_append_double(&bson, CWS_CONST_BSON_KEY(#objectName), *(objectParent##_sequence->objectName))))\
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read double " #objectName " of " #objectParent " object") \

#define READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B READ_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B

#define READ_O_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B READ_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B

#define READ_A_DOUBLE_NULLABLE_1411_VOID_B READ_DOUBLE_NULLABLE_1411_VOID_B

#define READ_OBJECT_1411_OR_ELSE_GOTO_RESUME(bson, objectParent, objectName, typeName) \
  if (bson_read_##typeName##1411(soap_internal, bson, CWS_CONST_BSON_KEY(#objectName), objectParent->objectName, 0)) \
    goto bson_read_##objectParent##1411_resume1;

#define READ_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(objectParent, objectName, typeName) \
  if (bson_read_##typeName##1411(soap_internal, &bson, CWS_CONST_BSON_KEY(#objectName), objectParent##_sequence->objectName, 0)) \
    goto bson_read_##objectParent##1411_resume1;

#define READ_OBJECT_ALIAS_1411_OR_ELSE_GOTO_RESUME_B(objectParent, objectName, alias, typeName) \
  if (bson_read_##typeName##1411(soap_internal, &bson, CWS_CONST_BSON_KEY(#alias), objectParent##_sequence->objectName, 0)) \
    goto bson_read_##objectParent##1411_resume1;

#define READ_A_OBJECT_ALIAS_1411_OR_ELSE_GOTO_RESUME_B READ_OBJECT_ALIAS_1411_OR_ELSE_GOTO_RESUME_B

#define READ_OBJECT_1411_OR_ELSE_GOTO_RESUME_BX(objectParent, objectName, typeName, suffix) \
  if (bson_read_##typeName##_sequence##suffix##1411(soap_internal, &bson, objectParent##_sequence->objectName)) \
    goto bson_read_##objectParent##1411_resume1;

#define READ_OBJECT_1411_VOID_BX(objectParent, objectName, typeName, suffix) \
  bson_read_##typeName##_sequence##suffix##1411(soap_internal, &bson, objectParent##_sequence->objectName);

#define READ_OBJECT_1411_VOID_CX(objectParent, parentSuffix, objectName, typeName, suffix) \
  bson_read_##typeName##_sequence##suffix##1411(soap_internal, bson, __##objectParent##_sequence##parentSuffix->objectName);

#define READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME_B1(objectParent, objectName, typeName, suffix) \
  if (bson_read_##typeName##_sequence##suffix##1411(soap_internal, thisDocument, objectParent##_sequence_->objectName)) \
    goto bson_read_##objectParent##_sequence_1411_resume1;

#define READ_OBJECT_1411_OR_ELSE_GOTO_RESUME_D(objectParent, objectName, typeName) \
  if (bson_read_##typeName##1411(soap_internal, &bson, CWS_CONST_BSON_KEY(#objectName), objectParent##_sequence_->objectName, 0)) \
    goto bson_read_##objectParent##1411_resume1;

#define READ_OBJECT_1411_OR_ELSE_GOTO_RESUME_C(objectParent, objectName, typeName, suffix) \
  if (bson_read_##typeName##1411(soap_internal, bson, CWS_CONST_BSON_KEY(#objectName), __##objectParent##_sequence##suffix->objectName, 0)) \
    goto bson_read_##objectParent##_sequence##suffix##1411_resume1;

#define READ_OBJECT_1411_VOID_C(objectParent, objectName, typeName, suffix) \
  bson_read_##typeName##1411(soap_internal, bson, CWS_CONST_BSON_KEY(#objectName), __##objectParent##_sequence##suffix->objectName, 0);

#define READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(objectParent, objectName, typeName) \
  READ_OBJECT_1411_OR_ELSE_GOTO_RESUME(thisDocument, objectParent##_sequence_, objectName, typeName)

#define READ_OBJECT_1411_VOID(bson, objectParent, objectName, typeName, addIfEmpty) \
  bson_read_##typeName##1411(soap_internal, bson, CWS_CONST_BSON_KEY(#objectName), objectParent->objectName, addIfEmpty);

#define READ_S_OBJECT_1411_VOID(objectParent, objectName, typeName) \
  READ_OBJECT_1411_VOID(thisDocument, objectParent##_sequence_, objectName, typeName, 0)

#define READ_O_OBJECT_1411_VOID_B(objectParent, objectName, typeName) \
  bson_read_##typeName##1411(soap_internal, &bson, CWS_CONST_BSON_KEY(#objectName), objectParent##_sequence->objectName, 0);

#define READ_O_OBJECT_ALIAS_1411_VOID_B(objectParent, objectName, alias, typeName) \
  bson_read_##typeName##1411(soap_internal, &bson, CWS_CONST_BSON_KEY(#alias), objectParent##_sequence->objectName, 0);

// #define READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME(objectParent, objectName, typeName)
//  READ_OBJECT_1411_OR_ELSE_GOTO_RESUME(thisDocument, objectParent##_sequence_, objectName, typeName)

#define READ_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(bson, objectParent, objectName, typeName) \
  if (bson_read_array_of_##typeName##1411(soap_internal, bson, CWS_CONST_BSON_KEY(#objectName), objectParent->__size##objectName ,objectParent->objectName)) \
    goto bson_read_##objectParent##1411_resume1;

#define READ_O_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(objectParent, objectName, typeName) \
  READ_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(thisDocument, objectParent, objectName, typeName)

#define READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(objectParent, objectName, typeName) \
  READ_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(objectParent, objectName, typeName)

#define READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_D(objectParent, objectName, typeName) \
  READ_OBJECT_1411_OR_ELSE_GOTO_RESUME_D(objectParent, objectName, typeName)

#define READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(objectParent, objectName, typeName)\
  READ_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(objectParent, objectName, typeName)

#define READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B1(objectParent, objectName, typeName, suffix)\
  READ_OBJECT_1411_OR_ELSE_GOTO_RESUME_BX(objectParent, objectName, typeName, suffix)

#define READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B1 READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B1

//#define READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_C1 READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B1
#define READ_O_OBJECT_1411_VOID_C1 READ_OBJECT_1411_VOID_CX

#define READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_C READ_OBJECT_1411_OR_ELSE_GOTO_RESUME_C

#define READ_O_OBJECT_1411_VOID_C READ_OBJECT_1411_VOID_C

#define READ_O_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(objectParent, objectName, typeName) \
  if (bson_read_array_of_##typeName##1411(soap_internal, &bson, CWS_CONST_BSON_KEY(#objectName), objectParent##_sequence->__size##objectName,\
    objectParent##_sequence->objectName)) \
    goto bson_read_##objectParent##1411_resume1;

#define READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B READ_O_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B

#define READ_O_ARRAY_OF_OBJECT_1411_VOID_B(objectParent, objectName, typeName) \
  bson_read_array_of_##typeName##1411(soap_internal, &bson, CWS_CONST_BSON_KEY(#objectName), objectParent##_sequence->__size##objectName,\
    objectParent##_sequence->objectName);

#define READ_A_ARRAY_OF_OBJECT_1411_VOID_B READ_O_ARRAY_OF_OBJECT_1411_VOID_B

#define READ_O_ARRAY_OF_OBJECT_1411_VOID_D(objectParent, objectName, typeName) \
  bson_read_array_of_##typeName##1411(soap_internal, &bson, CWS_CONST_BSON_KEY(#objectName), objectParent##_sequence_->__size##objectName,\
    objectParent##_sequence_->objectName);

#define READ_S_ARRAY_OF_OBJECT_1411_VOID(objectParent, objectName, typeName) \
  bson_read_array_of_##typeName##1411(soap_internal, thisDocument, CWS_CONST_BSON_KEY(#objectName), objectParent##_sequence_->__size##objectName,\
    objectParent##_sequence_->objectName);

#define READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(objectParent, objectName, typeName) \
  READ_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(thisDocument, objectParent##_sequence_, objectName, typeName)

#define READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(objectParent, objectName) \
  if ((objectParent->objectName)&&(!bson_append_time_t(&bson, CWS_CONST_BSON_KEY(#objectName), *(objectParent->objectName)))) { \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #objectName " of " #objectParent " object") \
    goto bson_read_##objectParent##1411_resume1; \
  }

#define READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(objectParent, objectName) \
  if ((objectParent##_sequence_->objectName)&&(!bson_append_time_t(thisDocument, CWS_CONST_BSON_KEY(#objectName), *(objectParent##_sequence_->objectName)))) { \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #objectName " of " #objectParent " object") \
    goto bson_read_##objectParent##_sequence_1411_resume1; \
  }

#define READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(objectParent, objectName) \
  if ((objectParent##_sequence->objectName)&&(!bson_append_time_t(&bson, CWS_CONST_BSON_KEY(#objectName), *(objectParent##_sequence->objectName)))) { \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #objectName " of " #objectParent " object") \
    goto bson_read_##objectParent##1411_resume1; \
  }

#define READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_C(objectParent, objectName, suffix) \
  if ((__##objectParent##_sequence##suffix->objectName)&&(!bson_append_time_t(bson, CWS_CONST_BSON_KEY(#objectName),\
    *(__##objectParent##_sequence##suffix->objectName)))) { \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #objectName " of " #objectParent " object") \
    goto bson_read_##objectParent##_sequence##suffix##1411_resume1; \
  }

#define READ_O_TIME_NULLABLE_1411_VOID_C(objectParent, objectName, suffix) \
  if ((__##objectParent##_sequence##suffix->objectName)&&(!bson_append_time_t(bson, CWS_CONST_BSON_KEY(#objectName),\
    *(__##objectParent##_sequence##suffix->objectName))))\
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #objectName " of " #objectParent " object")

#define READ_O_TIME_NULLABLE_1411_VOID_B(objectParent, objectName) \
  if ((objectParent##_sequence->objectName)&&(!bson_append_time_t(&bson, CWS_CONST_BSON_KEY(#objectName), *(objectParent##_sequence->objectName))))\
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #objectName " of " #objectParent " object")

#define READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_D(objectParent, objectName) \
  if ((objectParent##_sequence_->objectName)&&(!bson_append_time_t(&bson, CWS_CONST_BSON_KEY(#objectName), *(objectParent##_sequence_->objectName)))) { \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read " #objectName " of " #objectParent " object") \
    goto bson_read_##objectParent##1411_resume1; \
  }

#define READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B

#define READ_O_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(objectParent, objectName) \
  if ((objectParent##_sequence->objectName!=NULL)&&(!bson_append_int32(&bson, CWS_CONST_BSON_KEY(#objectName), (int32_t)*(objectParent##_sequence->objectName)))) { \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read short value " #objectName " of " #objectParent " object") \
    goto bson_read_##objectParent##1411_resume1; \
  }

#define READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B READ_O_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B

#define READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(objectParent, objectName) \
  if ((objectParent##_sequence_->objectName!=NULL)&&(!bson_append_int32(thisDocument, CWS_CONST_BSON_KEY(#objectName),\
    (int32_t)*(objectParent##_sequence_->objectName)))) { \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read short value " #objectName " of " #objectParent " object") \
    goto bson_read_##objectParent##_sequence_1411_resume1; \
  }

#define READ_S_INT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(objectParent, objectName) \
  if ((objectParent##_sequence_->objectName!=NULL)&&(!bson_append_int32(thisDocument, CWS_CONST_BSON_KEY(#objectName),\
    (int32_t)*(objectParent##_sequence_->objectName)))) { \
    CWS_SET_SOAP_FAULT(#objectParent "(READ). Could not read int value " #objectName " of " #objectParent " object") \
    goto bson_read_##objectParent##_sequence_1411_resume1; \
  }

#define READ_S_ARRAY_OF_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(objectParent, objectName, type)\
  if (bson_read_array_of_##type##_enum_nullable1411(soap_internal, thisDocument, CWS_CONST_BSON_KEY(#objectName),\
    objectParent##_sequence_->__size##objectName, objectParent##_sequence_->objectName))\
    goto bson_read_##objectParent##_sequence_1411_resume1;

#define READ_A_ARRAY_OF_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(objectParent, objectName, type)\
  if (bson_read_array_of_##type##_enum_nullable1411(soap_internal, &bson, CWS_CONST_BSON_KEY(#objectName),\
    objectParent##_sequence->__size##objectName, objectParent##_sequence->objectName))\
    goto bson_read_##objectParent##1411_resume1;

// ATTRIBUTES
//Multiple attributes for
#define READ_PUT_MULTIPLE_ATTRIBUTES_TYPED_1411_OR_ELSE_GOTO_RESUME(objectParent, ...) \
  if (bson_put_multiple_attributes_if_they_exist_typed(&bson, __VA_ARGS__)) {\
    CWS_SET_SOAP_FAULT(#objectParent "(READ)->#attributes. Could not set #attributes")\
    goto bson_read_##objectParent##1411_resume1;\
  }

#define READ_A_PUT_MULTIPLE_ATTRIBUTES_TYPED_1411_OR_ELSE_GOTO_RESUME(objectParent, ...) \
  READ_PUT_MULTIPLE_ATTRIBUTES_TYPED_1411_OR_ELSE_GOTO_RESUME(objectParent, __VA_ARGS__)

#define READ_O_PUT_MULTIPLE_ATTRIBUTES_TYPED_1411_OR_ELSE_GOTO_RESUME READ_A_PUT_MULTIPLE_ATTRIBUTES_TYPED_1411_OR_ELSE_GOTO_RESUME


#define BSON_READ_ARRAY_OF_OBJECT_ENUM_NULLABLE_1411_BUILDER(type) \
static int bson_read_array_of_##type##_enum_nullable1411(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  const char *key, size_t key_len,\
  int numberOfElements,\
  enum rd1witsml__##type *type\
)\
{\
  int n;\
  bson_t thisArray;\
  IdxType index_str_buf;\
  idx2str_fn indexer;\
  const char *index_str_key;\
  size_t index_str_key_len;\
\
  if (numberOfElements < 1)\
    return SOAP_OK;\
\
  if (!bson_append_array_begin(thisDocument, key, (int)key_len, &thisArray)) {\
    CWS_SET_SOAP_FAULT(#type "(READ). BEGIN ARRAY ENUM NULLABLE. Error")\
    return SOAP_FAULT;\
  }\
\
  n=0;\
  indexer=init_indexer(numberOfElements, index_str_buf);\
\
  do {\
    index_str_key_len=indexer((uint32_t)n, &index_str_key, index_str_buf);\
    if ((type!=NULL)&&(!bson_append_utf8(&thisArray, index_str_key, (int)index_str_key_len,\
      (const char *)soap_rd1witsml__##type##2s(soap_internal, *(type)), -1))) { \
      CWS_SET_SOAP_FAULT(#type "(READ). Could not read array of enum nullable ") \
      break;\
    }\
\
    type++;\
  } while (numberOfElements > (++n));\
\
  if (!bson_append_array_end(thisDocument, &thisArray))\
    CWS_SET_SOAP_FAULT(#type "(READ). END ARRAY ENUM NULLABLE Error")\
\
  CWS_RETURN(soap_internal)\
}

// BUILDER
#define BSON_READ_ARRAY_OF_OBJECT_1411_BEGIN(type) \
static int bson_read_##type##1411(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  const char *key, size_t key_len,\
  struct rd1witsml__##type *type,\
  int addIfEmpty\
)\
{\
  bson_t bson;\
\
  if ((addIfEmpty==0)&&(type==NULL))\
    return SOAP_OK;\
\
  if (!bson_append_document_begin(thisDocument, key, (int)key_len, &bson)) {\
    CWS_SET_SOAP_FAULT(#type "(READ). Could not BEGIN document in BSON")\
    return SOAP_FAULT;\
  }\
\
  if (!type)\
    goto bson_read_##type##1411_resume1;

#define BSON_READ_ARRAY_OF_OBJECT_1411_END(type)\
bson_read_##type##1411_resume1:\
  if (!bson_append_document_end(thisDocument, &bson))\
    CWS_SET_SOAP_FAULT(#type "(READ). Could not END document in BSON");\
\
  CWS_RETURN(soap_internal)\
}\
\
static int bson_read_array_of_##type##1411(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  const char *key, size_t key_len,\
  int numberOfElements,\
  struct rd1witsml__##type *type\
)\
{\
  int n;\
  bson_t thisArray;\
  IdxType index_str_buf;\
  idx2str_fn indexer;\
  const char *index_str_key;\
  size_t index_str_key_len;\
\
  if (numberOfElements < 1)\
    return SOAP_OK;\
\
  if (!bson_append_array_begin(thisDocument, key, (int)key_len, &thisArray)) {\
    CWS_SET_SOAP_FAULT(#type "(READ). BEGIN ARRAY. Error")\
    return SOAP_FAULT;\
  }\
\
  n=0;\
  indexer=init_indexer(numberOfElements, index_str_buf);\
\
  do {\
    index_str_key_len=indexer((uint32_t)n, &index_str_key, index_str_buf);\
    if (bson_read_##type##1411(soap_internal, &thisArray, index_str_key, index_str_key_len, type++, -1))\
      break;\
  } while (numberOfElements > (++n));\
\
  if (!bson_append_array_end(thisDocument, &thisArray))\
    CWS_SET_SOAP_FAULT(#type "(READ). END ARRAY Error")\
\
  CWS_RETURN(soap_internal)\
}

/////
#define BSON_READ_ARRAY_OF_OBJECT_1411_BEGIN_B(type) \
static int bson_read_##type##1411(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  const char *key, size_t key_len,\
  struct rd1witsml__##type *type,\
  int addIfEmpty\
)\
{\
  bson_t bson;\
  struct __rd1witsml__##type##_sequence *type##_sequence;\
\
  if (type)\
    type##_sequence=type->__##type##_sequence;\
  else\
    type##_sequence=NULL;\
\
  if ((addIfEmpty==0)&&(type==NULL)&&(type##_sequence==NULL))\
    return SOAP_FAULT;\
\
  if (!bson_append_document_begin(thisDocument, key, (int)key_len, &bson)) {\
    CWS_SET_SOAP_FAULT(#type "(READ). Could not BEGIN document in BSON")\
    return SOAP_FAULT;\
  }\
\
  if (!type)\
    goto bson_read_##type##1411_resume1;\
\
  if (!type##_sequence)\
    goto bson_read_##type##1411_resume1;

#define BSON_READ_ARRAY_OF_OBJECT_1411_END_B(type)\
bson_read_##type##1411_resume1:\
  if (!bson_append_document_end(thisDocument, &bson))\
    CWS_SET_SOAP_FAULT(#type "(READ). Could not END document in BSON");\
\
  CWS_RETURN(soap_internal)\
}\
\
static int bson_read_array_of_##type##1411(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  const char *key, size_t key_len,\
  int numberOfElements,\
  struct rd1witsml__##type *type\
)\
{\
  int n;\
  bson_t thisArray;\
  IdxType index_str_buf;\
  idx2str_fn indexer;\
  const char *index_str_key;\
  size_t index_str_key_len;\
\
  if (numberOfElements < 1)\
    return SOAP_OK;\
\
  if (!bson_append_array_begin(thisDocument, key, (int)key_len, &thisArray)) {\
    CWS_SET_SOAP_FAULT(#type "(READ). BEGIN ARRAY. Error")\
    return SOAP_FAULT;\
  }\
\
  n=0;\
  indexer=init_indexer(numberOfElements, index_str_buf);\
\
  do {\
    index_str_key_len=indexer((uint32_t)n, &index_str_key, index_str_buf);\
    if (bson_read_##type##1411(soap_internal, &thisArray, index_str_key, index_str_key_len, type++, -1))\
      break;\
  } while (numberOfElements > (++n));\
\
  if (!bson_append_array_end(thisDocument, &thisArray))\
    CWS_SET_SOAP_FAULT(#type "(READ). END ARRAY Error")\
\
  CWS_RETURN(soap_internal)\
}

////

#define BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(type) \
static int bson_read_##type##1411(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  const char *key, size_t key_len,\
  struct rd1witsml__##type *type,\
  int addIfEmpty\
)\
{\
  bson_t bson;\
  struct __rd1witsml__##type##_sequence *type##_sequence;\
\
  if ((addIfEmpty==0)&&(type==NULL))\
    return SOAP_OK;\
\
  if (!bson_append_document_begin(thisDocument, key, (int)key_len, &bson)) {\
    CWS_SET_SOAP_FAULT(#type "(READ). Could not BEGIN document in BSON")\
    return SOAP_FAULT;\
  }\
\
  if (!type)\
    goto bson_read_##type##1411_resume1;\
\
  if (bson_put_single_attribute_if_exists(&bson, CWS_CONST_BSON_KEY("uid"), type->uid, -1)) {\
    CWS_SET_SOAP_FAULT(#type "(READ). Could not set \"uid\" attribute to #attribute") \
    goto bson_read_##type##1411_resume1; \
  }\
\
  if (!(type##_sequence=type->__##type##_sequence))\
    goto bson_read_##type##1411_resume1;

#define BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(type)\
bson_read_##type##1411_resume1:\
  if (!bson_append_document_end(thisDocument, &bson))\
    CWS_SET_SOAP_FAULT(#type "(READ). Could not END document in BSON");\
\
  CWS_RETURN(soap_internal)\
}\
\
static int bson_read_array_of_##type##1411(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  const char *key, size_t key_len,\
  int numberOfElements,\
  struct rd1witsml__##type *type\
)\
{\
  int n;\
  bson_t thisArray;\
  IdxType index_str_buf;\
  idx2str_fn indexer;\
  const char *index_str_key;\
  size_t index_str_key_len;\
\
  if (numberOfElements < 1)\
    return SOAP_OK;\
\
  if (!bson_append_array_begin(thisDocument, key, (int)key_len, &thisArray)) {\
    CWS_SET_SOAP_FAULT(#type "(READ). BEGIN ARRAY. Error")\
    return SOAP_FAULT;\
  }\
\
  n=0;\
  indexer=init_indexer(numberOfElements, index_str_buf);\
\
  do {\
    index_str_key_len=indexer((uint32_t)n, &index_str_key, index_str_buf);\
    if (bson_read_##type##1411(soap_internal, &thisArray, index_str_key, index_str_key_len, type++, -1))\
      break;\
  } while (numberOfElements > (++n));\
\
  if (!bson_append_array_end(thisDocument, &thisArray))\
    CWS_SET_SOAP_FAULT(#type "(READ). END ARRAY Error")\
\
  CWS_RETURN(soap_internal)\
}

#define BSON_READ_OBJECT_1411_BEGIN(type)\
static int bson_read_##type##1411(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  const char *key, size_t key_len,\
  struct rd1witsml__##type *type,\
  int addIfEmpty\
)\
{\
  bson_t bson;\
\
  if ((addIfEmpty==0)&&(type==NULL))\
    return SOAP_OK;\
\
  if (!bson_append_document_begin(thisDocument, key, (int)key_len, &bson)) {\
    cws_set_soap_fault_util(soap_internal, -1234, CWS_FAULTSTR(#type "(READ). Could not BEGIN document in BSON"), -1);\
    return SOAP_FAULT;\
  }\
\
  if (!type)\
    goto bson_read_##type##1411_resume1;

#define BSON_READ_OBJECT_1411_END(type)\
bson_read_##type##1411_resume1:\
  if (!bson_append_document_end(thisDocument, &bson))\
    cws_set_soap_fault_util(soap_internal, -1234, CWS_FAULTSTR(#type "(READ). Could not END document in BSON"), -1);\
\
  CWS_RETURN(soap_internal)\
}

#define BSON_READ_OBJECT_1411_BEGIN_B(type)\
static int bson_read_##type##1411(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  const char *key, size_t key_len,\
  struct rd1witsml__##type *type,\
  int addIfEmpty\
)\
{\
  bson_t bson;\
  struct __rd1witsml__##type##_sequence *type##_sequence;\
\
  if (type)\
    type##_sequence=type->__##type##_sequence;\
  else\
    type##_sequence=NULL;\
\
  if ((addIfEmpty==0)&&(type==NULL)&&(type##_sequence==NULL))\
    return SOAP_OK;\
\
  if (!bson_append_document_begin(thisDocument, key, (int)key_len, &bson)) {\
    CWS_SET_SOAP_FAULT(#type "(READ). Could not BEGIN document in BSON")\
    return SOAP_FAULT;\
  }\
\
  if (!type)\
    goto bson_read_##type##1411_resume1;\
\
  if (!type##_sequence)\
    goto bson_read_##type##1411_resume1;

#define BSON_READ_OBJECT_1411_END_B(type)\
bson_read_##type##1411_resume1:\
  if (!bson_append_document_end(thisDocument, &bson))\
    CWS_SET_SOAP_FAULT(#type "(READ). Could not END document in BSON");\
\
  CWS_RETURN(soap_internal)\
}

#define BSON_READ_OBJECT_1411_BEGIN_C(type, suffix)\
static int bson_read_##type##_sequence##suffix##1411(\
  struct soap *soap_internal,\
  bson_t *bson,\
  struct __rd1witsml__##type##_sequence##suffix *__##type##_sequence##suffix\
)\
{\
\
  if (!__##type##_sequence##suffix)\
    return SOAP_OK;

#define BSON_READ_OBJECT_1411_END_C(type, suffix)\
bson_read_##type##_sequence##suffix##1411_resume1:\
  CWS_RETURN(soap_internal)\
}

#define BSON_READ_OBJECT_1411_END_C_(type)\
  CWS_RETURN(soap_internal)\
}

#define BSON_READ_OBJECT_1411_BEGIN_D(type)\
static int bson_read_##type##1411(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  const char *key, size_t key_len,\
  struct rd1witsml__##type *type,\
  int addIfEmpty\
)\
{\
  bson_t bson;\
  struct __rd1witsml__##type##_sequence *type##_sequence;\
  struct __rd1witsml__##type##_sequence_ *type##_sequence_;\
\
  if (type) {\
    if ((type##_sequence=type->__##type##_sequence))\
      type##_sequence_=type##_sequence->__##type##_sequence_;\
    else\
      type##_sequence_=NULL;\
  } else {\
    type##_sequence=NULL;\
    type##_sequence_=NULL;\
  }\
\
  if ((addIfEmpty==0)&&(type==NULL)&&(type##_sequence==NULL)&&(type##_sequence_==NULL))\
    return SOAP_OK;\
\
  if (!bson_append_document_begin(thisDocument, key, (int)key_len, &bson)) {\
    CWS_SET_SOAP_FAULT(#type "(READ). Could not BEGIN document in BSON")\
    return SOAP_FAULT;\
  }\
\
  if (!type)\
    goto bson_read_##type##1411_resume1;\
\
  if (!type##_sequence)\
    goto bson_read_##type##1411_resume1;\
\
  if (!type##_sequence_)\
    goto bson_read_##type##1411_resume1;

#define BSON_READ_OBJECT_1411_END_D(type)\
bson_read_##type##1411_resume1:\
  if (!bson_append_document_end(thisDocument, &bson))\
    CWS_SET_SOAP_FAULT(#type "(READ). Could not END document in BSON");\
\
  CWS_RETURN(soap_internal)\
}

// PUBLIC OBJECT SEQUENCE BUILDER
#define READ_S_OBJECT_1411_BEGIN(rootObject)\
static int bson_read_##rootObject##_sequence_1411(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  struct __rd1witsml__obj_USCORE##rootObject##_sequence_ *rootObject##_sequence_\
)\
{\
  if (!rootObject##_sequence_)\
    return SOAP_OK;

#define READ_S_OBJECT_1411_END(rootObject)\
bson_read_##rootObject##_sequence_1411_resume1:\
  CWS_RETURN(soap_internal)\
}\
\
static int bson_read_##rootObject##1411_array(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  const char *key, int key_len,\
  struct rd1witsml__obj_USCORE##rootObject *rootObject\
)\
{\
  bson_t bson;\
  struct __rd1witsml__obj_USCORE##rootObject##_sequence *rootObject##_sequence;\
\
  if (!bson_append_document_begin(thisDocument, key, key_len, &bson)) {\
    CWS_SET_SOAP_FAULT(#rootObject "(READ)->ObjectArray(attachment). Could not BEGIN document in BSON Array")\
    return SOAP_FAULT;\
  }\
\
  if (!rootObject)\
    goto bson_read_##rootObject##1411_array_resume1;\
\
  if (!(rootObject##_sequence=rootObject->__obj_USCORE##rootObject##_sequence))\
    goto bson_read_##rootObject##1411_array_resume1;\
\
  if (bson_put_multiple_attributes_if_they_exist(&bson,\
    SET_MULTIPLE_ATTRIBUTES(\
      CWS_CONST_VALUE("uidWell"), rootObject->uidWell,\
      CWS_CONST_VALUE("uidWellbore"), rootObject->uidWellbore,\
      CWS_CONST_VALUE("uid"), rootObject->uid\
    )\
  )) {\
    CWS_SET_SOAP_FAULT(#rootObject "s(READ)->ObjectArray->#attributes. Could not set #attributes")\
    goto bson_read_##rootObject##1411_array_resume1;\
  }\
\
  READ_W_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rootObject, nameWell)\
  READ_W_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rootObject, nameWellbore)\
  READ_W_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rootObject, name)\
\
  if (bson_read_##rootObject##_sequence_1411(soap_internal, &bson, rootObject##_sequence->__obj_USCORE##rootObject##_sequence_))\
    goto bson_read_##rootObject##1411_array_resume1;\
\
  if (bson_read_cs_USCOREcommonData1411(soap_internal, &bson, CWS_CONST_BSON_KEY("commonData"), rootObject##_sequence->commonData, 0))\
    goto bson_read_##rootObject##1411_array_resume1;\
\
  bson_read_cs_USCOREcustomData1411(soap_internal, &bson, CWS_CONST_BSON_KEY("customData"), rootObject##_sequence->customData, 0);\
\
bson_read_##rootObject##1411_array_resume1:\
  if (!bson_append_document_end(thisDocument, &bson))\
    CWS_SET_SOAP_FAULT(#rootObject "s(READ)->ObjectArray. Could not END document in BSON Array")\
\
  CWS_RETURN(soap_internal)\
}\
\
int bson_read_##rootObject##s1411(struct soap *soap_internal)\
{\
  DECLARE_CONFIG(soap_internal)\
  struct rd1witsml__obj_USCORE##rootObject##s *rootObject##s;\
  struct __rd1witsml__obj_USCORE##rootObject##s_sequence *rootObject##s_sequence;\
  struct rd1witsml__obj_USCORE##rootObject *rootObject;\
  IdxType index_str_buf;\
  const char *index_str_key;\
  size_t index_str_key_len;\
  idx2str_fn indexer;\
  bson_t\
    bson,\
    thisArray;\
\
  int n;\
\
  if ((rootObject##s=((struct rd1411__readObj1411_USCOREt *)config->witsmlObject)->rootObject##s)==NULL) {\
    CWS_SET_SOAP_FAULT("Error " #rootObject "s object is NULL")\
    return SOAP_FAULT;\
  }\
\
  if (((config->flag&CWS_FLAG_CHECK_VERSION_DISABLE)==0) && (check_client_schema_version(soap_internal, rootObject##s->version)==NULL)) {\
    cws_set_base_msg14x(soap_internal, -468);\
    return SOAP_OK;\
  }\
\
  CWS_CONSTRUCT_BSON(rootObject##s)\
\
  if (!bson_append_document_begin(config->object, CWS_CONST_VALUE(#rootObject "s"), &bson)) {\
    CWS_SET_SOAP_FAULT(#rootObject "s(READ). BEGIN: Could not append document in BSON")\
    return SOAP_FAULT;\
  }\
\
  if (bson_put_single_attribute_if_exists(&bson, CWS_CONST_BSON_KEY("version"), rootObject##s->version, -1)) {\
    CWS_SET_SOAP_FAULT(#rootObject "s(READ). Could not set version attribute")\
    goto  bson_read_##rootObject##s1411_resume1;\
  }\
\
  if (!(rootObject##s_sequence=rootObject##s->__obj_USCORE##rootObject##s_sequence))\
    goto bson_read_##rootObject##s1411_resume1;\
\
  if (bson_read_cs_USCOREdocumentInfo1411(soap_internal, &bson, CWS_CONST_BSON_KEY("documentInfo"), rootObject##s_sequence->documentInfo, 0))\
    goto bson_read_##rootObject##s1411_resume1;\
\
  if (rootObject##s_sequence->__size##rootObject < 1)\
    goto bson_read_##rootObject##s1411_resume1;\
\
  n=0;\
  rootObject=rootObject##s_sequence->rootObject;\
\
  indexer=init_indexer(rootObject##s_sequence->__size##rootObject, index_str_buf);\
\
  if (!bson_append_array_begin(&bson, CWS_CONST_BSON_KEY(#rootObject), &thisArray)) {\
    CWS_SET_SOAP_FAULT(#rootObject "(READ). BEGIN ARRAY. Error")\
    goto bson_read_##rootObject##s1411_resume1;\
  }\
\
  do {\
    index_str_key_len=indexer((uint32_t)n, &index_str_key, index_str_buf);\
    if (bson_read_##rootObject##1411_array(soap_internal, &thisArray, index_str_key, (int)index_str_key_len, rootObject++))\
      break;\
  } while (rootObject##s_sequence->__size##rootObject > (++n));\
\
  if (!bson_append_array_end(&bson, &thisArray))\
    CWS_SET_SOAP_FAULT(#rootObject "(READ). END ARRAY Error")\
\
bson_read_##rootObject##s1411_resume1:\
  if (!bson_append_document_end(config->object, &bson))\
    CWS_SET_SOAP_FAULT(#rootObject "s(READ). END: Could not end document in " #rootObject "s")\
\
  CWS_RETURN(soap_internal)\
}

#define READ_S_OBJECT_1411_BEGIN_C(rootObject)\
static int bson_read_##rootObject##_sequence_1411(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  struct __rd1witsml__obj_USCORE##rootObject##_sequence_ *rootObject##_sequence_\
)\
{\
  if (!rootObject##_sequence_)\
    return SOAP_OK;

#define READ_S_OBJECT_1411_END_C(rootObject)\
bson_read_##rootObject##_sequence_1411_resume1:\
  CWS_RETURN(soap_internal)\
}\
\
static int bson_read_##rootObject##1411_array(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  const char *key, int key_len,\
  struct rd1witsml__obj_USCORE##rootObject *rootObject\
)\
{\
  bson_t bson;\
  struct __rd1witsml__obj_USCORE##rootObject##_sequence *rootObject##_sequence;\
\
  if (!bson_append_document_begin(thisDocument, key, key_len, &bson)) {\
    CWS_SET_SOAP_FAULT(#rootObject "(READ)->ObjectArray(attachment). Could not BEGIN document in BSON Array")\
    return SOAP_FAULT;\
  }\
\
  if (!rootObject)\
    goto bson_read_##rootObject##1411_array_resume1;\
\
  if (!(rootObject##_sequence=rootObject->__obj_USCORE##rootObject##_sequence))\
    goto bson_read_##rootObject##1411_array_resume1;\
\
  if (bson_put_multiple_attributes_if_they_exist(&bson,\
    SET_MULTIPLE_ATTRIBUTES(\
      CWS_CONST_VALUE("uidWell"), rootObject->uidWell,\
      CWS_CONST_VALUE("uidWellbore"), rootObject->uidWellbore,\
      CWS_CONST_VALUE("uidObject"), rootObject->uidObject,\
      CWS_CONST_VALUE("uid"), rootObject->uid\
    )\
  )) {\
    CWS_SET_SOAP_FAULT(#rootObject "s(READ)->ObjectArray->#attributes. Could not set #attributes")\
    goto bson_read_##rootObject##1411_array_resume1;\
  }\
\
  READ_W_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rootObject, nameWell)\
  READ_W_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rootObject, nameWellbore)\
  READ_W_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rootObject, nameObject)\
  READ_W_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rootObject, objectType)\
\
  if (bson_read_##rootObject##_sequence_1411(soap_internal, &bson, rootObject##_sequence->__obj_USCORE##rootObject##_sequence_))\
    goto bson_read_##rootObject##1411_array_resume1;\
\
  if (bson_read_cs_USCOREcommonData1411(soap_internal, &bson, CWS_CONST_BSON_KEY("commonData"), rootObject##_sequence->commonData, 0))\
    goto bson_read_##rootObject##1411_array_resume1;\
\
  bson_read_cs_USCOREcustomData1411(soap_internal, &bson, CWS_CONST_BSON_KEY("customData"), rootObject##_sequence->customData, 0);\
\
bson_read_##rootObject##1411_array_resume1:\
  if (!bson_append_document_end(thisDocument, &bson))\
    CWS_SET_SOAP_FAULT(#rootObject "s(READ)->ObjectArray. Could not END document in BSON Array")\
\
  CWS_RETURN(soap_internal)\
}\
\
int bson_read_##rootObject##s1411(struct soap *soap_internal)\
{\
  DECLARE_CONFIG(soap_internal)\
  struct rd1witsml__obj_USCORE##rootObject##s *rootObject##s;\
  struct __rd1witsml__obj_USCORE##rootObject##s_sequence *rootObject##s_sequence;\
  struct rd1witsml__obj_USCORE##rootObject *rootObject;\
  IdxType index_str_buf;\
  const char *index_str_key;\
  size_t index_str_key_len;\
  idx2str_fn indexer;\
  bson_t\
    bson,\
    thisArray;\
\
  int n;\
\
  if ((rootObject##s=((struct rd1411__readObj1411_USCOREt *)config->witsmlObject)->rootObject##s)==NULL) {\
    CWS_SET_SOAP_FAULT("Error " #rootObject "s object is NULL")\
    return SOAP_FAULT;\
  }\
\
  if (((config->flag&CWS_FLAG_CHECK_VERSION_DISABLE)==0) && (check_client_schema_version(soap_internal, rootObject##s->version)==NULL)) {\
    cws_set_base_msg14x(soap_internal, -468);\
    return SOAP_OK;\
  }\
\
  CWS_CONSTRUCT_BSON(rootObject##s)\
\
  if (!bson_append_document_begin(config->object, CWS_CONST_VALUE(#rootObject "s"), &bson)) {\
    CWS_SET_SOAP_FAULT(#rootObject "s(READ). BEGIN: Could not append document in BSON")\
    return SOAP_FAULT;\
  }\
\
  if (bson_put_single_attribute_if_exists(&bson, CWS_CONST_BSON_KEY("version"), rootObject##s->version, -1)) {\
    CWS_SET_SOAP_FAULT(#rootObject "s(READ). Could not set version attribute")\
    goto  bson_read_##rootObject##s1411_resume1;\
  }\
\
  if (!(rootObject##s_sequence=rootObject##s->__obj_USCORE##rootObject##s_sequence))\
    goto bson_read_##rootObject##s1411_resume1;\
\
  if (bson_read_cs_USCOREdocumentInfo1411(soap_internal, &bson, CWS_CONST_BSON_KEY("documentInfo"), rootObject##s_sequence->documentInfo, 0))\
    goto bson_read_##rootObject##s1411_resume1;\
\
  if (rootObject##s_sequence->__size##rootObject < 1)\
    goto bson_read_##rootObject##s1411_resume1;\
\
  n=0;\
  rootObject=rootObject##s_sequence->rootObject;\
\
  indexer=init_indexer(rootObject##s_sequence->__size##rootObject, index_str_buf);\
\
  if (!bson_append_array_begin(&bson, CWS_CONST_BSON_KEY(#rootObject), &thisArray)) {\
    CWS_SET_SOAP_FAULT(#rootObject "(READ). BEGIN ARRAY. Error")\
    goto bson_read_##rootObject##s1411_resume1;\
  }\
\
  do {\
    index_str_key_len=indexer((uint32_t)n, &index_str_key, index_str_buf);\
    if (bson_read_##rootObject##1411_array(soap_internal, &thisArray, index_str_key, (int)index_str_key_len, rootObject++))\
      break;\
  } while (rootObject##s_sequence->__size##rootObject > (++n));\
\
  if (!bson_append_array_end(&bson, &thisArray))\
    CWS_SET_SOAP_FAULT(#rootObject "(READ). END ARRAY Error")\
\
bson_read_##rootObject##s1411_resume1:\
  if (!bson_append_document_end(config->object, &bson))\
    CWS_SET_SOAP_FAULT(#rootObject "s(READ). END: Could not end document in " #rootObject "s")\
\
  CWS_RETURN(soap_internal)\
}

#define READ_S_OBJECT_1411_BEGIN_B(rootObject)\
static int bson_read_##rootObject##_sequence_1411(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  struct __rd1witsml__obj_USCORE##rootObject##_sequence_ *rootObject##_sequence_\
)\
{\
  if (!rootObject##_sequence_)\
    return SOAP_OK;

#define READ_S_OBJECT_1411_END_B(rootObject)\
bson_read_##rootObject##_sequence_1411_resume1:\
  CWS_RETURN(soap_internal)\
}\
\
static int bson_read_##rootObject##1411_array(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  const char *key, int key_len,\
  struct rd1witsml__obj_USCORE##rootObject *rootObject\
)\
{\
  bson_t bson;\
  struct __rd1witsml__obj_USCORE##rootObject##_sequence *rootObject##_sequence;\
\
  if (!bson_append_document_begin(thisDocument, key, key_len, &bson)) {\
    CWS_SET_SOAP_FAULT(#rootObject "(READ)->ObjectArray(attachment). Could not BEGIN document in BSON Array")\
    return SOAP_FAULT;\
  }\
\
  if (!rootObject)\
    goto bson_read_##rootObject##1411_array_resume1;\
\
  if (!(rootObject##_sequence=rootObject->__obj_USCORE##rootObject##_sequence))\
    goto bson_read_##rootObject##1411_array_resume1;\
\
  if (bson_put_multiple_attributes_if_they_exist(&bson,\
    SET_MULTIPLE_ATTRIBUTES(\
      CWS_CONST_VALUE("uidWell"), rootObject->uidWell,\
      CWS_CONST_VALUE("uid"), rootObject->uid\
    )\
  )) {\
    CWS_SET_SOAP_FAULT(#rootObject "s(READ)->ObjectArray->#attributes. Could not set #attributes")\
    goto bson_read_##rootObject##1411_array_resume1;\
  }\
\
  READ_W_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rootObject, nameWell)\
  READ_W_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rootObject, name)\
\
  if (bson_read_##rootObject##_sequence_1411(soap_internal, &bson, rootObject##_sequence->__obj_USCORE##rootObject##_sequence_))\
    goto bson_read_##rootObject##1411_array_resume1;\
\
  if (bson_read_cs_USCOREcommonData1411(soap_internal, &bson, CWS_CONST_BSON_KEY("commonData"), rootObject##_sequence->commonData, 0))\
    goto bson_read_##rootObject##1411_array_resume1;\
\
  bson_read_cs_USCOREcustomData1411(soap_internal, &bson, CWS_CONST_BSON_KEY("customData"), rootObject##_sequence->customData, 0);\
\
bson_read_##rootObject##1411_array_resume1:\
  if (!bson_append_document_end(thisDocument, &bson))\
    CWS_SET_SOAP_FAULT(#rootObject "s(READ)->ObjectArray. Could not END document in BSON Array")\
\
  CWS_RETURN(soap_internal)\
}\
\
int bson_read_##rootObject##s1411(struct soap *soap_internal)\
{\
  DECLARE_CONFIG(soap_internal)\
  struct rd1witsml__obj_USCORE##rootObject##s *rootObject##s;\
  struct __rd1witsml__obj_USCORE##rootObject##s_sequence *rootObject##s_sequence;\
  struct rd1witsml__obj_USCORE##rootObject *rootObject;\
  IdxType index_str_buf;\
  const char *index_str_key;\
  size_t index_str_key_len;\
  idx2str_fn indexer;\
  bson_t\
    bson,\
    thisArray;\
\
  int n;\
\
  if ((rootObject##s=((struct rd1411__readObj1411_USCOREt *)config->witsmlObject)->rootObject##s)==NULL) {\
    CWS_SET_SOAP_FAULT("Error " #rootObject "s object is NULL")\
    return SOAP_FAULT;\
  }\
\
  if (((config->flag&CWS_FLAG_CHECK_VERSION_DISABLE)==0) && (check_client_schema_version(soap_internal, rootObject##s->version)==NULL)) {\
    cws_set_base_msg14x(soap_internal, -468);\
    return SOAP_OK;\
  }\
\
  CWS_CONSTRUCT_BSON(rootObject##s)\
\
  if (!bson_append_document_begin(config->object, CWS_CONST_VALUE(#rootObject "s"), &bson)) {\
    CWS_SET_SOAP_FAULT(#rootObject "s(READ). BEGIN: Could not append document in BSON")\
    return SOAP_FAULT;\
  }\
\
  if (bson_put_single_attribute_if_exists(&bson, CWS_CONST_BSON_KEY("version"), rootObject##s->version, -1)) {\
    CWS_SET_SOAP_FAULT(#rootObject "s(READ). Could not set version attribute")\
    goto  bson_read_##rootObject##s1411_resume1;\
  }\
\
  if (!(rootObject##s_sequence=rootObject##s->__obj_USCORE##rootObject##s_sequence))\
    goto bson_read_##rootObject##s1411_resume1;\
\
  if (bson_read_cs_USCOREdocumentInfo1411(soap_internal, &bson, CWS_CONST_BSON_KEY("documentInfo"), rootObject##s_sequence->documentInfo, 0))\
    goto bson_read_##rootObject##s1411_resume1;\
\
  if (rootObject##s_sequence->__size##rootObject < 1)\
    goto bson_read_##rootObject##s1411_resume1;\
\
  n=0;\
  rootObject=rootObject##s_sequence->rootObject;\
\
  indexer=init_indexer(rootObject##s_sequence->__size##rootObject, index_str_buf);\
\
  if (!bson_append_array_begin(&bson, CWS_CONST_BSON_KEY(#rootObject), &thisArray)) {\
    CWS_SET_SOAP_FAULT(#rootObject "(READ). BEGIN ARRAY. Error")\
    goto bson_read_##rootObject##s1411_resume1;\
  }\
\
  do {\
    index_str_key_len=indexer((uint32_t)n, &index_str_key, index_str_buf);\
    if (bson_read_##rootObject##1411_array(soap_internal, &thisArray, index_str_key, (int)index_str_key_len, rootObject++))\
      break;\
  } while (rootObject##s_sequence->__size##rootObject > (++n));\
\
  if (!bson_append_array_end(&bson, &thisArray))\
    CWS_SET_SOAP_FAULT(#rootObject "(READ). END ARRAY Error")\
\
bson_read_##rootObject##s1411_resume1:\
  if (!bson_append_document_end(config->object, &bson))\
    CWS_SET_SOAP_FAULT(#rootObject "s(READ). END: Could not end document in " #rootObject "s")\
\
  CWS_RETURN(soap_internal)\
}

#define READ_S_OBJECT_1411_BEGIN_A(rootObject)\
static int bson_read_##rootObject##_sequence_1411(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  struct __rd1witsml__obj_USCORE##rootObject##_sequence_ *rootObject##_sequence_\
)\
{\
  if (!rootObject##_sequence_)\
    return SOAP_OK;

#define READ_S_OBJECT_1411_END_A(rootObject)\
bson_read_##rootObject##_sequence_1411_resume1:\
  CWS_RETURN(soap_internal)\
}\
\
static int bson_read_##rootObject##1411_array(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  const char *key, int key_len,\
  struct rd1witsml__obj_USCORE##rootObject *rootObject\
)\
{\
  bson_t bson;\
  struct __rd1witsml__obj_USCORE##rootObject##_sequence *rootObject##_sequence;\
\
  if (!bson_append_document_begin(thisDocument, key, key_len, &bson)) {\
    CWS_SET_SOAP_FAULT(#rootObject "(READ)->ObjectArray(attachment). Could not BEGIN document in BSON Array")\
    return SOAP_FAULT;\
  }\
\
  if (!rootObject)\
    goto bson_read_##rootObject##1411_array_resume1;\
\
  if (!(rootObject##_sequence=rootObject->__obj_USCORE##rootObject##_sequence))\
    goto bson_read_##rootObject##1411_array_resume1;\
\
  if (bson_put_single_attribute_if_exists(&bson, CWS_CONST_VALUE("uid"), rootObject->uid, -1)) {\
    CWS_SET_SOAP_FAULT(#rootObject "s(READ)->ObjectArray->#attributes. Could not set #attributes")\
    goto bson_read_##rootObject##1411_array_resume1;\
  }\
\
  READ_W_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rootObject, name)\
\
  if (bson_read_##rootObject##_sequence_1411(soap_internal, &bson, rootObject##_sequence->__obj_USCORE##rootObject##_sequence_))\
    goto bson_read_##rootObject##1411_array_resume1;\
\
  if (bson_read_cs_USCOREcommonData1411(soap_internal, &bson, CWS_CONST_BSON_KEY("commonData"), rootObject##_sequence->commonData, 0))\
    goto bson_read_##rootObject##1411_array_resume1;\
\
  bson_read_cs_USCOREcustomData1411(soap_internal, &bson, CWS_CONST_BSON_KEY("customData"), rootObject##_sequence->customData, 0);\
\
bson_read_##rootObject##1411_array_resume1:\
  if (!bson_append_document_end(thisDocument, &bson))\
    CWS_SET_SOAP_FAULT(#rootObject "s(READ)->ObjectArray. Could not END document in BSON Array")\
\
  CWS_RETURN(soap_internal)\
}\
\
int bson_read_##rootObject##s1411(struct soap *soap_internal)\
{\
  DECLARE_CONFIG(soap_internal)\
  struct rd1witsml__obj_USCORE##rootObject##s *rootObject##s;\
  struct __rd1witsml__obj_USCORE##rootObject##s_sequence *rootObject##s_sequence;\
  struct rd1witsml__obj_USCORE##rootObject *rootObject;\
  IdxType index_str_buf;\
  const char *index_str_key;\
  size_t index_str_key_len;\
  idx2str_fn indexer;\
  bson_t\
    bson,\
    thisArray;\
\
  int n;\
\
  if ((rootObject##s=((struct rd1411__readObj1411_USCOREt *)config->witsmlObject)->rootObject##s)==NULL) {\
    CWS_SET_SOAP_FAULT("Error " #rootObject "s object is NULL")\
    return SOAP_FAULT;\
  }\
\
  if (((config->flag&CWS_FLAG_CHECK_VERSION_DISABLE)==0) && (check_client_schema_version(soap_internal, rootObject##s->version)==NULL)) {\
    cws_set_base_msg14x(soap_internal, -468);\
    return SOAP_OK;\
  }\
\
  CWS_CONSTRUCT_BSON(rootObject##s)\
\
  if (!bson_append_document_begin(config->object, CWS_CONST_VALUE(#rootObject "s"), &bson)) {\
    CWS_SET_SOAP_FAULT(#rootObject "s(READ). BEGIN: Could not append document in BSON")\
    return SOAP_FAULT;\
  }\
\
  if (bson_put_single_attribute_if_exists(&bson, CWS_CONST_BSON_KEY("version"), rootObject##s->version, -1)) {\
    CWS_SET_SOAP_FAULT(#rootObject "s(READ). Could not set version attribute")\
    goto  bson_read_##rootObject##s1411_resume1;\
  }\
\
  if (!(rootObject##s_sequence=rootObject##s->__obj_USCORE##rootObject##s_sequence))\
    goto bson_read_##rootObject##s1411_resume1;\
\
  if (bson_read_cs_USCOREdocumentInfo1411(soap_internal, &bson, CWS_CONST_BSON_KEY("documentInfo"), rootObject##s_sequence->documentInfo, 0))\
    goto bson_read_##rootObject##s1411_resume1;\
\
  if (rootObject##s_sequence->__size##rootObject < 1)\
    goto bson_read_##rootObject##s1411_resume1;\
\
  n=0;\
  rootObject=rootObject##s_sequence->rootObject;\
\
  indexer=init_indexer(rootObject##s_sequence->__size##rootObject, index_str_buf);\
\
  if (!bson_append_array_begin(&bson, CWS_CONST_BSON_KEY(#rootObject), &thisArray)) {\
    CWS_SET_SOAP_FAULT(#rootObject "(READ). BEGIN ARRAY. Error")\
    goto bson_read_##rootObject##s1411_resume1;\
  }\
\
  do {\
    index_str_key_len=indexer((uint32_t)n, &index_str_key, index_str_buf);\
    if (bson_read_##rootObject##1411_array(soap_internal, &thisArray, index_str_key, (int)index_str_key_len, rootObject++))\
      break;\
  } while (rootObject##s_sequence->__size##rootObject > (++n));\
\
  if (!bson_append_array_end(&bson, &thisArray))\
    CWS_SET_SOAP_FAULT(#rootObject "(READ). END ARRAY Error")\
\
bson_read_##rootObject##s1411_resume1:\
  if (!bson_append_document_end(config->object, &bson))\
    CWS_SET_SOAP_FAULT(#rootObject "s(READ). END: Could not end document in " #rootObject "s")\
\
  CWS_RETURN(soap_internal)\
}

// MEASURE BUILDER
#define BSON_READ_MEASURE_BUILDER_1411(type, enumTypeSuffixFunction) \
static int bson_read_##type##1411(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  const char *key, size_t key_len,\
  struct rd1witsml__##type *type,\
  int addIfEmpty\
)\
{\
  bson_t bson;\
\
  if ((addIfEmpty==0)&&(type==NULL))\
    return SOAP_OK;\
\
  if (!bson_append_document_begin(thisDocument, key, (int)key_len, &bson)) {\
    CWS_SET_SOAP_FAULT(#type "(READ). Could not BEGIN document in BSON")\
    return SOAP_FAULT;\
  }\
\
  if (!type)\
    goto bson_read_##type##1411_resume1;\
\
  if (bson_put_single_attribute_if_exists(&bson, CWS_CONST_BSON_KEY("uom"),\
    (char *)(type->uom?soap_rd1witsml__##enumTypeSuffixFunction##2s(soap_internal, *(type->uom)):NULL), -1)) {\
    CWS_SET_SOAP_FAULT(#type "(READ). Could not set uom attribute to #attribute") \
    goto bson_read_##type##1411_resume1; \
  }\
\
  READ_O_DOUBLE_ITEM_1411_VOID(type)\
\
bson_read_##type##1411_resume1:\
  if (!bson_append_document_end(thisDocument, &bson))\
    CWS_SET_SOAP_FAULT(#type "(READ). Could not END document in BSON")\
\
  CWS_RETURN(soap_internal)\
}

#define BSON_READ_STRUCT_BUILDER_1411(type, enumTypeSuffixFunction) \
static int bson_read_##type##1411(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  const char *key, size_t key_len,\
  struct rd1witsml__##type *type,\
  int addIfEmpty\
)\
{\
  bson_t bson;\
\
  if ((addIfEmpty==0)&&(type==NULL))\
    return SOAP_OK;\
\
  if (!bson_append_document_begin(thisDocument, key, (int)key_len, &bson)) {\
    CWS_SET_SOAP_FAULT(#type "(READ). Could not BEGIN document in BSON")\
    return SOAP_FAULT;\
  }\
\
  if (!type)\
    goto bson_read_##type##1411_resume1;\
\
  if (bson_put_single_attribute_if_exists(&bson, CWS_CONST_BSON_KEY("kind"),\
    (char *)(type->kind?soap_rd1witsml__##enumTypeSuffixFunction##2s(soap_internal, *(type->kind)):NULL), -1)) {\
    CWS_SET_SOAP_FAULT(#type "(READ). Could not set kind attribute to #attribute") \
    goto bson_read_##type##1411_resume1; \
  }\
\
  READ_O_UTF8_OBJECT_ITEM_1411_VOID(type)\
\
bson_read_##type##1411_resume1:\
  if (!bson_append_document_end(thisDocument, &bson))\
    CWS_SET_SOAP_FAULT(#type "(READ). Could not END document in BSON")\
\
  CWS_RETURN(soap_internal)\
}

#define BSON_READ_ARRAY_OF_STRUCT_BUILDER_1411(type, enumTypeSuffixFunction)\
BSON_READ_STRUCT_BUILDER_1411(type, enumTypeSuffixFunction)\
\
static int bson_read_array_of_##type##1411(\
  struct soap *soap_internal,\
  bson_t *thisDocument,\
  const char *key, size_t key_len,\
  int numberOfElements,\
  struct rd1witsml__##type *type\
)\
{\
  int n;\
  bson_t thisArray;\
  IdxType index_str_buf;\
  idx2str_fn indexer;\
  const char *index_str_key;\
  size_t index_str_key_len;\
\
  if (numberOfElements < 1)\
    return SOAP_OK;\
\
  if (!bson_append_array_begin(thisDocument, key, (int)key_len, &thisArray)) {\
    CWS_SET_SOAP_FAULT(#type "(READ). BEGIN ARRAY. Error")\
    return SOAP_FAULT;\
  }\
\
  n=0;\
  indexer=init_indexer(numberOfElements, index_str_buf);\
\
  do {\
    index_str_key_len=indexer((uint32_t)n, &index_str_key, index_str_buf);\
    if (bson_read_##type##1411(soap_internal, &thisArray, index_str_key, index_str_key_len, type++, -1))\
      break;\
  } while (numberOfElements > (++n));\
\
  if (!bson_append_array_end(thisDocument, &thisArray))\
    CWS_SET_SOAP_FAULT(#type "(READ). END ARRAY Error")\
\
  CWS_RETURN(soap_internal)\
}


//SPECIAL CASE
static int bson_read_array_of_string1411(
  struct soap *soap_internal,
  bson_t *thisDocument,
  const char *key, size_t key_len,
  int numberOfElements,
  char **strArr
)
{
  int n;
  bson_t thisArray;
  IdxType index_str_buf;
  idx2str_fn indexer;
  const char *index_str_key;
  size_t index_str_key_len;

  if (numberOfElements < 1)
    return SOAP_OK;

  if (!bson_append_array_begin(thisDocument, key, (int)key_len, &thisArray)) {
    CWS_SET_SOAP_FAULT("arrayOfString(READ). BEGIN ARRAY. Error")
    return SOAP_FAULT;
  }

  n=0;
  indexer=init_indexer(numberOfElements, index_str_buf);

  do {
    index_str_key_len=indexer((uint32_t)n, &index_str_key, index_str_buf);
    if (*(strArr)) {
      if (!bson_append_utf8(&thisArray, index_str_key, (int)index_str_key_len, (const char *)*(strArr), -1))
        break;
    } else if (!bson_append_null(&thisArray, index_str_key, (int)index_str_key_len))
      break;

    strArr++;
  } while (numberOfElements > (++n));

  if (!bson_append_array_end(thisDocument, &thisArray))\
    CWS_SET_SOAP_FAULT("arrayOfString(READ). END ARRAY Error")

  CWS_RETURN(soap_internal)
}

//SPECIAL CASE
static
int bson_read_base64Binary1411(
  struct soap *soap_internal,
  bson_t *thisDocument,
  const char *key, size_t key_len,
  struct xsd__base64Binary *base64Binary, // ALWAYS NOT NULL
  int addIfEmpty
)
{
  bson_t bson;

  if ((addIfEmpty==0)&&((base64Binary->__ptr==NULL)||(base64Binary->__size<1))&&(base64Binary->id==NULL)&&(base64Binary->type==NULL)&&(base64Binary->options==NULL))
    return SOAP_OK;

  if (!bson_append_document_begin(thisDocument, key, (int)key_len, &bson)) {
    CWS_SET_SOAP_FAULT("base64Binary(READ). Could not BEGIN document in BSON")
    return SOAP_FAULT;
  }
/*
  if (!base64Binary)
    goto bson_read_base64Binary1411_resume1;
*/
  if ((base64Binary->__ptr!=NULL)&&(base64Binary->__size>0)&&(!bson_append_binary(
    &bson, CWS_CONST_BSON_KEY("#binaryData"), BSON_TYPE_BINARY, (const uint8_t *)base64Binary->__ptr, (uint32_t)base64Binary->__size))) {
    CWS_SET_SOAP_FAULT("base64Binary(READ). Could not read #binaryData of base64Binary object")
    goto bson_read_base64Binary1411_resume1;
  }

  if ((base64Binary->id!=NULL)&&(!bson_append_utf8(&bson, CWS_CONST_BSON_KEY("#binaryId"), (const char *)base64Binary->id, -1))) {
    CWS_SET_SOAP_FAULT("base64Binary(READ). Could not read #binaryId of base64Binary object")
    goto bson_read_base64Binary1411_resume1;
  }

  if ((base64Binary->type!=NULL)&&(!bson_append_utf8(&bson, CWS_CONST_BSON_KEY("#binaryType"), (const char *)base64Binary->type, -1))) {
    CWS_SET_SOAP_FAULT("base64Binary(READ). Could not read #binaryType of base64Binary object")
    goto bson_read_base64Binary1411_resume1;
  }

  if ((base64Binary->options!=NULL)&&(!bson_append_utf8(&bson, CWS_CONST_BSON_KEY("#binaryOptions"), (const char *)base64Binary->options, -1)))
    CWS_SET_SOAP_FAULT("base64Binary(READ). Could not read #binaryOptions of base64Binary object")

bson_read_base64Binary1411_resume1:
  if (!bson_append_document_end(thisDocument, &bson))
    CWS_SET_SOAP_FAULT("base64Binary(READ). Could not END document in BSON");

  CWS_RETURN(soap_internal)
}

//BEGIN ENUM ARRAY NULLABLE BUILDER
//enum rd1witsml__RiskAffectedPersonnel
BSON_READ_ARRAY_OF_OBJECT_ENUM_NULLABLE_1411_BUILDER(RiskAffectedPersonnel)

//enum rd1witsml__StimAnalysisMethod
BSON_READ_ARRAY_OF_OBJECT_ENUM_NULLABLE_1411_BUILDER(StimAnalysisMethod)

//enum rd1witsml__SurveyToolOperatingMode
BSON_READ_ARRAY_OF_OBJECT_ENUM_NULLABLE_1411_BUILDER(SurveyToolOperatingMode)

//END ENUM ARRAY NULLABLE BUILDER

//BEGIN MEASURE BUILDERS

//struct rd1witsml__anglePerLengthMeasure
BSON_READ_MEASURE_BUILDER_1411(anglePerLengthMeasure, AnglePerLengthUom)

//struct rd1witsml__timeMeasure
BSON_READ_MEASURE_BUILDER_1411(timeMeasure, TimeUom)

//struct rd1witsml__forceMeasure
BSON_READ_MEASURE_BUILDER_1411(forceMeasure, ForceUom)

//struct rd1witsml__momentOfForceMeasure
BSON_READ_MEASURE_BUILDER_1411(momentOfForceMeasure, MomentOfForceUom)

//struct rd1witsml__densityMeasure
BSON_READ_MEASURE_BUILDER_1411(densityMeasure, DensityUom)

//struct rd1witsml__volumeFlowRateMeasure
BSON_READ_MEASURE_BUILDER_1411(volumeFlowRateMeasure, VolumeFlowRateUom)

//struct rd1witsml__powerMeasure
BSON_READ_MEASURE_BUILDER_1411(powerMeasure, PowerUom)

//struct rd1witsml__velocityMeasure
BSON_READ_MEASURE_BUILDER_1411(velocityMeasure, VelocityUom)

//struct rd1witsml__pressureMeasure
BSON_READ_MEASURE_BUILDER_1411(pressureMeasure, PressureUom)

//struct rd1witsml__lengthMeasure
BSON_READ_MEASURE_BUILDER_1411(lengthMeasure, LengthUom)

//struct rd1witsml__anglePerTimeMeasure
BSON_READ_MEASURE_BUILDER_1411(anglePerTimeMeasure, AnglePerTimeUom)

//struct rd1witsml__planeAngleMeasure
BSON_READ_MEASURE_BUILDER_1411(planeAngleMeasure, PlaneAngleUom)

//struct rd1witsml__thermodynamicTemperatureMeasure
BSON_READ_MEASURE_BUILDER_1411(thermodynamicTemperatureMeasure, ThermodynamicTemperatureUom)

//struct rd1witsml__forcePerVolumeMeasure
BSON_READ_MEASURE_BUILDER_1411(forcePerVolumeMeasure, ForcePerVolumeUom)

//struct rd1witsml__volumeMeasure
BSON_READ_MEASURE_BUILDER_1411(volumeMeasure, VolumeUom)

//struct rd1witsml__dynamicViscosityMeasure
BSON_READ_MEASURE_BUILDER_1411(dynamicViscosityMeasure, DynamicViscosityUom)

//struct rd1witsml__specificVolumeMeasure
BSON_READ_MEASURE_BUILDER_1411(specificVolumeMeasure, SpecificVolumeUom)

//struct rd1witsml__volumePerVolumeMeasure
BSON_READ_MEASURE_BUILDER_1411(volumePerVolumeMeasure, VolumePerVolumeUom)

//struct rd1witsml__dimensionlessMeasure
BSON_READ_MEASURE_BUILDER_1411(dimensionlessMeasure, DimensionlessUom)

//struct rd1witsml__massMeasure
BSON_READ_MEASURE_BUILDER_1411(massMeasure, MassUom)

//struct rd1witsml__massConcentrationMeasure
BSON_READ_MEASURE_BUILDER_1411(massConcentrationMeasure, MassConcentrationUom)

//struct rd1witsml__massPerLengthMeasure
BSON_READ_MEASURE_BUILDER_1411(massPerLengthMeasure, MassPerLengthUom)

//struct rd1witsml__electricCurrentMeasure
BSON_READ_MEASURE_BUILDER_1411(electricCurrentMeasure, ElectricCurrentUom)

//struct rd1witsml__equivalentPerMassMeasure
BSON_READ_MEASURE_BUILDER_1411(equivalentPerMassMeasure, EquivalentPerMassUom)

//struct rd1witsml__illuminanceMeasure
BSON_READ_MEASURE_BUILDER_1411(illuminanceMeasure, IlluminanceUom)

//struct rd1witsml__volumePerVolumeMeasurePercent
BSON_READ_MEASURE_BUILDER_1411(volumePerVolumeMeasurePercent, PercentUom)

//struct rd1witsml__areaPerAreaMeasure
BSON_READ_MEASURE_BUILDER_1411(areaPerAreaMeasure, AreaPerAreaUom)

//struct rd1witsml__electricPotentialMeasure
BSON_READ_MEASURE_BUILDER_1411(electricPotentialMeasure, ElectricPotentialUom)

//struct rd1witsml__perLengthMeasure
BSON_READ_MEASURE_BUILDER_1411(perLengthMeasure, PerLengthUom)

//struct rd1witsml__accelerationLinearMeasure
BSON_READ_MEASURE_BUILDER_1411(accelerationLinearMeasure, AccelerationLinearUom)

//struct rd1witsml__magneticInductionMeasure
BSON_READ_MEASURE_BUILDER_1411(magneticInductionMeasure, MagneticInductionUom)

//struct rd1witsml__areaMeasure
BSON_READ_MEASURE_BUILDER_1411(areaMeasure, AreaUom)

//struct rd1witsml__relativePowerMeasure
BSON_READ_MEASURE_BUILDER_1411(relativePowerMeasure, RelativePowerUom)

//struct rd1witsml__standardVolumeMeasure
BSON_READ_MEASURE_BUILDER_1411(standardVolumeMeasure, StandardVolumeUom)

//struct rd1witsml__standardVolumePerTimeMeasure
BSON_READ_MEASURE_BUILDER_1411(standardVolumePerTimeMeasure, StandardVolumePerTimeUom)

//struct rd1witsml__volumePerLengthMeasure
BSON_READ_MEASURE_BUILDER_1411(volumePerLengthMeasure, VolumePerLengthUom)

//struct rd1witsml__compressibilityMeasure
BSON_READ_MEASURE_BUILDER_1411(compressibilityMeasure, CompressibilityUom)

//struct rd1witsml__specificHeatCapacityMeasure
BSON_READ_MEASURE_BUILDER_1411(specificHeatCapacityMeasure, SpecificHeatCapacityUom)

//struct rd1witsml__thermalConductivityMeasure
BSON_READ_MEASURE_BUILDER_1411(thermalConductivityMeasure, ThermalConductivityUom)

//struct rd1witsml__thermalVolumetricExpansionMeasure
BSON_READ_MEASURE_BUILDER_1411(thermalVolumetricExpansionMeasure, ThermalVolumetricExpansionUom)

//struct rd1witsml__permeabilityRockMeasure
BSON_READ_MEASURE_BUILDER_1411(permeabilityRockMeasure, PermeabilityRockUom)

//struct rd1witsml__lengthPerLengthMeasure
BSON_READ_MEASURE_BUILDER_1411(lengthPerLengthMeasure, LengthPerLengthUom)

//struct rd1witsml__forcePerLengthMeasure
BSON_READ_MEASURE_BUILDER_1411(forcePerLengthMeasure, ForcePerLengthUom)

//END MEASURE BUILDERS

//BEGIN STRUCT BUILDERS

//struct rd1witsml__lithostratigraphyStruct
BSON_READ_ARRAY_OF_STRUCT_BUILDER_1411(lithostratigraphyStruct, LithostratigraphyUnit)

//struct rd1witsml__chronostratigraphyStruct
BSON_READ_ARRAY_OF_STRUCT_BUILDER_1411(chronostratigraphyStruct, ChronostratigraphyUnit)

//END STRUCT BUILDERS

//struct rd1witsml__refObjectString
BSON_READ_OBJECT_1411_BEGIN(refObjectString)
  READ_O_PUT_MULTIPLE_ATTRIBUTES_1411_OR_ELSE_GOTO_RESUME(refObjectString,
    SET_MULTIPLE_ATTRIBUTES(
      ATTR_KEY_1411(refObjectString, object),
      ATTR_KEY_1411(refObjectString, uidRef)
    )
  )
  READ_O_UTF8_OBJECT_ITEM_1411_VOID(refObjectString)
BSON_READ_OBJECT_1411_END(refObjectString)

//struct rd1witsml__indexedObject
BSON_READ_ARRAY_OF_OBJECT_1411_BEGIN(indexedObject)
  READ_A_PUT_MULTIPLE_ATTRIBUTES_TYPED_1411_OR_ELSE_GOTO_RESUME(indexedObject, SET_MULTIPLE_ATTRIBUTES(
    ATTR_KEY_TYPED_1411(indexedObject, _CWS_NULLABLE_XSD_SIGNED_SHORT, index),
    ATTR_KEY_TYPED_1411(indexedObject, _CWS_NULLABLE_XSD_STR, name),
    ATTR_KEY_TYPED_1411(indexedObject, _CWS_NULLABLE_XSD_STR, uom),
    ATTR_KEY_TYPED_1411(indexedObject, _CWS_NULLABLE_XSD_STR, description),
    ATTR_KEY_TYPED_1411(indexedObject, _CWS_NULLABLE_XSD_STR, uid)
  ))
  READ_A_UTF8_OBJECT_ITEM_1411_VOID(indexedObject)
BSON_READ_ARRAY_OF_OBJECT_1411_END(indexedObject)

//struct rd1witsml__timestampedTimeZone
BSON_READ_ARRAY_OF_OBJECT_1411_BEGIN(timestampedTimeZone)
  READ_A_PUT_MULTIPLE_ATTRIBUTES_TYPED_1411_OR_ELSE_GOTO_RESUME(timestampedTimeZone, SET_MULTIPLE_ATTRIBUTES(
    ATTR_KEY_TYPED_1411(timestampedTimeZone, _CWS_NULLABLE_DATE_TIME, dTim)
  ))
  READ_A_UTF8_OBJECT_ITEM_1411_VOID(timestampedTimeZone)
BSON_READ_ARRAY_OF_OBJECT_1411_END(timestampedTimeZone)

//struct rd1witsml__refNameString
BSON_READ_ARRAY_OF_OBJECT_1411_BEGIN(refNameString)
  READ_A_PUT_SINGLE_ATTRIBUTE_1411_OR_ELSE_GOTO_RESUME(refNameString, uidRef)
  READ_A_UTF8_OBJECT_ITEM_1411_VOID(refNameString)
BSON_READ_ARRAY_OF_OBJECT_1411_END(refNameString)

//struct rd1witsml__cs_USCOREextensionAny
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREextensionAny)
  READ_O_ARRAY_OF_ANY_OBJECT_1411_VOID_B(cs_USCOREextensionAny)
BSON_READ_OBJECT_1411_END_B(cs_USCOREextensionAny)

//struct rd1witsml__extensionvalue
BSON_READ_OBJECT_1411_BEGIN(extensionvalue)
  READ_O_PUT_SINGLE_ATTRIBUTE_1411_OR_ELSE_GOTO_RESUME(extensionvalue, uom)
  READ_O_UTF8_OBJECT_ITEM_1411_VOID(extensionvalue)
BSON_READ_OBJECT_1411_END(extensionvalue)

//struct rd1witsml__measuredDepthCoord
BSON_READ_OBJECT_1411_BEGIN(measuredDepthCoord)
  READ_O_PUT_MULTIPLE_ATTRIBUTES_1411_OR_ELSE_GOTO_RESUME(measuredDepthCoord,
    SET_MULTIPLE_ATTRIBUTES(
      ATTR_ENUM_KEY_NULLABLE_1411(measuredDepthCoord, uom, MeasuredDepthUom),
      ATTR_KEY_1411(measuredDepthCoord, datum)
    )
  )
  READ_O_DOUBLE_ITEM_1411_VOID(measuredDepthCoord)
BSON_READ_OBJECT_1411_END(measuredDepthCoord)

//struct rd1witsml__wellVerticalDepthCoord
BSON_READ_OBJECT_1411_BEGIN(wellVerticalDepthCoord)
  READ_O_PUT_MULTIPLE_ATTRIBUTES_1411_OR_ELSE_GOTO_RESUME(wellVerticalDepthCoord,
    SET_MULTIPLE_ATTRIBUTES(
      ATTR_ENUM_KEY_NULLABLE_1411(wellVerticalDepthCoord, uom, WellVerticalCoordinateUom),
      ATTR_KEY_1411(wellVerticalDepthCoord, datum)
    )
  )
  READ_O_DOUBLE_ITEM_1411_VOID(wellVerticalDepthCoord)
BSON_READ_OBJECT_1411_END(wellVerticalDepthCoord)

//struct rd1witsml__cs_USCOREextensionNameValue
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREextensionNameValue)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREextensionNameValue, name)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREextensionNameValue, value, extensionvalue)
  READ_O_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREextensionNameValue, dataType, PrimitiveType)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREextensionNameValue, dTim)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREextensionNameValue, md, measuredDepthCoord)
  READ_O_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREextensionNameValue, index)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREextensionNameValue, measureClass)
  READ_O_UTF8_OBJECT_1411_VOID_B(cs_USCOREextensionNameValue, description)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREextensionNameValue)

//struct __rd1witsml__cs_USCOREcommonData
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREcommonData)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcommonData, sourceName)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcommonData, dTimCreation)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcommonData, dTimLastChange)
  READ_O_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcommonData, itemState, ItemState)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcommonData, serviceCategory)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcommonData, comments)
  READ_O_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcommonData, acquisitionTimeZone, timestampedTimeZone)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcommonData, defaultDatum, refNameString)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcommonData, privateGroupOnly)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcommonData, extensionAny, cs_USCOREextensionAny)
  READ_O_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREcommonData, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_OBJECT_1411_END_B(cs_USCOREcommonData)

//struct rd1witsml__cs_USCOREcustomData
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREcustomData)
  READ_O_ARRAY_OF_ANY_OBJECT_1411_VOID_B(cs_USCOREcustomData)
BSON_READ_OBJECT_1411_END_B(cs_USCOREcustomData)

//struct rd1witsml__nameStruct
BSON_READ_ARRAY_OF_OBJECT_1411_BEGIN(nameStruct)
  READ_A_PUT_SINGLE_ATTRIBUTE_1411_OR_ELSE_GOTO_RESUME(nameStruct, namingSystem)
  READ_A_UTF8_OBJECT_ITEM_1411_VOID(nameStruct)
BSON_READ_ARRAY_OF_OBJECT_1411_END(nameStruct)

//struct rd1witsml__cs_USCOREdocumentFileCreation
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREdocumentFileCreation)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdocumentFileCreation, fileCreationDate)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdocumentFileCreation, softwareName)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdocumentFileCreation, fileCreator)
  READ_O_UTF8_OBJECT_1411_VOID_B(cs_USCOREdocumentFileCreation, comment)
BSON_READ_OBJECT_1411_END_B(cs_USCOREdocumentFileCreation)

//struct rd1witsml__cs_USCOREdocumentSecurityInfo
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREdocumentSecurityInfo)
  READ_O_UTF8_OBJECT_WITH_ALIAS_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdocumentSecurityInfo, class_, class)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdocumentSecurityInfo, securitySystem)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdocumentSecurityInfo, endDate)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdocumentSecurityInfo, comment)
  READ_O_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREdocumentSecurityInfo, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREdocumentSecurityInfo)

//struct rd1witsml__cs_USCOREdocumentEvent
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREdocumentEvent)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdocumentEvent, eventDate)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdocumentEvent, eventType)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdocumentEvent, responsibleParty)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdocumentEvent, comment)
  READ_O_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREdocumentEvent, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREdocumentEvent)

//struct rd1witsml__cs_USCOREdocumentAudit
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREdocumentAudit)
  READ_O_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREdocumentAudit, event, cs_USCOREdocumentEvent)
BSON_READ_OBJECT_1411_END_B(cs_USCOREdocumentAudit)

//struct rd1witsml__cs_USCOREdocumentInfo
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREdocumentInfo)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdocumentInfo, documentName, nameStruct)
  READ_O_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdocumentInfo, documentAlias, nameStruct)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdocumentInfo, documentDate)
  READ_O_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdocumentInfo, documentClass, nameStruct)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdocumentInfo, fileCreationInformation, cs_USCOREdocumentFileCreation)
  READ_O_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdocumentInfo, securityInformation, cs_USCOREdocumentSecurityInfo)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdocumentInfo, disclaimer)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdocumentInfo, auditTrail, cs_USCOREdocumentAudit)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdocumentInfo, owner)
  READ_O_UTF8_OBJECT_1411_VOID_B(cs_USCOREdocumentInfo, comment)
BSON_READ_OBJECT_1411_END_B(cs_USCOREdocumentInfo)

//struct rd1witsml__cs_USCOREdrillingParams
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREdrillingParams)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, eTimOpBit, timeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, mdHoleStart, measuredDepthCoord)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, mdHoleStop, measuredDepthCoord)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, tubular, refNameString)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, hkldRot, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, overPull, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, slackOff, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, hkldUp, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, hkldDn, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, tqOnBotAv, momentOfForceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, tqOnBotMx, momentOfForceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, tqOnBotMn, momentOfForceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, tqOffBotAv, momentOfForceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, tqDhAv, momentOfForceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, wtAboveJar, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, wtBelowJar, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, wtMud, densityMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, flowratePump, volumeFlowRateMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, powBit, powerMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, velNozzleAv, velocityMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, presDropBit, pressureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, cTimHold, timeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, cTimSteering, timeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, cTimDrillRot, timeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, cTimDrillSlid, timeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, cTimCirc, timeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, cTimReam, timeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, distDrillRot, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, distDrillSlid, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, distReam, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, distHold, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, distSteering, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, rpmAv, anglePerTimeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, rpmMx, anglePerTimeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, rpmMn, anglePerTimeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, rpmAvDh, anglePerTimeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, ropAv, velocityMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, ropMx, velocityMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, ropMn, velocityMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, wobAv, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, wobMx, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, wobMn, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, wobAvDh, forceMeasure)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, reasonTrip)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, objectiveBha)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, aziTop, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, aziBottom, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, inclStart, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, inclMx, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, inclMn, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, inclStop, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, tempMudDhMx, thermodynamicTemperatureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, presPumpAv, pressureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, flowrateBit, volumeFlowRateMeasure)
  READ_O_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, mudClass, MudClass)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, mudSubClass)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillingParams, comments)
  READ_O_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREdrillingParams, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREdrillingParams)

//struct __rd1witsml__cs_USCOREcementTest
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREcementTest)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, presTest, pressureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, eTimTest, timeMeasure)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, cementShoeCollar)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, cetRun)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, cetBondQual)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, cblRun)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, cblBondQual)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, cblPres, pressureMeasure)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, tempSurvey)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, eTimCementLog, timeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, formPit, forcePerVolumeMeasure)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, toolCompanyPit)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, eTimPitStart, timeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, mdCementTop, measuredDepthCoord)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, topCementMethod)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, tocOK)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, jobRating)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, remedialCement)
  READ_O_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, numRemedial)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, failureMethod)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, linerTop, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, linerLap, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, eTimBeforeTest, timeMeasure)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, testNegativeTool)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, testNegativeEmw, densityMeasure)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, testPositiveTool)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, testPositiveEmw, densityMeasure)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementTest, cementFoundOnTool)
  READ_O_OBJECT_1411_VOID_B(cs_USCOREcementTest, mdDVTool, measuredDepthCoord)
BSON_READ_OBJECT_1411_END_B(cs_USCOREcementTest)

//struct __rd1witsml__cs_USCOREcementPumpSchedule_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREcementPumpSchedule)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementPumpSchedule, eTimPump, timeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementPumpSchedule, ratePump, volumeFlowRateMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementPumpSchedule, volPump, volumeMeasure)
  READ_O_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementPumpSchedule, strokePump)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementPumpSchedule, presBack, pressureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementPumpSchedule, eTimShutdown, timeMeasure)
  READ_O_UTF8_OBJECT_1411_VOID_B(cs_USCOREcementPumpSchedule, comments)
BSON_READ_OBJECT_1411_END_B(cs_USCOREcementPumpSchedule)

//struct __rd1witsml__cs_USCOREcementAdditive_sequence_
BSON_READ_OBJECT_1411_BEGIN_C(cs_USCOREcementAdditive, _)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_C(cs_USCOREcementAdditive, typeConc, _)
  READ_O_OBJECT_1411_VOID_C(cs_USCOREcementAdditive, concentration, massConcentrationMeasure, _)
BSON_READ_OBJECT_1411_END_C(cs_USCOREcementAdditive, _)

//struct __rd1witsml__cs_USCOREcementAdditive_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREcementAdditive)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementAdditive, nameAdd)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementAdditive, typeAdd)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementAdditive, formAdd)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementAdditive, densAdd, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B1(cs_USCOREcementAdditive, __cs_USCOREcementAdditive_sequence_, cs_USCOREcementAdditive, _)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementAdditive, wtSack, massMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementAdditive, volSack, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementAdditive, additive, massMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREcementAdditive, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREcementAdditive)

//struct __rd1witsml__cs_USCOREcementingFluid_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREcementingFluid)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, typeFluid)
  READ_O_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, fluidIndex)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, descFluid)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, purpose)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, classSlurryDryBlend)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, mdFluidTop, measuredDepthCoord)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, mdFluidBottom, measuredDepthCoord)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, sourceWater)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, volWater, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, volCement, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, ratioMixWater, specificVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, volFluid, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, cementPumpSchedule, cs_USCOREcementPumpSchedule)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, excessPc, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, volYield, specificVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, density, densityMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, solidVolumeFraction, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, volPumped, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, volOther, volumeMeasure)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, fluidRheologicalModel)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, vis, dynamicViscosityMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, yp, pressureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, n, dimensionlessMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, k, dimensionlessMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, gel10SecReading, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, gel10SecStrength, pressureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, gel1MinReading, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, gel1MinStrength, pressureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, gel10MinReading, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, gel10MinStrength, pressureMeasure)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, typeBaseFluid)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, densBaseFluid, densityMeasure)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, dryBlendName)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, dryBlendDescription)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, massDryBlend, massMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, densDryBlend, densityMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, massSackDryBlend, massMeasure)
  READ_O_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, cementAdditive, cs_USCOREcementAdditive)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, foamUsed)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, typeGasFoam)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, volGasFoam, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, ratioConstGasMethodAv, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, densConstGasMethod, densityMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, ratioConstGasMethodStart, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, ratioConstGasMethodEnd, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, densConstGasFoam, densityMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, eTimThickening, timeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, tempThickening, thermodynamicTemperatureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, presTestThickening, pressureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, consTestThickening, dimensionlessMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, pcFreeWater, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, tempFreeWater, thermodynamicTemperatureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, volTestFluidLoss, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, tempFluidLoss, thermodynamicTemperatureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, presTestFluidLoss, pressureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, timeFluidLoss, timeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, volAPIFluidLoss, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, eTimComprStren1, timeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, eTimComprStren2, timeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, presComprStren1, pressureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, presComprStren2, pressureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, tempComprStren1, thermodynamicTemperatureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, tempComprStren2, thermodynamicTemperatureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, densAtPres, densityMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementingFluid, volReserved, volumeMeasure)
  READ_O_OBJECT_1411_VOID_B(cs_USCOREcementingFluid, volTotSlurry, volumeMeasure)
BSON_READ_OBJECT_1411_END_B(cs_USCOREcementingFluid)

//struct __rd1witsml__cs_USCOREcementStage_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREcementStage)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, numStage)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, typeStage)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, dTimMixStart)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, dTimPumpStart)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, dTimPumpEnd)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, dTimDisplaceStart)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, mdTop, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, mdBottom, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, volExcess, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, flowrateDisplaceAv, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, flowrateDisplaceMx, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, presDisplace, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, volReturns, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, eTimMudCirculation, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, flowrateMudCirc, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, presMudCirc, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, flowrateEnd, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, cementingFluid, cs_USCOREcementingFluid)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, afterFlowAnn)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, squeezeObj)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, squeezeObtained)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, mdString, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, mdTool, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, mdCoilTbg, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, volCsgIn, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, volCsgOut, volumeMeasure)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, tailPipeUsed)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, diaTailPipe, lengthMeasure)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, tailPipePerf)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, presTbgStart, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, presTbgEnd, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, presCsgStart, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, presCsgEnd, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, presBackPressure, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, presCoilTbgStart, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, presCoilTbgEnd, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, presBreakDown, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, flowrateBreakDown, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, presSqueezeAv, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, presSqueezeEnd, pressureMeasure)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, presSqueezeHeld)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, presSqueeze, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, eTimPresHeld, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, flowrateSqueezeAv, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, flowrateSqueezeMx, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, flowratePumpStart, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, flowratePumpEnd, volumeFlowRateMeasure)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, pillBelowPlug)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, plugCatcher)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, mdCircOut, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, volCircPrior, volumeMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, typeOriginalMud)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, wtMud, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, visFunnelMud, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, pvMud, dynamicViscosityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, ypMud, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, gel10Sec, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, gel10Min, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, tempBHCT, thermodynamicTemperatureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, tempBHST, thermodynamicTemperatureMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, volExcessMethod)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, mixMethod)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, densMeasBy)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, annFlowAfter)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, topPlug)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, botPlug)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, botPlugNumber)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, plugBumped)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, presPriorBump, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, presBump, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, presHeld, pressureMeasure)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, floatHeld)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, volMudLost, volumeMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, fluidDisplace)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, densDisplaceFluid, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcementStage, volDisplaceFluid, volumeMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREcementStage, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREcementStage)

//struct __rd1witsml__cs_USCOREwbGeometrySection_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREwbGeometrySection)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwbGeometrySection, typeHoleCasing, HoleCasingType)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwbGeometrySection, mdTop, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwbGeometrySection, mdBottom, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwbGeometrySection, tvdTop, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwbGeometrySection, tvdBottom, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwbGeometrySection, idSection, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwbGeometrySection, odSection, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwbGeometrySection, wtPerLen, massPerLengthMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwbGeometrySection, grade)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwbGeometrySection, curveConductor)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwbGeometrySection, diaDrift, lengthMeasure)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwbGeometrySection, factFric)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREwbGeometrySection, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREwbGeometrySection)

//struct __rd1witsml__cs_USCOREwbGeometry_sequence_
BSON_READ_OBJECT_1411_BEGIN_D(cs_USCOREwbGeometry)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_D(cs_USCOREwbGeometry, dTimReport)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_D(cs_USCOREwbGeometry, mdBottom, measuredDepthCoord)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_D(cs_USCOREwbGeometry, gapAir, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_D(cs_USCOREwbGeometry, depthWaterMean, lengthMeasure)
  READ_O_ARRAY_OF_OBJECT_1411_VOID_D(cs_USCOREwbGeometry, wbGeometrySection, cs_USCOREwbGeometrySection)
BSON_READ_OBJECT_1411_END_D(cs_USCOREwbGeometry)

//struct __rd1witsml__cs_USCOREqualifier_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREqualifier)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREqualifier, type)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREqualifier, abundance, volumePerVolumeMeasurePercent)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREqualifier, abundanceCode)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREqualifier, description)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREqualifier, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREqualifier)

//struct __rd1witsml__cs_USCORElithology_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCORElithology)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, type)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, codeLith)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, lithPc, volumePerVolumeMeasurePercent)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, description)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, lithClass)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, grainType)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, dunhamClass)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, color)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, texture)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, hardness)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, compaction)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, sizeGrain)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, roundness)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, sphericity)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, sorting)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, matrixCement)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, porosityVisible)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, porosityFabric)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, permeability)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, densShale, densityMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElithology, qualifier, cs_USCOREqualifier)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCORElithology, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCORElithology)

//struct __rd1witsml__cs_USCOREshow_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREshow)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, showRat, ShowRating)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, stainColor)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, stainDistr)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, stainPc, areaPerAreaMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, natFlorColor)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, natFlorPc, areaPerAreaMeasure)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, natFlorLevel, ShowFluorescence)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, natFlorDesc)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, cutColor)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, cutSpeed, ShowSpeed)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, cutStrength)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, cutForm, ShowLevel)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, cutLevel)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, cutFlorColor)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, cutFlorSpeed, ShowSpeed)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, cutFlorStrength)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, cutFlorForm, ShowLevel)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, cutFlorLevel, ShowFluorescence)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, residueColor)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, showDesc)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshow, impregnatedLitho)
  READ_A_UTF8_OBJECT_1411_VOID_B(cs_USCOREshow, odor)
BSON_READ_OBJECT_1411_END_B(cs_USCOREshow)

//struct __rd1witsml__cs_USCOREchromatograph_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREchromatograph)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, dTim)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, mdTop, measuredDepthCoord)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, mdBottom, measuredDepthCoord)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, wtMudIn, densityMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, wtMudOut, densityMeasure)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, chromType)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, eTimChromCycle, timeMeasure)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, chromIntRpt)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, methAv, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, methMn, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, methMx, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, ethAv, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, ethMn, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, ethMx, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, propAv, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, propMn, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, propMx, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, ibutAv, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, ibutMn, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, ibutMx, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, nbutAv, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, nbutMn, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, nbutMx, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, ipentAv, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, ipentMn, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, ipentMx, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, npentAv, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, npentMn, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, npentMx, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, epentAv, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, epentMn, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, epentMx, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, ihexAv, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, ihexMn, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, ihexMx, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, nhexAv, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, nhexMn, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, nhexMx, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, co2Av, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, co2Mn, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, co2Mx, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, h2sAv, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, h2sMn, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchromatograph, h2sMx, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_VOID_B(cs_USCOREchromatograph, acetylene, volumePerVolumeMeasure)
BSON_READ_OBJECT_1411_END_B(cs_USCOREchromatograph)

//struct __rd1witsml__cs_USCOREmudGas_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREmudGas)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudGas, gasAv, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudGas, gasPeak, volumePerVolumeMeasure)
  READ_O_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudGas, gasPeakType, GasPeakType)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudGas, gasBackgnd, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudGas, gasConAv, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudGas, gasConMx, volumePerVolumeMeasure)
  READ_O_OBJECT_1411_VOID_B(cs_USCOREmudGas, gasTrip, volumePerVolumeMeasure)
BSON_READ_OBJECT_1411_END_B(cs_USCOREmudGas)

//struct __rd1witsml__cs_USCOREcommonTime_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREcommonTime)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcommonTime, dTimCreation)
  READ_O_TIME_NULLABLE_1411_VOID_B(cs_USCOREcommonTime, dTimLastChange)
BSON_READ_OBJECT_1411_END_B(cs_USCOREcommonTime)

//struct __rd1witsml__cs_USCOREgeologyInterval_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREgeologyInterval)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, typeLithology, LithologySource)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, mdTop, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, mdBottom, measuredDepthCoord)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, dTim)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, tvdTop, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, tvdBase, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, ropAv, velocityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, ropMn, velocityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, ropMx, velocityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, wobAv, forceMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, tqAv, momentOfForceMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, currentAv, electricCurrentMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, rpmAv, anglePerTimeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, wtMudAv, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, ecdTdAv, densityMeasure)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, dxcAv)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, lithology, cs_USCORElithology)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, show, cs_USCOREshow)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, chromatograph, cs_USCOREchromatograph)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, mudGas, cs_USCOREmudGas)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, densBulk, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, densShale, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, calcite, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, dolomite, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, cec, equivalentPerMassMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, qft, illuminanceMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, calcStab, volumePerVolumeMeasure)
  READ_A_ARRAY_OF_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, nameFormation)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, lithostratigraphic, lithostratigraphyStruct)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, chronostratigraphic, chronostratigraphyStruct)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, sizeMn, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, sizeMx, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, lenPlug, lengthMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, description)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, cuttingFluid)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, cleaningMethod)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, dryingMethod)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, comments)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeologyInterval, commonTime, cs_USCOREcommonTime)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREgeologyInterval, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREgeologyInterval)

//struct __rd1witsml__cs_USCOREwellAlias_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREwellAlias)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwellAlias, name)
  READ_O_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwellAlias, namingSystem, WellNamingSystem)
  READ_O_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREwellAlias, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREwellAlias)

//struct rd1witsml__wellKnownNameStruct
BSON_READ_OBJECT_1411_BEGIN(wellKnownNameStruct)
  READ_O_PUT_MULTIPLE_ATTRIBUTES_1411_OR_ELSE_GOTO_RESUME(wellKnownNameStruct,
    SET_MULTIPLE_ATTRIBUTES(
      ATTR_KEY_1411(wellKnownNameStruct, namingSystem),
      ATTR_KEY_1411(wellKnownNameStruct, code)
    )
  )
  READ_O_UTF8_OBJECT_ITEM_1411_VOID(wellKnownNameStruct)
BSON_READ_OBJECT_1411_END(wellKnownNameStruct)

//struct __rd1witsml__cs_USCORErefWellWellbore_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCORErefWellWellbore)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErefWellWellbore, wellboreReference, refNameString)
  READ_O_OBJECT_1411_VOID_B(cs_USCORErefWellWellbore, wellParent, refNameString)
BSON_READ_OBJECT_1411_END_B(cs_USCORErefWellWellbore)

//struct __rd1witsml__cs_USCORErefWellWellboreRig_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCORErefWellWellboreRig)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErefWellWellboreRig, rigReference, refNameString)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErefWellWellboreRig, wellboreParent, refNameString)
  READ_O_OBJECT_1411_VOID_B(cs_USCORErefWellWellboreRig, wellParent, refNameString)
BSON_READ_OBJECT_1411_END_B(cs_USCORErefWellWellboreRig)

//struct rd1witsml__wellElevationCoord
BSON_READ_OBJECT_1411_BEGIN(wellElevationCoord)
  READ_O_PUT_MULTIPLE_ATTRIBUTES_1411_OR_ELSE_GOTO_RESUME(wellElevationCoord,
    SET_MULTIPLE_ATTRIBUTES(
      ATTR_ENUM_KEY_NULLABLE_1411(wellElevationCoord, uom, WellVerticalCoordinateUom),
      ATTR_KEY_1411(wellElevationCoord, datum)
    )
  )
  READ_O_DOUBLE_ITEM_1411_VOID(wellElevationCoord)
BSON_READ_OBJECT_1411_END(wellElevationCoord)

//struct __rd1witsml__cs_USCORElocation_sequence_
BSON_READ_OBJECT_1411_BEGIN_C(cs_USCORElocation, _)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_C(cs_USCORElocation, latitude, planeAngleMeasure, _)
  READ_O_OBJECT_1411_VOID_C(cs_USCORElocation, longitude, planeAngleMeasure, _)
BSON_READ_OBJECT_1411_END_C(cs_USCORElocation, _)

//struct __rd1witsml__cs_USCORElocation_sequence__
BSON_READ_OBJECT_1411_BEGIN_C(cs_USCORElocation, __)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_C(cs_USCORElocation, easting, lengthMeasure, __)
  READ_O_OBJECT_1411_VOID_C(cs_USCORElocation, northing, lengthMeasure, __)
BSON_READ_OBJECT_1411_END_C(cs_USCORElocation, __)

//struct __rd1witsml__cs_USCORElocation_sequence___
BSON_READ_OBJECT_1411_BEGIN_C(cs_USCORElocation, ___)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_C(cs_USCORElocation, westing, lengthMeasure, ___)
  READ_O_OBJECT_1411_VOID_C(cs_USCORElocation, southing, lengthMeasure, ___)
BSON_READ_OBJECT_1411_END_C(cs_USCORElocation, ___)

//struct __rd1witsml__cs_USCORElocation_sequence____
BSON_READ_OBJECT_1411_BEGIN_C(cs_USCORElocation, ____)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_C(cs_USCORElocation, projectedX, lengthMeasure, ____)
  READ_O_OBJECT_1411_VOID_C(cs_USCORElocation, projectedY, lengthMeasure, ____)
BSON_READ_OBJECT_1411_END_C(cs_USCORElocation, ____)

//struct __rd1witsml__cs_USCORElocation_sequence_____
BSON_READ_OBJECT_1411_BEGIN_C(cs_USCORElocation, _____)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_C(cs_USCORElocation, localX, lengthMeasure, _____)
  READ_O_OBJECT_1411_VOID_C(cs_USCORElocation, localY, lengthMeasure, _____)
BSON_READ_OBJECT_1411_END_C(cs_USCORElocation, _____)

//struct __rd1witsml__cs_USCORElocation_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCORElocation)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElocation, wellCRS, refNameString)
//        struct __rd1witsml__cs_USCORElocation_sequence_ *__cs_USCORElocation_sequence_;
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B1(cs_USCORElocation, __cs_USCORElocation_sequence_, cs_USCORElocation, _)
//        struct __rd1witsml__cs_USCORElocation_sequence__ *__cs_USCORElocation_sequence__;
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B1(cs_USCORElocation, __cs_USCORElocation_sequence__, cs_USCORElocation, __)
//        struct __rd1witsml__cs_USCORElocation_sequence___ *__cs_USCORElocation_sequence___;
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B1(cs_USCORElocation, __cs_USCORElocation_sequence___, cs_USCORElocation, ___)
//        struct __rd1witsml__cs_USCORElocation_sequence____ *__cs_USCORElocation_sequence____;
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B1(cs_USCORElocation, __cs_USCORElocation_sequence____, cs_USCORElocation, ____)
//        struct __rd1witsml__cs_USCORElocation_sequence_____ *__cs_USCORElocation_sequence_____;
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B1(cs_USCORElocation, __cs_USCORElocation_sequence_____, cs_USCORElocation, _____)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElocation, original)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElocation, description)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCORElocation, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCORElocation)

//struct __rd1witsml__cs_USCOREwellDatum_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREwellDatum)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwellDatum, name)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwellDatum, code, ElevCodeEnum)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwellDatum, datumName, wellKnownNameStruct)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwellDatum, datumCRS, refNameString)
  READ_A_ARRAY_OF_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwellDatum, kind)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwellDatum, wellbore, cs_USCORErefWellWellbore)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwellDatum, rig, cs_USCORErefWellWellboreRig)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwellDatum, elevation, wellElevationCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwellDatum, measuredDepth, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwellDatum, horizontalLocation, cs_USCORElocation)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwellDatum, comment)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREwellDatum, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREwellDatum)

//struct __rd1witsml__cs_USCOREprojectionx_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREprojectionx)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, nameCRS, wellKnownNameStruct)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, projectionCode, Projection)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, projectedFrom, refNameString)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, stdParallel1, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, stdParallel2, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, centralMeridian, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, originLatitude, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, originLongitude, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, latitude1, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, longitude1, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, latitude2, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, longitude2, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, latitudeForScale, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, longitudeForScale, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, trueScaleLatitude, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, spheroidRadius, lengthMeasure)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, scaleFactor)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, methodVariant, ProjectionVariantsObliqueMercator)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, perspectiveHeight, lengthMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, zone)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, NADType, NADTypes)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, falseEasting, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, falseNorthing, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, bearing, planeAngleMeasure)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, hemisphere, Hemispheres)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREprojectionx, description)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREprojectionx, parameter, indexedObject)
BSON_READ_OBJECT_1411_END_B(cs_USCOREprojectionx)

//struct __rd1witsml__cs_USCOREgeodeticModel_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREgeodeticModel)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeodeticModel, nameCRS, wellKnownNameStruct)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeodeticModel, geodeticDatumCode, GeodeticDatum)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeodeticModel, xTranslation, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeodeticModel, yTranslation, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeodeticModel, zTranslation, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeodeticModel, xRotation, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeodeticModel, yRotation, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeodeticModel, zRotation, planeAngleMeasure)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeodeticModel, scaleFactor)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeodeticModel, ellipsoidCode, Ellipsoid)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREgeodeticModel, ellipsoidSemiMajorAxis, lengthMeasure)
  READ_A_DOUBLE_NULLABLE_1411_VOID_B(cs_USCOREgeodeticModel, ellipsoidInverseFlattening)
BSON_READ_OBJECT_1411_END_B(cs_USCOREgeodeticModel)

//struct rd1witsml__yAxisAzimuth
BSON_READ_OBJECT_1411_BEGIN(yAxisAzimuth)
  READ_O_PUT_MULTIPLE_ATTRIBUTES_1411_OR_ELSE_GOTO_RESUME(yAxisAzimuth,
    SET_MULTIPLE_ATTRIBUTES(
      ATTR_ENUM_KEY_NULLABLE_1411(yAxisAzimuth, uom, PlaneAngleUom),
      ATTR_ENUM_KEY_NULLABLE_1411(yAxisAzimuth, northDirection, AziRef)
    )
  )
  READ_O_DOUBLE_ITEM_1411_VOID(yAxisAzimuth)
BSON_READ_OBJECT_1411_END(yAxisAzimuth)

//struct __rd1witsml__cs_USCORElocalCRS_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCORElocalCRS)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElocalCRS, usesWellAsOrigin)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElocalCRS, origin, refNameString)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElocalCRS, originDescription)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElocalCRS, yAxisAzimuth, yAxisAzimuth)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElocalCRS, magneticDeclination, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElocalCRS, gridConvergence, planeAngleMeasure)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElocalCRS, yAxisDescription)
  READ_O_BOOLEAN_NULLABLE_1411_VOID_B(cs_USCORElocalCRS, xRotationCounterClockwise)
BSON_READ_OBJECT_1411_END_B(cs_USCORElocalCRS)

//struct __rd1witsml__cs_USCOREwellCRS_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREwellCRS)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwellCRS, name)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwellCRS, mapProjection, cs_USCOREprojectionx)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwellCRS, geographic, cs_USCOREgeodeticModel)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwellCRS, mapProjectionCRS, refNameString)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwellCRS, geodeticCRS, refNameString)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwellCRS, localCRS, cs_USCORElocalCRS)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREwellCRS, description)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREwellCRS, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREwellCRS)

//struct __rd1witsml__cs_USCOREalias_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREalias)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREalias, name)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREalias, namingSystem)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREalias, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREalias)

//struct __rd1witsml__cs_USCOREdrillReportWellboreInfo_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREdrillReportWellboreInfo)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellboreInfo, dTimSpud)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellboreInfo, dTimPreSpud)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellboreInfo, dateDrillComplete)
  READ_O_UTF8_OBJECT_WITH_ALIAS_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellboreInfo, operator_, operator)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellboreInfo, drillContractor)
  READ_O_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREdrillReportWellboreInfo, rigAlias, cs_USCOREalias)
BSON_READ_OBJECT_1411_END_B(cs_USCOREdrillReportWellboreInfo)

//struct rd1witsml__cost
BSON_READ_OBJECT_1411_BEGIN(cost)
  READ_O_PUT_SINGLE_ATTRIBUTE_1411_OR_ELSE_GOTO_RESUME(cost, currency)
  READ_O_DOUBLE_ITEM_1411_VOID(cost)
BSON_READ_OBJECT_1411_END(cost)

//struct __rd1witsml__cs_USCOREdrillReportStatusInfo_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREdrillReportStatusInfo)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, dTim)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, md, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, tvd, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, mdPlugTop, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, diaHole, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, mdDiaHoleStart, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, diaPilot, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, mdDiaPilotPlan, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, tvdDiaPilotPlan, wellVerticalDepthCoord)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, typeWellbore, WellboreType)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, mdKickoff, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, tvdKickoff, measuredDepthCoord)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, parentWellbore, cs_USCOREwellAlias)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, strengthForm, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, mdStrengthForm, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, tvdStrengthForm, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, diaCsgLast, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, mdCsgLast, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, tvdCsgLast, wellVerticalDepthCoord)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, presTestType, PresTestType)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, mdPlanned, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, distDrill, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, elevKelly, wellElevationCoord)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, sum24Hr)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, forecast24Hr)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, ropCurrent, velocityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, rig, refNameString)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, eTimStart, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, eTimSpud, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, eTimLoc, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, eTimDrill, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, ropAv, velocityMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, supervisor)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, engineer)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, geologist)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, eTimDrillRot, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, eTimDrillSlid, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, eTimCirc, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, eTimReam, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, eTimHold, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, eTimSteering, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, distDrillRot, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, distDrillSlid, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, distReam, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, distHold, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, distSteering, lengthMeasure)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, numPob)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, numContract)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, numOperator)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, numService)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, numAFE)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, costDay, cost)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, costDayMud, cost)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, conditionHole)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, tvdLot, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, presLotEmw, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, presKickTol, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, volKickTol, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, maasp, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStatusInfo, tubular, refNameString)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREdrillReportStatusInfo, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREdrillReportStatusInfo)

//struct __rd1witsml__cs_USCOREbitRecord_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREbitRecord)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, numBit)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, diaBit, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, diaPassThru, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, diaPilot, lengthMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, manufacturer)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, typeBit, BitType)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, cost, cost)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, codeMfg)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, codeIADC)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, condInitInner)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, condInitOuter)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, condInitDull, BitDullCode)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, condInitLocation)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, condInitBearing)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, condInitGauge)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, condInitOther)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, condInitReason, BitReasonPulled)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, condFinalInner)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, condFinalOuter)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, condFinalDull, BitDullCode)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, condFinalLocation)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, condFinalBearing)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, condFinalGauge)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, condFinalOther)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, condFinalReason, BitReasonPulled)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, drive)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, bitClass)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, customData, cs_USCOREcustomData)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbitRecord, extensionAny, cs_USCOREextensionAny)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREbitRecord, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREbitRecord)

//struct __rd1witsml__cs_USCORErheometer_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCORErheometer)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErheometer, tempRheom, thermodynamicTemperatureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErheometer, presRheom, pressureMeasure)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErheometer, vis3Rpm)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErheometer, vis6Rpm)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErheometer, vis100Rpm)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErheometer, vis200Rpm)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErheometer, vis300Rpm)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErheometer, vis600Rpm)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCORErheometer, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCORErheometer)

//struct __rd1witsml__cs_USCOREfluid_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREfluid)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, type)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, locationSample)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, dTim)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, md, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, tvd, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, presBopRating, pressureMeasure)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, mudClass, MudClass)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, density, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, visFunnel, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, tempVis, thermodynamicTemperatureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, pv, dynamicViscosityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, yp, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, gel10Sec, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, gel10Min, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, gel30Min, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, filterCakeLtlp, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, filtrateLtlp, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, tempHthp, thermodynamicTemperatureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, presHthp, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, filtrateHthp, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, filterCakeHthp, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, solidsPc, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, waterPc, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, oilPc, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, sandPc, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, solidsLowGravPc, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, solidsCalcPc, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, baritePc, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, lcm, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, mbt, equivalentPerMassMeasure)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, ph)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, tempPh, thermodynamicTemperatureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, pm, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, pmFiltrate, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, mf, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, alkalinityP1, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, alkalinityP2, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, chloride, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, calcium, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, magnesium, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, potassium, densityMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, rheometer, cs_USCORErheometer)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, brinePc, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, lime, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, electStab, electricPotentialMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, calciumChloride, densityMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, company)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, engineer)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, asg)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, solidsHiGravPc, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, polymer, volumePerVolumeMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, polyType)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, solCorPc, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, oilCtg, massConcentrationMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, hardnessCa, massConcentrationMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, sulfide, densityMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREfluid, comments)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREfluid, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREfluid)

//struct __rd1witsml__cs_USCOREdrillReportPorePressure_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREdrillReportPorePressure)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportPorePressure, readingKind, ReadingKind)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportPorePressure, equivalentMudWeight, densityMeasure)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportPorePressure, dTim)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportPorePressure, md, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportPorePressure, tvd, wellVerticalDepthCoord)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREdrillReportPorePressure, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREdrillReportPorePressure)

//struct rd1witsml__timestampedCommentString
BSON_READ_OBJECT_1411_BEGIN(timestampedCommentString)
  READ_O_PUT_MULTIPLE_ATTRIBUTES_TYPED_1411_OR_ELSE_GOTO_RESUME(timestampedCommentString,
    SET_MULTIPLE_ATTRIBUTES(
      ATTR_KEY_TYPED_1411(timestampedCommentString, _CWS_NULLABLE_DATE_TIME, dTim)
    )
  )
  READ_O_UTF8_OBJECT_ITEM_1411_VOID(timestampedCommentString)
BSON_READ_OBJECT_1411_END(timestampedCommentString)

//struct __rd1witsml__cs_USCOREdrillReportSurveyStation_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREdrillReportSurveyStation)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportSurveyStation, dTim)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportSurveyStation, md, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportSurveyStation, tvd, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportSurveyStation, incl, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportSurveyStation, azi, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportSurveyStation, vertSect, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportSurveyStation, dls, anglePerLengthMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportSurveyStation, location, cs_USCORElocation)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREdrillReportSurveyStation, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREdrillReportSurveyStation)

//struct __rd1witsml__cs_USCOREactivity_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREactivity)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, dTimStart)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, dTimEnd)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, duration, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, md, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, tvd, wellVerticalDepthCoord)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, phase)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, activityCode)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, proprietaryCode, nameStruct)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, detailActivity)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, typeActivityClass, ActivityClassType)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, mdHoleStart, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, tvdHoleStart, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, mdHoleEnd, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, tvdHoleEnd, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, mdBitStart, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, mdBitEnd, measuredDepthCoord)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, state)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, stateDetailActivity, StateDetailActivity)
  READ_A_UTF8_OBJECT_WITH_ALIAS_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, operator_, operator)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, tubular, refNameString)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, optimum)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, productive)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, itemState, ItemState)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREactivity, comments)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREactivity, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREactivity)

//struct __rd1witsml__cs_USCOREdrillReportLogInfo_sequence_
BSON_READ_OBJECT_1411_BEGIN_C(cs_USCOREdrillReportLogInfo, _)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_C(cs_USCOREdrillReportLogInfo, tempBHST, thermodynamicTemperatureMeasure, _)
  READ_O_OBJECT_1411_VOID_C(cs_USCOREdrillReportLogInfo, eTimStatic, timeMeasure, _)
BSON_READ_OBJECT_1411_END_C(cs_USCOREdrillReportLogInfo, _)

//struct __rd1witsml__cs_USCOREdrillReportLogInfo_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREdrillReportLogInfo)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportLogInfo, dTim)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportLogInfo, runNumber)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportLogInfo, serviceCompany)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportLogInfo, mdTop, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportLogInfo, mdBottom, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportLogInfo, tvdTop, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportLogInfo, tvdBottom, wellVerticalDepthCoord)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportLogInfo, tool)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportLogInfo, tempBHCT, thermodynamicTemperatureMeasure)
//        struct __rd1witsml__cs_USCOREdrillReportLogInfo_sequence_ *__cs_USCOREdrillReportLogInfo_sequence_;
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B1(cs_USCOREdrillReportLogInfo, __cs_USCOREdrillReportLogInfo_sequence_, cs_USCOREdrillReportLogInfo, _)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportLogInfo, mdTempTool, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportLogInfo, tvdTempTool, wellVerticalDepthCoord)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREdrillReportLogInfo, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREdrillReportLogInfo)

//struct __rd1witsml__cs_USCOREdrillReportCoreInfo_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREdrillReportCoreInfo)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportCoreInfo, dTim)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportCoreInfo, coreNumber)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportCoreInfo, mdTop, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportCoreInfo, mdBottom, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportCoreInfo, tvdTop, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportCoreInfo, tvdBottom, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportCoreInfo, lenRecovered, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportCoreInfo, recoverPc, volumePerVolumeMeasurePercent)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportCoreInfo, lenBarrel, lengthMeasure)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportCoreInfo, innerBarrelType, InnerBarrelType)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportCoreInfo, coreDescription)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREdrillReportCoreInfo, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREdrillReportCoreInfo)

//struct __rd1witsml__cs_USCOREdrillReportWellTestInfo_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREdrillReportWellTestInfo)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, dTim)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, testType, WellTestType)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, testNumber)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, mdTop, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, mdBottom, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, tvdTop, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, tvdBottom, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, chokeOrificeSize, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, densityOil, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, densityWater, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, densityGas, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, flowRateOil, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, flowRateWater, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, flowRateGas, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, presShutIn, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, presFlowing, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, presBottom, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, gasOilRatio, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, waterOilRatio, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, chloride, massConcentrationMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, carbonDioxide, massConcentrationMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, hydrogenSulfide, massConcentrationMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, volOilTotal, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, volGasTotal, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, volWaterTotal, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportWellTestInfo, volOilStored, volumeMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREdrillReportWellTestInfo, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREdrillReportWellTestInfo)

//struct __rd1witsml__cs_USCOREdrillReportFormTestInfo_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREdrillReportFormTestInfo)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportFormTestInfo, dTim)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportFormTestInfo, md, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportFormTestInfo, tvd, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportFormTestInfo, presPore, pressureMeasure)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportFormTestInfo, goodSeal)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportFormTestInfo, mdSample, measuredDepthCoord)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportFormTestInfo, dominateComponent)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportFormTestInfo, densityHC, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportFormTestInfo, volumeSample, volumeMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportFormTestInfo, description)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREdrillReportFormTestInfo, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREdrillReportFormTestInfo)

//struct __rd1witsml__cs_USCOREdrillReportLithShowInfo_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREdrillReportLithShowInfo)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportLithShowInfo, dTim)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportLithShowInfo, mdTop, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportLithShowInfo, mdBottom, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportLithShowInfo, tvdTop, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportLithShowInfo, tvdBottom, wellVerticalDepthCoord)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportLithShowInfo, show)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportLithShowInfo, lithology)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREdrillReportLithShowInfo, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREdrillReportLithShowInfo)

//struct __rd1witsml__cs_USCOREdrillReportEquipFailureInfo_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREdrillReportEquipFailureInfo)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportEquipFailureInfo, dTim)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportEquipFailureInfo, md, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportEquipFailureInfo, tvd, wellVerticalDepthCoord)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportEquipFailureInfo, equipClass)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportEquipFailureInfo, eTimMissProduction, timeMeasure)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportEquipFailureInfo, dTimRepair)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportEquipFailureInfo, description)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREdrillReportEquipFailureInfo, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREdrillReportEquipFailureInfo)

//struct __rd1witsml__cs_USCOREdrillReportControlIncidentInfo_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREdrillReportControlIncidentInfo)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, dTim)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, mdInflow, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, tvdInflow, wellVerticalDepthCoord)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, phase)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, activityCode)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, proprietaryCode, nameStruct)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, detailActivity)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, eTimLost, timeMeasure)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, dTimRegained)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, diaBit, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, mdBit, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, wtMud, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, porePressure, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, diaCsgLast, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, mdCsgLast, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, volMudGained, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, presShutInCasing, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, presShutInDrill, pressureMeasure)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, incidentType, WellControlIncidentType)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, killingType, WellKillingProcedureType)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, formation)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, tempBottom, thermodynamicTemperatureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, presMaxChoke, pressureMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportControlIncidentInfo, description)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREdrillReportControlIncidentInfo, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREdrillReportControlIncidentInfo)

//struct __rd1witsml__cs_USCOREdrillReportStratInfo_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREdrillReportStratInfo)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStratInfo, dTim)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStratInfo, mdTop, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStratInfo, tvdTop, wellVerticalDepthCoord)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportStratInfo, description)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREdrillReportStratInfo, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREdrillReportStratInfo)

//struct __rd1witsml__cs_USCOREdrillReportPerfInfo_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREdrillReportPerfInfo)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportPerfInfo, dTimOpen)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportPerfInfo, dTimClose)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportPerfInfo, mdTop, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportPerfInfo, mdBottom, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportPerfInfo, tvdTop, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportPerfInfo, tvdBottom, wellVerticalDepthCoord)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREdrillReportPerfInfo, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREdrillReportPerfInfo)

//struct __rd1witsml__cs_USCOREdrillReportGasReadingInfo_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREdrillReportGasReadingInfo)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportGasReadingInfo, dTim)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportGasReadingInfo, readingType, GasPeakType)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportGasReadingInfo, mdTop, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportGasReadingInfo, mdBottom, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportGasReadingInfo, tvdTop, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportGasReadingInfo, tvdBottom, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportGasReadingInfo, gasHigh, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportGasReadingInfo, gasLow, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportGasReadingInfo, meth, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportGasReadingInfo, eth, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportGasReadingInfo, prop, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportGasReadingInfo, ibut, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportGasReadingInfo, nbut, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdrillReportGasReadingInfo, ipent, volumePerVolumeMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREdrillReportGasReadingInfo, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREdrillReportGasReadingInfo)

//struct rd1witsml__shortNameStruct
BSON_READ_OBJECT_1411_BEGIN(shortNameStruct)
  READ_O_PUT_SINGLE_ATTRIBUTE_1411_OR_ELSE_GOTO_RESUME(shortNameStruct, namingSystem)
  READ_O_UTF8_OBJECT_ITEM_1411_VOID(shortNameStruct)
BSON_READ_OBJECT_1411_END(shortNameStruct)

//struct rd1witsml__genericMeasure
BSON_READ_OBJECT_1411_BEGIN(genericMeasure)
  READ_O_PUT_SINGLE_ATTRIBUTE_1411_OR_ELSE_GOTO_RESUME(genericMeasure, uom)
  READ_O_DOUBLE_ITEM_1411_VOID(genericMeasure)
BSON_READ_OBJECT_1411_END(genericMeasure)

//struct __rd1witsml__cs_USCOREaxisDefinition_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREaxisDefinition)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREaxisDefinition, order)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREaxisDefinition, count)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREaxisDefinition, name)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREaxisDefinition, propertyType)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREaxisDefinition, uom)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREaxisDefinition, doubleValues)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREaxisDefinition, stringValues)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREaxisDefinition, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREaxisDefinition)

//struct __rd1witsml__cs_USCORElogCurveInfo_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCORElogCurveInfo)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogCurveInfo, mnemonic, shortNameStruct)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogCurveInfo, classWitsml)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogCurveInfo, classIndex)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogCurveInfo, unit)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogCurveInfo, mnemAlias, shortNameStruct)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogCurveInfo, nullValue)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogCurveInfo, alternateIndex)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogCurveInfo, wellDatum, refNameString)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogCurveInfo, minIndex, genericMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogCurveInfo, maxIndex, genericMeasure)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogCurveInfo, minDateTimeIndex)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogCurveInfo, maxDateTimeIndex)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogCurveInfo, curveDescription)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogCurveInfo, sensorOffset, lengthMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogCurveInfo, dataSource)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogCurveInfo, densData, perLengthMeasure)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogCurveInfo, traceState, LogTraceState)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogCurveInfo, traceOrigin, LogTraceOrigin)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogCurveInfo, typeLogData, LogDataType)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogCurveInfo, axisDefinition, cs_USCOREaxisDefinition)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCORElogCurveInfo, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCORElogCurveInfo)

//struct __rd1witsml__cs_USCORElogData_sequence
BSON_READ_ARRAY_OF_OBJECT_1411_BEGIN_B(cs_USCORElogData)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogData, mnemonicList)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORElogData, unitList)
  READ_A_ARRAY_OF_UTF8_OBJECT_1411_VOID_B(cs_USCORElogData, data)
BSON_READ_ARRAY_OF_OBJECT_1411_END_B(cs_USCORElogData)

//struct __rd1witsml__cs_USCOREmudLogParameter_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREmudLogParameter)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLogParameter, type, MudLogParameterType)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLogParameter, dTime)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLogParameter, mdTop, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLogParameter, mdBottom, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLogParameter, force, forceMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLogParameter, concentration, volumePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLogParameter, equivalentMudWeight, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLogParameter, pressureGradient, forcePerVolumeMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLogParameter, text)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLogParameter, commonTime, cs_USCOREcommonTime)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREmudLogParameter, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREmudLogParameter)

//struct rd1witsml__ratioGenericMeasure
BSON_READ_OBJECT_1411_BEGIN(ratioGenericMeasure)
  READ_O_PUT_MULTIPLE_ATTRIBUTES_TYPED_1411_OR_ELSE_GOTO_RESUME(ratioGenericMeasure,
    SET_MULTIPLE_ATTRIBUTES(
      ATTR_KEY_TYPED_1411(ratioGenericMeasure, _CWS_NULLABLE_XSD_STR, uom),
      ATTR_KEY_TYPED_1411(ratioGenericMeasure, _CWS_NULLABLE_DOUBLE, numerator),
      ATTR_KEY_TYPED_1411(ratioGenericMeasure, _CWS_NULLABLE_DOUBLE, denominator)
    )
  )
  READ_O_DOUBLE_ITEM_1411_VOID(ratioGenericMeasure)
BSON_READ_OBJECT_1411_END(ratioGenericMeasure)

//struct __rd1witsml__obj_USCORElog_sequence__
BSON_READ_OBJECT_1411_BEGIN_C(obj_USCORElog, __)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_C(obj_USCORElog, startIndex, genericMeasure, __)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_C(obj_USCORElog, endIndex, genericMeasure, __)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_C(obj_USCORElog, stepIncrement, ratioGenericMeasure, __)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_C(obj_USCORElog, startDateTimeIndex, __)
  READ_O_TIME_NULLABLE_1411_VOID_C(obj_USCORElog, endDateTimeIndex, __)
BSON_READ_OBJECT_1411_END_C(obj_USCORElog, __)

//struct rd1witsml__objectSequence
BSON_READ_OBJECT_1411_BEGIN(objectSequence)
  READ_O_PUT_SINGLE_ATTRIBUTE_1411_OR_ELSE_GOTO_RESUME(objectSequence, description)
  READ_O_SHORT_ITEM_1411_VOID(objectSequence)
BSON_READ_OBJECT_1411_END(objectSequence)

//struct __rd1witsml__cs_USCOREmemberObject_sequence___
BSON_READ_OBJECT_1411_BEGIN_C(cs_USCOREmemberObject, ___)
  READ_O_OBJECT_1411_VOID_C(cs_USCOREmemberObject, sequence3, objectSequence, ___)
BSON_READ_OBJECT_1411_END_C_(cs_USCOREmemberObject)

//struct __rd1witsml__cs_USCOREmemberObject_sequence__
BSON_READ_OBJECT_1411_BEGIN_C(cs_USCOREmemberObject, __)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_C(cs_USCOREmemberObject, sequence2, objectSequence, __)
//        struct __rd1witsml__cs_USCOREmemberObject_sequence___ *__cs_USCOREmemberObject_sequence___;
  READ_O_OBJECT_1411_VOID_C1(cs_USCOREmemberObject, __, __cs_USCOREmemberObject_sequence___, cs_USCOREmemberObject, ___)
BSON_READ_OBJECT_1411_END_C(cs_USCOREmemberObject, __)

//struct __rd1witsml__cs_USCOREmemberObject_sequence_
BSON_READ_OBJECT_1411_BEGIN_C(cs_USCOREmemberObject, _)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_C(cs_USCOREmemberObject, sequence1, objectSequence, _)
// implement struct __rd1witsml__cs_USCOREmemberObject_sequence__ *__cs_USCOREmemberObject_sequence__
  READ_O_OBJECT_1411_VOID_C1(cs_USCOREmemberObject, _, __cs_USCOREmemberObject_sequence__, cs_USCOREmemberObject, __)
BSON_READ_OBJECT_1411_END_C(cs_USCOREmemberObject, _)

//struct __rd1witsml__cs_USCOREmemberObject_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREmemberObject)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmemberObject, objectReference, refObjectString)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmemberObject, indexType, LogIndexType)
//        struct __rd1witsml__cs_USCOREmemberObject_sequence_ *__cs_USCOREmemberObject_sequence_;
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B1(cs_USCOREmemberObject, __cs_USCOREmemberObject_sequence_, cs_USCOREmemberObject, _)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmemberObject, rangeMin, genericMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmemberObject, rangeMax, genericMeasure)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmemberObject, rangeDateTimeMin)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmemberObject, rangeDateTimeMax)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmemberObject, mnemonicList)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmemberObject, referenceDepth, measuredDepthCoord)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmemberObject, referenceDateTime)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmemberObject, param, indexedObject)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREmemberObject, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREmemberObject)

//struct __rd1witsml__cs_USCOREnameTag_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREnameTag)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREnameTag, name)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREnameTag, numberingScheme)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREnameTag, technology)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREnameTag, location)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREnameTag, installationDate)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREnameTag, installationCompany)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREnameTag, mountingCode)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREnameTag, comment)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREnameTag, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREnameTag)

//struct __rd1witsml__cs_USCOREdayCost_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREdayCost)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, numAFE)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, costGroup)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, costClass)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, costCode)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, costSubCode)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, costItemDescription)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, costPerItem, cost)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, itemKind)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, itemSize)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, qtyItem)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, costAmount, cost)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, numInvoice)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, numPO)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, numTicket)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, isCarryOver)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, isRental)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, nameTag, cs_USCOREnameTag)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, numSerial)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, nameVendor)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, numVendor)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, pool)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdayCost, estimated)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREdayCost, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREdayCost)

//struct __rd1witsml__cs_USCOREstnTrajRawData_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREstnTrajRawData)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajRawData, gravAxialRaw, accelerationLinearMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajRawData, gravTran1Raw, accelerationLinearMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajRawData, gravTran2Raw, accelerationLinearMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajRawData, magAxialRaw, magneticInductionMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajRawData, magTran1Raw, magneticInductionMeasure)
  READ_O_OBJECT_1411_VOID_B(cs_USCOREstnTrajRawData, magTran2Raw, magneticInductionMeasure)
BSON_READ_OBJECT_1411_END_B(cs_USCOREstnTrajRawData)

//struct __rd1witsml__cs_USCOREstnTrajCorUsed_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREstnTrajCorUsed)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajCorUsed, gravAxialAccelCor, accelerationLinearMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajCorUsed, gravTran1AccelCor, accelerationLinearMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajCorUsed, gravTran2AccelCor, accelerationLinearMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajCorUsed, magAxialDrlstrCor, magneticInductionMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajCorUsed, magTran1DrlstrCor, magneticInductionMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajCorUsed, magTran2DrlstrCor, magneticInductionMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajCorUsed, magTran1MSACor, magneticInductionMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajCorUsed, magTran2MSACor, magneticInductionMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajCorUsed, magAxialMSACor, magneticInductionMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajCorUsed, sagIncCor, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajCorUsed, sagAziCor, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajCorUsed, stnMagDeclUsed, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajCorUsed, stnGridCorUsed, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajCorUsed, stnGridConUsed, planeAngleMeasure)
  READ_O_OBJECT_1411_VOID_B(cs_USCOREstnTrajCorUsed, dirSensorOffset, lengthMeasure)
BSON_READ_OBJECT_1411_END_B(cs_USCOREstnTrajCorUsed)

//struct __rd1witsml__cs_USCOREstnTrajValid_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREstnTrajValid)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajValid, magTotalFieldCalc, magneticInductionMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajValid, magDipAngleCalc, planeAngleMeasure)
  READ_O_OBJECT_1411_VOID_B(cs_USCOREstnTrajValid, gravTotalFieldCalc, accelerationLinearMeasure)
BSON_READ_OBJECT_1411_END_B(cs_USCOREstnTrajValid)

//struct __rd1witsml__cs_USCOREstnTrajMatrixCov_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREstnTrajMatrixCov)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajMatrixCov, varianceNN, areaMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajMatrixCov, varianceNE, areaMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajMatrixCov, varianceNVert, areaMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajMatrixCov, varianceEE, areaMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajMatrixCov, varianceEVert, areaMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajMatrixCov, varianceVertVert, areaMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajMatrixCov, biasN, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstnTrajMatrixCov, biasE, lengthMeasure)
  READ_O_OBJECT_1411_VOID_B(cs_USCOREstnTrajMatrixCov, biasVert, lengthMeasure)
BSON_READ_OBJECT_1411_END_B(cs_USCOREstnTrajMatrixCov)

//struct __rd1witsml__cs_USCORErefWellboreTrajectoryStation_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCORErefWellboreTrajectoryStation)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErefWellboreTrajectoryStation, stationReference)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErefWellboreTrajectoryStation, trajectoryParent, refNameString)
  READ_O_OBJECT_1411_VOID_B(cs_USCORErefWellboreTrajectoryStation, wellboreParent, refNameString)
BSON_READ_OBJECT_1411_END_B(cs_USCORErefWellboreTrajectoryStation)

//struct __rd1witsml__cs_USCOREtrajectoryStation_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREtrajectoryStation)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, target, refNameString)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, dTimStn)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, typeTrajStation, TrajStationType)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, typeSurveyTool)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, calcAlgorithm)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, md, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, tvd, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, incl, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, azi, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, mtf, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, gtf, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, dispNs, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, dispEw, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, vertSect, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, dls, anglePerLengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, rateTurn, anglePerLengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, rateBuild, anglePerLengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, mdDelta, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, tvdDelta, lengthMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, modelToolError)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, iscwsaToolErrorModel, refNameString)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, gravTotalUncert, accelerationLinearMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, dipAngleUncert, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, magTotalUncert, magneticInductionMeasure)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, gravAccelCorUsed)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, magXAxialCorUsed)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, sagCorUsed)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, magDrlstrCorUsed)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, infieldRefCorUsed)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, interpolatedInfieldRefCorUsed)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, inHoleRefCorUsed)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, axialMagInterferenceCorUsed)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, cosagCorUsed)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, MSACorUsed)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, gravTotalFieldReference, accelerationLinearMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, magTotalFieldReference, magneticInductionMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, magDipAngleReference, planeAngleMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, magModelUsed)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, magModelValid)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, geoModelUsed)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, statusTrajStation, TrajStationStatus)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, rawData, cs_USCOREstnTrajRawData)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, corUsed, cs_USCOREstnTrajCorUsed)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, valid, cs_USCOREstnTrajValid)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, matrixCov, cs_USCOREstnTrajMatrixCov)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, location, cs_USCORElocation)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, sourceStation, cs_USCORErefWellboreTrajectoryStation)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtrajectoryStation, commonData, cs_USCOREcommonData)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREtrajectoryStation, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREtrajectoryStation)

BSON_READ_OBJECT_1411_BEGIN(refPositiveCount)
  READ_O_PUT_SINGLE_ATTRIBUTE_1411_OR_ELSE_GOTO_RESUME(refPositiveCount, uidRef)
  READ_O_SHORT_ITEM_1411_VOID(refPositiveCount)
BSON_READ_OBJECT_1411_END(refPositiveCount)

//struct __rd1witsml__cs_USCOREpitVolume_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREpitVolume)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpitVolume, pit, refPositiveCount)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpitVolume, dTim)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpitVolume, volPit, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpitVolume, densFluid, densityMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpitVolume, descFluid)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpitVolume, visFunnel, timeMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREpitVolume, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREpitVolume)

//struct __rd1witsml__cs_USCOREscr_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREscr)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREscr, dTim)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREscr, pump, refPositiveCount)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREscr, typeScr, ScrType)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREscr, rateStroke, anglePerTimeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREscr, presRecorded, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREscr, mdBit, measuredDepthCoord)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREscr, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREscr)

//struct __rd1witsml__cs_USCOREmudLosses_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREmudLosses)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLosses, volLostShakerSurf, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLosses, volLostMudCleanerSurf, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLosses, volLostPitsSurf, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLosses, volLostTrippingSurf, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLosses, volLostOtherSurf, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLosses, volTotMudLostSurf, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLosses, volLostCircHole, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLosses, volLostCsgHole, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLosses, volLostCmtHole, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLosses, volLostBhdCsgHole, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLosses, volLostAbandonHole, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudLosses, volLostOtherHole, volumeMeasure)
  READ_O_OBJECT_1411_VOID_B(cs_USCOREmudLosses, volTotMudLostHole, volumeMeasure)
BSON_READ_OBJECT_1411_END_B(cs_USCOREmudLosses)

//struct __rd1witsml__cs_USCOREmudVolume_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREmudVolume)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudVolume, volTotMudStart, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudVolume, volMudDumped, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudVolume, volMudReceived, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudVolume, volMudReturned, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudVolume, mudLosses, cs_USCOREmudLosses)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudVolume, volMudBuilt, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudVolume, volMudString, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudVolume, volMudCasing, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudVolume, volMudHole, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmudVolume, volMudRiser, volumeMeasure)
  READ_O_OBJECT_1411_VOID_B(cs_USCOREmudVolume, volTotMudEnd, volumeMeasure)
BSON_READ_OBJECT_1411_END_B(cs_USCOREmudVolume)

//struct __rd1witsml__cs_USCOREinventory_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREinventory)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREinventory, name)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREinventory, itemWtPerUnit, massMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREinventory, itemVolPerUnit, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREinventory, pricePerUnit, cost)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREinventory, qtyStart)
  READ_A_INT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREinventory, qtyAdjustment)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREinventory, qtyReceived)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREinventory, qtyReturned)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREinventory, qtyUsed)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREinventory, costItem, cost)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREinventory, qtyOnLocation)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREinventory, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREinventory)

//struct __rd1witsml__cs_USCORErigResponse_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCORErigResponse)
  READ_O_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, anchorTension, indexedObject)
  READ_O_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, anchorAngle, indexedObject)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, rigHeading, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, rigHeave, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, rigPitchAngle, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, rigRollAngle, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, riserAngle, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, riserDirection, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, riserTension, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, variableDeckLoad, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, totalDeckLoad, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, guideBaseAngle, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, ballJointAngle, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, ballJointDirection, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, offsetRig, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, loadLeg1, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, loadLeg2, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, loadLeg3, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, loadLeg4, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, penetrationLeg1, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, penetrationLeg2, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, penetrationLeg3, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, penetrationLeg4, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErigResponse, dispRig, lengthMeasure)
  READ_O_OBJECT_1411_VOID_B(cs_USCORErigResponse, meanDraft, lengthMeasure)
BSON_READ_OBJECT_1411_END_B(cs_USCORErigResponse)

//struct __rd1witsml__cs_USCOREpumpOp_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREpumpOp)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpumpOp, dTim)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpumpOp, pump, refPositiveCount)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpumpOp, typeOperation, PumpOpType)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpumpOp, idLiner, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpumpOp, lenStroke, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpumpOp, rateStroke, anglePerTimeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpumpOp, pressure, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpumpOp, pcEfficiency, relativePowerMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpumpOp, pumpOutput, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpumpOp, mdBit, measuredDepthCoord)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREpumpOp, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREpumpOp)

//struct __rd1witsml__cs_USCOREshakerScreen_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREshakerScreen)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshakerScreen, dTimStart)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshakerScreen, dTimEnd)
  READ_O_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshakerScreen, numDeck)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshakerScreen, meshX, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshakerScreen, meshY, lengthMeasure)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshakerScreen, manufacturer)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshakerScreen, model)
  READ_O_OBJECT_1411_VOID_B(cs_USCOREshakerScreen, cutPoint, lengthMeasure)
BSON_READ_OBJECT_1411_END_B(cs_USCOREshakerScreen)

//struct __rd1witsml__cs_USCOREshakerOp_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREshakerOp)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshakerOp, shaker, refNameString)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshakerOp, mdHole, measuredDepthCoord)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshakerOp, dTim)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshakerOp, hoursRun, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshakerOp, pcScreenCovered, areaPerAreaMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshakerOp, shakerScreen, cs_USCOREshakerScreen)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREshakerOp, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREshakerOp)

//struct __rd1witsml__cs_USCOREincident_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREincident)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREincident, dTim)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREincident, reporter)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREincident, numMinorInjury)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREincident, numMajorInjury)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREincident, numFatality)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREincident, isNearMiss)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREincident, descLocation)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREincident, descAccident)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREincident, remedialActionDesc)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREincident, causeDesc)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREincident, eTimLostGross, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREincident, costLostGross, cost)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREincident, responsibleCompany)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREincident, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREincident)

//struct __rd1witsml__cs_USCOREhse_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREhse)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, daysIncFree, timeMeasure)
  READ_O_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, incident, cs_USCOREincident)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, lastCsgPresTest)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, presLastCsg, pressureMeasure)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, lastBopPresTest)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, nextBopPresTest)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, presStdPipe, pressureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, presKellyHose, pressureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, presDiverter, pressureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, presAnnular, pressureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, presRams, pressureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, presChokeLine, pressureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, presChokeMan, pressureMeasure)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, lastFireBoatDrill)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, lastAbandonDrill)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, lastRigInspection)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, lastSafetyMeeting)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, lastSafetyInspection)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, lastTripDrill)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, lastDiverterDrill)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, lastBopDrill)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, regAgencyInsp)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, nonComplianceIssued)
  READ_O_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, numStopCards)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, fluidDischarged, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, volCtgDischarged, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, volOilCtgDischarge, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhse, wasteDischarged, volumeMeasure)
  READ_O_UTF8_OBJECT_1411_VOID_B(cs_USCOREhse, comments)
BSON_READ_OBJECT_1411_END_B(cs_USCOREhse)

//struct __rd1witsml__cs_USCOREpersonnel_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREpersonnel)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpersonnel, company)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpersonnel, typeService)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpersonnel, numPeople)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpersonnel, totalTime, timeMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREpersonnel, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREpersonnel)

//struct __rd1witsml__cs_USCOREsupportCraft_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREsupportCraft)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsupportCraft, name)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsupportCraft, typeSuppCraft, SupportCraft)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsupportCraft, dTimArrived)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsupportCraft, dTimDeparted)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsupportCraft, comments)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREsupportCraft, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREsupportCraft)

//struct __rd1witsml__cs_USCOREweather_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREweather)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, dTim)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, agency)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, barometricPressure, pressureMeasure)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, beaufortScaleNumber)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, tempSurfaceMn, thermodynamicTemperatureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, tempSurfaceMx, thermodynamicTemperatureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, tempWindChill, thermodynamicTemperatureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, tempsea, thermodynamicTemperatureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, visibility, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, aziWave, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, htWave, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, significantWave, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, maxWave, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, periodWave, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, aziWind, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, velWind, velocityMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, typePrecip)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, amtPrecip, lengthMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, coverCloud)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, ceilingCloud, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, currentSea, velocityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, aziCurrentSea, planeAngleMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREweather, comments)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREweather, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREweather)

//struct __rd1witsml__cs_USCOREbopComponent_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREbopComponent)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbopComponent, typeBopComp, BopType)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbopComponent, descComp)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbopComponent, idPassThru, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbopComponent, presWork, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbopComponent, diaCloseMn, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbopComponent, diaCloseMx, lengthMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbopComponent, nomenclature)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbopComponent, isVariable)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREbopComponent, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREbopComponent)

//struct __rd1witsml__cs_USCOREbop_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREbop)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, manufacturer)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, model)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, dTimInstall)
  READ_O_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, dTimRemove)
  READ_O_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, nameTag, cs_USCOREnameTag)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, typeConnectionBop)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, sizeConnectionBop, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, presBopRating, pressureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, sizeBopSys, lengthMeasure)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, rotBop)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, idBoosterLine, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, odBoosterLine, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, lenBoosterLine, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, idSurfLine, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, odSurfLine, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, lenSurfLine, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, idChkLine, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, odChkLine, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, lenChkLine, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, idKillLine, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, odKillLine, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, lenKillLine, lengthMeasure)
  READ_O_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, bopComponent, cs_USCOREbopComponent)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, typeDiverter)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, diaDiverter, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, presWorkDiverter, pressureMeasure)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, accumulator)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, capAccFluid, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, presAccPreCharge, pressureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, volAccPreCharge, volumeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, presAccOpRating, pressureMeasure)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, typeControlManifold)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, descControlManifold)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbop, typeChokeManifold)
  READ_O_OBJECT_1411_VOID_B(cs_USCOREbop, presChokeManifold, pressureMeasure)
BSON_READ_OBJECT_1411_END_B(cs_USCOREbop)

//struct __rd1witsml__cs_USCOREpit_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREpit)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpit, index)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpit, dTimInstall)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpit, dTimRemove)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpit, capMx, volumeMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpit, owner)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpit, typePit, PitType)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpit, isActive)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpit, nameTag, cs_USCOREnameTag)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREpit, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREpit)

//struct __rd1witsml__cs_USCOREpump_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREpump)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, index)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, manufacturer)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, model)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, dTimInstall)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, dTimRemove)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, owner)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, typePump, PumpType)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, numCyl)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, odRod, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, idLiner, lengthMeasure)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, pumpAction)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, eff, relativePowerMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, lenStroke, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, presMx, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, powHydMx, powerMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, spmMx, anglePerTimeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, displacement, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, presDamp, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, volDamp, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, powMechMx, powerMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpump, nameTag, cs_USCOREnameTag)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREpump, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREpump)

//struct __rd1witsml__cs_USCOREshaker_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREshaker)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshaker, name)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshaker, manufacturer)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshaker, model)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshaker, dTimInstall)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshaker, dTimRemove)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshaker, type)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshaker, locationShaker)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshaker, numDecks)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshaker, numCascLevel)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshaker, mudCleaner)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshaker, capFlow, volumeFlowRateMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshaker, owner)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshaker, sizeMeshMn, lengthMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREshaker, nameTag, cs_USCOREnameTag)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREshaker, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREshaker)

//struct __rd1witsml__cs_USCOREcentrifuge_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREcentrifuge)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcentrifuge, manufacturer)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcentrifuge, model)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcentrifuge, dTimInstall)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcentrifuge, dTimRemove)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcentrifuge, type)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcentrifuge, capFlow, volumeFlowRateMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcentrifuge, owner)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREcentrifuge, nameTag, cs_USCOREnameTag)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREcentrifuge, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREcentrifuge)

//struct __rd1witsml__cs_USCOREhydrocyclone_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREhydrocyclone)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhydrocyclone, manufacturer)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhydrocyclone, model)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhydrocyclone, dTimInstall)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhydrocyclone, dTimRemove)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhydrocyclone, type)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhydrocyclone, descCone)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhydrocyclone, owner)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREhydrocyclone, nameTag, cs_USCOREnameTag)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREhydrocyclone, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREhydrocyclone)

//struct __rd1witsml__cs_USCOREdegasser_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREdegasser)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdegasser, manufacturer)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdegasser, model)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdegasser, dTimInstall)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdegasser, dTimRemove)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdegasser, type)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdegasser, owner)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdegasser, height, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdegasser, len, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdegasser, id, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdegasser, capFlow, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdegasser, areaSeparatorFlow, areaMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdegasser, htMudSeal, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdegasser, idInlet, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdegasser, idVentLine, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdegasser, lenVentLine, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdegasser, capGasSep, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdegasser, capBlowdown, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdegasser, presRating, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdegasser, tempRating, thermodynamicTemperatureMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREdegasser, nameTag, cs_USCOREnameTag)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREdegasser, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREdegasser)

//struct __rd1witsml__cs_USCOREsurfaceEquipment_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREsurfaceEquipment)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, description)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, presRating, pressureMeasure)
  READ_O_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, typeSurfEquip, SurfEquipType)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, usePumpDischarge)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, useStandpipe)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, useHose)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, useSwivel)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, useKelly)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, useTopStack)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, useInjStack)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, useSurfaceIron)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, idStandpipe, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, lenStandpipe, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, idHose, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, lenHose, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, idSwivel, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, lenSwivel, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, idKelly, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, lenKelly, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, idSurfaceIron, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, lenSurfaceIron, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, htSurfaceIron, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, idDischargeLine, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, lenDischargeLine, lengthMeasure)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, ctWrapType)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, odReel, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, odCore, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, widReelWrap, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, lenReel, lengthMeasure)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, injStkUp)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, htInjStk, lengthMeasure)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, umbInside)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, odUmbilical, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, lenUmbilical, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, idTopStk, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurfaceEquipment, htTopStk, lengthMeasure)
  READ_O_OBJECT_1411_VOID_B(cs_USCOREsurfaceEquipment, htFlange, lengthMeasure)
BSON_READ_OBJECT_1411_END_B(cs_USCOREsurfaceEquipment)

//struct __rd1witsml__cs_USCOREswcSample_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREswcSample)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREswcSample, md, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREswcSample, lithology, cs_USCORElithology)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREswcSample, show, cs_USCOREshow)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREswcSample, nameFormation)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREswcSample, comments)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREswcSample, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREswcSample)

//struct __rd1witsml__cs_USCOREstimProppantUsage_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREstimProppantUsage)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimProppantUsage, name)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimProppantUsage, mass, massMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREstimProppantUsage, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREstimProppantUsage)

//struct __rd1witsml__cs_USCOREstimShutInPressure_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREstimShutInPressure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimShutInPressure, pres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimShutInPressure, timeAfterShutin, timeMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREstimShutInPressure, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREstimShutInPressure)

//struct __rd1witsml__cs_USCOREstimTubular_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREstimTubular)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimTubular, type)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimTubular, id, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimTubular, od, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimTubular, weight, massPerLengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimTubular, mdTop, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimTubular, mdBottom, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimTubular, tvdTop, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimTubular, tvdBottom, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimTubular, volumeFactor, volumePerLengthMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREstimTubular, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREstimTubular)

//struct __rd1witsml__cs_USCOREstimAdditive_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREstimAdditive)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimAdditive, name)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimAdditive, kind, StimAdditiveType)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimAdditive, volume, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimAdditive, mass, massMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREstimAdditive, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREstimAdditive)

//struct __rd1witsml__cs_USCOREstimProppant_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREstimProppant)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimProppant, name)
  READ_O_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimProppant, kind, StimProppantType)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimProppant, weight, massMeasure)
  READ_O_UTF8_OBJECT_1411_VOID_B(cs_USCOREstimProppant, sieveSize)
BSON_READ_OBJECT_1411_END_B(cs_USCOREstimProppant)

//struct __rd1witsml__cs_USCOREstimFluid_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREstimFluid)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFluid, name)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFluid, fluidVol, volumeMeasure)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFluid, waterSource)
  READ_O_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFluid, additive, cs_USCOREstimAdditive)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFluid, proppant, cs_USCOREstimProppant)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFluid, density, densityMeasure)
  READ_O_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFluid, pH)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFluid, purpose)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFluid, description)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFluid, supplier)
  READ_O_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFluid, fluidType, StimFluidType)
  READ_O_OBJECT_ENUM_NULLABLE_1411_VOID_B(cs_USCOREstimFluid, fluidSubtype, StimFluidSubtype)
BSON_READ_OBJECT_1411_END_B(cs_USCOREstimFluid)

//struct __rd1witsml__cs_USCOREstimJobStage_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREstimJobStage)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, kind, StimStageType)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, name)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, description)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, number)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, dTimStart)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, dTimEnd)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, pumpTime, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, startRateSurfaceLiquid, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, endRateSurfaceLiquid, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgRateSurfaceLiquid, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, startRateSurfaceCO2, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, endRateSurfaceCO2, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgRateSurfaceCO2, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, startStdRateSurfaceN2, standardVolumePerTimeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, endStdRateSurfaceN2, standardVolumePerTimeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgStdRateSurfaceN2, standardVolumePerTimeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, startPresSurface, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, endPresSurface, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, averagePresSurface, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, startPumpRateBottomhole, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, endPumpRateBottomhole, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgPumpRateBottomhole, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, startPresBottomhole, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, endPresBottomhole, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, averagePresBottomhole, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, startProppantConcSurface, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, endProppantConcSurface, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgProppantConcSurface, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, startProppantConcBottomhole, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, endProppantConcBottomhole, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgProppantConcBottomhole, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, startFoamRateN2, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, endFoamRateN2, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, startFoamRateCO2, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, endFoamRateCO2, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, fluidVolBase, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, fluidVolSlurry, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, slurryRateBegin, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, slurryRateEnd, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, proppantMassWellHead, massMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, proppantMass, massMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, maxPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, maxSlurryRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, maxWellheadRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, maxN2StdRate, standardVolumePerTimeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, maxCO2LiquidRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, maxPropConc, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, maxSlurryPropConc, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgPropConc, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgSlurryPropConc, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgTemperature, thermodynamicTemperatureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgInternalPhaseFraction, volumePerVolumeMeasurePercent)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgBaseFluidQuality, volumePerVolumeMeasurePercent)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgN2BaseFluidQuality, volumePerVolumeMeasurePercent)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgCO2BaseFluidQuality, volumePerVolumeMeasurePercent)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgHydraulicPower, powerMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgBaseFluidRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgSlurryRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgWellheadRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgN2StdRate, standardVolumePerTimeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgCO2Rate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, baseFluidVol, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, slurryVol, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, wellheadVol, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, maxPmaxPacPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, maxPmaxWeaklinkPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, maxGelRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, maxOilRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, maxAcidRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgGelRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgOilRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, avgAcidRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, gelVolume, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, oilVolume, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, acidVolume, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, baseFluidBypassVol, volumeMeasure)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, frictionFactor)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobStage, stageFluid, cs_USCOREstimFluid)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREstimJobStage, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREstimJobStage)

//struct __rd1witsml__cs_USCOREstimEvent_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREstimEvent)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimEvent, number)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimEvent, dTim)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimEvent, comment)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimEvent, numStage)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREstimEvent, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREstimEvent)

//struct __rd1witsml__cs_USCOREstimFlowPath_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREstimFlowPath)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, kind, StimStageFlowPathType)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, name)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, description)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, maxTreatmentPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, maxSlurryRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, maxWellheadRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, maxN2StdRate, standardVolumePerTimeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, maxCO2LiquidRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, maxGelRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, maxOilRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, maxAcidRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, maxPropConc, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, maxSlurryPropConc, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, avgTreatPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, avgBaseFluidRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, avgSlurryRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, avgWellheadRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, avgN2StdRate, standardVolumePerTimeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, avgCO2LiquidRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, avgGelRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, avgOilRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, avgAcidRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, avgPropConc, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, avgSlurryPropConc, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, avgTemperature, thermodynamicTemperatureMeasure)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, avgIntervalPhaseFraction)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, avgBaseFluidQuality, volumePerVolumeMeasurePercent)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, avgN2BaseFluidQuality, volumePerVolumeMeasurePercent)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, avgCO2BaseFluidQuality, volumePerVolumeMeasurePercent)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, avgHydraulicPower, powerMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, baseFluidVol, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, slurryVol, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, wellheadVol, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, stdVolN2, standardVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, massCO2, massMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, gelVol, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, oilVol, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, acidVol, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, baseFluidBypassVol, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, propMass, massMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, maxPmaxPacPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, maxPmaxWeaklinkPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, avgPmaxPacPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, avgPmaxWeaklinkPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, shutinPres5Min, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, shutinPres10Min, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, shutinPres15Min, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, breakDownPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, percentPad, volumePerVolumeMeasurePercent)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, fractureGradient, forcePerVolumeMeasure)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, pipeFrictionFactor)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, stageCount)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, tubular, cs_USCOREstimTubular)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, jobStage, cs_USCOREstimJobStage)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFlowPath, jobEvent, cs_USCOREstimEvent)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREstimFlowPath, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREstimFlowPath)

//struct __rd1witsml__cs_USCOREstimPressureFlowRate_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREstimPressureFlowRate)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPressureFlowRate, pres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPressureFlowRate, bottomholeRate, volumeFlowRateMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREstimPressureFlowRate, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREstimPressureFlowRate)

//struct __rd1witsml__cs_USCOREstimStepTest_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREstimStepTest)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimStepTest, presMeasurement, cs_USCOREstimPressureFlowRate)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimStepTest, fractureExtensionPres, pressureMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREstimStepTest, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREstimStepTest)

//struct __rd1witsml__cs_USCOREstimFetTest_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREstimFetTest)
  READ_A_ARRAY_OF_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFetTest, analysisMethod, StimAnalysisMethod)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFetTest, dTimStart)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFetTest, dTimEnd)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFetTest, endPdlDuration, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFetTest, fractureCloseDuration, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFetTest, fractureClosePres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFetTest, fractureExtensionPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFetTest, netPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFetTest, porePres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFetTest, pseudoRadialPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFetTest, fractureLength, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFetTest, fractureWidth, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFetTest, fluidEfficiency, volumePerVolumeMeasurePercent)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFetTest, pdlCoef)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimFetTest, residualPermeability, permeabilityRockMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREstimFetTest, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREstimFetTest)

//struct __rd1witsml__cs_USCOREstimPumpFlowBackTest_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREstimPumpFlowBackTest)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPumpFlowBackTest, fractureCloseDuration, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPumpFlowBackTest, fractureClosePres, pressureMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREstimPumpFlowBackTest, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREstimPumpFlowBackTest)

//struct __rd1witsml__cs_USCOREstimTestStep_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREstimTestStep)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimTestStep, number)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimTestStep, bottomholeRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimTestStep, pres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimTestStep, pipeFriction, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimTestStep, entryFriction, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimTestStep, perfFriction, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimTestStep, nearWellboreFriction, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimTestStep, surfaceRate, volumeFlowRateMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREstimTestStep, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREstimTestStep)

//struct __rd1witsml__cs_USCOREstimStepDownTest_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREstimStepDownTest)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimStepDownTest, initialShutinPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimStepDownTest, bottomholeFluidDensity, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimStepDownTest, diameterEntryHole, lengthMeasure)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimStepDownTest, perforationCount)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimStepDownTest, dischargeCoefficient)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimStepDownTest, effectivePerfs)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimStepDownTest, step, cs_USCOREstimTestStep)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREstimStepDownTest, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREstimStepDownTest)

//struct __rd1witsml__cs_USCOREstimPdatSession_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREstimPdatSession)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, name)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, description)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, number)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, dTimPumpOn)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, dTimPumpOff)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, dTimWellShutin)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, dTimFractureClose)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, pumpDuration, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, avgBottomholeTreatmentPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, bottomholeHydrostaticPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, bubblePointPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, fractureClosePres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, frictionPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, initialShutinPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, porePres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, avgBottomholeTreatmentRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, fluidDensity, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, baseFluidVol, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, wellboreVolume, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, mdSurface, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, mdBottomhole, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, mdMidPerforation, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, tvdMidPerforation, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, surfaceTemperature, thermodynamicTemperatureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, bottomholeTemperature, thermodynamicTemperatureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, surfaceFluidTemperature, thermodynamicTemperatureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, fluidCompressibility, compressibilityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, reservoirTotalCompressibility, compressibilityMeasure)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, fluidNprimeFactor)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, fluidKprimeFactor)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, fluidSpecificHeat, specificHeatCapacityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, fluidThermalConductivity, thermalConductivityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, fluidThermalExpansionCoefficient, thermalVolumetricExpansionMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, fluidEfficiency, volumePerVolumeMeasurePercent)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, foamQuality, volumePerVolumeMeasurePercent)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, percentPad, volumePerVolumeMeasurePercent)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, stageNumber)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, temperatureCorrectionApplied)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, stepRateTest, cs_USCOREstimStepTest)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, fluidEfficiencyTest, cs_USCOREstimFetTest)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, pumpFlowBackTest, cs_USCOREstimPumpFlowBackTest)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPdatSession, stepDownTest, cs_USCOREstimStepDownTest)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREstimPdatSession, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREstimPdatSession)

//struct __rd1witsml__cs_USCOREstimReservoirInterval_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREstimReservoirInterval)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, mdLithTop, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, mdLithBottom, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, lithFormationPermeability, permeabilityRockMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, lithYoungsModulus, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, lithPorePres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, lithNetPayThickness, lengthMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, lithName)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, mdGrossPayTop, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, mdGrossPayBottom, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, grossPayThickness, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, netPayThickness, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, netPayPorePres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, netPayFluidCompressibility, compressibilityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, netPayFluidViscosity, dynamicViscosityMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, netPayName)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, netPayFormationPermeability, permeabilityRockMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, lithPoissonsRatio, dimensionlessMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, netPayFormationPorosity, volumePerVolumeMeasurePercent)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, formationPermeability, permeabilityRockMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, formationPorosity, volumePerVolumeMeasurePercent)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimReservoirInterval, nameFormation)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREstimReservoirInterval, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREstimReservoirInterval)

//struct __rd1witsml__cs_USCOREstimPerforationSet_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREstimPerforationSet)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPerforationSet, type)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPerforationSet, mdPerforationsTop, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPerforationSet, mdPerforationsBottom, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPerforationSet, tvdPerforationsTop, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPerforationSet, tvdPerforationsBottom, wellVerticalDepthCoord)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPerforationSet, perforationCount)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPerforationSet, size, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPerforationSet, densityPerforation, perLengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPerforationSet, phasingPerforation, planeAngleMeasure)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPerforationSet, frictionFactor)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPerforationSet, frictionPres, pressureMeasure)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimPerforationSet, dischargeCoefficient)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREstimPerforationSet, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREstimPerforationSet)

//struct __rd1witsml__cs_USCOREstimJobInterval_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREstimJobInterval)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, uidTreatmentInterval)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, name)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, number)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, dTimStart)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, dTimEnd)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, formationName)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, mdFormationTop, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, mdFormationBottom, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, tvdFormationTop, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, tvdFormationBottom, wellVerticalDepthCoord)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, openHoleName)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, openHoleDiameter, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, mdOpenHoleTop, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, mdOpenHoleBottom, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, tvdOpenHoleTop, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, tvdOpenHoleBottom, wellVerticalDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, totalFrictionPresLoss, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, totalPumpTime, timeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, maxPresTubing, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, maxPresCasing, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, maxPresAnnulus, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, maxFluidRateTubing, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, maxFluidRateCasing, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, maxFluidRateAnnulus, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, avgPresTubing, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, avgPresCasing, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, avgPresAnnulus, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, breakDownPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, averagePres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, avgBaseFluidReturnRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, avgSlurryReturnRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, avgBottomholeRate, volumeFlowRateMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, totalVolume, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, maxProppantConcSurface, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, maxProppantConcBottomhole, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, avgProppantConcSurface, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, avgProppantConcBottomhole, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, perfproppantConc, densityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, totalProppantMass, massMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, totalProppantUsage, cs_USCOREstimProppantUsage)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, percentProppantPumped, volumePerVolumeMeasurePercent)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, wellboreProppantMass, massMeasure)
  READ_A_ARRAY_OF_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, proppantName)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, formationProppantMass, massMeasure)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, perfBallCount)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, totalN2StdVolume, standardVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, totalCO2Mass, massMeasure)
  READ_A_ARRAY_OF_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, fluidName)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, fractureGradient, forcePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, finalFractureGradient, forcePerVolumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, initialShutinPres, pressureMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, shutinPres, cs_USCOREstimShutInPressure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, screenOutPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, hhpOrderedCO2, powerMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, hhpOrderedFluid, powerMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, hhpUsedCO2, powerMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, hhpUsedFluid, powerMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, perfBallSize, lengthMeasure)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, screenedOut)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, avgFractureWidth, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, avgConductivity, velocityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, netPres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, closurePres, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, closureDuration, timeMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, flowPath, cs_USCOREstimFlowPath)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, pdatSession, cs_USCOREstimPdatSession)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, reservoirInterval, cs_USCOREstimReservoirInterval)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, perforationInterval, cs_USCOREstimPerforationSet)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, avgBHStaticTemperature, thermodynamicTemperatureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, avgBHTreatingTemperature, thermodynamicTemperatureMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstimJobInterval, additive, cs_USCOREstimAdditive)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREstimJobInterval, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREstimJobInterval)

//struct __rd1witsml__cs_USCOREsurveySection_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREsurveySection)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurveySection, sequence)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurveySection, name)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurveySection, mdStart, measuredDepthCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurveySection, mdEnd, measuredDepthCoord)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurveySection, nameSurveyCompany)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurveySection, nameTool)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurveySection, typeTool)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurveySection, modelError)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurveySection, overwrite)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurveySection, frequencyMx, lengthMeasure)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurveySection, itemState, ItemState)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsurveySection, comments)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREsurveySection, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREsurveySection)

//struct __rd1witsml__cs_USCOREtargetSection_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREtargetSection)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtargetSection, sectNumber)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtargetSection, typeTargetSectionScope, TargetSectionScope)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtargetSection, lenRadius, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtargetSection, angleArc, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtargetSection, thickAbove, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtargetSection, thickBelow, lengthMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtargetSection, location, cs_USCORElocation)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREtargetSection, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREtargetSection)

//struct __rd1witsml__cs_USCORErefWellboreTrajectory_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCORErefWellboreTrajectory)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErefWellboreTrajectory, trajectoryReference, refNameString)
  READ_O_OBJECT_1411_VOID_B(cs_USCORErefWellboreTrajectory, wellboreParent, refNameString)
BSON_READ_OBJECT_1411_END_B(cs_USCORErefWellboreTrajectory)

//struct __rd1witsml__cs_USCOREnozzle_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREnozzle)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREnozzle, index)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREnozzle, diaNozzle, lengthMeasure)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREnozzle, typeNozzle, NozzleType)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREnozzle, len, lengthMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREnozzle, orientation)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREnozzle, customData, cs_USCOREcustomData)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREnozzle, extensionAny, cs_USCOREextensionAny)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREnozzle, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREnozzle)

//struct __rd1witsml__cs_USCOREconnection_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREconnection)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREconnection, id, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREconnection, od, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREconnection, len, lengthMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREconnection, typeThread)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREconnection, sizeThread, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREconnection, tensYield, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREconnection, tqYield, momentOfForceMeasure)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREconnection, position, ConnectionPosition)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREconnection, criticalCrossSection, areaMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREconnection, presLeak, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREconnection, tqMakeup, momentOfForceMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREconnection, customData, cs_USCOREcustomData)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREconnection, extensionAny, cs_USCOREextensionAny)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREconnection, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREconnection)

//struct __rd1witsml__cs_USCOREjar_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREjar)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREjar, forUpSet, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREjar, forDownSet, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREjar, forUpTrip, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREjar, forDownTrip, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREjar, forPmpOpen, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREjar, forSealFric, forceMeasure)
  READ_O_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREjar, typeJar, JarType)
  READ_O_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREjar, jarAction, JarAction)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREjar, customData, cs_USCOREcustomData)
  READ_O_OBJECT_1411_VOID_B(cs_USCOREjar, extensionAny, cs_USCOREextensionAny)
BSON_READ_OBJECT_1411_END_B(cs_USCOREjar)

//struct __rd1witsml__cs_USCOREsensor_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREsensor)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsensor, typeMeasurement, MeasurementType)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsensor, offsetBot, lengthMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsensor, comments)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsensor, customData, cs_USCOREcustomData)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREsensor, extensionAny, cs_USCOREextensionAny)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREsensor, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREsensor)

//struct __rd1witsml__cs_USCOREmwdTool_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREmwdTool)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmwdTool, flowrateMn, volumeFlowRateMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmwdTool, flowrateMx, volumeFlowRateMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmwdTool, tempMx, thermodynamicTemperatureMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmwdTool, idEquv, lengthMeasure)
  READ_O_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmwdTool, sensor, cs_USCOREsensor)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmwdTool, customData, cs_USCOREcustomData)
  READ_O_OBJECT_1411_VOID_B(cs_USCOREmwdTool, extensionAny, cs_USCOREextensionAny)
BSON_READ_OBJECT_1411_END_B(cs_USCOREmwdTool)

//struct __rd1witsml__cs_USCOREmotor_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREmotor)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmotor, offsetTool, lengthMeasure)
  READ_O_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmotor, presLossFact)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmotor, flowrateMn, volumeFlowRateMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmotor, flowrateMx, volumeFlowRateMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmotor, diaRotorNozzle, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmotor, clearanceBearBox, lengthMeasure)
  READ_O_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmotor, lobesRotor)
  READ_O_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmotor, lobesStator)
  READ_O_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmotor, typeBearing, BearingType)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmotor, tempOpMx, thermodynamicTemperatureMeasure)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmotor, rotorCatcher)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmotor, dumpValve)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmotor, diaNozzle, lengthMeasure)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmotor, rotatable)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmotor, bendSettingsMn, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmotor, bendSettingsMx, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREmotor, customData, cs_USCOREcustomData)
  READ_O_OBJECT_1411_VOID_B(cs_USCOREmotor, extensionAny, cs_USCOREextensionAny)
BSON_READ_OBJECT_1411_END_B(cs_USCOREmotor)

//struct __rd1witsml__cs_USCOREstabilizer_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREstabilizer)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstabilizer, lenBlade, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstabilizer, lenBladeGauge, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstabilizer, odBladeMx, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstabilizer, odBladeMn, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstabilizer, distBladeBot, lengthMeasure)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstabilizer, shapeBlade, BladeShapeType)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstabilizer, factFric)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstabilizer, typeBlade, BladeType)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstabilizer, customData, cs_USCOREcustomData)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstabilizer, extensionAny, cs_USCOREextensionAny)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREstabilizer, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREstabilizer)

//struct __rd1witsml__cs_USCOREbend_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREbend)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbend, angle, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbend, distBendBot, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbend, customData, cs_USCOREcustomData)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREbend, extensionAny, cs_USCOREextensionAny)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREbend, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREbend)

//struct __rd1witsml__cs_USCOREholeOpener_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREholeOpener)
  READ_O_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREholeOpener, typeHoleOpener, HoleOpenerType)
  READ_O_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREholeOpener, numCutter)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREholeOpener, manufacturer)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREholeOpener, diaHoleOpener, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREholeOpener, customData, cs_USCOREcustomData)
  READ_O_OBJECT_1411_VOID_B(cs_USCOREholeOpener, extensionAny, cs_USCOREextensionAny)
BSON_READ_OBJECT_1411_END_B(cs_USCOREholeOpener)

//struct __rd1witsml__cs_USCORErotarySteerableTool_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCORErotarySteerableTool)
  READ_O_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, deflectionMethod, DeflectionMethod)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, bendAngle, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, bendOffset, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, holeSizeMn, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, holeSizeMx, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, wobMx, forceMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, operatingSpeed, anglePerTimeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, speedMx, anglePerTimeMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, flowRateMn, volumeFlowRateMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, flowRateMx, volumeFlowRateMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, downLinkFlowRateMn, volumeFlowRateMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, downLinkFlowRateMx, volumeFlowRateMeasure)
  READ_O_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, pressLossFact)
  READ_O_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, padCount)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, padLen, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, padWidth, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, padOffset, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, openPadOd, lengthMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, closePadOd, lengthMeasure)
  READ_O_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, sensor, cs_USCOREsensor)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCORErotarySteerableTool, customData, cs_USCOREcustomData)
  READ_O_OBJECT_1411_VOID_B(cs_USCORErotarySteerableTool, extensionAny, cs_USCOREextensionAny)
BSON_READ_OBJECT_1411_END_B(cs_USCORErotarySteerableTool)

//struct __rd1witsml__cs_USCOREtubularComponent_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREtubularComponent)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, typeTubularComp, TubularComponent)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, sequence)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, description)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, id, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, od, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, odMx, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, len, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, lenJointAv, lengthMeasure)
  READ_A_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, numJointStand)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, wtPerLen, massPerLengthMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, grade)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, odDrift, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, tensYield, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, tqYield, momentOfForceMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, stressFatig, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, lenFishneck, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, idFishneck, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, odFishneck, lengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, disp, volumeMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, presBurst, pressureMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, presCollapse, pressureMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, classService)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, wearWall, lengthPerLengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, thickWall, lengthMeasure)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, configCon, BoxPinConfig)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, bendStiffness, forcePerLengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, axialStiffness, forcePerLengthMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, torsionalStiffness, forcePerLengthMeasure)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, typeMaterial, MaterialType)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, doglegMx, anglePerLengthMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, vendor)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, model)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, nameTag, cs_USCOREnameTag)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, bitRecord, cs_USCOREbitRecord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, areaNozzleFlow, areaMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, nozzle, cs_USCOREnozzle)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, connection, cs_USCOREconnection)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, jar, cs_USCOREjar)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, mwdTool, cs_USCOREmwdTool)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, motor, cs_USCOREmotor)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, stabilizer, cs_USCOREstabilizer)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, bend, cs_USCOREbend)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, holeOpener, cs_USCOREholeOpener)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, rotarySteerableTool, cs_USCORErotarySteerableTool)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, customData, cs_USCOREcustomData)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREtubularComponent, extensionAny, cs_USCOREextensionAny)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREtubularComponent, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREtubularComponent)

//struct rd1witsml__footageNorthSouth
BSON_READ_OBJECT_1411_BEGIN(footageNorthSouth)
  READ_O_PUT_MULTIPLE_ATTRIBUTES_1411_OR_ELSE_GOTO_RESUME(footageNorthSouth,
    SET_MULTIPLE_ATTRIBUTES(
      ATTR_ENUM_KEY_NULLABLE_1411(footageNorthSouth, uom, LengthUom),
      ATTR_ENUM_KEY_NULLABLE_1411(footageNorthSouth, ref, NorthOrSouth)
    )
  )
  READ_O_DOUBLE_ITEM_1411_VOID(footageNorthSouth)
BSON_READ_OBJECT_1411_END(footageNorthSouth)

//struct rd1witsml__footageEastWest
BSON_READ_OBJECT_1411_BEGIN(footageEastWest)
  READ_O_PUT_MULTIPLE_ATTRIBUTES_1411_OR_ELSE_GOTO_RESUME(footageEastWest,
    SET_MULTIPLE_ATTRIBUTES(
      ATTR_ENUM_KEY_NULLABLE_1411(footageEastWest, uom, LengthUom),
      ATTR_ENUM_KEY_NULLABLE_1411(footageEastWest, ref, EastOrWest)
    )
  )
  READ_O_DOUBLE_ITEM_1411_VOID(footageEastWest)
BSON_READ_OBJECT_1411_END(footageEastWest)

//struct __rd1witsml__cs_USCOREpublicLandSurveySystem_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREpublicLandSurveySystem)
  READ_O_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpublicLandSurveySystem, principalMeridian, PrincipalMeridian)
  READ_O_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpublicLandSurveySystem, range)
  READ_O_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpublicLandSurveySystem, rangeDir, EastOrWest)
  READ_O_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpublicLandSurveySystem, township)
  READ_O_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpublicLandSurveySystem, townshipDir, NorthOrSouth)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpublicLandSurveySystem, section)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpublicLandSurveySystem, quarterSection)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpublicLandSurveySystem, quarterTownship)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREpublicLandSurveySystem, footageNS, footageNorthSouth)
  READ_O_OBJECT_1411_VOID_B(cs_USCOREpublicLandSurveySystem, footageEW, footageEastWest)
BSON_READ_OBJECT_1411_END_B(cs_USCOREpublicLandSurveySystem)

//struct __rd1witsml__cs_USCOREreferencePoint_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREreferencePoint)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREreferencePoint, name)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREreferencePoint, type)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREreferencePoint, elevation, wellElevationCoord)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREreferencePoint, measuredDepth, measuredDepthCoord)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREreferencePoint, location, cs_USCORElocation)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREreferencePoint, description)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREreferencePoint, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREreferencePoint)

//struct __rd1witsml__cs_USCOREchangeHistory_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREchangeHistory)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchangeHistory, dTimChange)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchangeHistory, changeType, ChangeInfoType)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchangeHistory, objectGrowingState)
  READ_A_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchangeHistory, updatedHeader)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchangeHistory, changeInfo)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchangeHistory, startIndex, genericMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchangeHistory, endIndex, genericMeasure)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchangeHistory, startDateTimeIndex)
  READ_A_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchangeHistory, endDateTimeIndex)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREchangeHistory, mnemonics)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREchangeHistory, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREchangeHistory)

//struct __rd1witsml__cs_USCOREiscwsaAuthorizationData_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREiscwsaAuthorizationData)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaAuthorizationData, author)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaAuthorizationData, source)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaAuthorizationData, authority)
  READ_O_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaAuthorizationData, status, AuthorizationStatus)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaAuthorizationData, version)
  READ_O_UTF8_OBJECT_1411_VOID_B(cs_USCOREiscwsaAuthorizationData, comment)
BSON_READ_OBJECT_1411_END_B(cs_USCOREiscwsaAuthorizationData)

//struct __rd1witsml__cs_USCOREiscwsaSurveyToolOperatingCondition_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREiscwsaSurveyToolOperatingCondition)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaSurveyToolOperatingCondition, parameter)
  READ_A_OBJECT_ALIAS_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaSurveyToolOperatingCondition, min_, max, genericMeasure)
  READ_A_OBJECT_ALIAS_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaSurveyToolOperatingCondition, max_, max, genericMeasure)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaSurveyToolOperatingCondition, value)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREiscwsaSurveyToolOperatingCondition, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREiscwsaSurveyToolOperatingCondition)

//struct __rd1witsml__cs_USCOREiscwsaSurveyToolOperatingInterval_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREiscwsaSurveyToolOperatingInterval)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaSurveyToolOperatingInterval, mode, SurveyToolOperatingMode)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaSurveyToolOperatingInterval, start, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaSurveyToolOperatingInterval, end, planeAngleMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaSurveyToolOperatingInterval, speed, velocityMeasure)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaSurveyToolOperatingInterval, sampleRate, timeMeasure)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREiscwsaSurveyToolOperatingInterval, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREiscwsaSurveyToolOperatingInterval)

//struct __rd1witsml__cs_USCOREiscwsaModelParameters_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREiscwsaModelParameters)
  READ_O_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaModelParameters, misalignmentMode, ErrorModelMisalignmentMode)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaModelParameters, gyroInitialization, planeAngleMeasure)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaModelParameters, gyroReinitializationDistance, lengthMeasure)
  READ_O_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaModelParameters, switching)
  READ_O_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaModelParameters, noiseReductionFactor)
  READ_O_OBJECT_1411_VOID_B(cs_USCOREiscwsaModelParameters, gyroRunningSpeed, velocityMeasure)
BSON_READ_OBJECT_1411_END_B(cs_USCOREiscwsaModelParameters)

//struct rd1witsml__measureOrQuantity
BSON_READ_OBJECT_1411_BEGIN(measureOrQuantity)
  READ_O_PUT_SINGLE_ATTRIBUTE_1411_OR_ELSE_GOTO_RESUME(measureOrQuantity, uom)
  READ_O_DOUBLE_ITEM_1411_VOID(measureOrQuantity)
BSON_READ_OBJECT_1411_END(measureOrQuantity)

//struct __rd1witsml__cs_USCOREiscwsaErrorTermValue_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREiscwsaErrorTermValue)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaErrorTermValue, term, refNameString)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaErrorTermValue, prop, ErrorPropagationMode)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaErrorTermValue, bias)
  READ_A_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaErrorTermValue, value, measureOrQuantity)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaErrorTermValue, comment)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREiscwsaErrorTermValue, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREiscwsaErrorTermValue)

//struct __rd1witsml__cs_USCOREiscwsaNameAndDescription_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREiscwsaNameAndDescription)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaNameAndDescription, name)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaNameAndDescription, description)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREiscwsaNameAndDescription, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREiscwsaNameAndDescription)

//struct __rd1witsml__cs_USCOREiscwsaNomenclatureConstant_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREiscwsaNomenclatureConstant)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaNomenclatureConstant, name)
  READ_A_DOUBLE_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaNomenclatureConstant, value)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaNomenclatureConstant, unit)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaNomenclatureConstant, description)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREiscwsaNomenclatureConstant, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREiscwsaNomenclatureConstant)

//struct __rd1witsml__cs_USCOREiscwsaNomenclature_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREiscwsaNomenclature)
  READ_O_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaNomenclature, parameter, cs_USCOREiscwsaNameAndDescription)
  READ_O_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaNomenclature, function, cs_USCOREiscwsaNameAndDescription)
  READ_O_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREiscwsaNomenclature, constant, cs_USCOREiscwsaNomenclatureConstant)
BSON_READ_OBJECT_1411_END_B(cs_USCOREiscwsaNomenclature)

//struct __rd1witsml__cs_USCOREiscwsaErrorCoefficient_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREiscwsaErrorCoefficient)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaErrorCoefficient, azi)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaErrorCoefficient, inc)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaErrorCoefficient, depth)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaErrorCoefficient, tvd)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREiscwsaErrorCoefficient, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREiscwsaErrorCoefficient)

//struct __rd1witsml__cs_USCOREiscwsaErrorTerm_sequence
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_BEGIN_B(cs_USCOREiscwsaErrorTerm)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaErrorTerm, name)
  READ_A_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaErrorTerm, type, ErrorTermSource)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaErrorTerm, measureClass)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaErrorTerm, label)
  READ_A_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaErrorTerm, description)
  READ_A_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaErrorTerm, errorCoefficient, cs_USCOREiscwsaErrorCoefficient)
  READ_A_ARRAY_OF_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREiscwsaErrorTerm, operatingMode, SurveyToolOperatingMode)
  READ_A_ARRAY_OF_OBJECT_1411_VOID_B(cs_USCOREiscwsaErrorTerm, extensionNameValue, cs_USCOREextensionNameValue)
BSON_READ_ARRAY_OF_OBJECT_WITH_UID_1411_END_B(cs_USCOREiscwsaErrorTerm)

// AQUI

//struct rd1witsml__obj_USCOREattachments
READ_S_OBJECT_1411_BEGIN(attachment)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(attachment, objectReference, refObjectString)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(attachment, subObjectReference, refObjectString)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(attachment, md, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(attachment, mdBit, measuredDepthCoord)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(attachment, param, indexedObject)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(attachment, fileName)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(attachment, description)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(attachment, fileType)
// SPECIAL CASE
  bson_read_base64Binary1411(soap_internal, thisDocument, CWS_CONST_BSON_KEY("content"), &attachment_sequence_->content, 0);
READ_S_OBJECT_1411_END(attachment)

//struct rd1witsml__obj_USCOREbhaRuns
READ_S_OBJECT_1411_BEGIN(bhaRun)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(bhaRun, tubular, refNameString)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(bhaRun, dTimStart)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(bhaRun, dTimStop)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(bhaRun, dTimStartDrilling)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(bhaRun, dTimStopDrilling)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(bhaRun, planDogleg, anglePerLengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(bhaRun, actDogleg, anglePerLengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(bhaRun, actDoglegMx, anglePerLengthMeasure)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(bhaRun, statusBha, BhaStatus)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(bhaRun, numBitRun)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(bhaRun, numStringRun)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(bhaRun, reasonTrip)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(bhaRun, objectiveBha)
  READ_S_ARRAY_OF_OBJECT_1411_VOID(bhaRun, drillingParams, cs_USCOREdrillingParams)
READ_S_OBJECT_1411_END(bhaRun)

//struct rd1witsml__obj_USCOREcementJobs
READ_S_OBJECT_1411_BEGIN(cementJob)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(cementJob, jobType, CementJobType)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, jobConfig)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(cementJob, dTimJob)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, nameCementedString)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, holeConfig, cs_USCOREwbGeometry)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, nameWorkString)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, contractor)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, cementEngr)
  READ_S_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME(cementJob, offshoreJob)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, mdWater, lengthMeasure)
  READ_S_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME(cementJob, returnsToSeabed)
  READ_S_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME(cementJob, reciprocating)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, woc, timeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, mdPlugTop, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, mdPlugBot, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, mdHole, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, mdShoe, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, tvdShoe, wellVerticalDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, mdStringSet, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, tvdStringSet, wellVerticalDepthCoord)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, cementStage, cs_USCOREcementStage)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, cementTest, cs_USCOREcementTest)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, typePlug)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, nameCementString)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(cementJob, dTimPlugSet)
  READ_S_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME(cementJob, cementDrillOut)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(cementJob, dTimCementDrillOut)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, typeSqueeze)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, mdSqueeze, measuredDepthCoord)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(cementJob, dTimSqueeze)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, toolCompany)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, typeTool)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(cementJob, dTimPipeRotStart)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(cementJob, dTimPipeRotEnd)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, rpmPipe, anglePerTimeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, tqInitPipeRot, momentOfForceMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, tqPipeAv, momentOfForceMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, tqPipeMx, momentOfForceMeasure)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(cementJob, dTimRecipStart)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(cementJob, dTimRecipEnd)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, overPull, forceMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, slackOff, forceMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, rpmPipeRecip, anglePerTimeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(cementJob, lenPipeRecipStroke, lengthMeasure)
  READ_S_BOOLEAN_NULLABLE_1411_VOID(cementJob, coilTubing)
READ_S_OBJECT_1411_END(cementJob)

//struct __rd1witsml__obj_USCOREchangeLog_sequence_
READ_S_OBJECT_1411_BEGIN_C(changeLog)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(changeLog, sourceName)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(changeLog, lastChangeType, ChangeInfoType)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(changeLog, lastChangeInfo)
  READ_S_ARRAY_OF_OBJECT_1411_VOID(changeLog, changeHistory, cs_USCOREchangeHistory)
READ_S_OBJECT_1411_END_C(changeLog)

//struct rd1witsml__obj_USCOREconvCores
READ_S_OBJECT_1411_BEGIN(convCore)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(convCore, mdCoreTop, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(convCore, mdCoreBottom, measuredDepthCoord)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(convCore, dTimCoreStart)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(convCore, dTimCoreEnd)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(convCore, coreReference)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(convCore, coringContractor)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(convCore, analysisContractor)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(convCore, coreBarrel)
  READ_S_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME(convCore, innerBarrelUsed)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(convCore, innerBarrelType)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(convCore, lenBarrel, lengthMeasure)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(convCore, coreBitType)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(convCore, diaBit, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(convCore, diaCore, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(convCore, lenCored, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(convCore, lenRecovered, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(convCore, recoverPc, volumePerVolumeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(convCore, inclHole, planeAngleMeasure)
  READ_S_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME(convCore, coreOrientation)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(convCore, coreMethod)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(convCore, coreTreatmentMethod)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(convCore, coreFluidUsed)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(convCore, nameFormation)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(convCore, geologyInterval, cs_USCOREgeologyInterval)
  READ_S_UTF8_OBJECT_1411_VOID(convCore, coreDescription)
READ_S_OBJECT_1411_END(convCore)

/*
//struct rd1gml__GeodeticCRSType
BSON_READ_OBJECT_1411_BEGIN_B(GeodeticCRSType)
  READ_O_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(GeodeticCRSType, remarks)
//  READ_O_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(GeodeticCRSType, domainOfValidity_, domainOfValidity)
//  READ_O_ARRAY_OF_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(GeodeticCRSType, scope_)
//  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME(GeodeticCRSType, ellipsoidalCS, EllipsoidalCSPropertyType)
//  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME(GeodeticCRSType, usesEllipsoidalCS, EllipsoidalCSPropertyType)
//  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME(GeodeticCRSType, cartesianCS, CartesianCSPropertyType)
//  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME(GeodeticCRSType, usesCartesianCS, CartesianCSPropertyType)
//  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME(GeodeticCRSType, sphericalCS, SphericalCSPropertyType)
//  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME(GeodeticCRSType, usesSphericalCS, SphericalCSPropertyType)
//  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME(GeodeticCRSType, geodeticDatum, GeodeticDatumPropertyType)
//  READ_O_OBJECT_1411_VOID(GeodeticCRSType, usesGeodeticDatum, GeodeticDatumPropertyType)
BSON_READ_OBJECT_1411_END(GeodeticCRSType)
*/
//struct __rd1witsml__cs_USCOREstandardGeodeticCRS_sequence
BSON_READ_OBJECT_1411_BEGIN_B(cs_USCOREstandardGeodeticCRS)
  READ_O_OBJECT_1411_OR_ELSE_GOTO_RESUME_B(cs_USCOREstandardGeodeticCRS, nameCRS, wellKnownNameStruct)
//  READ_O_OBJECT_ALIAS_1411_VOID_B(cs_USCOREstandardGeodeticCRS, rd1gml__GeodeticCRS, GeodeticCRS, GeodeticCRSType)
BSON_READ_OBJECT_1411_END_B(cs_USCOREstandardGeodeticCRS)

//TODO
//struct __rd1witsml__obj_USCOREcoordinateReferenceSystem_sequence_
READ_S_OBJECT_1411_BEGIN_A(coordinateReferenceSystem)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(coordinateReferenceSystem, geodeticCRS, cs_USCOREstandardGeodeticCRS)
//  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(coordinateReferenceSystem, projectedCRS, cs_USCOREstandardProjectedCRS)
//  READ_S_OBJECT_1411_VOID(coordinateReferenceSystem, verticalCRS, cs_USCOREstandardVerticalCRS)
READ_S_OBJECT_1411_END_A(coordinateReferenceSystem)

//struct rd1witsml__obj_USCOREdrillReports
READ_S_OBJECT_1411_BEGIN(drillReport)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(drillReport, dTimStart)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(drillReport, dTimEnd)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(drillReport, versionKind, OpsReportVersion)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(drillReport, createDate)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, wellAlias, cs_USCOREwellAlias)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, wellboreAlias, cs_USCOREwellAlias)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, wellDatum, cs_USCOREwellDatum)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, wellCRS, cs_USCOREwellCRS)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, wellboreInfo, cs_USCOREdrillReportWellboreInfo)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, statusInfo, cs_USCOREdrillReportStatusInfo)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, bitRecord, cs_USCOREbitRecord)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, fluid, cs_USCOREfluid)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, porePressure, cs_USCOREdrillReportPorePressure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, extendedReport, timestampedCommentString)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, surveyStation, cs_USCOREdrillReportSurveyStation)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, activity, cs_USCOREactivity)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, logInfo, cs_USCOREdrillReportLogInfo)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, coreInfo, cs_USCOREdrillReportCoreInfo)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, wellTestInfo, cs_USCOREdrillReportWellTestInfo)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, formTestInfo, cs_USCOREdrillReportFormTestInfo)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, lithShowInfo, cs_USCOREdrillReportLithShowInfo)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, equipFailureInfo, cs_USCOREdrillReportEquipFailureInfo)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, controlIncidentInfo, cs_USCOREdrillReportControlIncidentInfo)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, stratInfo, cs_USCOREdrillReportStratInfo)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(drillReport, perfInfo, cs_USCOREdrillReportPerfInfo)
  READ_S_ARRAY_OF_OBJECT_1411_VOID(drillReport, gasReadingInfo, cs_USCOREdrillReportGasReadingInfo)
READ_S_OBJECT_1411_END(drillReport)

//struct __rd1witsml__obj_USCOREfluidsReport_sequence_
READ_S_OBJECT_1411_BEGIN(fluidsReport)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(fluidsReport, dTim)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(fluidsReport, md, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(fluidsReport, tvd, wellVerticalDepthCoord)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(fluidsReport, numReport)
  READ_S_ARRAY_OF_OBJECT_1411_VOID(fluidsReport, fluid, cs_USCOREfluid)
READ_S_OBJECT_1411_END(fluidsReport)

//struct __rd1witsml__obj_USCOREformationMarker_sequence_
READ_S_OBJECT_1411_BEGIN(formationMarker)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(formationMarker, mdPrognosed, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(formationMarker, tvdPrognosed, wellVerticalDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(formationMarker, mdTopSample, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(formationMarker, tvdTopSample, wellVerticalDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(formationMarker, thicknessBed, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(formationMarker, thicknessApparent, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(formationMarker, thicknessPerpen, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(formationMarker, mdLogSample, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(formationMarker, tvdLogSample, wellVerticalDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(formationMarker, dip, planeAngleMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(formationMarker, dipDirection, planeAngleMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(formationMarker, lithostratigraphic, lithostratigraphyStruct)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(formationMarker, chronostratigraphic, chronostratigraphyStruct)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(formationMarker, nameFormation)
  READ_S_UTF8_OBJECT_1411_VOID(formationMarker, description)
READ_S_OBJECT_1411_END(formationMarker)

//struct __rd1witsml__obj_USCORElog_sequence_
READ_S_OBJECT_1411_BEGIN(log)
  READ_S_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME(log, objectGrowing)
  READ_S_INT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(log, dataUpateRate)
  READ_S_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME(log, curveSensorsAligned)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(log, dataGroup)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(log, serviceCompany)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(log, runNumber)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(log, bhaRunNumber)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(log, pass)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(log, creationDate)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(log, description)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(log, dataDelimiter)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(log, indexType, LogIndexType)
  //struct __rd1witsml__obj_USCORElog_sequence__ *__obj_USCORElog_sequence__;
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME_B1(log, __obj_USCORElog_sequence__, obj_USCORElog, __)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(log, direction, LogIndexDirection)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(log, indexCurve)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(log, nullValue)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(log, logParam, indexedObject)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(log, logCurveInfo, cs_USCORElogCurveInfo)
  READ_S_ARRAY_OF_OBJECT_1411_VOID(log, logData, cs_USCORElogData)
READ_S_OBJECT_1411_END(log)

//struct __rd1witsml__obj_USCOREmessage_sequence_
READ_S_OBJECT_1411_BEGIN(message)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(message, objectReference, refObjectString)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(message, subObjectReference, refObjectString)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(message, dTim)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(message, activityCode)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(message, detailActivity)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(message, md, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(message, mdBit, measuredDepthCoord)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(message, typeMessage, MessageType)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(message, messageText)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(message, param, indexedObject)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(message, severity, MessageSeverity)
  READ_S_OBJECT_ENUM_NULLABLE_1411_VOID(message, warnProbability, MessageProbability)
READ_S_OBJECT_1411_END(message)

//struct __rd1witsml__obj_USCOREmudLog_sequence_
READ_S_OBJECT_1411_BEGIN(mudLog)
  READ_S_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME(mudLog, objectGrowing)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(mudLog, dTim)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(mudLog, mudLogCompany)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(mudLog, mudLogEngineers)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(mudLog, startMd, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(mudLog, endMd, measuredDepthCoord)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(mudLog, relatedLog, refNameString)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(mudLog, parameter, cs_USCOREmudLogParameter)
  READ_S_ARRAY_OF_OBJECT_1411_VOID(mudLog, geologyInterval, cs_USCOREgeologyInterval)
READ_S_OBJECT_1411_END(mudLog)

//struct __rd1witsml__obj_USCOREobjectGroup_sequence_
READ_S_OBJECT_1411_BEGIN(objectGroup)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(objectGroup, groupType)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(objectGroup, groupSubtype)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(objectGroup, sequence)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(objectGroup, description)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(objectGroup, param, indexedObject)
  READ_S_ARRAY_OF_OBJECT_1411_VOID(objectGroup, memberObject, cs_USCOREmemberObject)
READ_S_OBJECT_1411_END(objectGroup)

//struct __rd1witsml__obj_USCOREopsReport_sequence_
READ_S_OBJECT_1411_BEGIN(opsReport)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, rig, refNameString)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(opsReport, dTim)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, eTimStart, timeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, eTimSpud, timeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, eTimLoc, timeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, mdReport, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, tvdReport, wellVerticalDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, distDrill, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, eTimDrill, timeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, mdPlanned, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, ropAv, velocityMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, ropCurrent, velocityMeasure)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, supervisor)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, engineer)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, geologist)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, eTimDrillRot, timeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, eTimDrillSlid, timeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, eTimCirc, timeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, eTimReam, timeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, eTimHold, timeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, eTimSteering, timeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, distDrillRot, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, distDrillSlid, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, distReam, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, distHold, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, distSteering, lengthMeasure)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(opsReport, numPob)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(opsReport, numContract)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(opsReport, numOperator)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(opsReport, numService)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, activity, cs_USCOREactivity)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, drillingParams, cs_USCOREdrillingParams)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, wbGeometry, cs_USCOREwbGeometry)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, dayCost, cs_USCOREdayCost)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, trajectoryStation, cs_USCOREtrajectoryStation)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, fluid, cs_USCOREfluid)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, scr, cs_USCOREscr)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, pitVolume, cs_USCOREpitVolume)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, mudVolume, cs_USCOREmudVolume)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, mudInventory, cs_USCOREinventory)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, bulk, cs_USCOREinventory)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, rigResponse, cs_USCORErigResponse)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, pumpOp, cs_USCOREpumpOp)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, shakerOp, cs_USCOREshakerOp)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, hse, cs_USCOREhse)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, personnel, cs_USCOREpersonnel)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, supportCraft, cs_USCOREsupportCraft)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, weather, cs_USCOREweather)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, numAFE)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, costDay, cost)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, costDayMud, cost)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, diaHole, lengthMeasure)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, conditionHole)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, lithology)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, nameFormation)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, diaCsgLast, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, mdCsgLast, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, tvdCsgLast, wellVerticalDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, tvdLot, wellVerticalDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, presLotEmw, densityMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, presKickTol, pressureMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, volKickTol, volumeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, maasp, pressureMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, tubular, refNameString)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, sum24Hr)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(opsReport, forecast24Hr)
  READ_S_UTF8_OBJECT_1411_VOID(opsReport, statusCurrent)
READ_S_OBJECT_1411_END(opsReport)

//struct __rd1witsml__obj_USCORErig_sequence_
READ_S_OBJECT_1411_BEGIN(rig)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, owner)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(rig, typeRig, RigType)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, manufacturer)
  READ_S_INT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(rig, yearEntService)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, classRig)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, approvals)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, registration)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, telNumber)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, faxNumber)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, emailAddress)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, nameContact)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, ratingDrillDepth, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, ratingWaterDepth, lengthMeasure)
  READ_S_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME(rig, isOffshore)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, airGap, lengthMeasure)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(rig, dTimStartOp)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(rig, dTimEndOp)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, bop, cs_USCOREbop)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, pit, cs_USCOREpit)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, pump, cs_USCOREpump)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, shaker, cs_USCOREshaker)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, centrifuge, cs_USCOREcentrifuge)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, hydrocyclone, cs_USCOREhydrocyclone)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, degasser, cs_USCOREdegasser)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, surfaceEquipment, cs_USCOREsurfaceEquipment)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(rig, numDerricks)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(rig, typeDerrick, DerrickType)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, ratingDerrick, forceMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, htDerrick, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, ratingHkld, forceMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, capWindDerrick, velocityMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, wtBlock, forceMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, ratingBlock, forceMeasure)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(rig, numBlockLines)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, typeHook)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, ratingHook, forceMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, sizeDrillLine, lengthMeasure)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(rig, typeDrawWorks, DrawWorksType)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, powerDrawWorks, powerMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, ratingDrawWorks, forceMeasure)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, motorDrawWorks)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, descBrake)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, typeSwivel)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, ratingSwivel, forceMeasure)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(rig, rotSystem, DriveType)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, descRotSystem)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, ratingTqRotSys, momentOfForceMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, rotSizeOpening, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, ratingRotSystem, forceMeasure)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, scrSystem)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, pipeHandlingSystem)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, capBulkMud, volumeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, capLiquidMud, volumeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, capDrillWater, volumeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, capPotableWater, volumeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, capFuel, volumeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, capBulkCement, volumeMeasure)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, mainEngine)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, generator)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, cementUnit)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(rig, numBunks)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(rig, bunksPerRoom)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(rig, numCranes)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(rig, numAnch)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, moorType)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(rig, numGuideTens)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(rig, numRiserTens)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, varDeckLdMx, forceMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, vdlStorm, forceMeasure)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(rig, numThrusters)
  READ_S_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME(rig, azimuthing)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, motionCompensationMn, forceMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, motionCompensationMx, forceMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, strokeMotionCompensation, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, riserAngleLimit, planeAngleMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, heaveMx, lengthMeasure)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(rig, gantry)
  READ_S_UTF8_OBJECT_1411_VOID(rig, flares)
READ_S_OBJECT_1411_END(rig)

//struct __rd1witsml__obj_USCORErisk_sequence_
READ_S_OBJECT_1411_BEGIN(risk)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(risk, objectReference, refObjectString)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(risk, type, RiskType)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(risk, category, RiskCategory)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(risk, subCategory, RiskSubCategory)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(risk, extendCategory)
  READ_S_ARRAY_OF_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(risk, affectedPersonnel, RiskAffectedPersonnel)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(risk, dTimStart)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(risk, dTimEnd)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(risk, mdHoleStart, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(risk, mdHoleEnd, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(risk, tvdHoleStart, wellVerticalDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(risk, tvdHoleEnd, wellVerticalDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(risk, mdBitStart, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(risk, mdBitEnd, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(risk, diaHole, lengthMeasure)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(risk, severityLevel)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(risk, probabilityLevel)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(risk, summary)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(risk, details)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(risk, identification)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(risk, contingency)
  READ_S_ARRAY_OF_UTF8_OBJECT_1411_VOID(risk, mitigation)
READ_S_OBJECT_1411_END(risk)

//struct __rd1witsml__obj_USCOREsidewallCore_sequence_
READ_S_OBJECT_1411_BEGIN(sidewallCore)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(sidewallCore, dTimToolRun)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(sidewallCore, dTimToolPull)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(sidewallCore, mdToolReference, measuredDepthCoord)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(sidewallCore, coreReferenceLog)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(sidewallCore, mdCore, measuredDepthCoord)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(sidewallCore, serviceCompany)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(sidewallCore, analysisContractor)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(sidewallCore, analysisBy)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(sidewallCore, sidewallCoringTool)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(sidewallCore, diaHole, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(sidewallCore, diaPlug, lengthMeasure)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(sidewallCore, numPlugsShot)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(sidewallCore, numRecPlugs)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(sidewallCore, numMisfiredPlugs)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(sidewallCore, numEmptyPlugs)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(sidewallCore, numLostPlugs)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(sidewallCore, numPaidPlugs)
  READ_S_ARRAY_OF_OBJECT_1411_VOID(sidewallCore, swcSample, cs_USCOREswcSample)
READ_S_OBJECT_1411_END(sidewallCore)

//struct __rd1witsml__obj_USCOREstimJob_sequence_
READ_S_OBJECT_1411_BEGIN(stimJob)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, kind)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(stimJob, commodityCode, PIDXCommodityCode)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, serviceCompany)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, supervisor)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, apiNumber)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, customerName)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(stimJob, dTimArrival)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(stimJob, dTimStart)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(stimJob, dTimEnd)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, totalPumpTime, timeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, maxJobPres, pressureMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, maxFluidRate, volumeFlowRateMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, avgJobPres, pressureMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, totalJobVolume, volumeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, totalProppantWt, massMeasure)
  READ_S_ARRAY_OF_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, proppantName)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(stimJob, perfBallCount)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, totalN2StdVolume, standardVolumeMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, totalCO2Mass, massMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, hhpOrdered, powerMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, hhpUsed, powerMeasure)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(stimJob, treatmentCount)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, fluidEfficiency, volumePerVolumeMeasurePercent)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, flowBackPres, pressureMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, flowBackRate, volumeFlowRateMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, flowBackVolume, volumeMeasure)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(stimJob, treatmentIntervalCount)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, bottomholeStaticTemperature, thermodynamicTemperatureMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(stimJob, treatingBottomholeTemperature, thermodynamicTemperatureMeasure)
  READ_S_ARRAY_OF_OBJECT_1411_VOID(stimJob, jobInterval, cs_USCOREstimJobInterval)
READ_S_OBJECT_1411_END(stimJob)

//struct __rd1witsml__obj_USCOREsurveyProgram_sequence_
READ_S_OBJECT_1411_BEGIN(surveyProgram)
  READ_S_SHORT_NULLABLE_1411_OR_ELSE_GOTO_RESUME(surveyProgram, surveyVer)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(surveyProgram, dTimTrajProg)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(surveyProgram, engineer)
  READ_S_UTF8_OBJECT_ALIAS_1411_OR_ELSE_GOTO_RESUME(surveyProgram, final_, final)
  READ_S_ARRAY_OF_OBJECT_1411_VOID(surveyProgram, surveySection, cs_USCOREsurveySection)
READ_S_OBJECT_1411_END(surveyProgram)

//struct __rd1witsml__obj_USCOREtarget_sequence_
READ_S_OBJECT_1411_BEGIN(target)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(target, parentTarget, refNameString)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(target, dispNsCenter, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(target, dispEwCenter, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(target, tvd, wellVerticalDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(target, dispNsOffset, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(target, dispEwOffset, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(target, thickAbove, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(target, thickBelow, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(target, dip, planeAngleMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(target, strike, planeAngleMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(target, rotation, planeAngleMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(target, lenMajorAxis, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(target, widMinorAxis, lengthMeasure)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(target, typeTargetScope, TargetScope)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(target, dispNsSectOrig, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(target, dispEwSectOrig, lengthMeasure)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(target, aziRef, AziRef)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(target, catTarg, TargetCategory)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(target, location, cs_USCORElocation)
  READ_S_ARRAY_OF_OBJECT_1411_VOID(target, targetSection, cs_USCOREtargetSection)
READ_S_OBJECT_1411_END(target)

//struct __rd1witsml__obj_USCOREtoolErrorModel_sequence_
READ_S_OBJECT_1411_BEGIN_A(toolErrorModel)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(toolErrorModel, authorization, cs_USCOREiscwsaAuthorizationData)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(toolErrorModel, typeSurveyTool)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(toolErrorModel, operatingCondition, cs_USCOREiscwsaSurveyToolOperatingCondition)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(toolErrorModel, operatingInterval, cs_USCOREiscwsaSurveyToolOperatingInterval)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(toolErrorModel, modelParameters, cs_USCOREiscwsaModelParameters)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(toolErrorModel, useErrorTermSet, refNameString)
  READ_S_ARRAY_OF_OBJECT_1411_VOID(toolErrorModel, errorTermValue, cs_USCOREiscwsaErrorTermValue)
READ_S_OBJECT_1411_END_A(toolErrorModel)

//struct __rd1witsml__obj_USCOREtoolErrorTermSet_sequence_
READ_S_OBJECT_1411_BEGIN_A(toolErrorTermSet)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(toolErrorTermSet, authorization, cs_USCOREiscwsaAuthorizationData)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(toolErrorTermSet, nomenclature, cs_USCOREiscwsaNomenclature)
  READ_S_ARRAY_OF_OBJECT_1411_VOID(toolErrorTermSet, errorTerm, cs_USCOREiscwsaErrorTerm)
READ_S_OBJECT_1411_END_A(toolErrorTermSet)

//struct __rd1witsml__obj_USCOREtrajectory_sequence_
READ_S_OBJECT_1411_BEGIN(trajectory)
  READ_S_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME(trajectory, objectGrowing)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(trajectory, parentTrajectory, cs_USCORErefWellboreTrajectory)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(trajectory, dTimTrajStart)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(trajectory, dTimTrajEnd)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(trajectory, mdMn, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(trajectory, mdMx, measuredDepthCoord)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(trajectory, serviceCompany)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(trajectory, magDeclUsed, planeAngleMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(trajectory, gridCorUsed, planeAngleMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(trajectory, gridConUsed, planeAngleMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(trajectory, aziVertSect, planeAngleMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(trajectory, dispNsVertSectOrig, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(trajectory, dispEwVertSectOrig, lengthMeasure)
  READ_S_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME(trajectory, definitive)
  READ_S_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME(trajectory, memory)
  READ_S_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME(trajectory, finalTraj)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(trajectory, aziRef, AziRef)
  READ_S_ARRAY_OF_OBJECT_1411_VOID(trajectory, trajectoryStation, cs_USCOREtrajectoryStation)
READ_S_OBJECT_1411_END(trajectory)

//struct __rd1witsml__obj_USCOREtubular_sequence_
READ_S_OBJECT_1411_BEGIN(tubular)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(tubular, typeTubularAssy, TubularAssembly)
  READ_S_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME(tubular, valveFloat)
  READ_S_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME(tubular, sourceNuclear)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(tubular, diaHoleAssy, lengthMeasure)
  READ_S_ARRAY_OF_OBJECT_1411_VOID(tubular, tubularComponent, cs_USCOREtubularComponent)
READ_S_OBJECT_1411_END(tubular)

//struct __rd1witsml__obj_USCOREwbGeometry_sequence_
READ_S_OBJECT_1411_BEGIN(wbGeometry)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(wbGeometry, dTimReport)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(wbGeometry, mdBottom, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(wbGeometry, gapAir, lengthMeasure)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(wbGeometry, depthWaterMean, lengthMeasure)
  READ_S_ARRAY_OF_OBJECT_1411_VOID(wbGeometry, wbGeometrySection, cs_USCOREwbGeometrySection)
READ_S_OBJECT_1411_END(wbGeometry)

//struct __rd1witsml__obj_USCOREwellbore_sequence_
READ_S_OBJECT_1411_BEGIN_B(wellbore)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(wellbore, parentWellbore, refNameString)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(wellbore, number)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(wellbore, suffixAPI)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(wellbore, numGovt)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(wellbore, statusWellbore, WellStatus)
  READ_S_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME(wellbore, isActive)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(wellbore, purposeWellbore, WellPurpose)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(wellbore, typeWellbore, WellboreType)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(wellbore, shape, WellboreShape)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(wellbore, dTimKickoff)
  READ_S_BOOLEAN_NULLABLE_1411_OR_ELSE_GOTO_RESUME(wellbore, achievedTD)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(wellbore, md, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(wellbore, tvd, wellVerticalDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(wellbore, mdBit, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(wellbore, tvdBit, wellVerticalDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(wellbore, mdKickoff, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(wellbore, tvdKickoff, wellVerticalDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(wellbore, mdPlanned, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(wellbore, tvdPlanned, wellVerticalDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(wellbore, mdSubSeaPlanned, measuredDepthCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(wellbore, tvdSubSeaPlanned, wellVerticalDepthCoord)
  READ_S_OBJECT_1411_VOID(wellbore, dayTarget, timeMeasure)
READ_S_OBJECT_1411_END_B(wellbore)

//struct __rd1witsml__obj_USCOREwell_sequence_
READ_S_OBJECT_1411_BEGIN_A(well)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, nameLegal)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, numLicense)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, numGovt)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(well, dTimLicense)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, field)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, country)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, state)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, county)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, region)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, district)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, block)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, timeZone)
  READ_S_UTF8_OBJECT_ALIAS_1411_OR_ELSE_GOTO_RESUME(well, operator_, operator)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, operatorDiv)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, pcInterest, dimensionlessMeasure)
  READ_S_UTF8_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, numAPI)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(well, statusWell, WellStatus)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(well, purposeWell, WellPurpose)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(well, fluidWell, WellFluid)
  READ_S_OBJECT_ENUM_NULLABLE_1411_OR_ELSE_GOTO_RESUME(well, directionWell, WellDirection)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(well, dTimSpud)
  READ_S_TIME_NULLABLE_1411_OR_ELSE_GOTO_RESUME(well, dTimPa)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, wellheadElevation, wellElevationCoord)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, wellDatum, cs_USCOREwellDatum)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, groundElevation, wellElevationCoord)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, waterDepth, lengthMeasure)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, wellLocation, cs_USCORElocation)
  READ_S_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, wellPublicLandSurveySystemLocation, cs_USCOREpublicLandSurveySystem)
  READ_S_ARRAY_OF_OBJECT_1411_OR_ELSE_GOTO_RESUME(well, referencePoint, cs_USCOREreferencePoint)
  READ_S_ARRAY_OF_OBJECT_1411_VOID(well, wellCRS, cs_USCOREwellCRS)
READ_S_OBJECT_1411_END_A(well)


typedef int (*readWitsmlObject1411Fn)(struct soap *soap_internal);

SOAP_FMAC5 int SOAP_FMAC6 rd1411__readObj1411(struct soap *soap_internal, struct rd1411__readObj1411_USCOREt *witsmlObject, char **result)
{
  DECLARE_CONFIG(soap_internal)
  readWitsmlObject1411Fn fn=NULL;
  int n=0;

  if (!witsmlObject) {
    // Sentinel. It should not happen.
    *result="Unexpected rd1411__readObj1411 NULL pointer";
    cws_set_soap_fault_util(soap_internal, -1232, CWS_FAULTSTR("Unexpected error. Check gSoap implementation"), -1);
    return SOAP_FAULT;
  }

  config->witsmlObject=(void *)witsmlObject;

  CWS_DETECT_OBJ(attachment)
  CWS_DETECT_OBJ(bhaRun)
  CWS_DETECT_OBJ(cementJob)
  CWS_DETECT_OBJ(changeLog)
  CWS_DETECT_OBJ(convCore)
  CWS_DETECT_OBJ(coordinateReferenceSystem)
  CWS_DETECT_OBJ(drillReport)
  CWS_DETECT_OBJ(fluidsReport)
  CWS_DETECT_OBJ(formationMarker)
  CWS_DETECT_OBJ(log)
  CWS_DETECT_OBJ(message)
  CWS_DETECT_OBJ(mudLog)
  CWS_DETECT_OBJ(objectGroup)
  CWS_DETECT_OBJ(opsReport)
  CWS_DETECT_OBJ(rig)
  CWS_DETECT_OBJ(risk)
  CWS_DETECT_OBJ(sidewallCore)
  CWS_DETECT_OBJ(stimJob)
  CWS_DETECT_OBJ(surveyProgram)
  CWS_DETECT_OBJ(target)
  CWS_DETECT_OBJ(toolErrorModel)
  CWS_DETECT_OBJ(toolErrorTermSet)
  CWS_DETECT_OBJ(trajectory)
  CWS_DETECT_OBJ(tubular)
  CWS_DETECT_OBJ(wbGeometry)
  CWS_DETECT_OBJ(wellbore)
  CWS_DETECT_OBJ(well)

  if (n==1) {
    *result=((n=fn(soap_internal))==SOAP_OK)?"rd1411__readObj1411 soap internal OK":"rd1411__readObj1411 soap internal FAIL";
    return n;
  }

  config->objectName="READ: Unknown object";

  if (n)
    CWS_SET_SOAP_FAULT_CLIENT("READ: Too many objects. Only one allowed!")
  else
    CWS_SET_SOAP_FAULT_CLIENT("READ: No object to parse")

  *result="rd1411__readObj1411 soap internal FAIL. Unknown object";

  return SOAP_FAULT;
}

