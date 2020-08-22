package bgu.spl.net.api.messages.ClientFrames;

import bgu.spl.net.api.messages.AbstractFrame;
import bgu.spl.net.api.messages.ServerFrames.Receipt;
import bgu.spl.net.impl.stomp.Database;
import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;
import javafx.util.Pair;
import java.util.LinkedList;
import java.util.List;

public class Unsbscribe extends AbstractFrame {
    public Unsbscribe(String id, String receipt) {
        super("UNSUBSCRIBE");
        Pair<String, String> id_header = new Pair<>("id:", id);
        Pair<String, String> receipt_header = new Pair<>("receipt:", receipt);
        List<Pair<String, String>> headers = new LinkedList<>();
        headers.add(id_header);
        headers.add(receipt_header);
        super.setHeaders(headers);
        ;
    }

    @Override
    public AbstractFrame process(Connections<AbstractFrame> connections, ConnectionHandler<AbstractFrame> connectionHandler, Integer connectionid) {
        Database database = Database.getInstance();
        String subscriptionid = this.getHeaders().get(0).getValue();
        database.unsubscribe(subscriptionid,connectionid);
        return new Receipt(getReceiptID());
    }
}
