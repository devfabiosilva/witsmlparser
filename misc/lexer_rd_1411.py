import sys

DEBUG = False
file1 = open("texto.txt")

lines = file1.readlines()

lexer_list = {}
lexer_list_atrs = {}
cnt: int = 0
lineLen = len(lines)

e_type = ""

if (len(sys.argv) >= 3):
  e_type = sys.argv[2]
else:
  e_type = ""

ROOT_OBJ_READ_NS1 = "struct __rd1witsml__obj_USCORE"
ROOT_OBJ_READ_NS2 = "struct rd1witsml__"
ROOT_OBJ_READ_NS3 = "struct __rd1witsml__"
ROOT_OBJ_READ_NS4 = "struct rd1gml__"
ROOT_OBJECT_TYP1 = "_sequence_ {\n"
ROOT_OBJECT_TYP2 = " {\n"
ROOT_OBJECT_TYP3 = "_sequence {\n"

TYPE_IS_BOOLEAN = "boolean"
TYPE_IS_STRING = "string"
TYPE_IS_TIME = "time"
TYPE_IS_DOUBLE = "double"
TYPE_IS_SHORT = "short"
TYPE_IS_INT = "int"
OBJ_NAME_IS_ITEM = "__item"

def detectRootType(val: str)-> dict:
  m = val.find(ROOT_OBJECT_TYP1)
  if (m > -1):
    return { "rootType": "S", "index": m }

  m = val.find(ROOT_OBJECT_TYP3)
  if (m > -1):
    if (e_type == ""):
      return { "rootType": "O", "index": m }
    return { "rootType": "A", "index": m }

  m = val.find(ROOT_OBJECT_TYP2)
  if (m > -1):
    return { "rootType": "O", "index": m }

  raise Exception("Could not find root object type")

def rootComment() -> str:
  global lines
  s = lines[0]

  m = s.find(" {")

  return "//" + s[:m]

def detectRootObject() -> None:
  global cnt
  global lines
  global lineLen
  global lexer_list

  if (cnt > 0):
    raise Exception("First line must be 0")

  if (lineLen < 1):
    raise Exception("Empty file")

  s = lines[0]
  rt = detectRootType(s)
  m = s.find(ROOT_OBJ_READ_NS1)
  obj = {}

  if (m > -1):
    n = m + len(ROOT_OBJ_READ_NS1)
  elif ((m := s.find(ROOT_OBJ_READ_NS2)) > -1):
    n = m + len(ROOT_OBJ_READ_NS2)
  elif ((m := s.find(ROOT_OBJ_READ_NS3)) > -1):
    n = m + len(ROOT_OBJ_READ_NS3)
  elif ((m := s.find(ROOT_OBJ_READ_NS4)) > -1):
    n = m + len(ROOT_OBJ_READ_NS4)
  else:
    raise Exception("Not found root C struct NS")

  rt["objectName"] = s[n:rt["index"]]
  rt.pop("index")

  lexer_list[cnt] = rt

  cnt = cnt + 1

def advanceObject() -> str:
  global cnt
  global lines
  global lineLen

  if (cnt >= lineLen):
    raise Exception("Lines out of index " + str(cnt) + " >= " + str(lineLen))

  s = lines[cnt]

  cnt = cnt + 1

  return s

