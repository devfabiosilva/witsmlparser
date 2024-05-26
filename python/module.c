#define PY_SSIZE_T_CLEAN
#include <cws_soap.h>
#include <cws_utils.h>
#include <base_msgs.h>
#include <Python.h>
//https://docs.python.org/3/c-api/intro.html#useful-macros

#define ERR ((Py_WITSML14X_13X_PARSER *)self)->err
#define GET_INTERNAL_SOAP_ERROR ((Py_WITSML14X_13X_PARSER *)self)->config->internal_soap_error
#define GET_BASEMSG_CODE (int)((Py_WITSML14X_13X_PARSER *)self)->config->base_msg.code
#define GET_OBJECT_NAME_PY ((Py_WITSML14X_13X_PARSER *)self)->config->objectName
#define GET_INSTANCE_NAME ((Py_WITSML14X_13X_PARSER *)self)->config->instance_name
#define CHECK_HAS_ERROR(msgOnError, retn) \
  if ((ERR!=0)||(GET_INTERNAL_SOAP_ERROR!=0)||(GET_BASEMSG_CODE<0)||(GET_OBJECT_NAME_PY==NULL)) {\
    PyErr_SetString(PyExc_Exception, msgOnError);\
    return retn;\
  }

typedef struct {
  PyObject_HEAD
  int err;
  CWS_CONFIG *config;
} Py_WITSML14X_13X_PARSER;

#define SET_CONST_TYPE(val)\
  {#val, val}

static struct const_type_t {
  const char *name;
  int value;
} CONST_TYPE[]={
  SET_CONST_TYPE(ACTION_READ_141X),
  SET_CONST_TYPE(ACTION_WRITE_141X),
  SET_CONST_TYPE(ACTION_UPDATE_141X),
  SET_CONST_TYPE(ACTION_DELETE_141X),
  {NULL}
};

#ifdef PY_SOAP_DEBUG
 #define Py_WITSML14X_13X_DEBUG(std, ...) \
    fprintf(std, __VA_ARGS__);
#else
 #define Py_WITSML14X_13X_DEBUG(std, ...)
#endif

#define Py_WITSML_14X_13X_ERROR(err_msg, errNumber) \
 {\
   PyErr_SetString(PyExc_Exception, err_msg);\
    return errNumber;\
 }

#define PyGET_CWS_CONFIG(ptr) ((Py_WITSML14X_13X_PARSER *)ptr)->config

const char *py_cws_check_action(int action)
{
  struct const_type_t *c=CONST_TYPE;

  while ((c->value!=action)&&(c->name!=NULL))
    c++;

  return c->name;
}

static PyObject *c_obj_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
  PyObject *self;

  if (!(self=type->tp_alloc(type, 0)))
    Py_WITSML_14X_13X_ERROR("Could not alloc Py_WITSML14X_13X_PARSER object", NULL)

  ERR=0;
  PyGET_CWS_CONFIG(self)=NULL;

  Py_WITSML14X_13X_DEBUG(stdout, "New object self created at %p\n", self)

  return (PyObject *)self;
}

static int c_obj_init(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
  char
   *kwlist[] = {"rule", "versionCheckDisable", NULL},
   msg[128];

  const char *act;

  int
    rule=ACTION_READ_141X,
    versionCheckDisable=0; //false

  if (!PyArg_ParseTupleAndKeywords(
    args, kwds, "|ip", kwlist,
    &rule, &versionCheckDisable
  )) Py_WITSML_14X_13X_ERROR("Error on parse WITSML 1.3.X - 1.4.X BSON parser", -498)

  if (!(act=py_cws_check_action(rule)))
    Py_WITSML_14X_13X_ERROR("Invalid action rule", -499)
  else if ((void *)act!=(void *)CONST_TYPE[0].name) {
    snprintf(msg, sizeof(msg), "Rule %s not implemented yet", act);
    Py_WITSML_14X_13X_ERROR(msg, -500)
  }

  Py_WITSML14X_13X_DEBUG(stdout, "Initializing config %s\n", py_cws_check_action(rule))

  if (versionCheckDisable)
    versionCheckDisable=CWS_FLAG_CHECK_VERSION_DISABLE;

  if (!(PyGET_CWS_CONFIG(self)=cws_config_new("PyWITSML 1.3.X - 1.4.X BSON parser", NULL, CWS_FLAG_RECYCLABLE|versionCheckDisable, rule)))
    Py_WITSML_14X_13X_ERROR("Could not initialize CWS config", -501)

  Py_WITSML14X_13X_DEBUG(stdout, "Initializing config %p\n", PyGET_CWS_CONFIG(self))

  return 0;
}

