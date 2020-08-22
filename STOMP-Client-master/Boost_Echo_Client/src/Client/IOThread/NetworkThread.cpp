//
// Created by hachamto@wincs.cs.bgu.ac.il on 09/01/2020.
//

#include <STOMP/MessegeEncoderDecoder.h>
#include <STOMP/MessageProtocol.h>
#include <Client/IOThreads/connectionHandler.h>
#include <Frames/AbstractFrame.h>
#include <Frames/ClientFrames/Send.h>
#include "Client/IOThreads/NetworkThread.h"
#include "Client/IOThreads/KeyboardThread.h"




NetworkThread::NetworkThread(MessageEncoderDecoder &encdec, MessageProtocol &messageProtocol, boost::mutex &mutex, Inventory &inventory, ConnectionHandler *connectionHandler )
              : encdec(encdec), messageProtocol(messageProtocol), _mutex(mutex), connectionHandler(connectionHandler), inventory(inventory){}

NetworkThread::~NetworkThread() {}


/*
NetworkThread &NetworkThread::operator=(const NetworkThread &other) {
    this->encdec= other.encdec;
    this->messageProtocol= other.messageProtocol;
    this->_mutex= other._mutex;
    this->connectionHandler= other.connectionHandler;
    this->inventory= other.inventory;
}
*/


void NetworkThread::setConnectionHandler(ConnectionHandler* connectionHandler) {
    this->connectionHandler=connectionHandler;
}

void NetworkThread::run() {
    while (!messageProtocol.ShouldTerminate()){
    while(!this->connectionHandler->getActive() && messageProtocol.ShouldTerminate()){boost::this_thread::sleep_for( boost::chrono::milliseconds (200) );}
    //cout<<"Listening to the socket"<<endl;
    while (this->connectionHandler->getActive() && !messageProtocol.ShouldTerminate() ) {
        AbstractFrame *incomeframe = receive();
        if (incomeframe != nullptr) {
            messageProtocol.process(*incomeframe);

            //region Response to Has message -  CHECKED(for multi-word bookname)
            if (isHasAMessage(incomeframe->getBody())) {
                stringstream bodystream;
                string owner = ParseSpaces(incomeframe->getBody()).at(0);
                string bookname = getBookNameFromHasMessage(incomeframe->getBody(), owner);
                if (inventory.isBookInWishList(bookname)) {
                    inventory.addBook(bookname, incomeframe->getHeaders().at(2).second, owner);
                    inventory.removeFromWishList(bookname);
                    bodystream << "Taking " << bookname << " from " << owner;
                    string body = bodystream.str();
                    Send response = Send(incomeframe->getHeaders().at(2).second, body);
                    this->connectionHandler->sendFrameAscii(response.toString(), '\0');
                }
            }

                //endregion

                //region Response to Return message - CHECKED(for multi-word bookname)
            else if (isReturnMessage(incomeframe->getBody())) {
                vector<string> param = ParseSpaces(incomeframe->getBody());
                string bookname = getBookNameFromReturningMessage(incomeframe->getBody());
                string owner = param.at(param.size() - 1);
                if (inventory.getUsername() == owner) {
                    inventory.receivedBook(bookname);
                }
            }
                //endregion

                //region Response to Wish message
            else if (isWishMessage(incomeframe->getBody())) {
                string bookname = getBookNameFromWishMessage(incomeframe->getBody());
                if (inventory.findBook(bookname) != nullptr) {
                    //inventory.lendBook(bookname);
                    string dest = incomeframe->getHeaders().at(2).second;
                    Send response = Send(dest, inventory.getUsername() + " has " + bookname);
                    this->connectionHandler->sendFrameAscii(response.toString(), '\0');
                }
            }
                //endregion

                //region Response to Taking message
            else if (isTakingMessage(incomeframe->getBody())) {
                string lendingName = getLendingNameFromTakingMessage(incomeframe->getBody());
                string bookname = getBookNameFromTakingMessage(incomeframe->getBody(), lendingName);
                if (this->inventory.getUsername() == lendingName) {
                    this->inventory.lendBook(bookname);
                }
            }
                //endregion

                //region Response to Status message
            else if (isBookStatusMessage(incomeframe->getBody())) {
                string dest = incomeframe->getHeaders().at(2).second;
                Send response = Send(dest, inventory.getAvailableBooks(dest));
                this->connectionHandler->sendFrameAscii(response.toString(), '\0');
            }
            //endregion
            delete incomeframe;
        }


    }
}
}

