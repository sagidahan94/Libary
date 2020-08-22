//
// Created by hachamto@wincs.cs.bgu.ac.il on 04/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_MESSAGE_H
#define BOOST_ECHO_CLIENT_MESSAGE_H

#include <string>
#include "Frames/AbstractFrame.h"
using namespace std;

class Message :public AbstractFrame{

public:
    Message(string subscription, string messageId, string destination,string body);
    ~Message();
    void process() override;
};


#endif //BOOST_ECHO_CLIENT_MESSAGE_H
