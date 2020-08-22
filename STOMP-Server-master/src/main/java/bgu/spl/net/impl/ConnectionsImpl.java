package bgu.spl.net.impl;

import bgu.spl.net.impl.stomp.Database;
import bgu.spl.net.srv.ConnectionHandler;
import bgu.spl.net.srv.Connections;

import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;

public class ConnectionsImpl<T> implements Connections<T> {
    //Fields:
    ConcurrentMap<Integer, ConnectionHandler> connectionid_connetionHandler; //connection_id to connectionHandler
    ConcurrentHashMap<String, List<User>> Channel_User;// will hold the connections ids of the users subscribe to the channel


    public ConnectionsImpl() {
        connectionid_connetionHandler = new ConcurrentHashMap<>();
        Channel_User = new ConcurrentHashMap<>();
    }

    @Override
    public boolean send(int connectionId, T msg) {
        connectionid_connetionHandler.get(connectionId).send(msg);
        return true;
    }

    @Override
    public void send(String channel, T msg) {
        if (Channel_User.containsKey(channel)) {
            List<User> usersPool = Channel_User.get(channel);
            for (User user : usersPool) {
                send(user.getConnectionId(), msg);
            }
        }

    }

    @Override
    public void disconnect(int connectionId) {
        if (connectionid_connetionHandler.containsKey(connectionId)) {
            connectionid_connetionHandler.remove(connectionId, connectionid_connetionHandler.get(connectionId));
            User disconnected_user = Database.getInstance().getUserbyConnectionId(connectionId);
            for (String channel : Channel_User.keySet()) {
                List<User> usersPool = Channel_User.get(channel);
                for (User user : usersPool) {
                    if (user.getUserName().equals(disconnected_user.getUserName())) {
                        usersPool.remove(disconnected_user);
                    }
                }
            }
            disconnected_user.clearsubscription();
        }
    }


/*                for (User user : Channel_User.get(channel)) {
                    if (user.getConnectionId() == connectionId) {
                        Channel_User.get(channel).remove(user);
                        user.clearsubscription();
                    }
                }
            }

        }
    }*/

    @Override
    public void addNewconnection(Integer connectionid, ConnectionHandler connectionHandler) {
        //connectionid_connetionHandler.putIfAbsent(connectionid, connectionHandler);
        if(!connectionid_connetionHandler.containsKey(connectionid)){
            connectionid_connetionHandler.put(connectionid,connectionHandler);
        }
    }

    @Override
    public void subscribe(String channel, String subscriptionid, Integer connectionid) {
        List<User> usersPool;
        User user = Database.getInstance().getUserbyConnectionId(connectionid);
        synchronized (Channel_User) {
            if (Channel_User.containsKey(channel)) {
                usersPool = Channel_User.get(channel);
            } else {
                usersPool = new LinkedList<>();
                Channel_User.put(channel, usersPool);
            }
            usersPool.add(user);
        }
    }

    @Override
    public void unsubscribe(String channel, Integer connectionid) {
        User user = Database.getInstance().getUserbyConnectionId(connectionid);
        if (Channel_User.containsKey(channel) && !Channel_User.get(channel).isEmpty() && user != null && channel!="") {
            Channel_User.get(channel).remove(user);
            user.removeChannel(user.getSubscriptionId(channel));
        }
    }
}
