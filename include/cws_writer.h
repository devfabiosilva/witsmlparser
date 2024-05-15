#ifndef CWS_WRITER_H
 #define CWS_WRITER_H

#include <bson/bson.h>
//TODO bson to xml
enum bsonObjectType_e {
  OBJ_TYPE_UNINITIALIZE=0,
  OBJ_TYPE_DOCUMENT,
  OBJ_TYPE_ARRAY,
  OBJ_TYPE_ATTRIBUTES,
  OBJ_TYPE_VALUE,
  OBJ_TYPE_ANY,
  OBJ_TYPE_UNKNOWN,
  OBJ_TYPE_OTHER
};

enum bson_xml_err_msg_type_e {
  XML_ERR_MSG_UNITIALIZED=0,
  XML_ERR_MSG_CONST,
  XML_ERR_MSG_ALLOCABLE
};

struct bson_xml_err_msg_t {
  enum bson_xml_err_msg_type_e bson_xml_err_msg_type;
  int errMsgLen;
  char *errMsg;
};

struct bson_to_xml_writer_t {
  int err;
  int *depth;
  int *depthMax;
  bool utf8_validate;
  const char *parentKey;
  uint32_t parentKeyLen;
  struct bson_xml_err_msg_t *bson_xml_err_msg;
};

void bson_xml_err_msg_free(struct bson_xml_err_msg_t *);

struct bson_to_xml_writer_t *parseBsonToXml(struct bson_to_xml_writer_t *, bson_t *);

#endif
