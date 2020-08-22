package bgu.spl.net.api.messages.ServerFrames;

import bgu.spl.net.api.messages.AbstractFrame;
import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;
import javafx.util.Pair;

import java.util.LinkedList;
import java.util.List;

public class Connected extends AbstractFrame {
    public Connected(String version) {
        super("CONNECTED");
        Pair<String,String> version_header = new Pair<>("version:",version);
        List<Pair<String,String>> headers = new LinkedList<>();
        headers.add(version_header);
        super.setHeaders(headers);;

    }

    @Override
    public AbstractFrame process(Connections<AbstractFrame> connections, ConnectionHandler<AbstractFrame> connectionHandler, Integer connectionid) {
        return null;
    }
}
