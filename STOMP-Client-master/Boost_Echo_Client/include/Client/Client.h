//
// Created by sagidaha@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_CLIENT_H
#define BOOST_ECHO_CLIENT_CLIENT_H
#include <boost/thread.hpp>
#include <Client/IOThreads/connectionHandler.h>
#include <STOMP/MessegeEncoderDecoder.h>
#include <STOMP/MessageProtocol.h>
#include <Client/IOThreads/KeyboardThread.h>
#include <Client/IOThreads/NetworkThread.h>
#include <string> // To use string
#include <boost/tokenizer.hpp>
#include <mutex>
#include <thread>
#include <Client/Data/Inventory.h>

using namespace std;
using namespace boost;

class Client {
private:
    int id;
    KeyboardThread* keyboardthread;
    NetworkThread* networkthread;

    ConnectionHandler* connectionHandler;
    MessageEncoderDecoder* encdec;
    MessageProtocol* messageProtocol;
   // MessageProtocol* messageProtocol_network;
    boost::mutex* _mutex;
    Inventory* inventory;
    vector<pair<string, AbstractFrame*>> receiptId_frame;


public:
    Client();
    ~Client();

/*
    Client&operator=(const Client &other);
*/


    void run();
};


#endif //BOOST_ECHO_CLIENT_CLIENT_H