static void c_obj_dealloc(PyTypeObject *self)
{
  Py_WITSML14X_13X_DEBUG(stdout, "Destroying config %p\n", PyGET_CWS_CONFIG(self))
  cws_config_free(&PyGET_CWS_CONFIG(self));
  Py_WITSML14X_13X_DEBUG(stdout, "Destroyed config %p\n", PyGET_CWS_CONFIG(self))
}

enum c_parse_util_e {
  IS_BSON=1,
  IS_JSON
};

static int c_parse_util(
  CWS_CONFIG *config, 
  void **v_ser,
  const char *c_xml,
  Py_ssize_t c_xml_size,
  const char **errMsg,
  enum c_parse_util_e c_parse_util,
  int fromMem
)
{
  *v_ser=NULL;
  short code;

  if ((fromMem!=0)&&(c_xml_size<1)) {
    *errMsg="Wrong xml size or empty xml string";
    return -100;
  }

  if (cws_recycle_config(config)) {
    *errMsg="Could not recycle instance";
    return -104;
  }

  if (fromMem) {
    if (!cws_parse_XML_soap_envelope(config, (char *)c_xml, (size_t)c_xml_size)) {
      *errMsg="Could not parse xml string. See xml errors for details";
      return -101;
    }
  } else if (!cws_parse_XML_soap_envelope_from_file(config, (const char *)c_xml)) {
    *errMsg="Could not parse file. See xml errors for details";
    return -105;
  }

  if (cws_internal_serve(config)) {
    *errMsg="Could not deserialize xml string. See xml errors for details";
    return -102;
  }

  catch_base_msg14x(config, &code, (char **)errMsg);

  if (code<0)
    return (int)code;

  if (c_parse_util==IS_BSON) {
    if ((*v_ser=(void *)bsonSerialize(config))) {
      *errMsg="";
      return 0;
    }

    *errMsg="Could not serialize BSON";
  } else {
    if ((*v_ser=(void *)getJson(config))) {
      *errMsg="";
      return 0;
    }
    *errMsg="Could not serialize JSON";
  }

  return -103;
}

static PyObject *c_parse(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
  struct c_bson_serialized_t *bson_ser;
  char
   *kwlist[] = {"witsml_1.x.x.x_xml", NULL};

  const char
    *c_xml=NULL,
    *errMsg;
  Py_ssize_t c_xml_size=0;

  if (!PyArg_ParseTupleAndKeywords(
    args, kwds, "s#", kwlist,
    &c_xml, &c_xml_size
  )) Py_WITSML_14X_13X_ERROR("Error on parse WITSML 1.4.x.x | 1.3.x.x xml", NULL)

  if ((ERR=c_parse_util(PyGET_CWS_CONFIG(self), (void **)&bson_ser, c_xml, c_xml_size, &errMsg, IS_BSON, -1)))
    Py_WITSML_14X_13X_ERROR(errMsg, NULL)

  return Py_BuildValue("y#", (const char *)bson_ser->bson, (Py_ssize_t)bson_ser->bson_size);
}

static PyObject *c_parse_from_file(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
  struct c_bson_serialized_t *bson_ser;

  char
   *kwlist[] = {"witsml_1.x.x.x_xml_file", NULL},
   msgBuf[512];

  const char
    *c_xml_file,
    *errMsg;

  if (!PyArg_ParseTupleAndKeywords(
    args, kwds, "s", kwlist,
    &c_xml_file
  )) Py_WITSML_14X_13X_ERROR("Error on parse WITSML 1.4.x.x | 1.3.x.x file xml", NULL)


  if ((ERR=c_parse_util(PyGET_CWS_CONFIG(self), (void **)&bson_ser, c_xml_file, 1, &errMsg, IS_BSON, 0))) {
    snprintf(msgBuf, sizeof(msgBuf), "Error %d. %s", ERR, errMsg);
    PyErr_SetString(PyExc_Exception, msgBuf);
    return NULL;
  }

  return Py_BuildValue("y#", (const char *)bson_ser->bson, (Py_ssize_t)bson_ser->bson_size);
}

