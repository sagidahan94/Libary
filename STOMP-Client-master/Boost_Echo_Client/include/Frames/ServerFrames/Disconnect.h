//
// Created by sagidaha@wincs.cs.bgu.ac.il on 04/01/2020.
//

#include <string>
#include "Frames/AbstractFrame.h"

#ifndef BOOST_ECHO_CLIENT_DISCONNECT_H
#define BOOST_ECHO_CLIENT_DISCONNECT_H

#endif //BOOST_ECHO_CLIENT_DISCONNECT_H

using namespace std;

class Disconnect : public AbstractFrame{
public:
    Disconnect(string recipt);
    ~Disconnect();

};