//
// Created by hachamto@wincs.cs.bgu.ac.il on 09/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_NETWORKTHREAD_H
#define BOOST_ECHO_CLIENT_NETWORKTHREAD_H
#include <boost/thread.hpp>
#include <Client/IOThreads/connectionHandler.h>
#include <STOMP/MessegeEncoderDecoder.h>
#include <STOMP/MessageProtocol.h>
#include <STOMP/MessageProtocol.h>
#include <iostream>
#include <string> // To use string
#include <boost/tokenizer.hpp>
#include <Frames/ClientFrames/Connect.h>
#include <mutex>
#include <thread>
#include <Client/Data/Inventory.h>

using namespace std;
using namespace boost;


class NetworkThread {
public:
    NetworkThread(MessageEncoderDecoder &encdec, MessageProtocol &messageProtocol, boost::mutex &mutex,
                  Inventory &inventory, ConnectionHandler *connectionHandler
                  );
    ~NetworkThread();


/*
    NetworkThread&operator=(const NetworkThread &other);
*/

    void run();
    AbstractFrame* receive();
    void setConnectionHandler(ConnectionHandler* connectionHandler );

private:
    MessageEncoderDecoder& encdec;
    MessageProtocol& messageProtocol;
    boost::mutex& _mutex;
    ConnectionHandler* connectionHandler;
    Inventory& inventory;
    bool isHasAMessage(string body);
    bool isReturnMessage(string body);
    bool isWishMessage(string body);
    bool isBookStatusMessage(string body);
    bool isTakingMessage(string body);
    string getBookNameFromReturningMessage(string body);
    string getBookNameFromHasMessage(string body, string owner);
    string getBookNameFromWishMessage(string body);
    string getBookNameFromTakingMessage(string body,string lendingname);
    string getLendingNameFromTakingMessage(string body);

    vector<string> ParseSpaces(string body);

};


#endif //BOOST_ECHO_CLIENT_NETWORKTHREAD_H