def detectObject() -> None:
  global cnt
  global lines
  global lineLen
  global lexer_list
  global lexer_list_atrs

  s = advanceObject()
  isAttr = False
  isArray = False
  isNullable = False
  typeIs = None
  objectName = None
  explicitNullable = False
  isComplex = False
  isEnum = False

  if (s.find("/**") > -1):
    isAttr = (s.find("attribute") > -1)
    s = advanceObject()

  if (s.find("int __size") > -1):
    isArray = True
    s = advanceObject()

  n = s.find(";\n")
  if (n < 0):
    raise Exception("Missing \";\"")

  m = s.find("enum xsd__boolean ")
  if (m > -1):
    typeIs = TYPE_IS_BOOLEAN
    s_tmp = s[m + len("enum xsd__boolean "):]
    isNullable = (s_tmp.find("*") > -1)

    if (isArray):
      raise Exception("TODO Implement array of boolean")
    if (isNullable):
      objectName = s_tmp[1:s_tmp.find(";")]
    else:
      objectName = s_tmp[:s_tmp.find(";")]

    explicitNullable = True

  elif ((m := s.find("char *")) > -1):
    s_tmp = s[m + len("char *"):]
    if (((n := s_tmp.find("*")) < 0) and isArray):
      raise Exception("Inconsistent string array object")

    if (n < 0):
      n=0
    else:
      n=n+len("*")

    typeIs = TYPE_IS_STRING
    isNullable = True
    objectName = s_tmp[n:s_tmp.find(";")]
  elif ((m := s.find("time_t ")) > -1):
    s_tmp = s[m + len("time_t "):]
    n = s_tmp.find("*")
    isNullable = (n > -1)

    if (n < 0):
      n=0
    else:
      n=n+len("*")

    typeIs = TYPE_IS_TIME
    if (isArray):
      raise Exception("TODO Implement array of time_t")

    objectName = s_tmp[n:s_tmp.find(";")]

    explicitNullable = True

  elif ((m := s.find("double ")) > -1):
    s_tmp = s[m + len("double "):]
    n = s_tmp.find("*")
    isNullable = (n > -1)

    if (isArray):
      raise Exception("TODO Implement array of double")

    if (n < 0):
      n=0
    else:
      n=n+len("*")

    typeIs = TYPE_IS_DOUBLE

    objectName = s_tmp[n:s_tmp.find(";")]

    explicitNullable = True

  elif ((m := s.find("short ")) > -1):
    s_tmp = s[m + len("short "):]
    n = s_tmp.find("*")
    isNullable = (n > -1)

    if (isArray):
      raise Exception("TODO Implement array of short")

    if (n < 0):
      n=0
    else:
      n=n+len("*")

    typeIs = TYPE_IS_SHORT
    explicitNullable = True

    objectName = s_tmp[n:s_tmp.find(";")]
  elif ((m := s.find("int ")) > -1):
    s_tmp = s[m + len("int "):]
    n = s_tmp.find("*")
    isNullable = (n > -1)

    print(s.find("int "))
    if (isArray):
      raise Exception("TODO Implement array of int")

    if (n < 0):
      n=0
    else:
      n=n+len("*")

    typeIs = TYPE_IS_INT
    explicitNullable = True

    objectName = s_tmp[n:s_tmp.find(";")]
  elif ((m := s.find("struct rd1witsml__")) > -1):
    s_tmp = s[m + len("struct rd1witsml__"):]
    if ((n := s_tmp.find(" *")) > -1):
      isNullable = True
      typeIs = s_tmp[:n]
      n = n + len(" *")
    else:
      n = s_tmp.find(" ")
      typeIs = s_tmp[:n]
      n = n + len(" ")

    objectName = s_tmp[n:s_tmp.find(";")]

    isComplex = True
  elif ((m := s.find("struct rd1gml__")) > -1):
    s_tmp = s[m + len("struct rd1gml__"):]
    if ((n := s_tmp.find(" *")) > -1):
      isNullable = True
      typeIs = s_tmp[:n]
      n = n + len(" *")
    else:
      n = s_tmp.find(" ")
      typeIs = s_tmp[:n]
      n = n + len(" ")

    objectName = s_tmp[n:s_tmp.find(";")]

    isComplex = True
  elif ((m := s.find("struct _rd1gml__")) > -1):
    s_tmp = s[m + len("struct _rd1gml__"):]
    if ((n := s_tmp.find(" *")) > -1):
      isNullable = True
      typeIs = s_tmp[:n]
      n = n + len(" *")
    else:
      n = s_tmp.find(" ")
      typeIs = s_tmp[:n]
      n = n + len(" ")

    objectName = s_tmp[n:s_tmp.find(";")]

    isComplex = True
  elif ((m := s.find("enum rd1witsml__")) > -1):
    s_tmp = s[m + len("enum rd1witsml__"):]
    if ((n := s_tmp.find(" *")) > -1):
      isNullable = True
      typeIs = s_tmp[:n]
      n = n + len(" *")
    else:
      n = s_tmp.find(" ")
      typeIs = s_tmp[:n]
      n = n + len(" ")

    objectName = s_tmp[n:s_tmp.find(";")]
    explicitNullable = True
    isEnum = True
  elif (s.find("}") < 0):
    raise Exception("Unknown line " + s)

  this = {}
  this["isArray"] = isArray
  this["isNullable"] = isNullable
  this["explicitNullable"] = explicitNullable
  this["typeIs"] = typeIs
  this["objectName"] = objectName
  this["isComplex"] = isComplex
  this["isEnum"] = isEnum

  if (isAttr):
    lexer_list_atrs[cnt] = this
  else:
    lexer_list[cnt] = this

