#ifndef READ_1411_DESERIALIZER
 #define READ_1411_DESERIALIZER

//typedef int (*readWitsmlObject1411Fn)(struct soap *soap_internal);

int bson_read_attachments1411(struct soap *);
int bson_read_bhaRuns1411(struct soap *);
int bson_read_cementJobs1411(struct soap *);
int bson_read_changeLogs1411(struct soap *);
int bson_read_convCores1411(struct soap *);
int bson_read_coordinateReferenceSystems1411(struct soap *);
int bson_read_drillReports1411(struct soap *);
int bson_read_fluidsReports1411(struct soap *);
int bson_read_formationMarkers1411(struct soap *);
int bson_read_logs1411(struct soap *);
int bson_read_messages1411(struct soap *);
int bson_read_mudLogs1411(struct soap *);
int bson_read_objectGroups1411(struct soap *);
int bson_read_opsReports1411(struct soap *);
int bson_read_rigs1411(struct soap *);
int bson_read_risks1411(struct soap *);
int bson_read_sidewallCores1411(struct soap *);
int bson_read_stimJobs1411(struct soap *);
int bson_read_surveyPrograms1411(struct soap *);
int bson_read_targets1411(struct soap *);
int bson_read_toolErrorModels1411(struct soap *);
int bson_read_toolErrorTermSets1411(struct soap *);
int bson_read_trajectorys1411(struct soap *);
int bson_read_tubulars1411(struct soap *);
int bson_read_wbGeometrys1411(struct soap *);
int bson_read_wellbores1411(struct soap *);
int bson_read_wells1411(struct soap *);

#define READ_1411_PARSER_BUILDER \
SOAP_FMAC5 int SOAP_FMAC6 rd1411__readObj1411(struct soap *soap_internal, struct rd1411__readObj1411_USCOREt *witsmlObject, char **result)\
{\
  DECLARE_CONFIG(soap_internal)\
  readWitsmlObject1411Fn fn=NULL;\
  int n=0;\
\
  if (!witsmlObject) {\
    *result="Unexpected rd1411__readObj1411 NULL pointer";\
    cws_set_soap_fault_util(soap_internal, -1232, CWS_FAULTSTR("Unexpected error. Check gSoap implementation"), -1);\
    return SOAP_FAULT;\
  }\
\
  config->witsmlObject=(void *)witsmlObject;\
\
  CWS_DETECT_OBJ(attachment)\
  CWS_DETECT_OBJ(bhaRun)\
  CWS_DETECT_OBJ(cementJob)\
  CWS_DETECT_OBJ(changeLog)\
  CWS_DETECT_OBJ(convCore)\
  CWS_DETECT_OBJ(coordinateReferenceSystem)\
  CWS_DETECT_OBJ(drillReport)\
  CWS_DETECT_OBJ(fluidsReport)\
  CWS_DETECT_OBJ(formationMarker)\
  CWS_DETECT_OBJ(log)\
  CWS_DETECT_OBJ(message)\
  CWS_DETECT_OBJ(mudLog)\
  CWS_DETECT_OBJ(objectGroup)\
  CWS_DETECT_OBJ(opsReport)\
  CWS_DETECT_OBJ(rig)\
  CWS_DETECT_OBJ(risk)\
  CWS_DETECT_OBJ(sidewallCore)\
  CWS_DETECT_OBJ(stimJob)\
  CWS_DETECT_OBJ(surveyProgram)\
  CWS_DETECT_OBJ(target)\
  CWS_DETECT_OBJ(toolErrorModel)\
  CWS_DETECT_OBJ(toolErrorTermSet)\
  CWS_DETECT_OBJ(trajectory)\
  CWS_DETECT_OBJ(tubular)\
  CWS_DETECT_OBJ(wbGeometry)\
  CWS_DETECT_OBJ(wellbore)\
  CWS_DETECT_OBJ(well)\
\
  if (n==1) {\
    *result=((n=fn(soap_internal))==SOAP_OK)?"rd1411__readObj1411 soap internal OK":"rd1411__readObj1411 soap internal FAIL";\
    return n;\
  }\
\
  config->objectName="READ: Unknown object";\
\
  if (n)\
    CWS_SET_SOAP_FAULT_CLIENT("READ: Too many objects. Only one allowed!")\
  else\
    CWS_SET_SOAP_FAULT_CLIENT("READ: No object to parse")\
\
  *result="rd1411__readObj1411 soap internal FAIL. Unknown object";\
\
  return SOAP_FAULT;\
}

#endif
