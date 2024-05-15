#define _GNU_SOURCE
#include <stdarg.h>
#include <cws_writer.h>

void bson_xml_err_msg_free(struct bson_xml_err_msg_t *bson_xml_err_msg)
{
  if ((bson_xml_err_msg->errMsg!=NULL)&&(bson_xml_err_msg->bson_xml_err_msg_type==XML_ERR_MSG_ALLOCABLE))
    free((void *)bson_xml_err_msg->errMsg);

  bson_xml_err_msg->errMsg=NULL;
  bson_xml_err_msg->errMsgLen=0;
  bson_xml_err_msg->bson_xml_err_msg_type=XML_ERR_MSG_UNITIALIZED;
}

static void bson_xml_err_msg_fmt(struct bson_xml_err_msg_t *bson_xml_err_msg, const char *fmt, ...)
{
  va_list args;
#define ERR_ALLOC_BSON_MSG_ERR "bson_xml_err_msg_fmt: Unable to allocate"
  if (bson_xml_err_msg->errMsg==NULL) {

    va_start(args, fmt);

    if ((bson_xml_err_msg->errMsgLen=vasprintf(&bson_xml_err_msg->errMsg, fmt, args))>=0)
      bson_xml_err_msg->bson_xml_err_msg_type=XML_ERR_MSG_ALLOCABLE;
    else {
      bson_xml_err_msg->bson_xml_err_msg_type=XML_ERR_MSG_CONST;
      bson_xml_err_msg->errMsgLen=(int)(sizeof(ERR_ALLOC_BSON_MSG_ERR)-1);
      bson_xml_err_msg->errMsg=ERR_ALLOC_BSON_MSG_ERR;
    }

    va_end(args);

  }
#undef ERR_ALLOC_BSON_MSG_ERR
}

#define XML_ERR_MSG_CHECK(cond, errNo, fmt, ...) \
  if (cond) {\
    xmlBsonWriter->err=errNo;\
    bson_xml_err_msg_fmt(xmlBsonWriter->bson_xml_err_msg, fmt, __VA_ARGS__);\
    return xmlBsonWriter->err;\
  }

#define XML_BSON_WRITER_INIT_CHILD(bsonType)\
xmlBsonWriterChild.err=0;\
xmlBsonWriterChild.depth=xmlBsonWriter->depth;\
xmlBsonWriterChild.depthMax=xmlBsonWriter->depthMax;\
xmlBsonWriterChild.parentKey=parentKey;\
xmlBsonWriterChild.parentKeyLen=parentKeyLen;\
xmlBsonWriterChild.bson_xml_err_msg=xmlBsonWriter->bson_xml_err_msg;\
if ((xmlBsonWriter->err=(cws_bson_parser_xml(&xmlBsonWriterChild, &child_iter, bsonType))))\
  return xmlBsonWriter->err;

#define CHECK_BSON_TYPE(ret) \
if (parentKey[0]!='#')\
  bsonTypeChild=ret;\
else {\
  if ((((size_t)parentKeyLen)==(sizeof("#attributes")-1))&&(strcmp("#attributes", parentKey)==0))\
    bsonTypeChild=OBJ_TYPE_ATTRIBUTES;\
  else if ((((size_t)parentKeyLen)==(sizeof("#value")-1))&&(strcmp("#value", parentKey)==0))\
    bsonTypeChild=OBJ_TYPE_VALUE;\
  else if ((((size_t)parentKeyLen)==(sizeof("#any")-1))&&(strcmp("#any", parentKey)==0))\
    bsonTypeChild=OBJ_TYPE_ANY;\
  else\
    bsonTypeChild=OBJ_TYPE_UNKNOWN;\
}

