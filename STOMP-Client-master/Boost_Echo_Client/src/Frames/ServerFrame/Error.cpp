//
// Created by hachamto@wincs.cs.bgu.ac.il on 04/01/2020.
//

#include <vector>
#include <iostream>
#include <Frames/ServerFrames/Error.h>
using namespace std;

Error::Error(string receipt, string message, string body) :AbstractFrame("ERROR"){
    vector<pair<string,string>> headers;
    headers.emplace_back("receipt:",receipt);
    headers.emplace_back("message:",message);
    setHeaders(headers);
    setBody(body);
}
Error::~Error() {

}

void Error::process() {
    cout<<"ERROR: "<<this->getHeaders().at(1).second<<endl;// will print the the error message
    //AbstractFrame::process();

}


