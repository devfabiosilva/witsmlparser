#sáb 29 jul 2023 18:08:53 
ENDIAN?=LITTLE
STAT?=WITH_STATISTICS
AR=ar rcs
LD=ld -r -b binary
CC=gcc
STRIP=strip
CURDIR=$(PWD)
INCLUDEDIR=$(CURDIR)/include
FLAG=-Wall -Wno-stringop-truncation -DWITH_NONAMESPACES -DWITH_NOSERVEREQUEST -D$(STAT) -DCWS_$(ENDIAN)_ENDIAN -lpthread
DEBUG_FLAG=-fsanitize=address,leak -DSOAP_DEBUG $(FLAG)
LIBANAME_PY=$(LIBANAME)_py
FLAG_JNI=-Wno-stringop-truncation -DCWS_$(ENDIAN)_ENDIAN -D$(STAT) -DWITH_NONAMESPACES -DWITH_NOSERVEREQUEST
FLAG_PY=-Wno-stringop-truncation -DCWS_$(ENDIAN)_ENDIAN -D$(STAT)
LIBANAME_JS=$(LIBANAME)_js
FLAG_JS=-Wno-stringop-truncation -DCWS_$(ENDIAN)_ENDIAN -D$(STAT)
TARG=cws
TARG_DBG=$(TARG)_debug
LIBANAME=cws
LIBDIR=$(CURDIR)/lib

MONGO_C_GIT=https://github.com/mongodb/mongo-c-driver.git
MONGO_C_BRANCH=1.27.1
MONGO_C_DIR=$(CURDIR)/third-party/mongo-c-driver

LIBANAME_JNI=$(LIBANAME)_jni
LIBJNI=libjwitsmlparserx.so
JAVAINCLUDE=/usr/lib/jvm/java-11-openjdk-amd64/include
JAVAINCLUDE_LINUX=/usr/lib/jvm/java-11-openjdk-amd64/include/linux
EXECSTACK=execstack -c

PARSE_1411_DIR=$(CURDIR)/parser/w1411

PARSE_1411_READ_DIR=$(PARSE_1411_DIR)/read
PARSE_1411_READ_INCLUDE_DIR=-I$(PARSE_1411_READ_DIR)/include

PARSE_1411_WRITE_DIR=$(PARSE_1411_DIR)/write
PARSE_1411_WRITE_INCLUDE_DIR=-I$(PARSE_1411_WRITE_DIR)/include

PARSE_1411_UPDATE_DIR=$(PARSE_1411_DIR)/update
PARSE_1411_UPDATE_INCLUDE_DIR=-I$(PARSE_1411_UPDATE_DIR)/include

PARSE_1411_DELETE_DIR=$(PARSE_1411_DIR)/delete
PARSE_1411_DELETE_INCLUDE_DIR=-I$(PARSE_1411_DELETE_DIR)/include

#-DWITH_NONAMESPACES -DWITH_NOSERVEREQUEST
all: main

cws_version.o:
	@echo "Generating version ..."
	@$(CC) -O2 $(CURDIR)/misc/versionBuilder.c $(CURDIR)/util/cws_utils.c $(CURDIR)/util/cws_bson_utils.c -I$(INCLUDEDIR) -o $(CURDIR)/misc/versionBuilder -L$(LIBDIR) -lbson-static-1.0 -Wall $(FLAG) -DVERGEN
	cd $(CURDIR)/misc/;./versionBuilder
	$(LD) -o $(CURDIR)/util/cws_version.o version.bson

request_context.o:
	@echo "Build request context for parsing ..."
	@$(CC) -O2 -c $(CURDIR)/util/request_context.c -I$(INCLUDEDIR) $(PARSE_1411_READ_INCLUDE_DIR) $(PARSE_1411_WRITE_INCLUDE_DIR) $(PARSE_1411_UPDATE_INCLUDE_DIR) $(PARSE_1411_DELETE_INCLUDE_DIR) -o $(CURDIR)/util/request_context.o $(FLAG)

cws_utils.o:
	@echo "Build CWS Utilities ..."
	@$(CC) -O2 -c $(CURDIR)/util/cws_utils.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_utils.o $(FLAG)

cws_soap.o:
	@echo "Build CWS INTERNAL/EXTERNAL SOAP constructors/destructors ..."
	@$(CC) -O2 -c $(CURDIR)/util/cws_soap.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_soap.o $(FLAG)

cws_memory.o:
	@echo "Build CWS MEMORY management ..."
	@$(CC) -O2 -c $(CURDIR)/util/cws_memory.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_memory.o $(FLAG)

cws_bson_utils.o:
	@echo "Build CWS BSON utilities ..."
	@$(CC) -O2 -c $(CURDIR)/util/cws_bson_utils.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_bson_utils.o $(FLAG)

base_msgs.o:
	@echo "Build base messages ..."
	@$(CC) -O2 -c $(CURDIR)/util/base_msgs.c -I$(INCLUDEDIR) -o $(CURDIR)/util/base_msgs.o $(FLAG)

cws_writer.o:
	@echo "Build BSON TO XML WRITER ..."
	@$(CC) -O2 -c $(CURDIR)/util/cws_writer.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_writer.o $(FLAG)

deserializer_util.o:
	@echo "Build deserializer (UTILITY 1.4.1.1) ..."
	@$(CC) -O2 -c $(CURDIR)/parser/w1411/deserializer_util.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/deserializer_util.o $(FLAG)

read_1411_deserializer.o:
	@echo "Build deserializer (READ 1.4.1.1) ..."
	@$(CC) -O2 -c $(CURDIR)/parser/w1411/read_1411_deserializer.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/read_1411_deserializer.o $(FLAG)

write_1411_deserializer.o:
	@echo "Build deserializer (WRITE 1.4.1.1) ..."
	@$(CC) -O2 -c $(CURDIR)/parser/w1411/write_1411_deserializer.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/write_1411_deserializer.o $(FLAG)

update_1411_deserializer.o:
	@echo "Build deserializer (UPDATE 1.4.1.1) ..."
	@$(CC) -O2 -c $(CURDIR)/parser/w1411/update_1411_deserializer.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/update_1411_deserializer.o $(FLAG)

delete_1411_deserializer.o:
	@echo "Build deserializer (DELETE 1.4.1.1) ..."
	@$(CC) -O2 -c $(CURDIR)/parser/w1411/delete_1411_deserializer.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/delete_1411_deserializer.o $(FLAG)

