//
// Created by sagidaha@wincs.cs.bgu.ac.il on 03/01/2020.
//

#include <string>
#include <vector>
#include <iostream>
#include <Frames/AbstractFrame.h>

using namespace std;


AbstractFrame::AbstractFrame(string command) : command(command), body(""), endOfFrame('\0') ,headers(vector<pair<string,string>>()) {}

AbstractFrame::~AbstractFrame() {
    headers.clear();
}

string AbstractFrame::getCommand() {
    return this->command;
}

void AbstractFrame::SetCommand(string command) {
    this->command = command;
}

vector<pair<string, string>> AbstractFrame::getHeaders() {
    return this->headers;
}

void AbstractFrame::setHeaders(vector<pair<string, string>> &headers) {
    this->headers = headers;
}

string AbstractFrame::getBody() {
    return this->body;
}

void AbstractFrame::setBody(string &body) {
    this->body = body;
}

string AbstractFrame::toString() {
    string output = "";
    output = output + command + '\n';
    output = output + headers_concate();
    output = output + '\n';
    output = output + body;
    output = output + '\n';
    //output= output+ endOfFrame;
    return output;
}

/*byte AbstractFrame::getBytes() {
    return nullptr;
}*/
string AbstractFrame::headers_concate() {
    string _headers = "";
    for (auto header: headers) {
        _headers = _headers + header.first + header.second + '\n';
    }
    return _headers;
}

void AbstractFrame::process() {
}





