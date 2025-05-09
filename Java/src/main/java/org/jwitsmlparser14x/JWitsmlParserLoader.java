package org.jwitsmlparser14x;

import org.bson.BSONDecoder;
import org.bson.BSONObject;
import org.bson.BasicBSONDecoder;
import org.jwitsmlparser14x.exception.JWitsmlException;

import java.nio.charset.StandardCharsets;
import java.util.TreeMap;

//https://thebreakfastpost.com/2012/03/06/wrapping-a-c-library-with-jni-part-4/

public class JWitsmlParserLoader {
    static {
        try {
            System.loadLibrary("jwitsmlparserx");
        } catch (Throwable e) {
            System.out.println("JNI example load library error.");
            System.out.println(e.getMessage());
            throw e;
        }
    }
    public enum RULE_TYPE {
        ACTION_READ_141X,
        ACTION_WRITE_141X,
        ACTION_UPDATE_141X,
        ACTION_DELETE_141X,
    }

    BSONDecoder decoder = new BasicBSONDecoder();
    private TreeMap<Integer, String> baseMsgListMap = null;
    private BSONObject bsonVersion = null;

    @SuppressWarnings("all")
    public byte[] handler = null;

    private native void init(int rule, boolean versionCheckDisable) throws Exception;
    public native byte[] parser(String xml) throws JWitsmlException, Exception;
    private native byte[] parserJson(String xml) throws JWitsmlException, Exception;
    private native byte[] parserFromFile(String filename) throws JWitsmlException, Exception;
    private native byte[] parserFromFileJson(String filename) throws JWitsmlException, Exception;
    public native void saveToFile(String filename) throws Exception;
    public native void saveToFileJSON(String filename) throws Exception;
    public native int getError() throws Exception;
    public static native byte[] getBinaryBsonVersion() throws Exception;
    private native TreeMap<Integer, String> baseMsgList() throws Exception;
    public native void close() throws Exception;
    public native boolean isClosed() throws Exception;
    public native byte[] getSerializedBson() throws Exception;
    private native byte [] getJsonStr() throws Exception;

    private int nativeRuleType(RULE_TYPE rule) {
        switch (rule) {
            case ACTION_READ_141X:
                return 0;
            case ACTION_WRITE_141X:
                return 1;
            case ACTION_DELETE_141X:
                return 2;
            case ACTION_UPDATE_141X:
                return 3;
            default:
                return -1;
        }
    }
    JWitsmlParserLoader() throws Exception {
        this.init(0, false);
    }

    JWitsmlParserLoader(RULE_TYPE rule, boolean versionCheckDisable) throws Exception {
        this.init(nativeRuleType(rule), versionCheckDisable);
    }

    public BSONObject parseToBson(String xml) throws JWitsmlException, Exception {
        return this.decoder.readObject(this.parser(xml));
    }

    public String parseToJson(String xml) throws JWitsmlException, Exception {
        return new String(this.parserJson(xml), StandardCharsets.UTF_8);
    }

    public BSONObject parseFromFileToBson(String filename) throws JWitsmlException, Exception {
        return this.decoder.readObject(this.parserFromFile(filename));
    }

    public String parseFromFileToJson(String filename) throws JWitsmlException, Exception {
        return new String(this.parserFromFileJson(filename), StandardCharsets.UTF_8);
    }

    //javah -jni -v -d <LOCAL_FOLDER> org.jwitsmlparser14x.JWitsmlParserLoader
    //https://stackoverflow.com/questions/32988798/memory-allocated-in-native-code-between-jni-calls

    public TreeMap<Integer, String> getBaseMsgList() throws Exception {
        if (this.baseMsgListMap == null)
            this.baseMsgListMap = baseMsgList();
        return this.baseMsgListMap;
    }

    public BSONObject getBson() throws Exception {
        return this.decoder.readObject(this.getSerializedBson());
    }

    public String getJson() throws Exception {
        return new String(this.getJsonStr(), StandardCharsets.UTF_8);
    }

    public BSONObject getBsonVersion() throws Exception {
        if (this.bsonVersion == null)
            this.bsonVersion = this.decoder.readObject(getBinaryBsonVersion());
        return this.bsonVersion;
    }
}
