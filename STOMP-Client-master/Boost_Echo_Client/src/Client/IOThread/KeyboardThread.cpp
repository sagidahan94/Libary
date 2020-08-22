//
// Created by hachamto@wincs.cs.bgu.ac.il on 09/01/2020.
//

#include <Client/IOThreads/KeyboardThread.h>
#include <mutex>
#include <thread>
#include <Frames/ClientFrames/Subscribe.h>
#include <Frames/ClientFrames/Send.h>
#include <Frames/ServerFrames/Disconnect.h>
#include <Frames/ClientFrames/Unsubscribe.h>
#include <STOMP/MessegeEncoderDecoder.h>
#include <STOMP/MessageProtocol.h>
#include <boost/tokenizer.hpp>


using namespace std;
using namespace boost;

int KeyboardThread::receipt = 1;

KeyboardThread::KeyboardThread(MessageEncoderDecoder &encdec, MessageProtocol &messageProtocol, boost::mutex &mutex,
                               Inventory &inventory, ConnectionHandler *connectionHandler,
                               vector<pair<string, AbstractFrame *>> &receiptIdFrame)
        : encdec(encdec), messageProtocol(messageProtocol), _mutex(mutex),
          connectionHandler(connectionHandler), networkThread(nullptr), subscription_id(1),
          userName(""), subscriptionList(vector<pair<string, int>>()),
          inventory(inventory), receiptId_frame(receiptIdFrame),logout(false) {
}


/*
KeyboardThread &KeyboardThread::operator=(const KeyboardThread &other) {
    if(this== other){
        return *this;
    }
        this->encdec= other->encdec;
        this->messageProtocol= other->messageProtocol;
        this->_mutex=other->_mutex;
        this->connectionHandler= other->connectionHandler;
        this->networkThread= other->networkThread;
        this->inventory= other->inventory;
        for(auto pair: other->receiptId_frame){
            this->receiptId_frame.push_back(pair);
        }
        for(auto pair: other->subscriptionList){
            this->subscriptionList.push_back(pair);
        }
        this->subscription_id= other->subscription_id;
        this->receipt= other->receipt;
        this->userName= other->userName;
        this->logout= other->logout;

}
*/


vector<string> KeyboardThread::getParameters(string &user_input) {
    char_separator<char> sep(" ");
    vector<string> parameters = vector<string>();
    tokenizer<char_separator<char>> tokens(user_input, sep);
    for (const auto &t : tokens) {
        parameters.emplace_back(t);
    }
    return parameters;
}

vector<string> KeyboardThread::extractIPPort(string &host) {
    char_separator<char> sep(":");
    vector<string> parameters = vector<string>();
    tokenizer<char_separator<char>> tokens(host, sep);
    for (const auto &t : tokens) {
        parameters.emplace_back(t);
    }
    return parameters;
}

bool KeyboardThread::setConnectionHandler(string &_ip, string &_port) {
    stringstream parse(_port);
    short port;
    parse >> port;
    this->connectionHandler->setIpandPort(_ip, port);
    return connectionHandler->connect();

}

void KeyboardThread::send(AbstractFrame *frame) {
    //boost::lock_guard<boost::mutex> lock(_mutex); //locks the mutex which sould be associate with the connectionhandler
    this->connectionHandler->sendFrameAscii(frame->toString(), '\0');
    receiptId_frame.emplace_back(make_pair(frame->getHeaders().at(frame->getHeaders().size()-1).second, frame));
}

