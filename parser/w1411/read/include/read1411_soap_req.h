#ifndef READ1411_SOAP_REQ_H
 #define READ1411_SOAP_REQ_H

/*
#define READ1411_SOAP_START "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<SOAP-ENV:Envelope\
    xmlns:SOAP-ENV=\"http://www.w3.org/2003/05/soap-envelope\"\
    xmlns:SOAP-ENC=\"http://www.w3.org/2003/05/soap-encoding\"\
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\
    xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"\
    xmlns:rd1gss=\"http://www.isotc211.org/2005/gss\"\
    xmlns:rd1gsr=\"http://www.isotc211.org/2005/gsr\"\
    xmlns:rd1abs=\"http://www.energistics.org/schemas/abstract\"\
    xmlns:rd1gml=\"http://www.opengis.net/gml/3.2\"\
    xmlns:xlink=\"http://www.w3.org/1999/xlink\"\
    xmlns:rd1gmd=\"http://www.isotc211.org/2005/gmd\"\
    xmlns:rd1gco=\"http://www.isotc211.org/2005/gco\"\
    xmlns:rd1gts=\"http://www.isotc211.org/2005/gts\"\
    xmlns:rd1411=\"http://cwitsml.org/rd1411.xsd\">\
 <SOAP-ENV:Body>\
  <rd1411:readObj1411>\
   <obj xsi:type=\"rd1411:readObj1411_t\">"
*/
//https://www.genivia.com/doc/guide/html/group__group__with.html#ga376e550466f3e75f529e113fcf36f86a

#define READ1411_SOAP_START "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\
<SOAP-ENV:Envelope\
    xmlns:SOAP-ENV=\"http://www.w3.org/2003/05/soap-envelope\"\
    xmlns:SOAP-ENC=\"http://www.w3.org/2003/05/soap-encoding\"\
    xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\
    xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\"\
    xmlns:rd1gss=\"http://www.isotc211.org/2005/gss\"\
    xmlns:rd1gsr=\"http://www.isotc211.org/2005/gsr\"\
    xmlns:rd1abs=\"http://www.energistics.org/schemas/abstract\"\
    xmlns:rd1witsml=\"http://www.witsml.org/schemas/1series\"\
    xmlns:rd1gml=\"http://www.opengis.net/gml/3.2\"\
    xmlns:xlink=\"http://www.w3.org/1999/xlink\"\
    xmlns:rd1gmd=\"http://www.isotc211.org/2005/gmd\"\
    xmlns:rd1gco=\"http://www.isotc211.org/2005/gco\"\
    xmlns:rd1gts=\"http://www.isotc211.org/2005/gts\"\
    xmlns:rd1411=\"http://cwitsml.org/rd1411.xsd\">\
 <SOAP-ENV:Body>\
  <rd1411:readObj1411>\
   <obj xsi:type=\"rd1411:readObj1411_t\">"

#define READ1411_SOAP_END "</obj>\
  </rd1411:readObj1411>\
 </SOAP-ENV:Body>\
</SOAP-ENV:Envelope>"

#endif

