//
// Created by sagidaha@wincs.cs.bgu.ac.il on 03/01/2020.
//

#ifndef STOMP_CLIENT_SEND_H
#define STOMP_CLIENT_SEND_H


#include <string>
#include "Frames/AbstractFrame.h"
using namespace std;


class Send : public AbstractFrame {
public:
    Send(string destination, string body);
    ~Send();
    void process() override;
};


#endif //STOMP_CLIENT_SEND_H