def processAttributes(rootType: str, parent: str) -> str:
  global lexer_list_atrs

  k = len(lexer_list_atrs)

  if (k == 0):
    return ""

  isSingle = k == 1

  onlyString = True

  text = "  READ_" + rootType

  for n in lexer_list_atrs:
    obj = lexer_list_atrs[n]

    if ((obj["typeIs"] == None) and (obj["objectName"] == None)):
      continue

    onlyString = onlyString and ((obj["typeIs"] == TYPE_IS_STRING) or (obj["isEnum"]))

  if (onlyString and isSingle):
    text = text + "_PUT_SINGLE_ATTRIBUTE_1411_OR_ELSE_GOTO_RESUME(" + parent + ", "
    for n in lexer_list_atrs:
      obj = lexer_list_atrs[n]

      if ((obj["typeIs"] == None) and (obj["objectName"] == None)):
        continue

      text = text + obj["objectName"] + ")"
  elif (onlyString):
    text = text + "_PUT_MULTIPLE_ATTRIBUTES_1411_OR_ELSE_GOTO_RESUME(" + parent + ",\n    SET_MULTIPLE_ATTRIBUTES(\n"
    i = 0
    for n in lexer_list_atrs:
      obj = lexer_list_atrs[n]

      i = i + 1

      objType = obj["typeIs"]
      objName = obj["objectName"]
      if ((objType == None) and (objName == None)):
        continue

      if (obj["isEnum"]):
        text = text + "      ATTR_ENUM_KEY"
        if (obj["explicitNullable"] and obj["isNullable"]):
          text = text + "_NULLABLE"

        text = text + "_1411(" + parent + ", " + objName + ", " + objType + ")"
      else:
        text = text + "      ATTR_KEY_1411(" + parent + ", " + objName + ")"

      if (k > i):
        text = text + ",\n"
      else:
        text = text + "\n"

    text = text + "    )\n  )"
  else:
    text = text + "_PUT_MULTIPLE_ATTRIBUTES_TYPED_1411_OR_ELSE_GOTO_RESUME(" + parent + ",\n    SET_MULTIPLE_ATTRIBUTES(\n"
    i = 0
    for n in lexer_list_atrs:
      obj = lexer_list_atrs[n]

      i = i + 1

      objType = obj["typeIs"]
      objName = obj["objectName"]
      if ((objType == None) and (objName == None)):
        continue

      if (objType == TYPE_IS_STRING):
        text = text + "      ATTR_KEY_TYPED_1411(" + parent + ", _CWS_NULLABLE_XSD_STR, " + objName + ")"
      elif (objType == TYPE_IS_TIME):
        if (obj["explicitNullable"] and obj["isNullable"]):
          text = text + "      ATTR_KEY_TYPED_1411(" + parent + ", _CWS_NULLABLE_DATE_TIME, " + objName + ")"
        else:
          raise Exception("TODO: Implement time not NULLABLE")
      elif (objType == TYPE_IS_DOUBLE):
        if (obj["explicitNullable"] and obj["isNullable"]):
          text = text + "      ATTR_KEY_TYPED_1411(" + parent + ", _CWS_NULLABLE_DOUBLE, " + objName + ")"
        else:
          raise Exception("TODO: Implement double not NULLABLE")
      else:
        raise Exception("TODO: Implement other types than TYPE_IS_TIME. Found " + objType) 

      if (k > i):
        text = text + ",\n"
      else:
        text = text + "\n"

    text = text + "    )\n  )"

  return text + "\n"