lib$(LIBANAME).a: cws_version.o cws_utils.o request_context.o cws_soap.o cws_memory.o cws_bson_utils.o base_msgs.o cws_writer.o deserializer_util.o read_1411_deserializer.o write_1411_deserializer.o update_1411_deserializer.o delete_1411_deserializer.o
ifneq ("$(wildcard $(LIBDIR)/lib$(LIBANAME).a)","")
	@echo "Nothing to do with lib$(LIBANAME).a"
else
	@echo "Build lib$(LIBANAME).a ..."
	$(AR) $(LIBDIR)/lib$(LIBANAME).a $(CURDIR)/util/cws_version.o $(CURDIR)/util/cws_utils.o $(CURDIR)/util/request_context.o $(CURDIR)/util/cws_soap.o $(CURDIR)/util/cws_memory.o $(CURDIR)/util/cws_bson_utils.o $(CURDIR)/util/base_msgs.o $(CURDIR)/util/cws_writer.o $(CURDIR)/parser/w1411/deserializer_util.o $(CURDIR)/parser/w1411/read_1411_deserializer.o $(CURDIR)/parser/w1411/write_1411_deserializer.o $(CURDIR)/parser/w1411/update_1411_deserializer.o $(CURDIR)/parser/w1411/delete_1411_deserializer.o -v
endif

read1411ServerLib.o:
ifneq ("$(wildcard $(PARSE_1411_READ_DIR)/read1411ServerLib.o)","")
	@echo "Nothing to do with read1411ServerLib.o"
else
	@echo "Building read1411ServerLib (READ PARSER 1.4.X)... It can take a little time ..."
	@$(CC) -O2 -c -o $(PARSE_1411_READ_DIR)/read1411ServerLib.o $(PARSE_1411_READ_DIR)/read1411ServerLib.c -I$(INCLUDEDIR) $(FLAG)
	@echo "Finishing read1411ServerLib.o"
endif

write1411ServerLib.o:
ifneq ("$(wildcard $(PARSE_1411_WRITE_DIR)/write1411ServerLib.o)","")
	@echo "Nothing to do with write1411ServerLib.o"
else
	@echo "Building write1411ServerLib (WRITE PARSER 1.4.X)... It can take a little time ..."
	@$(CC) -O2 -c -o $(PARSE_1411_WRITE_DIR)/write1411ServerLib.o $(PARSE_1411_WRITE_DIR)/write1411ServerLib.c -I$(INCLUDEDIR) $(FLAG)
	@echo "Finishing write1411ServerLib.o"
endif

update1411ServerLib.o:
ifneq ("$(wildcard $(PARSE_1411_UPDATE_DIR)/update1411ServerLib.o)","")
	@echo "Nothing to do with update1411ServerLib.o"
else
	@echo "Building update1411ServerLib (UPDATE PARSER 1.4.X)... It can take a little time ..."
	@$(CC) -O2 -c -o $(PARSE_1411_UPDATE_DIR)/update1411ServerLib.o $(PARSE_1411_UPDATE_DIR)/update1411ServerLib.c -I$(INCLUDEDIR) $(FLAG)
	@echo "Finishing update1411ServerLib.o"
endif

delete1411ServerLib.o:
ifneq ("$(wildcard $(PARSE_1411_DELETE_DIR)/delete1411ServerLib.o)","")
	@echo "Nothing to do with delete1411ServerLib.o"
else
	@echo "Building delete1411ServerLib (DELETE PARSER 1.4.X)... It can take a little time ..."
	@$(CC) -O2 -c -o $(PARSE_1411_DELETE_DIR)/delete1411ServerLib.o $(PARSE_1411_DELETE_DIR)/delete1411ServerLib.c -I$(INCLUDEDIR) $(FLAG)
	@echo "Finishing delete1411ServerLib.o"
endif

####
read1411ServerLib_shared.o:
ifneq ("$(wildcard $(PARSE_1411_READ_DIR)/read1411ServerLib_shared.o)","")
	@echo "Nothing to do with read1411ServerLib_shared.o"
else
	@echo "Building read1411ServerLib_shared (READ PARSER 1.4.X)... It can take a little time ..."
	@$(CC) -O2 -c -fPIC -o $(PARSE_1411_READ_DIR)/read1411ServerLib_shared.o $(PARSE_1411_READ_DIR)/read1411ServerLib.c -I$(INCLUDEDIR) $(FLAG)
	@echo "Finishing read1411ServerLib_shared.o"
endif

write1411ServerLib_shared.o:
ifneq ("$(wildcard $(PARSE_1411_WRITE_DIR)/write1411ServerLib_shared.o)","")
	@echo "Nothing to do with write1411ServerLib_shared.o"
else
	@echo "Building write1411ServerLib_shared (WRITE PARSER 1.4.X)... It can take a little time ..."
	@$(CC) -O2 -fPIC -c -o $(PARSE_1411_WRITE_DIR)/write1411ServerLib_shared.o $(PARSE_1411_WRITE_DIR)/write1411ServerLib.c -I$(INCLUDEDIR) $(FLAG)
	@echo "Finishing write1411ServerLib_shared.o"
endif

update1411ServerLib_shared.o:
ifneq ("$(wildcard $(PARSE_1411_UPDATE_DIR)/update1411ServerLib_shared.o)","")
	@echo "Nothing to do with update1411ServerLib_shared.o"
else
	@echo "Building update1411ServerLib_shared (UPDATE PARSER 1.4.X)... It can take a little time ..."
	@$(CC) -O2 -fPIC -c -o $(PARSE_1411_UPDATE_DIR)/update1411ServerLib_shared.o $(PARSE_1411_UPDATE_DIR)/update1411ServerLib.c -I$(INCLUDEDIR) $(FLAG)
	@echo "Finishing update1411ServerLib_shared.o"
endif

delete1411ServerLib_shared.o:
ifneq ("$(wildcard $(PARSE_1411_DELETE_DIR)/delete1411ServerLib_shared.o)","")
	@echo "Nothing to do with delete1411ServerLib_shared.o"
else
	@echo "Building delete1411ServerLib_shared (DELETE PARSER 1.4.X)... It can take a little time ..."
	@$(CC) -O2 -fPIC -c -o $(PARSE_1411_DELETE_DIR)/delete1411ServerLib_shared.o $(PARSE_1411_DELETE_DIR)/delete1411ServerLib.c -I$(INCLUDEDIR) $(FLAG)
	@echo "Finishing delete1411ServerLib_shared.o"
endif

####

cws_utils_debug.o:
	@echo "Build CWS Utilities (DEBUG)..."
	@$(CC) -O2 -c $(CURDIR)/util/cws_utils.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_utils_debug.o $(DEBUG_FLAG)

