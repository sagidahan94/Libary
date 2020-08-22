package bgu.spl.net.api.messages.ClientFrames;

import bgu.spl.net.api.messages.AbstractFrame;
import bgu.spl.net.api.messages.ServerFrames.Message;
import bgu.spl.net.impl.User;
import bgu.spl.net.impl.stomp.Database;
import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;
import javafx.util.Pair;

import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;

public class Send extends AbstractFrame {
    public Send(String destination, String body) {
        super("SEND");
        Pair<String,String> destination_header = new Pair<>("destination:",destination);
        List<Pair<String,String>> headers = new LinkedList<>();
        headers.add(destination_header);
        super.setHeaders(headers);;
        super.setBody(body);
    }

    @Override
    public AbstractFrame process(Connections<AbstractFrame> connections, ConnectionHandler<AbstractFrame> connectionHandler, Integer connectionid) {
        return makeMessageframe(connectionid);
    }

    /*    private String sendType(String body){
            String type="";
            if(body.contains(" has added the book ")){type="add";}
            else if(body.contains(" wish to borrow ")){type="borrow";}
            else if(body.contains("Returning")){type="return";}
            else if(body.contains("Taking")){type="take";}
            else if(body.contains("book status")){type="status";}
          return type;
        }
    /*    private LinkedList<String> spliterbytype(String type, String body){
            LinkedList<String> extractedParam=new LinkedList<>();
            String delimeter;
            switch (type){
                case "add":{delimeter=" has added the book "; extractedParam = advanceSpliter(delimeter,body);break;}//extractedParam at 0  is the USERNAME and 1 is the BOOKNAME
                case "borrow":{delimeter=" wish to borrow "; extractedParam=advanceSpliter(delimeter,body);break;}//extractedParam at 0  is the USERNAME and 1 is the BOOKNAME
                case "take":{delimeter="Taking ";extractedParam = advanceSpliter(" from ",advanceSpliter(delimeter,body).get(1));break;}
                case "return":{delimeter="Returning ";extractedParam = advanceSpliter(" to ",advanceSpliter(delimeter,body).get(1));break;}
                case "status":{break;}
            }
            return extractedParam;
        }
        private LinkedList<String> advanceSpliter(String delimeter,String sentence){
            return new LinkedList(Arrays.asList(sentence.split(delimeter)));
        }*/
    private Message makeMessageframe(Integer connectionid){
        User user = Database.getInstance().getUserbyConnectionId(connectionid);
        //TODO: what happened if you publish a book in channel that you not subscribe to, the subid is empty
        String subId = user.getSubscriptionId(this.getHeaders().get(0).getValue());
        String messageid = Database.getInstance().getnextMesaageID().toString();
        String destination = this.getHeaders().get(0).getValue();
        return new Message(subId,messageid,destination,this.getBody());
    }


}
