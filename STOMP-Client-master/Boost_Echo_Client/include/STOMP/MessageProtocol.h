//
// Created by hachamto@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_MESSAGEPROTOCOL_H
#define BOOST_ECHO_CLIENT_MESSAGEPROTOCOL_H


#include <Client/IOThreads/connectionHandler.h>
#include "Frames/AbstractFrame.h"

class MessageProtocol {
public:
    MessageProtocol(ConnectionHandler& connectionHandler,vector<pair<string, AbstractFrame *>> &receiptIdFrame);
    ~MessageProtocol();
    void process(AbstractFrame& );
    bool ShouldTerminate();
    void terminateConnectionHandler();
    void terminateProtocol();
private:
    bool terminate;
    ConnectionHandler& connectionHandler;
    vector<pair<string, AbstractFrame*>>& receiptId_frame;
    AbstractFrame* findFrame(string receiptId);


};


#endif //BOOST_ECHO_CLIENT_MESSAGEPROTOCOL_H