def processText() -> str:
  global cnt
  global lines
  global lineLen
  global lexer_list
  global lexer_list_atrs

  i = 1
  rootType = lexer_list[0]["rootType"]
  objectName = lexer_list[0]["objectName"]

  text = "READ"
  if (rootType == "S"):
    text = text + "_" + rootType
  else:
    text = "BSON_" + text

  text = rootComment() + "\n" + text + "_OBJECT_1411_BEGIN(" + objectName + ")\n"

  last = len(lexer_list) - 1

  text = text + processAttributes(rootType, objectName)

  for n in lexer_list:
    if (i == 1):
      i = i + 1
      continue

    obj = lexer_list[n]

    objectName_tmp = obj["objectName"]
    if (objectName_tmp == None):
      continue

    text = text + "  READ_" + rootType

    if (obj["isArray"]):
      text = text + "_ARRAY_OF"

    tmp = obj["typeIs"]

    cplxObj = ""
    if (obj["isEnum"]):
      cplxObj = ", " + tmp
      text = text + "_OBJECT_ENUM"
    elif (obj["isComplex"]):
      cplxObj = ", " + tmp
      text = text + "_OBJECT"
    elif (tmp == TYPE_IS_BOOLEAN):
      text = text + "_BOOLEAN"
    elif (tmp == TYPE_IS_STRING):
      text = text + "_UTF8_OBJECT"
    elif (tmp == TYPE_IS_TIME):
      text = text + "_TIME"
    elif (tmp == TYPE_IS_DOUBLE):
      text = text + "_DOUBLE"
    elif (tmp == TYPE_IS_SHORT):
      text = text + "_SHORT"
    elif (tmp == TYPE_IS_INT):
      text = text + "_INT"
    else:
      raise Exception("Unknown type: " + tmp)

    if (obj["explicitNullable"] and obj["isNullable"]):
      text = text + "_NULLABLE"

    isItem = objectName_tmp == OBJ_NAME_IS_ITEM

    if (i < last):
      if (isItem):
        raise Exception("TODO: Implement item object when it is not at the end")
      text = text + "_1411_OR_ELSE_GOTO_RESUME(" + objectName + ", " + objectName_tmp + cplxObj + ")\n"
    else:
      if (isItem):
        text = text + "_ITEM_1411_VOID(" + objectName + ")\n"
      else:
        text = text + "_1411_VOID(" + objectName + ", " + objectName_tmp + cplxObj + ")\n"

    i = i + 1

  if (rootType == "S"):
    text = text + "READ_" + rootType
  else:
    text = text + "BSON_READ"

  text = text + "_OBJECT_1411_END(" + objectName + ")\n"

  return text

def main():
  global cnt
  global lines
  global lineLen
  global lexer_list_atrs
  global lexer_list

  while (cnt < lineLen):
    if (cnt > 0):
      detectObject()
    else:
      detectRootObject()
  #print(lexer_list[3])
  print(lexer_list)
  print(lexer_list_atrs)
  #processFile()
  print(processText())

if __name__ == "__main__":
  main()
