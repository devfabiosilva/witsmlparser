import bson
import witsml14xbson

# SAMPLE USAGE:
# This example creates 5 WITSML instances with different configuration and reads all WITSML xml files in examples/files folder:
#	1- Create default instance (Read and Schema version check) and convert to JSON and BSON files
#	2- Create READ instance disabling Schema check and convert to JSON and BSON files
#	3- Default READ rule with Schema version enabled and convert to JSON and BSON files
#	4- Version check disable instance and convert to JSON and BSON files
#	5- Check Schema version instance and convert to JSON and BSON files
#	6- Load WITSML string from memory and parse to JSON string
#	7- Load WITSML string from memory and parse to Python3 dict

# HOW TO RUN:
# In source directory:
#######################
# make -j12 py        #
# cd examples         #
# source env_py.sh    #
# python3 example.py  #
#######################

# OR

#######################
# make py_example     #
#######################

# CLENUP:
# make clean_examples

FILE_LIST = [
 'log1_wrong', 'log1', 'log2_wrong', 'log2', 'message', 'mudLog', 'risk', 'trajectory', 'well', 'wellbore'
]

DEFAULT_PATH_XML = "files/"

FROM_MEMORY_STRING = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<messages xmlns=\"http://www.witsml.org/schemas/1series\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" version=\"1.4.1.1\">\
  <message uidWell=\"a03e86c7-72c1-414e-aecc-8ea3c5\" uidWellbore=\"5ed5bb6b-f6e5-465b-9779-d87220f9\" uid=\"6cdccc33-9210-45f1-95a1-7ff418a186c7\" xmlns=\"http://www.witsml.org/schemas/1series\">\
    <nameWell>EnergisticsWell2016-A</nameWell>\
    <nameWellbore>EnergisticsWellbore2016-A</nameWellbore>\
    <name>MSG-6cdccc33-9210-45f1-95a1-7ff418a186c7</name>\
    <dTim>2016-02-28T07:15:11.734Z</dTim>\
    <typeMessage>alarm</typeMessage>\
    <messageText>Troubleshoot PRS</messageText>\
    <commonData>\
      <sourceName>GeoServices</sourceName>\
      <dTimCreation>2016-04-04T11:51:36.158Z</dTimCreation>\
      <dTimLastChange>2016-04-04T11:51:36.158Z</dTimLastChange>\
      <comments>Message Object</comments>      \
    </commonData>\
    <customData>\
      <IASectionName xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">12.25in_drilling_run05</IASectionName>\
    </customData>\
  </message>\
</messages>"

def main():
    parser1 = witsml14xbson.create() # Create default instance: Action READ and Schema version check enabled
    print("parser1 created @ " + parser1.getInstanceName())

    parser2 = witsml14xbson.create(versionCheckDisable = True) # Create READ instance disabling Schema check
    print("parser2 created @ " + parser2.getInstanceName())

    parser3 = witsml14xbson.create(witsml14xbson.ACTION_READ_141X) # Default READ rule with Schema version enabled
    print("parser3 created @ " + parser3.getInstanceName())

    parser4 = witsml14xbson.create(witsml14xbson.ACTION_READ_141X, True) # Version check disable. Disable check Schema version
    print("parser4 created @ " + parser4.getInstanceName())

    parser5 = witsml14xbson.create(witsml14xbson.ACTION_READ_141X, False) # Check Schema version
    print("parser5 created @ " + parser5.getInstanceName())

    processFiles(parser1, parser2, parser3, parser4, parser5) # Testing all objects with different instance configurations

    print(parser1.parseToJSON(FROM_MEMORY_STRING)) # Loading XML from memory and converting to JSON string
    print("Object name (Autodetect): " + parser1.getObjectName()) # Auto-detect object

    objSer = parser2.parse(FROM_MEMORY_STRING) # Convert to serialized BSON
    obj = bson.decode(objSer) # Convert to Python3 dict
    print(obj)
    print("Name well: " + obj['messages']['message'][0]['nameWell']) # Loading XML from memory and accessing by Python3 dict
    print("Object name (Autodetect): " + parser2.getObjectName()) # Auto-detect object

def print_parser_error(parser, ex):
   print("Error number: " + str(parser.getError()))
   faultStr = parser.getFaultString()

   if (faultStr != None):
       print("fault string: " + faultStr)

   xmlFaultDetail = parser.getXMLfaultdetail()
   if (xmlFaultDetail != None):
       print("Witsml parser detail: " + xmlFaultDetail)

   try:
      print("Base message code: ")
      print(parser.getBaseMsgCode())
   except Exception as e:
      print(e)

   print(ex)

def run_instance(fileName, instanceName, instance):
    fp = DEFAULT_PATH_XML + fileName + ".xml"
    print("Opening " + fp)
    try:
        objSerialized = instance.parseFromFile(fp)
    except Exception as e:
        print_parser_error(instance, e)

    try:
        print("Object name " + instance.getObjectName())
        instance.saveToFile(DEFAULT_PATH_XML + fileName + "_" + instanceName + ".bson")
    except Exception as e:
        print_parser_error(instance, e)

    try:
        instance.saveToFileJSON(DEFAULT_PATH_XML + fileName + "_" + instanceName + ".json")
    except Exception as e:
        print_parser_error(instance, e)

def processFiles(p1, p2, p3, p4, p5):
    for l in FILE_LIST:
        print("Instance parser1: READ rule and Schema Version check enabled")
        run_instance(l, "parser1", p1)

        print("Instance parser2: READ instance disabling Schema check")
        run_instance(l, "parser2", p2)

        print("Instance parser3: READ instance with Schema version enabled")
        run_instance(l, "parser3", p3)

        print("Instance parser4: READ instance Version check disable. Disable check Schema version")
        run_instance(l, "parser4", p4)

        print("Instance parser5: READ instance Check Schema version")
        run_instance(l, "parser5", p5)

if __name__ == "__main__":
    main()