static PyObject *c_parse_to_json(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
  struct c_json_str_t *json_ser;
  char msgBuf[512];
  char
   *kwlist[] = {"witsml_1.x.x.x_xml", NULL};

  const char
    *c_xml_file=NULL,
    *errMsg;

  Py_ssize_t c_xml_len=0;

  if (!PyArg_ParseTupleAndKeywords(
    args, kwds, "s#", kwlist,
    &c_xml_file, &c_xml_len
  )) Py_WITSML_14X_13X_ERROR("c_parse_to_json: Error on parse WITSML 1.4.x.x | 1.3.x.x xml", NULL)

  if ((ERR=c_parse_util(PyGET_CWS_CONFIG(self), (void **)&json_ser, c_xml_file, c_xml_len, &errMsg, IS_JSON, -1))) {
    snprintf(msgBuf, sizeof(msgBuf), "c_parse_to_json: Error %d. %s", ERR, errMsg);
    PyErr_SetString(PyExc_Exception, msgBuf);
    return NULL;
  }

  return Py_BuildValue("s#", (const char *)json_ser->json, (Py_ssize_t)json_ser->json_len);
}

static PyObject *c_parse_to_json_from_file(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
  struct c_json_str_t *json_ser;
  char msgBuf[512];
  char
   *kwlist[] = {"witsml_1.x.x.x_xml_file", NULL};

  const char
    *c_xml_file,
    *errMsg;

  if (!PyArg_ParseTupleAndKeywords(
    args, kwds, "s", kwlist,
    &c_xml_file
  )) Py_WITSML_14X_13X_ERROR("c_parse_to_json_from_file: Error on parse WITSML 1.4.x.x | 1.3.x.x file xml", NULL)

  if ((ERR=c_parse_util(PyGET_CWS_CONFIG(self), (void **)&json_ser, c_xml_file, 1, &errMsg, IS_JSON, 0))) {
    snprintf(msgBuf, sizeof(msgBuf), "c_parse_to_json_from_file: Error %d. %s", ERR, errMsg);
    PyErr_SetString(PyExc_Exception, msgBuf);
    return NULL;
  }

  return Py_BuildValue("s#", (const char *)json_ser->json, (Py_ssize_t)json_ser->json_len);
}

static PyObject *c_get_object_name(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
  CHECK_HAS_ERROR("Could not get object name. Object not parsed or internal error", NULL)
  return Py_BuildValue("s", GET_OBJECT_NAME_PY);
}

static PyObject *c_get_instance_name(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
  return Py_BuildValue("s", (const char *)GET_INSTANCE_NAME);
}

static PyObject *c_get_error(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
  int err;

  if (GET_INTERNAL_SOAP_ERROR)
    err=GET_INTERNAL_SOAP_ERROR;
  else if (ERR)
    err=ERR;
  else if (GET_BASEMSG_CODE<0)
    err=GET_BASEMSG_CODE;
  else
    err=0;

  return PyLong_FromLong((long int)err);
}
#define PY_CWS_SET_CONST_NAME(name) #name, (Py_ssize_t)sizeof(#name)-1
static PyObject *c_get_basemsg_code(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
  int code;
  char *baseMsg;
  int baseMsgLen;

  if (GET_INTERNAL_SOAP_ERROR==0) {

    if ((code=PyGET_CWS_CONFIG(self)->base_msg.code)) {
      baseMsg=(char *)PyGET_CWS_CONFIG(self)->base_msg.message;
      baseMsgLen=PyGET_CWS_CONFIG(self)->base_msg.message_len;

c_get_basemsg_code_ret:
      return Py_BuildValue("{s#is#s#}",
        PY_CWS_SET_CONST_NAME(code), code,
        PY_CWS_SET_CONST_NAME(baseMessage), baseMsg, (Py_ssize_t)baseMsgLen
      );
    } else if ((ERR==0)&&(GET_OBJECT_NAME_PY!=NULL)) {
      code=1;
#define SUCCESS_MSG "Success"
      baseMsg=SUCCESS_MSG;
      baseMsgLen=(int)(sizeof(SUCCESS_MSG)-1);
#undef SUCCESS_MSG
      goto c_get_basemsg_code_ret;
    }
  }

  Py_WITSML_14X_13X_ERROR("Could not get base message code. Object not parsed or internal error", NULL)
}

static PyObject *c_get_faultstring(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
  return Py_BuildValue("z#",
    (const char *)PyGET_CWS_CONFIG(self)->cws_soap_fault.faultstring, (Py_ssize_t)PyGET_CWS_CONFIG(self)->cws_soap_fault.faultstring_len);
}

