package bgu.spl.net.srv;

import bgu.spl.net.api.MessageEncoderDecoder;
import bgu.spl.net.api.MessagingProtocol;
import bgu.spl.net.api.StompMessagingProtocol;
import bgu.spl.net.impl.ConnectionsImpl;
import bgu.spl.net.impl.User;
import bgu.spl.net.impl.stomp.Database;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ConcurrentHashMap;
import java.util.function.Supplier;

public abstract class BaseServer<AbstractFrame> implements Server<AbstractFrame> {

    private final int port;
    private final Supplier<StompMessagingProtocol> protocolFactory;
    private final Supplier<MessageEncoderDecoder> encdecFactory;
    private  Connections connections;
    private ServerSocket sock;
    private int nextConnectionId=1;
    private Database database;

    //user regarding fields
    private ConcurrentHashMap<Integer, User> User_Id;
    private ConcurrentHashMap<String, User> User_Name;
    private Integer NextId=1;

    public BaseServer(
            int port,
            Supplier<StompMessagingProtocol> protocolFactory,
            Supplier<MessageEncoderDecoder> encdecFactory) {

        this.port = port;
        this.protocolFactory = protocolFactory;
        this.encdecFactory = encdecFactory;
		this.sock = null;
		this.connections = new ConnectionsImpl<AbstractFrame>();
		this.database = Database.getInstance();
		database.setConnections(connections);
    }

    @Override
    public void serve() {

        try (ServerSocket serverSock = new ServerSocket(port)) {
			System.out.println("Server started");
            this.sock = serverSock; //just to be able to close

            while (!Thread.currentThread().isInterrupted()) {

                Socket clientSock = serverSock.accept();

                BlockingConnectionHandler<AbstractFrame> handler = new BlockingConnectionHandler<AbstractFrame>(
                        clientSock,
                        encdecFactory.get(),
                        protocolFactory.get(),
                        connections,
                        nextConnectionId
                        );
                database.addNewConnection(nextConnectionId,handler);
                nextConnectionId++;

                execute(handler);
            }
        } catch (IOException ex) {
        }

        System.out.println("server closed!!!");
    }

    @Override
    public void close() throws IOException {
		if (sock != null)
			sock.close();
    }

    protected abstract void execute(BlockingConnectionHandler<AbstractFrame>  handler);

}
