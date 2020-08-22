package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.api.MessagingProtocol;
import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.api.messages.AbstractFrame;
import bgu.spl.net.impl.MessageEncoderDecoderImpl;
import bgu.spl.net.impl.stomp.suppliers.EncoderDecoderFactory;
import bgu.spl.net.impl.stomp.suppliers.StompMessageProtocolFactory;
import bgu.spl.net.srv.Server;

import java.util.function.Supplier;

public class StompServer {

    public static void main(String[] args) {
        //Supplier init
        Supplier <StompMessagingProtocol>  protocolFactory = new StompMessageProtocolFactory();
        Supplier<MessageEncoderDecoder> encdecFactory = new EncoderDecoderFactory();
        //Server.threadPerClient( 8888,protocolFactory, encdecFactory).serve();
        Server.reactor(2,8888,protocolFactory,encdecFactory).serve();

    }


}
