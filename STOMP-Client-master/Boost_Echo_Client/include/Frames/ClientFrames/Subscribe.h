//
// Created by sagidaha@wincs.cs.bgu.ac.il on 03/01/2020.
//

#ifndef STOMP_CLIENT_SUBSCRIBE_H
#define STOMP_CLIENT_SUBSCRIBE_H

#include <string>
#include "Frames/AbstractFrame.h"

using namespace std;

class Subscribe : public AbstractFrame{
public:
    Subscribe(string destination, string id, string receipt);
    ~Subscribe();
    void process() override;
};


#endif //STOMP_CLIENT_SUBSCRIBE_H