static PyObject *c_get_XMLfaultdetail(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
  return Py_BuildValue("z#",
    (const char *)PyGET_CWS_CONFIG(self)->cws_soap_fault.XMLfaultdetail, (Py_ssize_t)PyGET_CWS_CONFIG(self)->cws_soap_fault.XMLfaultdetail_len);
}

static PyObject *c_get_bson_version(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
  struct cws_version_t version;
  cws_version(&version);
  return Py_BuildValue("y#", (const char *)version.version, (Py_ssize_t)version.versionSize);
}

static PyObject *c_get_bson_bytes(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
  struct c_bson_serialized_t *bson_ser;

  CHECK_HAS_ERROR("c_get_bson_bytes: Could not get BSON serialized for this object. Object not found or error on parsing", NULL)

  if ((bson_ser=bsonSerialize(PyGET_CWS_CONFIG(self))))
    return Py_BuildValue("y#", (const char *)bson_ser->bson, (Py_ssize_t)bson_ser->bson_size);

  PyErr_SetString(PyExc_Exception, "c_get_bson_bytes: Could not parse bson serialized. Maybe libbson out of memory");
  return NULL;
}

static PyObject *c_get_json(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
  struct c_json_str_t *c_json;

  CHECK_HAS_ERROR("c_get_json: Could not get JSON string for this object. Object not found or error on parsing", NULL)

  if ((c_json=getJson(PyGET_CWS_CONFIG(self))))
    return Py_BuildValue("s#", (const char *)c_json->json, (Py_ssize_t)c_json->json_len);

  PyErr_SetString(PyExc_Exception, "c_get_json: Could not parse JSON string. Maybe libbson error or out of memory");
  return NULL;
}

static PyObject *c_save_to_file(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
  char
   *kwlist[] = {"bson_filename", NULL};

  const char
    *c_xml_file=NULL;

  CHECK_HAS_ERROR("c_save_to_file: Could not save BSON serialized to file for this object. Object not found or error on parsing", NULL)

  if (!PyArg_ParseTupleAndKeywords(
    args, kwds, "|z", kwlist,
    &c_xml_file
  )) Py_WITSML_14X_13X_ERROR("c_save_to_file: Error on parse output BSON filename", NULL)

  if (!writeToFile(PyGET_CWS_CONFIG(self), c_xml_file))
    return Py_None;

  PyErr_SetString(PyExc_Exception, "c_save_to_file: Could not save BSON to file.");
  return NULL;
}

static PyObject *c_save_json_to_file(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
  char
   *kwlist[] = {"json_filename", NULL};

  const char
    *c_xml_file=NULL;

  CHECK_HAS_ERROR("c_save_json_to_file: Could not save JSON string to file for this object. Object not found or error on parsing", NULL)

  if (!PyArg_ParseTupleAndKeywords(
    args, kwds, "|z", kwlist,
    &c_xml_file
  )) Py_WITSML_14X_13X_ERROR("c_save_json_to_file: Error on parse output JSON string filename", NULL)

  if (!writeToFileJSON(PyGET_CWS_CONFIG(self), c_xml_file))
    return Py_None;

  PyErr_SetString(PyExc_Exception, "c_save_json_to_file: Could not save JSON string to file.");
  return NULL;
}

static PyObject *c_get_basemsg14x(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
  int code;
  char *kwlist[] = {"code", NULL};
  struct cws_base_msg_t *cws_has_base_msg;

  if (!PyArg_ParseTupleAndKeywords(
    args, kwds, "i", kwlist,
    &code
  )) Py_WITSML_14X_13X_ERROR("Unable to get code number. Was expected an integer", NULL)

  if ((cws_has_base_msg=cws_has_base_msg14x((short)code)))
    return Py_BuildValue("{s#is#s#}",
      PY_CWS_SET_CONST_NAME(code), code,
      PY_CWS_SET_CONST_NAME(baseMessage), cws_has_base_msg->message, (Py_ssize_t)cws_has_base_msg->message_len
    );

  return Py_None;
}
//https://docs.python.org/3/c-api/dict.html
//https://stackoverflow.com/questions/4163018/create-an-object-using-pythons-c-api
//https://docs.python.org/3/c-api/list.html
static PyObject *c_get_basemsg14x_list(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
  PyObject *ret, *obj;
  struct cws_base_msg_t *list=get_base_msg_list();

  if (!(ret=PyList_New(0)))
    Py_WITSML_14X_13X_ERROR("Unable to parse base message list", NULL);

  while (list->message) {
    if (!(obj=Py_BuildValue("{s#is#s#}",
      PY_CWS_SET_CONST_NAME(code), (int)list->code,
      PY_CWS_SET_CONST_NAME(baseMessage), list->message, (Py_ssize_t)list->message_len
    ))) {
      Py_DECREF(ret);
      Py_WITSML_14X_13X_ERROR("Could not add Base Message list into Python Object", NULL)
    }

    if (PyList_Append(ret, obj)==0)
      Py_DECREF(obj);
    else {
      Py_DECREF(obj);
      Py_DECREF(ret);
      Py_WITSML_14X_13X_ERROR("Could not add Python Object to Python Parent Object", NULL)
    }

    list++;
  }

  return ret;
}

