package bgu.spl.net.api.messages;

import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;
import javafx.util.Pair;

import java.util.List;

public abstract class AbstractFrame {
    //Fields:
    private String command;
    private List<Pair<String,String>> headers;
    private String body = "";
    private final String endOfFrame = "\u0000";

    private ConnectionHandler<AbstractFrame> connectionHandler;
    private int connectionid;

    //Constructor:
    public AbstractFrame(String command){
        this.command=command;
    }

    //Methods
    public String getCommand() {
        return command;
    }

    public void setCommand(String command) {
        this.command = command;
    }

    public List<Pair<String, String>> getHeaders() {
        return headers;
    }

    public void setHeaders(List<Pair<String, String>> headers) {
        this.headers = headers;
    }

    public String getBody() {
        return body;
    }

    public void setBody(String body) {
        this.body = body;
    }

    @Override
    public String toString() {
        //TODO: make output string as the requested format
        String output="";
        output=output+command+System.lineSeparator();
        output=output+headers_concate();
        output=output+System.lineSeparator();
        output=output+body;
        output=output+System.lineSeparator();
        output=output+endOfFrame;
        return output;
    }
    private String headers_concate(){
        String _headers="";
        for (Pair header:headers) {
            _headers=_headers+header.getKey()+ header.getValue()+System.lineSeparator();
        }
        return _headers;
    }

    public byte[] getBytes(){
        return toString().getBytes();
    }

    public String getReceiptID() {

        return headers.get(headers.size()-1).getValue();
    }

    public abstract AbstractFrame process(Connections<AbstractFrame> connections, ConnectionHandler<AbstractFrame> connectionHandler, Integer connectionid);
    public ConnectionHandler<AbstractFrame> getConnectionHandler() {
        return connectionHandler;
    }

    public void setConnectionHandler(ConnectionHandler<AbstractFrame> connectionHandler) {
        this.connectionHandler = connectionHandler;
    }

    public int getConnectionid() {
        return connectionid;
    }

    public void setConnectionid(int connectionid) {
        this.connectionid = connectionid;
    }
}
