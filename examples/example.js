const { BSON } = require('bson')
witsml = require('../build/Release/witsml14xbson')

// HOW TO RUN:
// In source directory:
//#######################
// make -j12 nodejs     #
// npm install          #
// cd examples          #
// node example.js      #
//#######################

// CLENUP:
// make clean_examples

var FILE_LIST = [
 'log1_wrong', 'log1', 'log2_wrong', 'log2', 'message', 'mudLog', 'risk', 'trajectory', 'well', 'wellbore'
]

var DEFAULT_PATH_XML = "files/"

var FROM_MEMORY_STRING = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
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


function printParserError(parser, ex) {
  console.log("Error number: " + parser.getError())

  var faultStr = parser.getFaultString()
  if (faultStr != null)
    console.log("fault string: " + faultStr)

  var xmlFaultDetail = parser.getXMLfaultdetail()
  if (xmlFaultDetail != null)
    console.log("Witsml parser detail: " + xmlFaultDetail)

  try {
    console.log("Base message code:")
    console.log(parser.getBaseMsgCode())
  } catch(e) {
    console.log(e)
  }

  console.log(ex)
}

function runInstance(fileName, instanceName, instance) {
  fp = DEFAULT_PATH_XML + fileName + ".xml"
  console.log("Opening " + fp)

  try {
    var objSerialized = instance.parseFromFile(fp)
    var obj = BSON.deserialize(objSerialized)
    console.log(obj)
  } catch (e) {
    printParserError(instance, e)
  }

  try {
    console.log("Object name " + instance.getObjectName())
    instance.saveToFile(DEFAULT_PATH_XML + fileName + "_" + instanceName + ".bson")
  } catch (e) {
    printParserError(instance, e)
  }

  try {
    instance.saveToFileJSON(DEFAULT_PATH_XML + fileName + "_" + instanceName + ".json")
  } catch (e) {
    printParserError(instance, e)
  }
}

function processFiles(p1, p2, p3) {
  for (l of FILE_LIST) {
    console.log("Instance parser1: READ rule and Schema Version check enabled")
    runInstance(l, "parser1", p1)

    console.log("Instance parser2: READ instance disabling Schema check")
    runInstance(l, "parser2", p2)

    console.log("Instance parser3: READ instance with Schema version enabled")
    runInstance(l, "parser3", p3)
  }
}

function main() {
  var parser1 = witsml.create() // Create default instance: Action READ and Schema version check enabled
  console.log("parser1 created @ " + parser1.getInstanceName())

  var parser2 = witsml.create(witsml.WITSML_RULES_TYPES.ACTION_READ_141X, true) // Create READ instance disabling Schema check
  console.log("parser2 created @ " + parser2.getInstanceName())

  var parser3 = witsml.create(witsml.WITSML_RULES_TYPES.ACTION_READ_141X, false) // Default READ rule with Schema version enabled
  console.log("parser3 created @ " + parser3.getInstanceName())

  processFiles(parser1, parser2, parser3) // Testing all objects with different instance configurations

  console.log(parser1.parseToJSON(FROM_MEMORY_STRING)) // Loading XML from memory and converting to JSON string
  console.log("Object name (Autodetect): " + parser1.getObjectName()) // Auto-detect object

  var objSer = parser2.parse(FROM_MEMORY_STRING) // Convert to serialized BSON
  var obj = BSON.deserialize(objSer) // Convert to NodeJS object
  console.log(obj)
  console.log("Name well: " + obj['messages']['message'][0]['nameWell']) // Loading XML from memory and accessing by NodeJS object
  console.log("Object name (Autodetect): " + parser2.getObjectName()) // Auto-detect object
}

main()

