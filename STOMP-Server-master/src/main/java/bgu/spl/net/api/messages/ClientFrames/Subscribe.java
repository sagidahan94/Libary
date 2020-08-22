package bgu.spl.net.api.messages.ClientFrames;

import bgu.spl.net.api.messages.AbstractFrame;
import bgu.spl.net.api.messages.ServerFrames.Receipt;
import bgu.spl.net.impl.stomp.Database;
import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;
import javafx.util.Pair;

import java.util.LinkedList;
import java.util.List;

public class Subscribe extends AbstractFrame {
    public Subscribe(String destination, String id, String receipt) {
        super("SUBSCRIBE");
        Pair<String,String> destination_header = new Pair<>("destination:",destination);
        Pair<String,String> id_header = new Pair<>("id:",id);
        Pair<String,String> receipt_header = new Pair<>("receipt:",receipt);
        List<Pair<String,String>> headers = new LinkedList<>();
        headers.add(destination_header);
        headers.add(id_header);
        headers.add(receipt_header);
        super.setHeaders(headers);;
    }

    @Override
    public AbstractFrame process(Connections<AbstractFrame> connections, ConnectionHandler<AbstractFrame> connectionHandler, Integer connectionid) {
        Database database = Database.getInstance();
        String channel = this.getHeaders().get(0).getValue();
        String subscriptionid = this.getHeaders().get(1).getValue();
        database.subscribe(channel,subscriptionid,connectionid);
        return new Receipt(getReceiptID());
    }
}
