#ifndef REQUEST_CONTEXT_H
 #define REQUEST_CONTEXT_H

#include <stdsoap2.h>
//#include <base_msgs.h>
#include <cws_bson_utils.h>

#ifndef WITH_NOIDREF
  #error "Error. Declare first line below in stdsoap2.h #define WITH_NOIDREF"
#endif

#define ACTION_READ_141X 0
#define ACTION_WRITE_141X 1
#define ACTION_UPDATE_141X 2
#define ACTION_DELETE_141X 3

#define OBJ_ATTACHMENT "attachment"
#define OBJ_BHA_RUN "bhaRun"
#define OBJ_CEMENT_JOB "cementJob"
#define OBJ_CHANGE_LOG "changeLog"
#define OBJ_CONV_CORE "convCore"
#define OBJ_COORDINATE_REFERENCE_SYSTEM "coordinateReferenceSystem"
#define OBJ_DRILL_REPORT "drillReport"
#define OBJ_FLUID_REPORT "fluidsReport"
#define OBJ_FORMATION_MARKER "formationMarker"
#define OBJ_LOG "log"
#define OBJ_MESSAGE "message"
#define OBJ_MUD_LOG "mudLog"
#define OBJ_OBJ_GROUP "objectGroup"
#define OBJ_OPS_REPORT "opsReport"
#define OBJ_RIG "rig"
#define OBJ_RISK "risk"
#define OBJ_SIDEWALL_CORE "sidewallCore"
#define OBJ_STIM_JOB "stimJob"
#define OBJ_SURVEY_PROGRAM "surveyProgram"
#define OBJ_TARGET "target"
#define OBJ_TOOL_ERROR_MODEL "toolErrorModel"
#define OBJ_TOOL_ERROR_TERM_SET "toolErrorTermSet"
#define OBJ_TRAJECTORY "trajectory"
#define OBJ_TUBULAR "tubular"
#define OBJ_WB_GEOMETRY "wbGeometry"
#define OBJ_WELLBORE "wellbore"
#define OBJ_WELL "well"

enum service_protocol_version_e {
  VER_14X=1,
  VER_13X
};

typedef int (*cws_soap_caller_fn)(struct soap *);

struct cws_action_t {
  int action_type; // Action type, READ, WRITE..
  const char *action_name; // Action name READ, WRITE ...
  const char *action_function_name; //Action function name
  struct Namespace *namespaces; // Namespaces
  const char **versions; // Support version into a parse function, E.g.: "1.4.1.1" and "1.4.1"
  const char *soap_start; // Soap internal envelope start pointer. NULL if not required. E.g. GetCap and GetVersion
  size_t soap_start_len; // Soap internal envelope start pointer length
  const char *soap_end; // Soap internal envelope end pointer. NULL if not required. E.g. GetCap and GetVersion
  size_t soap_end_len; // Soap internal envelope end pointer length
  const char *soap_caller_namespace; // Soap caller match namespace
  cws_soap_caller_fn cws_soap_caller; // Soap caller function pointer
};

struct cws_soap_fault_t {
  char *faultstring; // alloc'd human-readable message with the reason of the error. It should be free after use
  size_t faultstring_len; // length string of faultstring
  char *XMLfaultdetail; //alloc'd XML-formatted string with details or NULL. It should be free after use
  size_t XMLfaultdetail_len; // length string of XMLfaultdetail_len
};

struct cws_base_msg_t {
  short code; // 0 at init
  int is_allocable; //0 For not alocable, else TRUE
  int message_len; // Message len
  const char *message; // NULL at init or if there are not errors. If alloc'd, must be free after use
};

#define CWS_FLAG_RECYCLABLE (1<<0)
#define CWS_FLAG_CHECK_VERSION_DISABLE (1<<1)
#define SET_CONFIG_FLAG(val) config->flag|=val;
#define UNSET_CONFIG_FLAG(val) config->flag&=~(val);

#ifdef WITH_STATISTICS
struct statistics_t {
  //Statistics in objects
  int32_t costs;
  int32_t strings;
  int32_t shorts;
  int32_t ints;
  int32_t long64s;
  int32_t enums;
  int32_t arrays;
  int32_t booleans;
  int32_t doubles;
  int32_t date_times;
  int32_t measures;
  int32_t event_types;
  int32_t total;
  size_t used_memory;
};
#endif

