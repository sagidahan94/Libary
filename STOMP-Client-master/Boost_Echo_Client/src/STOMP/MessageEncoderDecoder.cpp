//
// Created by hachamto@wincs.cs.bgu.ac.il on 04/01/2020.
//
#include <Frames/ServerFrames/Connected.h>
#include <Frames/ServerFrames/Error.h>
#include <Frames/ServerFrames/Receipt.h>
#include <Frames/ClientFrames/Message.h>
#include <iostream>
#include <STOMP/MessegeEncoderDecoder.h>
#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>

using namespace std;
using namespace boost;

MessageEncoderDecoder::MessageEncoderDecoder(): endOfFrame('\0'){}
MessageEncoderDecoder::~MessageEncoderDecoder() {
}

AbstractFrame* MessageEncoderDecoder::parser(string result) {
    int index=1;
    bool iscontainbody=true;
    string delimiter = "\n";
    string body;
    vector<string> parameters;
    vector<string>* headers = new vector<string>();
    size_t prev_pos = 0;


    size_t pos = 0;
    string token;
    while ((pos = result.find(delimiter)) != string::npos ) {
        token = result.substr(0, pos);
        if(index>1 & index!=-1)
        {
            string var = result.substr(pos,pos+1);
            if(var=="\n\n"){
                iscontainbody=false;
            }
            if(token!="" & token.find(":")!=string::npos ){
                parameters.emplace_back(header_parser(token));
                headers->emplace_back(header_parser(token));
            }
            else{index=-1;}

        }
        else if(token!=""){
            parameters.emplace_back(token);
        }
        index++;
        //cout << token << endl;
        result.erase(0, pos + delimiter.length());
        prev_pos=pos;
    }
    if(iscontainbody){
        body = token;
    }
    else{
        body = "";
    }
    string command = parameters.at(0);
    AbstractFrame* toreturn = InterpretServerFrame(command,headers,body);
    headers->clear();
    delete headers;
    return toreturn;
}

string MessageEncoderDecoder::header_parser(string header) {
    vector<string> parameters;
    char_separator<char> sep(":");
    tokenizer<char_separator<char>> tokens(header, sep);
    for (auto& t : tokens) {
        parameters.emplace_back(t);
       // cout << t << endl;
    }
    return parameters.at(1);
}

AbstractFrame* MessageEncoderDecoder::InterpretServerFrame(string command, vector<string>* headers, string body) {
    AbstractFrame *frame = nullptr;
    if (command == "CONNECTED") { frame = new Connected(headers->at(0)); }
    else if (command == "ERROR") { frame = new Error(headers->at(0), headers->at(1), body); }
    else if (command == "MESSAGE") {frame = new Message(headers->at(0), headers->at(1), headers->at(2), body);}
    else if (command == "RECEIPT") {frame = new Receipt(headers->at(0));//TODO: find which receipt is return and set the body
     }
    return frame;
}


