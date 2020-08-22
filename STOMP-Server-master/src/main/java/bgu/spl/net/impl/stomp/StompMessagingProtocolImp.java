package bgu.spl.net.impl.stomp;

import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.api.messages.AbstractFrame;
import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;

public class StompMessagingProtocolImp<T> implements StompMessagingProtocol<AbstractFrame> {
    private int connectionId;
    private Connections<AbstractFrame> connections;
    private boolean terminate = false;


    @Override
    public void start(int connectionId, Connections<AbstractFrame> connections) {
        this.connectionId = connectionId;
        this.connections = connections;
    }

    @Override
    public void process(AbstractFrame message, ConnectionHandler<AbstractFrame> connectionHandler, int connectionid) {
        message.setConnectionHandler(connectionHandler);
        message.setConnectionid(connectionid);
        AbstractFrame response = message.process(connections, connectionHandler, connectionid);
        System.out.println("Sending Frame");
        System.out.println("-------------");
        System.out.println( response.toString());
        if (response.getCommand().equals("MESSAGE")) {
            String channel = message.getHeaders().get(0).getValue();
            connections.send(channel, response);
        }
        else
            {
            connectionHandler.send(response);
        }
        if (message.getCommand().equals("DISCONNECT") | response.getCommand().equals("ERROR")) {
            terminate = true;
        }
    }

    @Override
    public boolean shouldTerminate() {
        return terminate;
    }
}