static int cws_bson_parser_xml(struct bson_to_xml_writer_t *xmlBsonWriter, bson_iter_t *iter, enum bsonObjectType_e bsonType)
{
  void *value;
  const char *parentKey;
  const uint8_t *obj;
  uint32_t parentKeyLen, objLen, length;
  struct bson_to_xml_writer_t xmlBsonWriterChild;
  bson_iter_t child_iter;
  enum bsonObjectType_e bsonTypeChild;

  while (bson_iter_next(iter)) {
    parentKey=bson_iter_key(iter);
    parentKeyLen=bson_iter_key_len(iter);

    if (BSON_ITER_HOLDS_DOCUMENT(iter)) {

      CHECK_BSON_TYPE(OBJ_TYPE_DOCUMENT)

      XML_ERR_MSG_CHECK(bsonTypeChild==OBJ_TYPE_UNKNOWN, -410, "Wrong BSON type %.*s: -410", parentKeyLen, parentKey)

      bson_iter_document(iter, &objLen, &obj);
      XML_ERR_MSG_CHECK(obj==NULL, -401, "Child document %.*s iterator is NULL: -401", parentKeyLen, parentKey)

      XML_ERR_MSG_CHECK(!bson_iter_init_from_data(&child_iter, obj, objLen), -402, "Could not init document %.*s from data: -402", parentKeyLen, parentKey)

      if ((*(xmlBsonWriter->depthMax))>0)
        XML_ERR_MSG_CHECK((++(*(xmlBsonWriter->depth)))>(*(xmlBsonWriter->depthMax)), -400, "Max depth exceed %d at document %.*s: -400",
          *(xmlBsonWriter->depthMax), parentKeyLen, parentKey)

      printf("\nDOCUMENT %.*s depth: %d\n", parentKeyLen, parentKey, *(xmlBsonWriter->depth));

      XML_BSON_WRITER_INIT_CHILD(bsonTypeChild)

      --(*(xmlBsonWriter->depth));

    } else if (BSON_ITER_HOLDS_ARRAY(iter)) {

      CHECK_BSON_TYPE(OBJ_TYPE_ARRAY)

      XML_ERR_MSG_CHECK((bsonTypeChild!=OBJ_TYPE_ARRAY)&&(bsonTypeChild!=OBJ_TYPE_ANY), -411, "Wrong BSON array type %.*s: -411", parentKeyLen, parentKey)

      bson_iter_array(iter, &objLen, &obj);
      XML_ERR_MSG_CHECK(obj==NULL, -403, "Child array %.*s iterator is NULL: -403", parentKeyLen, parentKey)

      XML_ERR_MSG_CHECK(!bson_iter_init_from_data(&child_iter, obj, objLen), -404, "Could not init array %.*s from data: -404", parentKeyLen, parentKey)

      if ((*(xmlBsonWriter->depthMax))>0)
        XML_ERR_MSG_CHECK((++(*(xmlBsonWriter->depth)))>(*(xmlBsonWriter->depthMax)), -400, "Max depth exceed %d at array %.*s: -400",
          *(xmlBsonWriter->depthMax), parentKeyLen, parentKey)

      printf("\nARRAY %.*s depth: %d\n", parentKeyLen, parentKey, *(xmlBsonWriter->depth));

      XML_BSON_WRITER_INIT_CHILD(bsonTypeChild)

      --(*(xmlBsonWriter->depth));

    } else if (BSON_ITER_HOLDS_UTF8(iter)) {
      value=(void *)bson_iter_utf8(iter, &length);
      XML_ERR_MSG_CHECK((xmlBsonWriter->utf8_validate)&&(!bson_utf8_validate((const char *)value, (size_t)length, false)), -460,
        "Invalid UTF-8 in at key=%.*s", parentKeyLen, parentKey)
      //TODO implement bson_utf8_validate
      if (bsonType==OBJ_TYPE_DOCUMENT) {
        printf("\nType is VALUE and key=%.*s parent key=%.*s value=%.*s",
          parentKeyLen, parentKey, xmlBsonWriter->parentKeyLen, xmlBsonWriter->parentKey, length, (const char *)value);

      } else if (bsonType==OBJ_TYPE_VALUE) {
        printf("\nType is VALUE and key=%.*s parent key=%.*s value=%.*s",
          parentKeyLen, parentKey, xmlBsonWriter->parentKeyLen, xmlBsonWriter->parentKey, length, (const char *)value);

      } else if (bsonType==OBJ_TYPE_ATTRIBUTES) {
        printf("\nType is ATTRIBUTES and key=%.*s parent key=%.*s value=%.*s",
          parentKeyLen, parentKey, xmlBsonWriter->parentKeyLen, xmlBsonWriter->parentKey, length, (const char *)value);
      } else if (bsonType==OBJ_TYPE_ARRAY) {
        printf("\nType is ARRAY and key=%.*s parent key=%.*s value=%.*s",
          parentKeyLen, parentKey, xmlBsonWriter->parentKeyLen, xmlBsonWriter->parentKey, length, (const char *)value);
      } else if (bsonType==OBJ_TYPE_ANY) {
        printf("\nType is TYPE ANY and key=%.*s parent key=%.*s value=%.*s",
          parentKeyLen, parentKey, xmlBsonWriter->parentKeyLen, xmlBsonWriter->parentKey, length, (const char *)value);
      } else {
        printf("\nInvalid bson type attribute %d", bsonType);
        //XML_ERR_MSG_CHECK(true, -500, "Invalid bson type attribute %d", bsonType)
      }
    } else if (BSON_ITER_HOLDS_DOUBLE(iter)) {
      printf("\nPassed DOUBLE");
    } else if (BSON_ITER_HOLDS_INT32(iter)) {
      printf("\nPassed INT32");
    } else if (BSON_ITER_HOLDS_INT64(iter)) {
      printf("\nPassed INT64");
    } else if (BSON_ITER_HOLDS_BOOL(iter)) {
      printf("\nPassed BOOL");
    } else if (BSON_ITER_HOLDS_DATE_TIME(iter)) {
      printf("\nPassed DATE TIME");
    } else if (BSON_ITER_HOLDS_BINARY(iter)) {
      printf("\nPassed BINARY");
    } else if (BSON_ITER_HOLDS_NULL(iter)) {
      printf("\nPassed NULL");
    } else {
      xmlBsonWriter->err=-450;
      bson_xml_err_msg_fmt(xmlBsonWriter->bson_xml_err_msg, "Wrong BSON iteration type at key: %.*s: -450", parentKeyLen, parentKey);
      break;
    }
  }

//TODO
  printf("\n");
  return xmlBsonWriter->err;
}