AbstractFrame *NetworkThread::receive() {
    //boost::lock_guard<boost::mutex> lock(_mutex); //locks the mutex which should be associate with the connectionhandler
    if(connectionHandler->getActive()){
        string inputstream;
        this->connectionHandler->getFrameAscii(inputstream,'\0');
        AbstractFrame* incomeframe = encdec.parser(inputstream);
        return incomeframe;
    }
    return nullptr;
}

//region Messages kinds
bool NetworkThread::isHasAMessage(string body) {
    size_t found = body.find(" has ");
    return (found!=string::npos);
}
bool NetworkThread::isReturnMessage(string body) {
    size_t found = body.find("Returning");
    return (found!=string::npos);
}
bool NetworkThread::isWishMessage(string body) {
    size_t found = body.find(" wish to borrow ");
    return (found!=string::npos);
}
bool NetworkThread::isBookStatusMessage(string body) {
    size_t found = body.find("Book status");
    return (found!=string::npos);
}
bool NetworkThread::isTakingMessage(string body) {
    size_t found = body.find("Taking");
    return (found!=string::npos);
}
//endregion

string NetworkThread::getBookNameFromHasMessage(string body, string owner) {
    vector<string> parameters;
    char_separator<char> sep(" ");
    tokenizer<char_separator<char>> tokens(body, sep);
    for (const auto& t : tokens) {
        parameters.emplace_back(t);
        // cout << t << endl;
    }
    string bookname;
    for(string str:parameters){
        if(str!=owner && str!="has"){
            bookname= bookname+ " "+ str;
        }
    }
    return bookname.substr(1);
}
string NetworkThread::getBookNameFromReturningMessage(string body) {
    vector<string> parameters;
    char_separator<char> sep(" ");
    tokenizer<char_separator<char>> tokens(body, sep);
    for (const auto& t : tokens) {
        parameters.emplace_back(t);
        // cout << t << endl;
    }
    string bookname;
    for(string str:parameters){
        if(str!="to" && str!=parameters.at(parameters.size()-1) && str!="Returning"){
            bookname= bookname+ " "+ str;
        }
    }
    return bookname.substr(1);
}
vector<string> NetworkThread::ParseSpaces(string body) {
    vector<string> parameters;
    char_separator<char> sep(" ");
    tokenizer<char_separator<char>> tokens(body, sep);
    for (const auto& t : tokens) {
        parameters.emplace_back(t);
        // cout << t << endl;
    }
    return parameters;
}

string NetworkThread::getBookNameFromWishMessage(string body) {
    vector<string> parameters;
    char_separator<char> sep(" ");
    tokenizer<char_separator<char>> tokens(body, sep);
    for (const auto& t : tokens) {
        parameters.emplace_back(t);
        // cout << t << endl;
    }
    string asker = parameters.at(0);
    string bookname;
    for(string str:parameters){
        if(str!=asker && str!="wish" && str!="to" && str!="borrow"){
            bookname= bookname+ " "+ str;
        }
    }
    return bookname.substr(1);
}



string NetworkThread::getLendingNameFromTakingMessage(string body) {
    vector<string> parameters;
    char_separator<char> sep(" ");
    tokenizer<char_separator<char>> tokens(body, sep);
    for (const auto& t : tokens) {
        parameters.emplace_back(t);
        // cout << t << endl;
    }
    string lendingName= parameters.at(parameters.size()-1);
    return lendingName;
}

string NetworkThread::getBookNameFromTakingMessage(string body,string lendingname) {
    vector<string> parameters;
    char_separator<char> sep(" ");
    tokenizer<char_separator<char>> tokens(body, sep);
    for (const auto& t : tokens) {
        parameters.emplace_back(t);
        // cout << t << endl;
    }
    string bookname;
    for(string str:parameters){
        if(str!=lendingname && str!="Taking" && str!="from"){
            bookname= bookname+ " "+ str;
        }
    }
    return bookname.substr(1);

}


