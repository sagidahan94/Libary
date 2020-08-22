package bgu.spl.net.impl;

import javafx.util.Pair;

import java.util.LinkedList;
import java.util.List;

public class User {



    //Fields:
    private  Integer connectionId=-1;
    private String Password;
    private String username;
    private List<Pair<String, String>> channels;
    private boolean loggin; //indicate if the user is log in

    public User(String username, String password) {
        loggin=false;
        this.Password=password;
        this.username=username;
        channels = new LinkedList<>();
    }

    public void addChannel(String channel, String subscriptionid){
        channels.add(new Pair(channel,subscriptionid));
    }
    public Integer getConnectionId() {
        return connectionId;
    }
    public void setConnectionId(Integer connectionId) {
        this.connectionId = connectionId;
    }
    public void clearsubscription(){
        channels.removeAll(channels);
    }
    public void login(){loggin=true;}
    public void logout(){loggin=false; connectionId=-1;}
    public boolean isLoggin(){return this.loggin;}
    public String getPassword(){ return this.Password; }
    public String getUserName() {return this.username;}
    public void removeChannel(String subscriptionid) {
        if(channels!=null){
        for (Pair pair :channels) {
            if (pair.getValue().equals(subscriptionid)){
                channels.remove(pair);
            }
        }
    }
    }
    public String getSubscriptionId(String channel){
        for(Pair<String,String> pair:channels){
            if(pair.getKey().equals(channel)){
                return pair.getValue();
            }
        }
        return "";
    }
    public String getChannelbySubId(String subid){
        for(Pair<String, String> pair: channels){
            if(pair.getValue().equals(subid))
                return pair.getKey();
        }
        return "";
    }
}