request_context_debug.o:
	@echo "Build request context for parsing (DEBUG) ..."
	@$(CC) -O2 -c $(CURDIR)/util/request_context.c -I$(INCLUDEDIR) $(PARSE_1411_READ_INCLUDE_DIR) $(PARSE_1411_WRITE_INCLUDE_DIR) $(PARSE_1411_UPDATE_INCLUDE_DIR) $(PARSE_1411_DELETE_INCLUDE_DIR) -o $(CURDIR)/util/request_context_debug.o $(DEBUG_FLAG)

cws_soap_debug.o:
	@echo "Build CWS INTERNAL/EXTERNAL SOAP constructors/destructors (DEBUG) ..."
	@$(CC) -O2 -c $(CURDIR)/util/cws_soap.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_soap_debug.o $(DEBUG_FLAG)

cws_memory_debug.o:
	@echo "Build CWS MEMORY (DEBUG) management ..."
	@$(CC) -O2 -c $(CURDIR)/util/cws_memory.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_memory_debug.o $(DEBUG_FLAG)

cws_bson_utils_debug.o:
	@echo "Build BSON utilities (DEBUG) management ..."
	@$(CC) -O2 -c $(CURDIR)/util/cws_bson_utils.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_bson_utils_debug.o $(DEBUG_FLAG)

base_msgs_debug.o:
	@echo "Build base messages (DEBUG) ..."
	@$(CC) -O2 -c $(CURDIR)/util/base_msgs.c -I$(INCLUDEDIR) -o $(CURDIR)/util/base_msgs_debug.o $(DEBUG_FLAG)

cws_writer_debug.o:
	@echo "Build BSON TO XML WRITER (DEBUG)..."
	@$(CC) -O2 -c $(CURDIR)/util/cws_writer.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_writer_debug.o $(DEBUG_FLAG)

deserializer_util_debug.o:
	@echo "Build deserializer DEBUG (UTILITY 1.4.1.1) ..."
	@$(CC) -O2 -c $(CURDIR)/parser/w1411/deserializer_util.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/deserializer_util_debug.o $(DEBUG_FLAG)

read_1411_deserializer_debug.o:
	@echo "Build deserializer (READ 1.4.1.1) - DEBUG ..."
	@$(CC) -O2 -c $(CURDIR)/parser/w1411/read_1411_deserializer.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/read_1411_deserializer_debug.o $(DEBUG_FLAG)

write_1411_deserializer_debug.o:
	@echo "Build deserializer (WRITE 1.4.1.1) - DEBUG ..."
	@$(CC) -O2 -c $(CURDIR)/parser/w1411/write_1411_deserializer.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/write_1411_deserializer_debug.o $(DEBUG_FLAG)

update_1411_deserializer_debug.o:
	@echo "Build deserializer (UPDATE 1.4.1.1) - DEBUG ..."
	@$(CC) -O2 -c $(CURDIR)/parser/w1411/update_1411_deserializer.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/update_1411_deserializer_debug.o $(DEBUG_FLAG)

delete_1411_deserializer_debug.o:
	@echo "Build deserializer (DELETE 1.4.1.1) - DEBUG ..."
	@$(CC) -O2 -c $(CURDIR)/parser/w1411/delete_1411_deserializer.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/delete_1411_deserializer_debug.o $(DEBUG_FLAG)

lib$(LIBANAME)_debug.a: cws_version.o cws_utils_debug.o request_context_debug.o cws_soap_debug.o cws_memory_debug.o cws_bson_utils_debug.o base_msgs_debug.o cws_writer_debug.o  deserializer_util_debug.o read_1411_deserializer_debug.o write_1411_deserializer_debug.o update_1411_deserializer_debug.o delete_1411_deserializer_debug.o
ifneq ("$(wildcard $(LIBDIR)/lib$(LIBANAME)_debug.a)","")
	@echo "Nothing to do with lib$(LIBANAME)_debug.a"
else
	@echo "Build lib$(LIBANAME)_debug.a ..."
	$(AR) $(LIBDIR)/lib$(LIBANAME)_debug.a $(CURDIR)/util/cws_version.o $(CURDIR)/util/cws_utils_debug.o $(CURDIR)/util/request_context_debug.o $(CURDIR)/util/cws_soap_debug.o $(CURDIR)/util/cws_memory_debug.o $(CURDIR)/util/cws_bson_utils_debug.o $(CURDIR)/util/base_msgs_debug.o $(CURDIR)/util/cws_writer_debug.o $(CURDIR)/parser/w1411/deserializer_util_debug.o $(CURDIR)/parser/w1411/read_1411_deserializer_debug.o $(CURDIR)/parser/w1411/write_1411_deserializer_debug.o $(CURDIR)/parser/w1411/update_1411_deserializer_debug.o $(CURDIR)/parser/w1411/delete_1411_deserializer_debug.o -v
endif

read1411ServerLib_debug.o:
ifneq ("$(wildcard $(PARSE_1411_READ_DIR)/read1411ServerLib_debug.o)","")
	@echo "Nothing to do with read1411ServerLib_debug.o"
else
	@echo "Building read1411ServerLib_debug (READ PARSER 1.4.X)... It can take a little time ..."
	@$(CC) -O2 -c -o $(PARSE_1411_READ_DIR)/read1411ServerLib_debug.o $(PARSE_1411_READ_DIR)/read1411ServerLib.c -I$(INCLUDEDIR) $(DEBUG_FLAG)
	@echo "Finishing read1411ServerLib.o"
endif

write1411ServerLib_debug.o:
ifneq ("$(wildcard $(PARSE_1411_WRITE_DIR)/write1411ServerLib_debug.o)","")
	@echo "Nothing to do with write1411ServerLib_debug.o"
else
	@echo "Building write1411ServerLib_debug (WRITE PARSER 1.4.X)... It can take a little time ..."
	@$(CC) -O2 -c -o $(PARSE_1411_WRITE_DIR)/write1411ServerLib_debug.o $(PARSE_1411_WRITE_DIR)/write1411ServerLib.c -I$(INCLUDEDIR) $(DEBUG_FLAG)
	@echo "Finishing write1411ServerLib_debug.o"
endif

update1411ServerLib_debug.o:
ifneq ("$(wildcard $(PARSE_1411_UPDATE_DIR)/update1411ServerLib_debug.o)","")
	@echo "Nothing to do with update1411ServerLib_debug.o"
else
	@echo "Building update1411ServerLib_debug (UPDATE PARSER 1.4.X) - DEBUG... It can take a little time ..."
	@$(CC) -O2 -c -o $(PARSE_1411_UPDATE_DIR)/update1411ServerLib_debug.o $(PARSE_1411_UPDATE_DIR)/update1411ServerLib.c -I$(INCLUDEDIR) $(DEBUG_FLAG)
	@echo "Finishing update1411ServerLib_debug.o"
