#include <bson/bson.h>
#include "deserializer_util.h"

int bson_put_single_attribute_if_exists(bson_t *bson, const char *key, int key_length, char *value, int value_length)
{
  int err;
  bson_t childAttributes;

  if (value) {
    if (!bson_append_document_begin(bson, KEY_USCORE_ATTRIBUTES, &childAttributes))
      return 10;

    err=0;
    if (!bson_append_utf8(&childAttributes, key, key_length, (const char *)value, value_length))
      err=11;

    if (!bson_append_document_end(bson, &childAttributes))
      if (!err)
        err=12;

    return err;
  }

  return 0;
}

int bson_put_multiple_attributes_if_they_exist(bson_t *bson, ...)
{
  int
    err=0;
  const char *key;
  size_t key_length;
  char *value;
  va_list args;
  bson_t
    *childAttributesPtr=NULL,
    childAttributes;

  va_start(args, bson);
  while ((key=(const char *)va_arg(args, const char *))) {
    key_length=(size_t)va_arg(args, size_t);
    if ((value=(char *)va_arg(args, char *))) {

      if (childAttributesPtr) {

bson_put_multiple_attributes_if_they_exist_add:
        if (!bson_append_utf8(childAttributesPtr, key, key_length, value, -1)) {
          err=20;
          break;
        }

      } else if (bson_append_document_begin(bson, KEY_USCORE_ATTRIBUTES, childAttributesPtr=&childAttributes))
        goto bson_put_multiple_attributes_if_they_exist_add;
      else {
        childAttributesPtr=NULL;
        err=19;
        break;
      }
    }
  };

  if ((childAttributesPtr!=NULL)&&(!bson_append_document_end(bson, childAttributesPtr))&&(err==0))
    err=21;

  va_end(args);

  return err;
}

int bson_put_multiple_attributes_if_they_exist_typed(bson_t *bson, ...)
{
  int
    value_type,
    err=0;
  const char *key;
  size_t key_length;
  void *value;
  va_list args;
  bson_t
    *childAttributesPtr=NULL,
    childAttributes;

  va_start(args, bson);
  while ((key=(const char *)va_arg(args, const char *))) {
    key_length=(size_t)va_arg(args, size_t);
    value_type=(int)va_arg(args, int);
    if ((value=(void *)va_arg(args, void *))) {

      if (childAttributesPtr) {

bson_put_multiple_attributes_if_they_exist_add:
        if (value_type==_CWS_NULLABLE_XSD_STR) {
          if (bson_append_utf8(childAttributesPtr, key, key_length, (const char *)value, -1))
            continue;

          err=20;
          break;
        }

        if (value_type==_CWS_NULLABLE_XSD_SIGNED_SHORT) {
          if (bson_append_int32(childAttributesPtr, key, key_length, (int32_t)*((int16_t *)value)))
            continue;

          err=21;
          break;
        }

        if (value_type==_CWS_NULLABLE_DATE_TIME) {
          if (bson_append_time_t(childAttributesPtr, key, key_length, (time_t)*((time_t *)value)))
            continue;

          err=22;
          break;
        }

        if (value_type==_CWS_NULLABLE_DOUBLE) {
          if (bson_append_double(childAttributesPtr, key, key_length, (double)*((double *)value)))
            continue;

          err=23;
          break;
        }

      } else if (bson_append_document_begin(bson, KEY_USCORE_ATTRIBUTES, childAttributesPtr=&childAttributes))
        goto bson_put_multiple_attributes_if_they_exist_add;
      else {
        childAttributesPtr=NULL;
        err=19;
        break;
      }
    }
  }

  if ((childAttributesPtr!=NULL)&&(!bson_append_document_end(bson, childAttributesPtr))&&(err==0))
    err=50;

  va_end(args);

  return err;
}

