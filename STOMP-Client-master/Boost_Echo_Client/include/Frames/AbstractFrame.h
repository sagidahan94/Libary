//    AbstractFrame::setBody(body);

// Created by sagidaha@wincs.cs.bgu.ac.il on 03/01/2020.
//

#ifndef STOMP_CLIENT_ABSTRACTFRAME_H
#define STOMP_CLIENT_ABSTRACTFRAME_H

using namespace std;

#include <string>
#include <vector>

class AbstractFrame {

private:
    string command;
    string body;
    const char endOfFrame;
    vector<pair<string,string>> headers;
    string headers_concate();

public:
    //constructor and destructor:
    AbstractFrame (string command);
    virtual ~AbstractFrame();
    virtual void process();

    //methods:
     string getCommand();
     void SetCommand(string command);
     vector<pair<string,string>> getHeaders();
     void setHeaders(vector<pair<string,string>>&);
     void setBody(string&);
     string getBody();
     string toString();
};


#endif //STOMP_CLIENT_ABSTRACTFRAME_H