endif

delete1411ServerLib_debug.o:
ifneq ("$(wildcard $(PARSE_1411_DELETE_DIR)/delete1411ServerLib_debug.o)","")
	@echo "Nothing to do with delete1411ServerLib_debug.o"
else
	@echo "Building delete1411ServerLib_debug (DELETE PARSER 1.4.X) - DEBUG... It can take a little time ..."
	@$(CC) -O2 -c -o $(PARSE_1411_DELETE_DIR)/delete1411ServerLib_debug.o $(PARSE_1411_DELETE_DIR)/delete1411ServerLib.c -I$(INCLUDEDIR) $(DEBUG_FLAG)
	@echo "Finishing delete1411ServerLib_debug.o"
endif

main: read1411ServerLib.o write1411ServerLib.o update1411ServerLib.o delete1411ServerLib.o lib$(LIBANAME).a
#main: write1411ServerLib.o update1411ServerLib.o delete1411ServerLib.o lib$(LIBANAME).a
	@echo "Compiling ..."
	@$(CC) -O2 -o $(TARG) main.c $(PARSE_1411_READ_DIR)/read1411ServerLib.o $(PARSE_1411_WRITE_DIR)/write1411ServerLib.o $(PARSE_1411_UPDATE_DIR)/update1411ServerLib.o $(PARSE_1411_DELETE_DIR)/delete1411ServerLib.o stdsoap2.c -I$(INCLUDEDIR) -L$(LIBDIR) -l$(LIBANAME) -lbson-static-1.0 $(FLAG)
	@echo "Finished"

###

read1411ServerLib_shared_debug.o:
ifneq ("$(wildcard $(PARSE_1411_READ_DIR)/read1411ServerLib_shared_debug.o)","")
	@echo "Nothing to do with read1411ServerLib_shared_debug.o"
else
	@echo "Building read1411ServerLib_shared_debug (READ PARSER 1.4.X)... It can take a little time ..."
	@$(CC) -O2 -fPIC -c -o $(PARSE_1411_READ_DIR)/read1411ServerLib_shared_debug.o $(PARSE_1411_READ_DIR)/read1411ServerLib.c -I$(INCLUDEDIR) $(DEBUG_FLAG)
	@echo "Finishing read1411ServerLib_shared.o"
endif

write1411ServerLib_shared_debug.o:
ifneq ("$(wildcard $(PARSE_1411_WRITE_DIR)/write1411ServerLib_shared_debug.o)","")
	@echo "Nothing to do with write1411ServerLib_shared_debug.o"
else
	@echo "Building write1411ServerLib_shared_debug (WRITE PARSER 1.4.X)... It can take a little time ..."
	@$(CC) -O2 -fPIC -c -o $(PARSE_1411_WRITE_DIR)/write1411ServerLib_shared_debug.o $(PARSE_1411_WRITE_DIR)/write1411ServerLib.c -I$(INCLUDEDIR) $(DEBUG_FLAG)
	@echo "Finishing write1411ServerLib_shared_debug.o"
endif

update1411ServerLib_shared_debug.o:
ifneq ("$(wildcard $(PARSE_1411_UPDATE_DIR)/update1411ServerLib_shared_debug.o)","")
	@echo "Nothing to do with update1411ServerLib_shared_debug.o"
else
	@echo "Building update1411ServerLib_shared_debug (UPDATE PARSER 1.4.X) - DEBUG... It can take a little time ..."
	@$(CC) -O2 -fPIC -c -o $(PARSE_1411_UPDATE_DIR)/update1411ServerLib_shared_debug.o $(PARSE_1411_UPDATE_DIR)/update1411ServerLib.c -I$(INCLUDEDIR) $(DEBUG_FLAG)
	@echo "Finishing update1411ServerLib_shared_debug.o"
endif

delete1411ServerLib_shared_debug.o:
ifneq ("$(wildcard $(PARSE_1411_DELETE_DIR)/delete1411ServerLib_shared_debug.o)","")
	@echo "Nothing to do with delete1411ServerLib_shared_debug.o"
else
	@echo "Building delete1411ServerLib_shared_debug (DELETE PARSER 1.4.X) - DEBUG... It can take a little time ..."
	@$(CC) -O2 -fPIC -c -o $(PARSE_1411_DELETE_DIR)/delete1411ServerLib_shared_debug.o $(PARSE_1411_DELETE_DIR)/delete1411ServerLib.c -I$(INCLUDEDIR) $(DEBUG_FLAG)
	@echo "Finishing delete1411ServerLib_shared_debug.o"
endif

dbg: read1411ServerLib_debug.o write1411ServerLib_debug.o update1411ServerLib_debug.o delete1411ServerLib_debug.o lib$(LIBANAME)_debug.a
	@echo "Compiling in debug mode ..."
	@$(CC) -O2 -o $(TARG_DBG) main.c $(PARSE_1411_READ_DIR)/read1411ServerLib_debug.o $(PARSE_1411_WRITE_DIR)/write1411ServerLib_debug.o $(PARSE_1411_UPDATE_DIR)/update1411ServerLib_debug.o $(PARSE_1411_DELETE_DIR)/delete1411ServerLib_debug.o stdsoap2.c -I$(INCLUDEDIR) -L$(LIBDIR) -l$(LIBANAME)_debug -lbson-static-1.0 $(DEBUG_FLAG)
	@echo "Finished in debug mode."

#//////////////////////////////

#JNI
request_context_jni.o:
	@echo "Build request context for parsing for Java/Kotlin ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/request_context.c -I$(INCLUDEDIR) $(PARSE_1411_READ_INCLUDE_DIR) $(PARSE_1411_WRITE_INCLUDE_DIR) $(PARSE_1411_UPDATE_INCLUDE_DIR) $(PARSE_1411_DELETE_INCLUDE_DIR) -o $(CURDIR)/util/request_context_jni.o $(FLAG_JNI)

cws_utils_jni.o:
	@echo "Build CWS Utilities for Java/Kotlin ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/cws_utils.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_utils_jni.o $(FLAG_JNI)

cws_soap_jni.o:
	@echo "Build CWS INTERNAL/EXTERNAL SOAP constructors/destructors for Java/Kotlin ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/cws_soap.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_soap_jni.o $(FLAG_JNI)

cws_memory_jni.o:
	@echo "Build CWS MEMORY management for Java/Kotlin ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/cws_memory.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_memory_jni.o $(FLAG_JNI)