struct bson_to_xml_writer_t *parseBsonToXml(struct bson_to_xml_writer_t *bson_to_xml_writer, bson_t *bson)
{
  bson_iter_t iter;

  if (bson_iter_init(&iter, bson) && (cws_bson_parser_xml(bson_to_xml_writer, &iter, OBJ_TYPE_UNINITIALIZE)==0))
    return bson_to_xml_writer;

  return NULL;
}

/*
#define DECLARE_WRITER struct bson_to_xml_writer_t struct bson_to_xml_writer = {0};
#define DECLARE_WRITER_PTR struct bson_to_xml_writer_t *struct bson_to_xml_writer = \
(struct bson_to_xml_writer_t struct bson_to_xml_writer *)data;

#define WRITER_RETURN_PTR return bson_to_xml_writer->err != err;
//true stops iter and return error

bool cws_visit_before(const bson_iter_t *iter, const char *key, void *data)
{
  int err = 0;
  DECLARE_WRITER_PTR

  WRITER_RETURN_PTR
}

bool cws_visit_after(const bson_iter_t *iter, const char *key, void *data)
{
  int err = 0;
  DECLARE_WRITER_PTR

  WRITER_RETURN_PTR
}

bool cws_visit_utf8(
  const bson_iter_t *iter,
  const char *key, size_t v_utf8_len,
  const char *v_utf8,
  void *data
)
{
  int err = 0;
  DECLARE_WRITER_PTR

  WRITER_RETURN_PTR
}

bool cws_visit_double(
  const bson_iter_t *iter,
  const char *key,
  double v_double,
  void *data
)
{
  int err = 0;
  DECLARE_WRITER_PTR

  WRITER_RETURN_PTR
}

bool cws_visit_document(
  const bson_iter_t *iter,
  const char *key,
  const bson_t *v_document,
  void *data
)
{
  int err = 0;
  DECLARE_WRITER_PTR

  WRITER_RETURN_PTR
}

bool cws_visit_array(
  const bson_iter_t *iter,
  const char *key,
  const bson_t *v_array,
  void *data
)
{
  int err = 0;
  DECLARE_WRITER_PTR

  WRITER_RETURN_PTR
}

bool cws_visit_binary(
  const bson_iter_t *iter,
  const char *key,
  bson_subtype_t v_subtype,
  size_t v_binary_len,
  const uint8_t *v_binary,
  void *data
)
{
  int err = 0;
  DECLARE_WRITER_PTR

  WRITER_RETURN_PTR
}

bool cws_visit_bool(
  const bson_iter_t *iter,
  const char *key,
  bool v_bool,
  void *data
)
{
  int err = 0;
  DECLARE_WRITER_PTR

  WRITER_RETURN_PTR
}

bool cws_visit_int32(
  const bson_iter_t *iter,
  const char *key,
  int32_t v_int32,
  void *data
)
{
  int err = 0;
  DECLARE_WRITER_PTR

  WRITER_RETURN_PTR
}
*/
