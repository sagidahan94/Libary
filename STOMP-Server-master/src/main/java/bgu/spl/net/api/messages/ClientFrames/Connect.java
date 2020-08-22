package bgu.spl.net.api.messages.ClientFrames;

import bgu.spl.net.api.messages.AbstractFrame;
import bgu.spl.net.api.messages.ServerFrames.Connected;
import bgu.spl.net.api.messages.ServerFrames.Error;
import bgu.spl.net.impl.stomp.Database;
import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;
import javafx.util.Pair;

import java.util.LinkedList;
import java.util.List;

public class Connect extends AbstractFrame {
    public Connect(String version, String host, String login, String passcode) {
    super("CONNECT");
        Pair<String,String> accept_version_header = new Pair<>("accept-version:",version);
        Pair<String,String> host_header = new Pair<>("host:",host);
        Pair<String,String> login_header = new Pair<>("login:",login);
        Pair<String,String> passcode_header = new Pair<>("passcode:",passcode);


        List<Pair<String,String>> headers = new LinkedList<>();
        headers.add(accept_version_header);
        headers.add(host_header);
        headers.add(login_header);
        headers.add(passcode_header);


        super.setHeaders(headers);;
    }

    @Override
    public AbstractFrame process(Connections<AbstractFrame> connections, ConnectionHandler<AbstractFrame> connectionHandler, Integer connectionid) {
        String username = this.getHeaders().get(2).getValue();
        String passcode = this.getHeaders().get(3).getValue();
        AbstractFrame returnFrame;
        Integer returnCode = Database.getInstance().login(username,passcode,connectionHandler,connectionid);
        switch(returnCode){
            case 0:{ returnFrame = new Connected("1.2");break;}
            case 1:{returnFrame = new Error("CONNECT","the user is already logged in","Error according to the message:"+System.lineSeparator()+ this.toString());break;}
            case 2:{returnFrame = new Error("CONNECT","password incorrect","Error according to the message:"+System.lineSeparator()+ this.toString());break;}
            default:
                returnFrame = new Error(getReceiptID(),"unexpected returnCode","error accord in the login procees at database class");
        }
         
        return returnFrame;
    }
}

