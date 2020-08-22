//
// Created by sagidaha@wincs.cs.bgu.ac.il on 03/01/2020.
//

#include <vector>
#include <Frames/ClientFrames/Connect.h>
#include <iostream>


Connect::Connect(string version, string host, string login, string passcode) : AbstractFrame("CONNECT") {
    pair<string ,string > ver;
    ver.first= "accept-version:";
    ver.second= version;
    pair<string ,string > hos;
    hos.first= "host:";
    hos.second= host;
    pair<string ,string > log;
    log.first= "login:";
    log.second= login;
    pair<string ,string > pass;
    pass.first= "passcode:";
    pass.second= passcode;

    vector<pair<string,string >> hed;
    hed.emplace_back(ver);
    hed.emplace_back(hos);
    hed.emplace_back(log);
    hed.emplace_back(pass);

    AbstractFrame::setHeaders(hed);
}
Connect::~Connect() {}

void Connect::process() {
    cout << "Login successful." << endl;
}


