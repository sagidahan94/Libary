//
// Created by sagidaha@wincs.cs.bgu.ac.il on 04/01/2020.
//


#include <vector>
#include <Frames/ServerFrames/Disconnect.h>

Disconnect::Disconnect(string receipt) : AbstractFrame("DISCONNECT") {
    pair<string,string> des;
    des.first= "receipt:";
    des.second= receipt;
    vector<pair<string ,string >> hed;
    hed.push_back(des);
    AbstractFrame::setHeaders(hed);
}

Disconnect::~Disconnect() {
}

