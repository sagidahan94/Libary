//
// Created by hachamto@wincs.cs.bgu.ac.il on 09/01/2020.
//

#include <Frames/ClientFrames/Unsubscribe.h>
#include <iostream>

Unsubscribe::Unsubscribe(string id, string receipt, string channel) : AbstractFrame("UNSUBSCRIBE"), channel(channel) {
    pair<string ,string > ID;
    ID.first="id:";
    ID.second=id;
    pair<string,string > rec;
    rec.first= "receipt:";
    rec.second= receipt;
    vector<pair<string ,string >> hed;
    hed.push_back(ID);
    hed.push_back(rec);
    AbstractFrame::setHeaders(hed);
}
Unsubscribe::~Unsubscribe() {

}

void Unsubscribe::process() {
    cout << "Exited club "+ channel << endl;
}

const string &Unsubscribe::getChannel() const {
    return channel;
}