/*
#ifdef WITH_STATISTICS
#define Py_SET_STAT(k) #k, (long int)stat->k
static PyObject *c_get_statistics(PyTypeObject *self, PyObject *args, PyObject *kwds)
{
  struct soap *soap_internal=((Py_WITSML14X_13X_PARSER *)self)->soap_internal;
  struct statistics_t *stat;

  CHECK_HAS_ERROR("Statistics for this object not found or error on parsing", NULL)

  stat=getStatistics(soap_internal);

  return Py_BuildValue(
    "{sIsIsIsIsIsIsIsIsIsIsIsIsIsI}",
    Py_SET_STAT(costs),
    Py_SET_STAT(strings),
    Py_SET_STAT(shorts),
    Py_SET_STAT(ints),
    Py_SET_STAT(long64s),
    Py_SET_STAT(enums),
    Py_SET_STAT(arrays),
    Py_SET_STAT(booleans),
    Py_SET_STAT(doubles),
    Py_SET_STAT(date_times),
    Py_SET_STAT(measures),
    Py_SET_STAT(event_types),
    Py_SET_STAT(total),
    Py_SET_STAT(used_memory)
  );

}

#undef Py_SET_STAT
#endif

#undef CHECK_HAS_ERROR
#undef ERR
*/
static PyMethodDef py_witsml14x_methods[] = {

  {"parse", (PyCFunction)c_parse, METH_VARARGS|METH_KEYWORDS, "Parses a WITSML 1.4.x.x | 1.3.x.x XML to BSON"},
  {"parseToJSON", (PyCFunction)c_parse_to_json, METH_VARARGS|METH_KEYWORDS, "Parses a 1.4.x.x | 1.3.x.x XML to JSON string"},
  {"parseFromFile", (PyCFunction)c_parse_from_file, METH_VARARGS|METH_KEYWORDS, "Parses a WITSML 1.4.x.x | 1.3.x.x XML to BSON from file"},
  {"parseToJSONFromFile", (PyCFunction)c_parse_to_json_from_file, METH_VARARGS|METH_KEYWORDS, "Parses a WITSML 1.4.x.x | 1.3.x.x XML to JSON string from file"},
  {"getObjectName", (PyCFunction)c_get_object_name, METH_NOARGS, "Get WITSML 1.4.x.x | 1.3.x.x object name"},
  {"getInstanceName", (PyCFunction)c_get_instance_name, METH_NOARGS, "Get WITSML 1.4.x.x | 1.3.x.x instance name and its C config pointer"},
  {"getError", (PyCFunction)c_get_error, METH_NOARGS, "Get WITSML 1.4.x.x | 1.3.x.x error if exists"},
  {"getBaseMsgCode", (PyCFunction)c_get_basemsg_code, METH_NOARGS, "Get WITSML 1.4.x.x | 1.3.x.x base message code"},
  {"getFaultString", (PyCFunction)c_get_faultstring, METH_NOARGS, "Get WITSML 1.4.x.x | 1.3.x.x XML error 'faultstring' description"},
  {"getXMLfaultdetail", (PyCFunction)c_get_XMLfaultdetail, METH_NOARGS, "Get WITSML 1.4.x.x | 1.3.x.x XML error 'XMLfaultdetail' description"},
  {"getBsonBytes", (PyCFunction)c_get_bson_bytes, METH_NOARGS, "Get WITSML 1.4.x.x | 1.3.x.x objects in BSON serialized"},
  {"getJson", (PyCFunction)c_get_json, METH_NOARGS, "Get WITSML 1.4.x.x | 1.3.x.x objects in JSON string"},
  {"saveToFile", (PyCFunction)c_save_to_file, METH_VARARGS|METH_KEYWORDS, "Saves WITSML 1.4.x.x | 1.3.x.x objects to BSON file"},
  {"saveToFileJSON", (PyCFunction)c_save_json_to_file, METH_VARARGS|METH_KEYWORDS, "Saves WITSML 1.4.x.x | 1.3.x.x objects to JSON string file"},
/*#ifdef WITH_STATISTICS
  {"getStatistics", (PyCFunction)c_get_statistics, METH_NOARGS, "Get WITSML 2.1 xml document statistics"},
#endif
*/
  {NULL}
};

