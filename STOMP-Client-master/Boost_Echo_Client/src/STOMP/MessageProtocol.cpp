//
// Created by hachamto@wincs.cs.bgu.ac.il on 08/01/2020.
//

#include <STOMP/MessageProtocol.h>

MessageProtocol::MessageProtocol(ConnectionHandler& connectionHandler,vector<pair<string, AbstractFrame *>> &receiptIdFrame):terminate(false),connectionHandler(connectionHandler),receiptId_frame(receiptIdFrame) {

}

MessageProtocol::~MessageProtocol() {
    for(auto frame:receiptId_frame){
        delete frame.second;
    }
    receiptId_frame.clear();

}

void MessageProtocol::process(AbstractFrame& frame) {
    //TODO:implemets this
    //todo: return pointer to abstractFrame
    frame.process();
    if(frame.getCommand()=="RECEIPT" ){
        AbstractFrame* originalFrame= findFrame(frame.getHeaders().at(frame.getHeaders().size()-1).second);
        if(originalFrame!= nullptr){
            originalFrame->process();
            if(originalFrame->getCommand()=="DISCONNECT"){
                terminateConnectionHandler();
                terminateProtocol();
            }
        }
    }
    else if(frame.getCommand()=="ERROR" ){
        terminateConnectionHandler();
        //terminateProtocol();
    }
}

bool MessageProtocol::ShouldTerminate() {
    return terminate;
}

void MessageProtocol::terminateConnectionHandler() {
    this->connectionHandler.close();

}

AbstractFrame *MessageProtocol::findFrame(string receiptId) {
    for (auto pair: receiptId_frame) {
        if(pair.first==receiptId){
            return pair.second;
        }
    }
    return nullptr;
}

void MessageProtocol::terminateProtocol() {
    this->terminate=true;
}
