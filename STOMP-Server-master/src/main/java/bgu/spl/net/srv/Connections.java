package bgu.spl.net.srv;

import bgu.spl.net.impl.User;

import java.io.IOException;

public interface Connections<T> {

    boolean send(int connectionId, T msg);

    void send(String channel, T msg);

    void disconnect(int connectionId);


    //region my addition
    void addNewconnection(Integer connectionid, ConnectionHandler connectionHandler);

    void subscribe(String channel, String subscriptionid, Integer connectionid);

    void unsubscribe(String channel, Integer connectionid);

    //endregion
}
