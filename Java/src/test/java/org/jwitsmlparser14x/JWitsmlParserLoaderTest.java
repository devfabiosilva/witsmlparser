package org.jwitsmlparser14x;

import junit.framework.TestCase;
import org.bson.BSONObject;
import org.bson.BasicBSONObject;
import org.bson.types.BasicBSONList;
import org.jwitsmlparser14x.exception.JWitsmlException;

import static org.jwitsmlparser14x.JWitsmlParserLoader.RULE_TYPE.ACTION_READ_141X;
import static org.jwitsmlparser14x.JWitsmlParserLoader.getBinaryBsonVersion;

public class JWitsmlParserLoaderTest extends TestCase {

    private final String attachmentText =
            "<attachments version=\"1.4.1.1\">\n" +
            " <attachment uidWell=\"A\" uidWellbore=\"B\" uid=\"C\">\n" +
            "  <nameWell>name well</nameWell>\n" +
            "  <nameWellbore>name wellbore</nameWellbore>\n" +
            "  <name>NAME</name>\n" +
            " </attachment>\n" +
            "</attachments>";

    private final String expectedJsonStr = "{ \"attachments\" : { \"#attributes\" : { \"version\" : \"1.4.1.1\" }, \"attachment\" : [ { \"#attributes\" : { \"uidWell\" : \"A\", \"uidWellbore\" : \"B\", \"uid\" : \"C\" }, \"nameWell\" : \"name well\", \"nameWellbore\" : \"name wellbore\", \"name\" : \"NAME\" } ] } }";

    private JWitsmlParserLoader jWitsmlParserLoader = null;
    private JWitsmlParserLoader jWitsmlParserLoader2 = null;
    public void setUp() throws Exception {
        super.setUp();
        jWitsmlParserLoader = new JWitsmlParserLoader();
        jWitsmlParserLoader2 = new JWitsmlParserLoader(ACTION_READ_141X, true);
    }

    public void tearDown() throws Exception {
        if (!jWitsmlParserLoader.isClosed())
            jWitsmlParserLoader.close();
        jWitsmlParserLoader2.close();
    }

    private Object navigate(BSONObject obj, Object ...args) throws Exception {
        Object tmp = obj;
        for (Object arg : args) {
            if (tmp instanceof BasicBSONObject) {
                tmp = ((BSONObject) tmp).get((String) arg);
            } else if (tmp instanceof BasicBSONList) {
                tmp = ((BasicBSONList)tmp).get((Integer) arg);
            } else
                throw new Exception("Invalid object");
        }
        return tmp;
    }

    public void testParseToBson() throws JWitsmlException, Exception {
        BSONObject bson = jWitsmlParserLoader2.parseToBson(attachmentText);
        assertNotNull(bson);
        assertEquals("1.4.1.1", (String) navigate(bson, "attachments", "#attributes", "version"));

        BSONObject attachmentAttr = (BSONObject) navigate(bson, "attachments", "attachment", 0, "#attributes");

        assertEquals("A", attachmentAttr.get("uidWell"));
        assertEquals("B", attachmentAttr.get("uidWellbore"));
        assertEquals("C", attachmentAttr.get("uid"));

        BSONObject attachmentTags = (BSONObject) navigate(bson, "attachments", "attachment", 0);

        assertEquals("name well", attachmentTags.get("nameWell"));
        assertEquals("name wellbore", attachmentTags.get("nameWellbore"));
        assertEquals("NAME", attachmentTags.get("name"));

    }

    public void testParseToJson() throws JWitsmlException, Exception {
        String json = jWitsmlParserLoader2.parseToJson(attachmentText);
        assertNotNull(json);
        assertEquals(expectedJsonStr, json);
    }