cws_bson_utils_jni.o:
	@echo "Build CWS BSON utilities for Python 3 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/cws_bson_utils.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_bson_utils_jni.o $(FLAG_JNI)

base_msgs_jni.o:
	@echo "Build base messages for Java/Kotlin ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/base_msgs.c -I$(INCLUDEDIR) -o $(CURDIR)/util/base_msgs_jni.o $(FLAG_JNI)

cws_writer_jni.o:
	@echo "Build BSON TO XML WRITER for Java/Kotlin ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/cws_writer.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_writer_jni.o $(FLAG_JNI)

deserializer_util_jni.o:
	@echo "Build deserializer (UTILITY 1.4.1.1) for Java/Kotlin ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/parser/w1411/deserializer_util.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/deserializer_util_jni.o $(FLAG_JNI)

read_1411_deserializer_jni.o:
	@echo "Build deserializer (READ 1.4.1.1) for Java/Kotlin ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/parser/w1411/read_1411_deserializer.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/read_1411_deserializer_jni.o $(FLAG_JNI)

write_1411_deserializer_jni.o:
	@echo "Build deserializer (WRITE 1.4.1.1) for Java/Kotlin ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/parser/w1411/write_1411_deserializer.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/write_1411_deserializer_jni.o $(FLAG_JNI)

update_1411_deserializer_jni.o:
	@echo "Build deserializer (UPDATE 1.4.1.1) for Java/Kotlin ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/parser/w1411/update_1411_deserializer.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/update_1411_deserializer_jni.o $(FLAG_JNI)

delete_1411_deserializer_jni.o:
	@echo "Build deserializer (DELETE 1.4.1.1) for Java/Kotlin ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/parser/w1411/delete_1411_deserializer.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/delete_1411_deserializer_jni.o $(FLAG_JNI)

lib$(LIBANAME_JNI).a: cws_version.o cws_utils_jni.o request_context_jni.o cws_soap_jni.o cws_memory_jni.o cws_bson_utils_jni.o base_msgs_jni.o cws_writer_jni.o deserializer_util_jni.o read_1411_deserializer_jni.o write_1411_deserializer_jni.o update_1411_deserializer_jni.o delete_1411_deserializer_jni.o
ifneq ("$(wildcard $(LIBDIR)/lib$(LIBANAME_JNI).a)","")
	@echo "Nothing to do with lib$(LIBANAME_JNI).a for Java/Kotlin"
else
	@echo "Build lib$(LIBANAME_JNI).a for Java/Kotlin ..."
	$(AR) $(LIBDIR)/lib$(LIBANAME_JNI).a $(CURDIR)/util/cws_version.o $(CURDIR)/util/cws_utils_jni.o $(CURDIR)/util/request_context_jni.o $(CURDIR)/util/cws_soap_jni.o $(CURDIR)/util/cws_memory_jni.o $(CURDIR)/util/cws_bson_utils_jni.o $(CURDIR)/util/base_msgs_jni.o $(CURDIR)/util/cws_writer_jni.o $(CURDIR)/parser/w1411/deserializer_util_jni.o $(CURDIR)/parser/w1411/read_1411_deserializer_jni.o $(CURDIR)/parser/w1411/write_1411_deserializer_jni.o $(CURDIR)/parser/w1411/update_1411_deserializer_jni.o $(CURDIR)/parser/w1411/delete_1411_deserializer_jni.o -v
endif

#//////////////////////////////

#PY
request_context_py.o:
	@echo "Build request context for parsing for Python 3 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/request_context.c -I$(INCLUDEDIR) $(PARSE_1411_READ_INCLUDE_DIR) $(PARSE_1411_WRITE_INCLUDE_DIR) $(PARSE_1411_UPDATE_INCLUDE_DIR) $(PARSE_1411_DELETE_INCLUDE_DIR) -o $(CURDIR)/util/request_context_py.o $(FLAG_PY)

cws_utils_py.o:
	@echo "Build CWS Utilities for Python 3 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/cws_utils.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_utils_py.o $(FLAG_PY)

cws_soap_py.o:
	@echo "Build CWS INTERNAL/EXTERNAL SOAP constructors/destructors for Python 3 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/cws_soap.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_soap_py.o $(FLAG_PY)

cws_memory_py.o:
	@echo "Build CWS MEMORY management for Python 3 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/cws_memory.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_memory_py.o $(FLAG_PY)

cws_bson_utils_py.o:
	@echo "Build CWS BSON utilities for Python 3 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/cws_bson_utils.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_bson_utils_py.o $(FLAG_PY)

base_msgs_py.o:
	@echo "Build base messages for Python 3 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/base_msgs.c -I$(INCLUDEDIR) -o $(CURDIR)/util/base_msgs_py.o $(FLAG_PY)

cws_writer_py.o:
	@echo "Build BSON TO XML WRITER for Python 3 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/cws_writer.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_writer_py.o $(FLAG_PY)

deserializer_util_py.o:
	@echo "Build deserializer (UTILITY 1.4.1.1) for Python 3 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/parser/w1411/deserializer_util.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/deserializer_util_py.o $(FLAG_PY)

read_1411_deserializer_py.o:
	@echo "Build deserializer (READ 1.4.1.1) for Python 3 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/parser/w1411/read_1411_deserializer.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/read_1411_deserializer_py.o $(FLAG_PY)

write_1411_deserializer_py.o:
	@echo "Build deserializer (WRITE 1.4.1.1) for Python 3 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/parser/w1411/write_1411_deserializer.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/write_1411_deserializer_py.o $(FLAG_PY)

update_1411_deserializer_py.o:
	@echo "Build deserializer (UPDATE 1.4.1.1) for Python 3 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/parser/w1411/update_1411_deserializer.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/update_1411_deserializer_py.o $(FLAG_PY)

delete_1411_deserializer_py.o:
	@echo "Build deserializer (DELETE 1.4.1.1) for Python 3 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/parser/w1411/delete_1411_deserializer.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/delete_1411_deserializer_py.o $(FLAG_PY)

lib$(LIBANAME_PY).a: cws_version.o cws_utils_py.o request_context_py.o cws_soap_py.o cws_memory_py.o cws_bson_utils_py.o base_msgs_py.o cws_writer_py.o deserializer_util_py.o read_1411_deserializer_py.o write_1411_deserializer_py.o update_1411_deserializer_py.o delete_1411_deserializer_py.o
ifneq ("$(wildcard $(LIBDIR)/lib$(LIBANAME_PY).a)","")
	@echo "Nothing to do with lib$(LIBANAME_PY).a for Python 3"
