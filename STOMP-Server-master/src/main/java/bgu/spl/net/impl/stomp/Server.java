package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.api.messages.AbstractFrame;
import bgu.spl.net.srv.BaseServer;
import bgu.spl.net.srv.BlockingConnectionHandler;

import java.util.function.Supplier;

public class Server<AbstractFrame> extends BaseServer<AbstractFrame> {

    public Server(int port, Supplier<StompMessagingProtocol> protocolFactory, Supplier<MessageEncoderDecoder> encdecFactory) {
        super(port, protocolFactory, encdecFactory);
    }

    @Override
    public void serve(){
        super.serve();
    }

    @Override
    protected void execute(BlockingConnectionHandler<AbstractFrame> handler) {
        new Thread(handler).start();    }
}
