//
// Created by hachamto@wincs.cs.bgu.ac.il on 09/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_KEYBOARDTHREAD_H
#define BOOST_ECHO_CLIENT_KEYBOARDTHREAD_H
#include <boost/thread.hpp>
#include <Client/IOThreads/connectionHandler.h>
#include <STOMP/MessegeEncoderDecoder.h>
#include <STOMP/MessageProtocol.h>
#include <Client/IOThreads/NetworkThread.h>
#include <iostream>
#include <string> // To use string
#include <boost/tokenizer.hpp>
#include <Frames/ClientFrames/Connect.h>
#include <mutex>
#include <thread>
#include <Frames/AbstractFrame.h>
#include <Client/Data/Inventory.h>
#include "NetworkThread.h"

using namespace std;
using namespace boost;


class KeyboardThread {
public:
    KeyboardThread(MessageEncoderDecoder &encdec, MessageProtocol &messageProtocol, boost::mutex &mutex,
                   Inventory &inventory, ConnectionHandler *connectionHandler,vector<pair<string, AbstractFrame *>> &receiptIdFrame
    );

    //KeyboardThread(const KeyboardThread& other);
    ~KeyboardThread();

   /* KeyboardThread&operator=(const KeyboardThread &other);*/

    void setUserName(string username);
    void setNetworkThread(NetworkThread*);
    static string getNextReceipt();
    void run();

private:
    MessageEncoderDecoder& encdec;
    MessageProtocol& messageProtocol;
    boost::mutex& _mutex;
    ConnectionHandler* connectionHandler;
    NetworkThread* networkThread;
    Inventory& inventory;
    vector<pair<string, AbstractFrame*>>& receiptId_frame;
    vector<pair<string, int>> subscriptionList;
    int subscription_id;
    static int receipt;
    string userName;
    bool logout;

    bool isSubscribe(string genre);
    bool setConnectionHandler(string& ip, string& port);
    void send(AbstractFrame* frame);
    int getNextSubscriptionId();
    int subscribe(string channel);
    int unsubscribe(string channel);
    int getSubscriptionid(string channel);
    string concateBookname(vector<string> parameters);

    vector<string> getParameters(string& user_input);
    vector<string> extractIPPort(string& host);

};


#endif //BOOST_ECHO_CLIENT_KEYBOARDTHREAD_H