else
	@echo "Build lib$(LIBANAME_PY).a for Python 3 ..."
	$(AR) $(LIBDIR)/lib$(LIBANAME_PY).a $(CURDIR)/util/cws_version.o $(CURDIR)/util/cws_utils_py.o $(CURDIR)/util/request_context_py.o $(CURDIR)/util/cws_soap_py.o $(CURDIR)/util/cws_memory_py.o $(CURDIR)/util/cws_bson_utils_py.o $(CURDIR)/util/base_msgs_py.o $(CURDIR)/util/cws_writer_py.o $(CURDIR)/parser/w1411/deserializer_util_py.o $(CURDIR)/parser/w1411/read_1411_deserializer_py.o $(CURDIR)/parser/w1411/write_1411_deserializer_py.o $(CURDIR)/parser/w1411/update_1411_deserializer_py.o $(CURDIR)/parser/w1411/delete_1411_deserializer_py.o -v
endif

#NODEJS
request_context_js.o:
	@echo "Build request context for parsing for Nodejs >= 8 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/request_context.c -I$(INCLUDEDIR) $(PARSE_1411_READ_INCLUDE_DIR) $(PARSE_1411_WRITE_INCLUDE_DIR) $(PARSE_1411_UPDATE_INCLUDE_DIR) $(PARSE_1411_DELETE_INCLUDE_DIR) -o $(CURDIR)/util/request_context_js.o $(FLAG_JS)

cws_utils_js.o:
	@echo "Build CWS Utilities for Nodejs >= 8 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/cws_utils.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_utils_js.o $(FLAG_JS)

cws_soap_js.o:
	@echo "Build CWS INTERNAL/EXTERNAL SOAP constructors/destructors for Nodejs >=8 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/cws_soap.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_soap_js.o $(FLAG_JS)

cws_memory_js.o:
	@echo "Build CWS MEMORY management for Nodejs >=8 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/cws_memory.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_memory_js.o $(FLAG_JS)

cws_bson_utils_js.o:
	@echo "Build CWS BSON utilities for Nodejs >= 8 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/cws_bson_utils.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_bson_utils_js.o $(FLAG_JS)

base_msgs_js.o:
	@echo "Build base messages for Nodejs >= 8 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/base_msgs.c -I$(INCLUDEDIR) -o $(CURDIR)/util/base_msgs_js.o $(FLAG_JS)

cws_writer_js.o:
	@echo "Build BSON TO XML WRITER for Nodejs >= 8 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/util/cws_writer.c -I$(INCLUDEDIR) -o $(CURDIR)/util/cws_writer_js.o $(FLAG_JS)

deserializer_util_js.o:
	@echo "Build deserializer (UTILITY 1.4.1.1) for Nodejs >= 8 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/parser/w1411/deserializer_util.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/deserializer_util_js.o $(FLAG_JS)

read_1411_deserializer_js.o:
	@echo "Build deserializer (READ 1.4.1.1) for Nodejs >= 8 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/parser/w1411/read_1411_deserializer.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/read_1411_deserializer_js.o $(FLAG_JS)

write_1411_deserializer_js.o:
	@echo "Build deserializer (WRITE 1.4.1.1) for Nodejs >= 8 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/parser/w1411/write_1411_deserializer.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/write_1411_deserializer_js.o $(FLAG_JS)

update_1411_deserializer_js.o:
	@echo "Build deserializer (UPDATE 1.4.1.1) for Nodejs >= 8 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/parser/w1411/update_1411_deserializer.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/update_1411_deserializer_js.o $(FLAG_JS)

delete_1411_deserializer_js.o:
	@echo "Build deserializer (DELETE 1.4.1.1) for Nodejs >= 8 ..."
	@$(CC) -O2 -fPIC -c $(CURDIR)/parser/w1411/delete_1411_deserializer.c -I$(INCLUDEDIR) -o $(CURDIR)/parser/w1411/delete_1411_deserializer_js.o $(FLAG_JS)

lib$(LIBANAME_JS).a: cws_version.o cws_utils_js.o request_context_js.o cws_soap_js.o cws_memory_js.o cws_bson_utils_js.o base_msgs_js.o cws_writer_js.o deserializer_util_js.o read_1411_deserializer_js.o write_1411_deserializer_js.o update_1411_deserializer_js.o delete_1411_deserializer_js.o
ifneq ("$(wildcard $(LIBDIR)/lib$(LIBANAME_JS).a)","")
	@echo "Nothing to do with lib$(LIBANAME_JS).a for Nodejs >= 8"
else
	@echo "Build lib$(LIBANAME_JS).a for Nodejs >= 8 ..."
	$(AR) $(LIBDIR)/lib$(LIBANAME_JS).a $(CURDIR)/util/cws_version.o $(CURDIR)/util/cws_utils_js.o $(CURDIR)/util/request_context_js.o $(CURDIR)/util/cws_soap_js.o $(CURDIR)/util/cws_memory_js.o $(CURDIR)/util/cws_bson_utils_js.o $(CURDIR)/util/base_msgs_js.o $(CURDIR)/util/cws_writer_js.o $(CURDIR)/parser/w1411/deserializer_util_js.o $(CURDIR)/parser/w1411/read_1411_deserializer_js.o $(CURDIR)/parser/w1411/write_1411_deserializer_js.o $(CURDIR)/parser/w1411/update_1411_deserializer_js.o $(CURDIR)/parser/w1411/delete_1411_deserializer_js.o -v
endif

