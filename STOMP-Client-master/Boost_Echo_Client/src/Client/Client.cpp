//
// Created by sagidaha@wincs.cs.bgu.ac.il on 08/01/2020.
//
#include <boost/thread.hpp>
#include "Client/Client.h"
#include <Client/IOThreads/connectionHandler.h>
#include <STOMP/MessegeEncoderDecoder.h>
#include <STOMP/MessageProtocol.h>
#include <iostream>
#include <string> // To use string
#include <boost/tokenizer.hpp>
#include <Frames/ClientFrames/Connect.h>
#include "Client/IOThreads/KeyboardThread.h"
#include "Client/IOThreads/NetworkThread.h"
using namespace std;
using namespace boost;

using namespace std;

Client::Client():keyboardthread(nullptr),networkthread(nullptr),connectionHandler(nullptr),encdec(nullptr),messageProtocol(
        nullptr),_mutex(nullptr),inventory(nullptr), receiptId_frame(vector<pair<string, AbstractFrame*>>()){

 //   this->messageProtocol_network = new MessageProtocol(*connectionHandler,receiptId_frame);
    //TODO: need to add kind of sync on the inventory
    //this->keyboardthread = new KeyboardThread(*encdec,*messageProtocol,*_mutex);
    //this->networkthread = new NetworkThread(*encdec,*messageProtocol,*_mutex);
    //keyboardthread->setNetworkThread(this->networkthread);
encdec=new MessageEncoderDecoder();
_mutex=new boost::mutex();
inventory=new Inventory();
connectionHandler=new ConnectionHandler("0",0);
receiptId_frame= vector<pair<string, AbstractFrame*>>();
messageProtocol=new MessageProtocol(*connectionHandler,receiptId_frame);
}
Client::~Client(){
    delete encdec;
    delete connectionHandler;
    delete messageProtocol;
    delete _mutex;
    delete inventory;
    for(auto channel: receiptId_frame){
        delete channel.second;
    }
    receiptId_frame.clear();
}

void Client::run() {
    cout<<"Client is up\n"<<endl;
    KeyboardThread k1 = KeyboardThread(*encdec, *messageProtocol, *_mutex, *inventory, connectionHandler,receiptId_frame);
    NetworkThread n1 = NetworkThread(*encdec, *messageProtocol, *_mutex, *inventory, connectionHandler);
    k1.setNetworkThread(&n1);

    boost::thread th1(&KeyboardThread::run, &k1);
    boost::thread th2(&NetworkThread::run, &n1);
    //cout<<"main thread: "<<std::this_thread::get_id()<<endl;
    //cout<<"keyboard thread: "<<th1.get_id()<<endl;
    //cout<<"network thread: "<<th2.get_id()<<endl;
    th1.join();
    th2.join();
    cout << "client is shutting down"<< endl;
}



/*
Client &Client::operator=(const Client &other) {
    this->keyboardthread= other.keyboardthread;
    this->networkthread= other.networkthread;
    this->connectionHandler= other.connectionHandler;
    this->encdec= other.encdec;
    this->messageProtocol= other.messageProtocol;
    this->_mutex= other._mutex;
    this->inventory= other.inventory;
    for(auto pair: other.receiptId_frame){
        this->receiptId_frame.push_back(pair);
    }
}
*/

