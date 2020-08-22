package bgu.spl.net.api;

import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;

public interface StompMessagingProtocol<AbstractFrame>  {
	/**
	 * Used to initiate the current client protocol with it's personal connection ID and the connections implementation
	**/
    void start(int connectionId, Connections<AbstractFrame> connections);
    
    void process(AbstractFrame message, ConnectionHandler<AbstractFrame> connectionHandler, int connectionid);
	
	/**
     * @return true if the connection should be terminated
     */
    boolean shouldTerminate();
}
