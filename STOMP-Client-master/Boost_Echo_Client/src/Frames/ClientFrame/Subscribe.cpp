//
// Created by sagidaha@wincs.cs.bgu.ac.il on 03/01/2020.
//

#include <vector>
#include <Frames/ClientFrames/Subscribe.h>
#include <iostream>

Subscribe::Subscribe(string destination, string id, string receipt) : AbstractFrame("SUBSCRIBE") {
    pair<string, string> des;
    des.first = "destination:";
    des.second = destination;
    pair<string, string> ID;
    ID.first = "id:";
    ID.second = id;
    pair<string, string> rec;
    rec.first = "receipt:";
    rec.second = receipt;
    vector<pair<string, string >> hed;
    hed.push_back(des);
    hed.push_back(ID);
    hed.push_back(rec);
    AbstractFrame::setHeaders(hed);

}
Subscribe::~Subscribe() {

}
void Subscribe::process() {
    cout << "Joined club "+ this->getHeaders().at(0).second << endl;
}


