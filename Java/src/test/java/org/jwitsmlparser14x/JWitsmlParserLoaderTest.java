package org.jwitsmlparser14x;

import junit.framework.TestCase;
import org.bson.BSONObject;
import org.bson.BasicBSONObject;
import org.bson.types.BasicBSONList;
import org.jwitsmlparser14x.exception.JWitsmlException;

import static org.jwitsmlparser14x.JWitsmlParserLoader.RULE_TYPE.ACTION_READ_141X;
import static org.jwitsmlparser14x.JWitsmlParserLoader.getBinaryBsonVersion;

public class JWitsmlParserLoaderTest extends TestCase {

    private String attachmentText =
            "<attachments version=\"1.4.1.1\">\n" +
            " <attachment uidWell=\"A\" uidWellbore=\"B\" uid=\"C\">\n" +
            "  <nameWell>name well</nameWell>\n" +
            "  <nameWellbore>name wellbore</nameWellbore>\n" +
            "  <name xsi:type=\"nameString\">NAME</name>\n" +
            " </attachment>\n" +
            "</attachments>";

    private String expectedJsonStr = "{ \"attachments\" : { \"#attributes\" : { \"version\" : \"1.4.1.1\" }, \"attachment\" : [ { \"#attributes\" : { \"uidWell\" : \"A\", \"uidWellbore\" : \"B\", \"uid\" : \"C\" }, \"nameWell\" : \"name well\", \"nameWellbore\" : \"name wellbore\", \"name\" : \"NAME\" } ] } }";

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

    public void testParser() throws JWitsmlException, Exception {
        try {
            jWitsmlParserLoader.parser( "<wrongTag />");
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
        } catch (JWitsmlException e) {
            fail("Could not throw JWitsmlException in this line");
        } catch (Exception e) {
            assertEquals("parser: empty xml string", e.getMessage());
        }

        try {
            jWitsmlParserLoader.parser(null);
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
        assertNotNull(jWitsmlParserLoader2.getBsonVersion());
    }

    public void testBaseMsgList() throws Exception {
        assertNotNull(jWitsmlParserLoader.getBaseMsgList());
        assertNull(jWitsmlParserLoader2.getBaseMsgList());
    }

    public void testClose() throws Exception {
        jWitsmlParserLoader.close();
        //jWitsmlParserLoader2.close();
    }

    public void testIsClosed() throws Exception {
        assertFalse(jWitsmlParserLoader.isClosed());
        jWitsmlParserLoader.close();
        assertTrue(jWitsmlParserLoader.isClosed());
        assertFalse(jWitsmlParserLoader2.isClosed());
    }

    public void testParseFromFileToBson() throws JWitsmlException, Exception {
        BSONObject res = jWitsmlParserLoader.parseFromFileToBson("../testa.xml");
        assertNotNull(res);
    }

    public void testParseFromFileToJson() throws JWitsmlException, Exception {
        String res = jWitsmlParserLoader.parseFromFileToJson("../test.xml");
        assertEquals(0, jWitsmlParserLoader.getError());
        assertNotNull(res);
    }

    public void testFileInvalid1 () throws Exception {
        jWitsmlParserLoader.saveToFile(null);
    }

    public void testFileInvalid2 () throws Exception {
        jWitsmlParserLoader.saveToFile("test.bson");
    }

    public void testFileValid1 () throws Exception, JWitsmlException {
        jWitsmlParserLoader.parseFromFileToJson("../test.xml");
        jWitsmlParserLoader.saveToFile(null);
        jWitsmlParserLoader.saveToFileJSON(null);
    }

    public void testBsonSerialized() throws Exception, JWitsmlException {
        try {
            jWitsmlParserLoader.getSerializedBson();
        } catch (Exception e) {
            assertEquals("getSerializedBson: WITSML error or object not parsed yet", e.getMessage());
        }

        BSONObject resBson = jWitsmlParserLoader.parseFromFileToBson("../test.xml");
        assertNotNull(resBson);

        byte [] resBsonSerialized = jWitsmlParserLoader.getSerializedBson();
        assertNotNull(resBsonSerialized);
    }
}