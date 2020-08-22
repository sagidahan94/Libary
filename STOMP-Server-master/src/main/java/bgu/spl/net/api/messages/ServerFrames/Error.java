package bgu.spl.net.api.messages.ServerFrames;

import bgu.spl.net.api.messages.AbstractFrame;
import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;
import javafx.util.Pair;

import java.util.LinkedList;
import java.util.List;

public class Error extends AbstractFrame {
    public Error(String receipt,String message,String body) {
        super("ERROR");
        Pair<String,String> receipt_header = new Pair<>("receipt-id:",receipt);
        Pair<String,String> message_header = new Pair<>("message:",message);
        List<Pair<String,String>> headers = new LinkedList<>();
        headers.add(receipt_header);
        headers.add(message_header);
        super.setHeaders(headers);
        super.setBody(body);
    }

    @Override
    public AbstractFrame process(Connections<AbstractFrame> connections, ConnectionHandler<AbstractFrame> connectionHandler, Integer connectionid) {
        return null;
    }
}