struct c_json_str_t {
  char *json;
  size_t json_len;
};

struct c_bson_serialized_t {
  uint8_t *bson;
  size_t bson_size;
};

typedef struct cws_config_t {
  struct soap *soap_internal_master; //soap master local struct used only if CWS_FLAG_RECYCLABLE is set. Can be NULL. It must be free
  struct soap *soap_internal; // Pointer of soap internal. Used only if multi thread.
  enum service_protocol_version_e service_protocol_version; // Service protocol version
  char instance_name[96]; // Name of config instance (Optional)
  uint64_t flag; // Flags used mainly in threads
  int internal_soap_error; // Error number for internal soap. It overlaps base_msg. base_msg should be free
  int internalInitFlag; // soap internal initialization flag
  char *xmlIn; // Pointer of XML object in (from client)
  size_t xmlLen; // Length of XML in (from client) excluding NULL char
  char *xmlSoap; // Pointer of XML object with soap envelope (for internal service process object). Should be free
  size_t xmlSoapLen; //Length of XML with SOAP envelope in (from client) excluding NULL char
  size_t xmlSoapSize; // Size of xmlSoap alloc'd memory by soap external. Used only for thread recyclable.
  const char *internal_os; // Internal SOAP output stream. Used only for debug
  const char *internal_master_os; // Internal SOAP master output stream. Used only for debug if is recycle mode
  const char *client_version; // Witsml version set by client. It MUST exist in action->versions[] to pass else error
  struct cws_action_t *action; // Nullable. If success parsing XML client it SHOULD load valid versions, action and soap internal envelopes
  void *witsmlObject; // Pointer of parsed object in Soap internal. NON NULL is SUCCESS
  bson_t *object; // Object parsed in BSON. Must be free by bson library
  const char *objectName; // Object name in soap internal auto detect
  struct cws_base_msg_t base_msg; // Base MSG. It must be initialized
  struct cws_soap_fault_t cws_soap_fault; // CWS SOAP FAULT
  struct c_bson_serialized_t c_bson_serialized; // Bson serialized (can be flushed to file). Must be free by bson library
  struct c_json_str_t c_json_str; // C JSON parsed to string. *json can be NULL. SHOULD be free.
#ifdef WITH_STATISTICS
  struct statistics_t statistics; // Statistics about objects for monitoring systems support
  long int initial_resource_size; // Initial resource size for statistic
#endif
} CWS_CONFIG;

#define CWS_CONFIG_SZ sizeof(CWS_CONFIG)
#define DECLARE_CONFIG(soap_ptr) CWS_CONFIG *config=((CWS_CONFIG *)soap_ptr->user);

CWS_CONFIG *cws_config_new(const char *, int *, int, int);

void cws_config_free(CWS_CONFIG **);
int cws_recycle_config(CWS_CONFIG *);

const char *check_client_schema_version(struct soap *, const char *);

void set_action(struct soap *, int);

char *cws_parse_XML_soap_envelope(CWS_CONFIG *, char *, size_t);
char *cws_parse_XML_soap_envelope_from_file(CWS_CONFIG *, const char *);

struct c_json_str_t *getJson(CWS_CONFIG *);
struct c_bson_serialized_t *bsonSerialize(CWS_CONFIG *);

int writeToFile(CWS_CONFIG *, const char *);
int writeToFileJSON(CWS_CONFIG *, const char *);


#define CWS_BUILDER_14X_13X \
int soap_serve_request(struct soap *soap)\
{\
  DECLARE_CONFIG(soap)\
  soap->mode |= SOAP_XML_STRICT;\
  (void)soap_peek_element(soap);\
\
  if (!soap_match_tag(soap, soap->tag, config->action->soap_caller_namespace))\
    return config->action->cws_soap_caller(soap);\
\
  return soap->error = SOAP_NO_METHOD;\
}

#define GET_OBJECT_NAME ((CWS_CONFIG *)(soap_internal->user))->objectName

#endif

