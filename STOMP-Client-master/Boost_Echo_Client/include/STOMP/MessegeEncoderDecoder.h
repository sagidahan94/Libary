//
// Created by sagidaha@wincs.cs.bgu.ac.il on 04/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_MESSEGEDECODERENCODER_H
#define BOOST_ECHO_CLIENT_MESSEGEDECODERENCODER_H

#include <string>
#include <vector>
#include "Frames/AbstractFrame.h"

using namespace std;

class MessageEncoderDecoder {
public:
    MessageEncoderDecoder();
    ~MessageEncoderDecoder();

    //methods
    AbstractFrame* parser(string result);

private:
    const char endOfFrame{};
    AbstractFrame* InterpretServerFrame(string command, vector<string>* headers, string body);
    string header_parser(string header);


};




#endif //BOOST_ECHO_CLIENT_MESSEGEDECODERENCODER_H
