//
// Created by hachamto@wincs.cs.bgu.ac.il on 04/01/2020.
//

#include <vector>
#include <iostream>
#include <Frames/ClientFrames/Message.h>

Message::Message(string subscription, string messageId, string destination, string body) :AbstractFrame("MESSAGE"){
    vector<pair<string,string>> headers;
    headers.emplace_back("subscription:",subscription);
    headers.emplace_back("Message-id:",messageId);
    headers.emplace_back("desination:",destination);
    setHeaders(headers);
    setBody(body);
}
Message::~Message() {

}

void Message::process() {
/*    size_t found = this->getBody().find("book status");
    if (found==string::npos){
        cout << this->getHeaders().at(2).second<<":"<<this->getBody() << endl;
    }*/
    cout << this->getHeaders().at(2).second<<":"<<this->getBody() << endl;

}