void KeyboardThread::run() {
    cout << "Keyboard Thread is set up" << endl;
    while (!messageProtocol.ShouldTerminate() && !logout) {
        string user_input;
        cout<<"Enter Command"<<endl;
        getline(cin, user_input); //blocking?

        vector<string> parameters = getParameters(user_input);
        AbstractFrame *frame=nullptr;

        //region Framing user input and send to server
        if (parameters.at(0) == "login") {
            if(!this->connectionHandler->getActive()){
            string connection_details = parameters.at(1);
            string ip = extractIPPort(parameters.at(1)).at(0);
            string port = extractIPPort(parameters.at(1)).at(1);
            if (!connectionHandler->getActive() ){
                setConnectionHandler(ip, port);
            }
            string login = parameters.at(2);
            this->setUserName(login);
            string password = parameters.at(3);
            frame = new Connect("1.2", ip, login, password);
            send(frame);
            }
            else{cout<< "User already logged in. Logout before attempting to login again"<<endl;}
        }
        else if (parameters.at(0) == "join"&& this->connectionHandler->getActive() && parameters.size()>1) {
            string des = parameters.at(1);
            if(!isSubscribe(des)) {
                string subid = to_string(subscribe(des));
                frame = new Subscribe(des, subid, getNextReceipt());
                send(frame);
            }
            else {cout << "user is already subscribe to this channel:"<< des<< endl;}
        }
        else if (parameters.at(0) == "add"&& this->connectionHandler->getActive() && parameters.size()>2) {
            string dest = parameters.at(1);
            string bookName = concateBookname(parameters);
            this->inventory.addBook(bookName,dest ,this->userName);
            frame = new Send(dest, userName + " has added the book " + bookName);
            send(frame);
        }
        else if (parameters.at(0) == "borrow"&& this->connectionHandler->getActive() && parameters.size()>2 ){
            string dest = parameters.at(1);
            string bookName = concateBookname(parameters);
            this->inventory.askBook(bookName);
            frame = new Send(dest, userName + " wish to borrow " + bookName);
            send(frame);
        }
        else if (parameters.at(0) =="return" && this->connectionHandler->getActive() && parameters.size()>2 ){//TODO: in the forum they said to earse the book from the inventory of the lend man
            string dest = parameters.at(1);
            string bookName = concateBookname(parameters);
            string owner = inventory.returnBook(bookName);
            if(owner!="" ){
            frame = new Send(dest, "Returning " + bookName + " to " + owner);
            send(frame);
            }
        }
        else if (parameters.at(0) == "status"&& this->connectionHandler->getActive() && parameters.size()>1) {
            string dest = parameters.at(1);
            frame = new Send(dest, "book status");
            send(frame);
        }
        else if (parameters.at(0) == "logout") {
            if(this->connectionHandler->getActive()) {
                //this->inventory.clearInventory();
                frame = new Disconnect(getNextReceipt());
                send(frame);
                logout=true;
            }
            else{cout<< "There is no user logged in"<<endl;}
        }
        else if (parameters.at(0) == "bye") {
            this->messageProtocol.terminateProtocol();
            this->messageProtocol.terminateConnectionHandler();
            logout=true;
        }
        else if (parameters.at(0) == "exit"&& this->connectionHandler->getActive() && parameters.size()>1) {
            string dest = parameters.at(1);
            if(isSubscribe(dest)) {
                string subid = to_string(unsubscribe(dest));
                frame = new Unsubscribe(subid, getNextReceipt(), dest);
                send(frame);
            } else{ cout <<"user is not subscribe to this channel:"<< dest << endl;}
        }
        else if(this->connectionHandler->getActive()){
            cout<<"No valid command, please retype"<<endl;
        }
        //endregion
    }

}

string KeyboardThread::getNextReceipt() {
    int temp = receipt;
    receipt++;
    return to_string(temp);
}

void KeyboardThread::setUserName(string username) {
    this->userName = username;
    this->inventory.setUsername(username);
}

void KeyboardThread::setNetworkThread(NetworkThread *_networkthread) {
    this->networkThread = _networkthread;
}

int KeyboardThread::getNextSubscriptionId() {
    int temp = this->subscription_id;
    this->subscription_id++;
    return temp;
}

int KeyboardThread::subscribe(string channel) {
    int subid = getNextSubscriptionId();
    subscriptionList.emplace_back(make_pair(channel, subid));
    return subid;
}

int KeyboardThread::unsubscribe(string channel) {
    int subid = find(subscriptionList.begin(), subscriptionList.end(),
                     make_pair(channel, getSubscriptionid(channel)))->second;
    subscriptionList.erase(
            find(subscriptionList.begin(), subscriptionList.end(), make_pair(channel, getSubscriptionid(channel))));
    return subid;
}

int KeyboardThread::getSubscriptionid(string channel) {
    for (auto pair: subscriptionList) {
        if (pair.first == channel)
            return pair.second;
    }
    return -1;
}

KeyboardThread::~KeyboardThread() {}

string KeyboardThread::concateBookname(vector<string> parameters) {
    string output;
    for(auto param:parameters){
        if(param!=parameters.at(0) && param!=parameters.at(1)){
            output=output+param+" ";
        }
    }
    return output.substr(0,output.size()-1);
}

bool KeyboardThread::isSubscribe(string genre) {
    for(auto pair: subscriptionList){
        if(pair.first== genre){
            return true;
        }
    }
    return false;
}



