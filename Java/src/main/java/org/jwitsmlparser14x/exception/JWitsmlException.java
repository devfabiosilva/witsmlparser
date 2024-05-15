package org.jwitsmlparser14x.exception;

public class JWitsmlException extends Throwable {
    private final int cwitsmlError;
    private final String faultstring;
    private final String XMLfaultdetail;
    private final int baseMsgError;
    private final String baseMsg;
    private final String witsmlParserInstanceName;

    JWitsmlException(
            String message, int cwitsmlError,
            String faultstring, String XMLfaultdetail,
            int baseMsgError, String baseMsg, String witsmlParserInstanceName
    ) {
        super(message);
        this.cwitsmlError = cwitsmlError;
        this.faultstring = faultstring;
        this.XMLfaultdetail = XMLfaultdetail;
        this.baseMsgError = baseMsgError;
        this.baseMsg = baseMsg;
        this.witsmlParserInstanceName = witsmlParserInstanceName;
    }

    public int getCwitsmlError() { return this.cwitsmlError; }
    public String getFaultstring() { return this.faultstring; }
    public String getXMLfaultdetail() { return this.XMLfaultdetail; }
    public int getBaseMsgError() { return this.baseMsgError; }
    public String getBaseMsg() { return this.baseMsg; }
    public String getWitsmlParserInstanceName() { return this.witsmlParserInstanceName; }
}