static PyMethodDef py_witsml14x_modules_functions[] = {
  {"getBaseMessageList_14x", (PyCFunction)c_get_basemsg14x_list, METH_NOARGS, "Get a list of base message code descriptions for WITSML versions 1.4.x.x"},
  {"getBaseMsg_14x", (PyCFunction)c_get_basemsg14x, METH_VARARGS|METH_KEYWORDS, "Get base message code descriptions for WITSML versions 1.4.x.x"},
  {"getBsonVersion", (PyCFunction)c_get_bson_version, METH_NOARGS, "Get WITSML 1.4.x.x | 1.3.x.x API C version"},
  {NULL}
};

static PyTypeObject Py_WITSML14x_Type = {
  PyVarObject_HEAD_INIT(NULL, 0)
  .tp_name="WITSML 1.4.x.x | 1.3.x.x to BSON parser",
  .tp_doc="A WITSML 1.4.x.x | 1.3.x.x to BSON parser instance",
  .tp_basicsize=sizeof(Py_WITSML14X_13X_PARSER),
  .tp_itemsize=0,
  .tp_flags=Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE,
  .tp_new=c_obj_new,
  .tp_init=(initproc)c_obj_init,
  .tp_dealloc=(destructor)c_obj_dealloc,
  .tp_methods=py_witsml14x_methods
};

static PyModuleDef Py_WITSML14x_module = {
  PyModuleDef_HEAD_INIT,
  .m_name="WITSML 1.4.x.x | 1.3.x.x to BSON parser module",
  .m_doc="WITSML 1.4.x.x | 1.3.x.x to BSON parser module for Python 3 using C library",
  .m_size=-1,
};


PyMODINIT_FUNC PyInit_witsml14xbson(void)
{
  PyObject *m;
  struct const_type_t *ct;

  Py_WITSML14X_13X_DEBUG(stdout, "Check is WITSML 1.4.x.x | 1.3.x.x parser is ready\n")
  if (PyType_Ready(&Py_WITSML14x_Type)<0)
    Py_WITSML_14X_13X_ERROR("\n\"Can't initialize module WITSML 1.4.x.x | 1.3.x.x parser\"\n", NULL)

  Py_WITSML14X_13X_DEBUG(stdout, "Creating module ...\n")
  if (!(m=PyModule_Create(&Py_WITSML14x_module)))
    Py_WITSML_14X_13X_ERROR("\nCannot create module \"Py_WITSML1.4.x.x | 1.3.x.x_module\"\n", NULL)

  Py_WITSML14X_13X_DEBUG(stdout, "Module %p created\n", m);
  if (PyModule_AddObject(m, "create", (PyObject *) &Py_WITSML14x_Type)<0)
    Py_WITSML_14X_13X_ERROR("\nCannot create module \"WITSML 1.4.x.x | 1.3.x.x to BSON parser\" from \"Py_WITSML14x_Type\"\n", NULL)

  Py_WITSML14X_13X_DEBUG(stdout, "Add %p functions\n", m);
  if (PyModule_AddFunctions(m, py_witsml14x_modules_functions)<0)
    Py_WITSML_14X_13X_ERROR("\nCannot create functions \"WITSML 1.4.x.x | 1.3.x.x to BSON parser\" from \"py_witsml14x_modules_functions\"\n", NULL)

  ct=CONST_TYPE;
  Py_WITSML14X_13X_DEBUG(stdout, "Add %p constants\n", ct);
  while (ct->name) {
    if (PyModule_AddIntConstant(m, ct->name, (long int)ct->value))
      Py_WITSML_14X_13X_ERROR("Could not add const value", NULL)

    ct++;
  }

  return m;
}

/////////////////////////////////////////////////////// C Witsml Parser ///////////////////////////////////////////////////////

CWS_BUILDER_14X_13X

//https://docs.python.org/3/c-api/module.html#c.PyModule_AddObject

