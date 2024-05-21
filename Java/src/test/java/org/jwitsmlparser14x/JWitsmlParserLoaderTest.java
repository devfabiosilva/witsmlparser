package org.jwitsmlparser14x;

import junit.framework.TestCase;
import org.bson.BSONObject;
import org.jwitsmlparser14x.exception.JWitsmlException;

import static org.jwitsmlparser14x.JWitsmlParserLoader.RULE_TYPE.ACTION_READ_141X;
import static org.jwitsmlparser14x.JWitsmlParserLoader.getBinaryBsonVersion;

public class JWitsmlParserLoaderTest extends TestCase {

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
        assertNull(jWitsmlParserLoader.parser( " bhgg"));
        //assertNull(jWitsmlParserLoader2.parser( "hjhj"));
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