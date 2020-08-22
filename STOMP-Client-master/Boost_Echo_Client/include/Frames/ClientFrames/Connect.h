//
// Created by sagidaha@wincs.cs.bgu.ac.il on 03/01/2020.
//

#ifndef STOMP_CLIENT_CONNECT_H
#define STOMP_CLIENT_CONNECT_H

#include <string>
#include "Frames/AbstractFrame.h"
using namespace std;

class Connect : public AbstractFrame {
public:
    Connect(string version, string host, string login, string passcode);
    Connect(const Connect& other);
    ~Connect();
    void process() override;
};


#endif //STOMP_CLIENT_CONNECT_H