    public void testParser() throws JWitsmlException, Exception {
        try {
            jWitsmlParserLoader.parser( "<wrongTag />");
            fail("Could not execute this line");
        } catch (JWitsmlException e) {
            assertEquals("parser: Could not deserialize xml string. See xml errors for details", e.getMessage());
            assertEquals("Client validation error: Validation constraint violation: tag name or namespace mismatch in element 'wrongTag'", e.getBaseMsg());
            assertEquals(0, e.getCwitsmlError());
            assertEquals(-1004, e.getBaseMsgError());
        } catch (Exception e) {
            fail("Could not throw Exception in this line");
        }

        try {
            jWitsmlParserLoader.parser("");
            fail("Could not execute this line");
        } catch (JWitsmlException e) {
            fail("Could not throw JWitsmlException in this line");
        } catch (Exception e) {
            assertEquals("parser: empty xml string", e.getMessage());
        }

        try {
            jWitsmlParserLoader.parser(null);
            fail("Could not execute this line");
        } catch (JWitsmlException e) {
            fail("Could not throw JWitsmlException in this line");
        } catch (Exception e) {
            assertEquals("parser: null xml string", e.getMessage());
        }

        byte [] attachmentBsonBinary = jWitsmlParserLoader.parser(attachmentText);

        assertNotNull(attachmentBsonBinary);

        BSONObject attachments = (BSONObject)jWitsmlParserLoader.getBson().get("attachments");

        assertNotNull(attachments);

        BasicBSONList attachment = (BasicBSONList)attachments.get("attachment");
        assertTrue(attachments.containsField("#attributes"));
        assertNotNull(attachment);
        assertEquals(1, attachment.size());
        assertEquals("name well", ((BasicBSONObject) attachment.get(0)).get("nameWell"));
        assertTrue(((BasicBSONObject)attachment.get(0)).containsField("#attributes"));
        assertEquals("C", ((BasicBSONObject)(((BasicBSONObject)attachment.get(0)).get("#attributes"))).get("uid"));
        assertEquals(expectedJsonStr, jWitsmlParserLoader.getJson());
    }

    public void testGetBinaryBsonVersion() throws Exception {
        assertNotNull(getBinaryBsonVersion());
    }

    public void testGetBsonVersion() throws Exception {
        assertNotNull(jWitsmlParserLoader.getBsonVersion());
    }

    public void testBaseMsgList() throws Exception {
        assertNotNull(jWitsmlParserLoader.getBaseMsgList());
        assertNotNull(jWitsmlParserLoader2.getBaseMsgList());
    }

    public void testClose() throws Exception {
        jWitsmlParserLoader.close();
    }

    public void testIsClosed() throws Exception {
        assertFalse(jWitsmlParserLoader.isClosed());
        jWitsmlParserLoader.close();
        assertTrue(jWitsmlParserLoader.isClosed());
        assertFalse(jWitsmlParserLoader2.isClosed());
    }

    public void testParseFromFileToBson() throws JWitsmlException, Exception {
        BSONObject res = jWitsmlParserLoader.parseFromFileToBson("../test.xml");
        assertNotNull(res);
    }

    public void testParseFromFileToJson() throws JWitsmlException, Exception {
        String res = jWitsmlParserLoader.parseFromFileToJson("../test.xml");
        assertEquals(0, jWitsmlParserLoader.getError());
        assertNotNull(res);
    }

    public void testFileInvalid1 () {
        try {
            jWitsmlParserLoader.saveToFile(null);
            fail("Could not execute this line");
        } catch (Exception e) {
            assertEquals("saveToFile: WITSML error or object not parsed", e.getMessage());
        }
    }

    public void testFileInvalid2 () throws Exception, JWitsmlException {
        try {
            jWitsmlParserLoader.saveToFile("testBson.bson");
            fail("Could not execute this line");
        } catch (Exception e) {
            assertEquals("saveToFile: WITSML error or object not parsed", e.getMessage());
        }

        jWitsmlParserLoader.parser(attachmentText);
        jWitsmlParserLoader.saveToFile("testBson.bson");
        jWitsmlParserLoader.saveToFileJSON("testBson.json");
    }

    public void testFileValid1 () throws Exception, JWitsmlException {
        jWitsmlParserLoader.parseFromFileToJson("../test.xml");
        jWitsmlParserLoader.saveToFile(null);
        jWitsmlParserLoader.saveToFileJSON(null);
    }

    public void testBsonSerialized() throws Exception, JWitsmlException {
        try {
            jWitsmlParserLoader.getSerializedBson();
            fail("Could not execute this line");
        } catch (Exception e) {
            assertEquals("getSerializedBson: WITSML error or object not parsed yet", e.getMessage());
        }

        BSONObject resBson = jWitsmlParserLoader.parseFromFileToBson("../test.xml");
        assertNotNull(resBson);

        byte [] resBsonSerialized = jWitsmlParserLoader.getSerializedBson();
        assertNotNull(resBsonSerialized);
    }
}