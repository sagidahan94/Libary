//
// Created by hachamto@wincs.cs.bgu.ac.il on 04/01/2020.
//

#include <vector>
#include <iostream>
#include <Frames/ServerFrames/Connected.h>
#include <Frames/AbstractFrame.h>

//Connected::Connected(string version,string user_id) : AbstractFrame("CONNECTED") {
Connected::Connected(string version) : AbstractFrame("CONNECTED") {
    vector<pair<string,string>> headers;
    headers.emplace_back("version:",version);
    //headers.emplace_back("id:",user_id);
    setHeaders(headers);
}

/*Connected::Connected(const Connected &other) : AbstractFrame(other) {}

Connected::Connected(Connected &&other):AbstractFrame(other) {}*/

Connected::~Connected() {}

void Connected::process() {
    cout<<"Login Successful."<<endl;
}