.PHONY:
clean:
ifneq ("$(wildcard $(CURDIR)/util/*.o)","")
	@echo "Removing objects ..."
	rm -v $(CURDIR)/util/*.o
else
	@echo "Nothing to do with objects in util"
endif

ifneq ("$(wildcard $(CURDIR)/parser/w1411/*.o)","")
	@echo "Removing objects in $(CURDIR)/parser/w1411/ ..."
	rm -v $(CURDIR)/parser/w1411/*.o
else
	@echo "Nothing to do with objects in parser 1.4.1.1"
endif

ifneq ("$(wildcard $(CURDIR)/$(TARG_DBG))","")
	@echo "Removing main $(TARG_DBG)..."
	rm -v $(CURDIR)/$(TARG_DBG)
else
	@echo "Nothing to do $(TARG_DBG)"
endif

ifneq ("$(wildcard $(CURDIR)/$(TARG))","")
	@echo "Removing main $(TARG)..."
	rm -v $(CURDIR)/$(TARG)
else
	@echo "Nothing to do $(TARG)"
endif

ifneq ("$(wildcard $(LIBDIR)/lib$(LIBANAME).a)","")
	@echo "Removing lib$(LIBANAME).a..."
	rm -v $(LIBDIR)/lib$(LIBANAME).a
else
	@echo "Nothing to do $(LIBDIR)/lib$(LIBANAME).a"
endif

ifneq ("$(wildcard $(LIBDIR)/lib$(LIBANAME)_debug.a)","")
	@echo "Removing lib$(LIBANAME)_debug.a..."
	rm -v $(LIBDIR)/lib$(LIBANAME)_debug.a
else
	@echo "Nothing to do $(LIBDIR)/lib$(LIBANAME)_debug.a"
endif

ifneq ("$(wildcard $(CURDIR)/*.log)","")
	@echo "Removing debug logs ..."
	rm -iv $(CURDIR)/*.log
else
	@echo "Nothing to do with logs"
endif

ifneq ("$(wildcard $(CURDIR)/$(LIBJNI))","")
	@echo "Removing $(LIBJNI)..."
	rm -v $(CURDIR)/$(LIBJNI)
else
	@echo "Nothing to do with $(LIBJNI)"
endif

ifneq ("$(wildcard $(LIBDIR)/lib$(LIBANAME_JNI).a)","")
	@echo "Removing lib$(LIBANAME_JNI).a..."
	rm -v $(LIBDIR)/lib$(LIBANAME_JNI).a
else
	@echo "Nothing to do $(LIBDIR)/lib$(LIBANAME_JNI).a"
endif

ifneq ("$(wildcard $(LIBDIR)/lib$(LIBANAME_PY).a)","")
	@echo "Removing lib$(LIBANAME_PY).a..."
	rm -v $(LIBDIR)/lib$(LIBANAME_PY).a
else
	@echo "Nothing to do $(LIBDIR)/lib$(LIBANAME_PY).a"
endif

ifneq ("$(wildcard $(LIBDIR)/lib$(LIBANAME_JS).a)","")
	@echo "Removing lib$(LIBANAME_JS).a..."
	rm -v $(LIBDIR)/lib$(LIBANAME_JS).a
else
	@echo "Nothing to do $(LIBDIR)/lib$(LIBANAME_JS).a"
endif

ifneq ("$(wildcard $(CURDIR)/build)","")
	@echo "Removing Python 3 and/or NodeJS library $(CURDIR)/build ..."
	rm -frv $(CURDIR)/build
else
	@echo "Nothing to do $(CURDIR)/build"
endif

ifneq ("$(wildcard $(CURDIR)/*.bson)","")
	@echo "Removing BSON files ..."
	rm -v $(CURDIR)/*.bson
else
	@echo "Nothing to do with BSON files"
endif

.PHONY:
pre_remove:
ifneq ("$(wildcard $(PARSE_1411_READ_DIR)/read1411ServerLib.o)","")
	@echo "Removing read1411ServerLib.o ..."
	rm -v $(PARSE_1411_READ_DIR)/read1411ServerLib.o
else
	@echo "Nothing to do with read1411ServerLib.o"
endif

ifneq ("$(wildcard $(PARSE_1411_READ_DIR)/read1411ServerLib_shared.o)","")
	@echo "Removing read1411ServerLib_shared.o ..."
	rm -v $(PARSE_1411_READ_DIR)/read1411ServerLib_shared.o
else
	@echo "Nothing to do with read1411ServerLib_shared.o"
endif

ifneq ("$(wildcard $(PARSE_1411_READ_DIR)/read1411ServerLib_debug.o)","")
	@echo "Removing read1411ServerLib_debug.o ..."
	rm -v $(PARSE_1411_READ_DIR)/read1411ServerLib_debug.o
else
	@echo "Nothing to do with read1411ServerLib_debug.o"
endif

ifneq ("$(wildcard $(PARSE_1411_READ_DIR)/read1411ServerLib_shared_debug.o)","")
	@echo "Removing read1411ServerLib_shared_debug.o ..."
	rm -v $(PARSE_1411_READ_DIR)/read1411ServerLib_shared_debug.o
else
	@echo "Nothing to do with read1411ServerLib_shared_debug.o"
endif

ifneq ("$(wildcard $(PARSE_1411_WRITE_DIR)/write1411ServerLib.o)","")
	@echo "Removing write1411ServerLib.o ..."
	rm -v $(PARSE_1411_WRITE_DIR)/write1411ServerLib.o
else
	@echo "Nothing to do with write1411ServerLib.o"
endif

ifneq ("$(wildcard $(PARSE_1411_WRITE_DIR)/write1411ServerLib_shared.o)","")
	@echo "Removing write1411ServerLib_shared.o ..."
	rm -v $(PARSE_1411_WRITE_DIR)/write1411ServerLib_shared.o
else
	@echo "Nothing to do with write1411ServerLib_shared.o"
endif

ifneq ("$(wildcard $(PARSE_1411_WRITE_DIR)/write1411ServerLib_debug.o)","")
	@echo "Removing write1411ServerLib_debug.o ..."
	rm -v $(PARSE_1411_WRITE_DIR)/write1411ServerLib_debug.o
else
	@echo "Nothing to do with write1411ServerLib_debug.o"
endif

ifneq ("$(wildcard $(PARSE_1411_WRITE_DIR)/write1411ServerLib_shared_debug.o)","")
	@echo "Removing write1411ServerLib_shared_debug.o ..."
	rm -v $(PARSE_1411_WRITE_DIR)/write1411ServerLib_shared_debug.o
else
	@echo "Nothing to do with write1411ServerLib_shared_debug.o"
endif

ifneq ("$(wildcard $(PARSE_1411_UPDATE_DIR)/update1411ServerLib.o)","")
	@echo "Removing update1411ServerLib.o ..."
	rm -v $(PARSE_1411_UPDATE_DIR)/update1411ServerLib.o
else
	@echo "Nothing to do with update1411ServerLib.o"
endif

ifneq ("$(wildcard $(PARSE_1411_UPDATE_DIR)/update1411ServerLib_shared.o)","")
	@echo "Removing update1411ServerLib_shared.o ..."
	rm -v $(PARSE_1411_UPDATE_DIR)/update1411ServerLib_shared.o
else
	@echo "Nothing to do with update1411ServerLib_shared.o"
endif

ifneq ("$(wildcard $(PARSE_1411_UPDATE_DIR)/update1411ServerLib_debug.o)","")
	@echo "Removing update1411ServerLib_debug.o ..."
	rm -v $(PARSE_1411_UPDATE_DIR)/update1411ServerLib_debug.o
else
	@echo "Nothing to do with update1411ServerLib_debug.o"
endif

ifneq ("$(wildcard $(PARSE_1411_UPDATE_DIR)/update1411ServerLib_shared_debug.o)","")
	@echo "Removing update1411ServerLib_shared_debug.o ..."
	rm -v $(PARSE_1411_UPDATE_DIR)/update1411ServerLib_shared_debug.o
else
	@echo "Nothing to do with update1411ServerLib_shared_debug.o"
endif

ifneq ("$(wildcard $(PARSE_1411_DELETE_DIR)/delete1411ServerLib.o)","")
	@echo "Removing delete1411ServerLib.o ..."
	rm -v $(PARSE_1411_DELETE_DIR)/delete1411ServerLib.o
else
	@echo "Nothing to do with delete1411ServerLib.o"
endif

ifneq ("$(wildcard $(PARSE_1411_DELETE_DIR)/delete1411ServerLib_shared.o)","")
	@echo "Removing delete1411ServerLib_shared.o ..."
	rm -v $(PARSE_1411_DELETE_DIR)/delete1411ServerLib_shared.o
else
	@echo "Nothing to do with delete1411ServerLib_shared.o"
endif

ifneq ("$(wildcard $(PARSE_1411_DELETE_DIR)/delete1411ServerLib_debug.o)","")
	@echo "Removing delete1411ServerLib_debug.o ..."
	rm -v $(PARSE_1411_DELETE_DIR)/delete1411ServerLib_debug.o
else
	@echo "Nothing to do with delete1411ServerLib_debug.o"
endif

ifneq ("$(wildcard $(PARSE_1411_DELETE_DIR)/delete1411ServerLib_shared_debug.o)","")
	@echo "Removing delete1411ServerLib_shared_debug.o ..."
	rm -v $(PARSE_1411_DELETE_DIR)/delete1411ServerLib_shared_debug.o
else
	@echo "Nothing to do with delete1411ServerLib_shared_debug.o"
endif

.PHONY:
pre: read1411ServerLib.o read1411ServerLib_debug.o write1411ServerLib.o write1411ServerLib_debug.o update1411ServerLib.o update1411ServerLib_debug.o delete1411ServerLib.o delete1411ServerLib_debug.o

.PHONY:
pre_shared: read1411ServerLib_shared.o read1411ServerLib_shared_debug.o write1411ServerLib_shared.o write1411ServerLib_shared_debug.o update1411ServerLib_shared.o update1411ServerLib_shared_debug.o delete1411ServerLib_shared.o delete1411ServerLib_shared_debug.o

#JAVA/KOTLIN ONLY SOAP INTERNAL
#jni: lib$(LIBANAME_JNI).a
jni: lib$(LIBANAME_JNI).a
	@echo "Compiling $(LIBJNI)..."
	@$(CC) -O2 -shared -fPIC -o $(LIBJNI) jni/parser.c stdsoap2.c $(CURDIR)/parser/w1411/delete/delete1411ServerLib_shared.o $(CURDIR)/parser/w1411/read/read1411ServerLib_shared.o $(CURDIR)/parser/w1411/update/update1411ServerLib_shared.o $(CURDIR)/parser/w1411/write/write1411ServerLib_shared.o -I$(INCLUDEDIR) -I$(JAVAINCLUDE) -I$(JAVAINCLUDE_LINUX) -L$(LIBDIR) -lcws_jni -lpthread -lbson-shared-1.0 -Wall $(FLAG_JNI)
	#@$(CC) -O2 -shared -fPIC -o $(LIBJNI) jni/parser.c -I$(INCLUDEDIR) -I$(JAVAINCLUDE) -I$(JAVAINCLUDE_LINUX)  -L$(LIBDIR)
	@echo "Striping $(LIBJNI) ..."
	@$(STRIP) $(LIBJNI)
	@echo "Disabling execstack ..."
	@$(EXECSTACK) $(LIBJNI)
	@echo "Unchecking executable library ..."
	@chmod -x $(LIBJNI)
	@echo "Finished"

#PYTHON ONLY SOAP INTERNAL

.PHONY:
py: pre_shared lib$(LIBANAME_PY).a
	@echo "Compiling Python 3 module ..."
	@python3 setup.py build
	@echo "Finished"

#NODEJS ONLY SOAP INTERNAL
.PHONY:
nodejs: pre_shared lib$(LIBANAME_JS).a
	@echo "Compiling NodeJS (>= 8) module ..."
	@node-gyp configure #--thin=yes --verbose
	@node-gyp build #--thin=yes --verbose
	@echo "Finished"

.PHONY:
install_bson:
	@echo "Check if mongo-c-driver directory exists ..."
ifneq ("$(wildcard $(MONGO_C_DIR))","")
	@echo "Already cloned. Skip"
else
	@echo "Cloning branch $(MONGO_C_BRANCH) from $(MONGO_C_GIT)"
	pwd; cd $(CURDIR)/third-party; pwd; git clone -b $(MONGO_C_BRANCH) $(MONGO_C_GIT); cd mongo-c-driver;mkdir compiled && cd compiled; cmake .. -DCMAKE_BUILD_TYPE=Release -DENABLE_MONGOC=OFF -DCMAKE_INSTALL_PREFIX=$(MONGO_C_DIR)/compiled/out; make -j12;make install; pwd; cp out/lib/libbson-static-1.0.a $(LIBDIR) -v;cp -frv out/include/libbson-1.0/bson $(INCLUDEDIR);cd src/libbson/CMakeFiles/bson_shared.dir; pwd; ar rcs $(LIBDIR)/libbson-shared-1.0.a src/bson/*.o src/jsonsl/*.o __/common/*.o
endif

remove_bson:
ifneq ("$(wildcard $(LIBDIR)/lib*.a)","")
	@echo "Removing BSON library"
	rm -v $(LIBDIR)/lib*.a
	@echo "Removed"
else
	@echo "Nothing to do to remove BSON library"
endif

ifneq ("$(wildcard $(MONGO_C_DIR))","")
	@echo "Removing Mongo C branch $(MONGO_C_BRANCH)"
	rm -rfv $(MONGO_C_DIR)
	@echo "Removed Mongo C $(MONGO_C_BRANCH)"
else
	@echo "Nothing to do to remove Mongo C $(MONGO_C_BRANCH)"
endif

clean_examples:
ifneq ("$(wildcard $(CURDIR)/examples/files/*.bson)","")
	@echo "Cleaning BSON library"
	rm -v $(CURDIR)/examples/files/*.bson
	@echo "Removed"
else
	@echo "Nothing to do to remove BSON in examples"
endif

ifneq ("$(wildcard $(CURDIR)/examples/files/*.json)","")
	@echo "Removing JSON in examples"
	rm -v $(CURDIR)/examples/files/*.json
	@echo "Removed"
else
	@echo "Nothing to do to remove JSON in examples"
endif

