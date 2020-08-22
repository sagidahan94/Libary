//
// Created by sagidaha@wincs.cs.bgu.ac.il on 03/01/2020.
//
#include <vector>
#include <string>
#include <Frames/ClientFrames/Send.h>
#include <Frames/AbstractFrame.h>
#include <iostream>

Send::Send(string destination, string body) : AbstractFrame("SEND") {
    pair<string,string > des;
    des.first="destination:";
    des.second= destination;

    vector<pair<string ,string >> hed;
    hed.push_back(des);

    AbstractFrame::setHeaders(hed);
    AbstractFrame::setBody(body);
}
Send::~Send() {

}

void Send::process() {
    cout << this->getBody() << endl;
}



