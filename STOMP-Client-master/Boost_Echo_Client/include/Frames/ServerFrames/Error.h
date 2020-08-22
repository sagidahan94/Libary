//
// Created by hachamto@wincs.cs.bgu.ac.il on 04/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_ERROR_H
#define BOOST_ECHO_CLIENT_ERROR_H


#include <string>
#include "Frames/AbstractFrame.h"

class Error : public AbstractFrame{
    public:
    Error(string receipt,string message, string body);
    ~Error();
    void process();
};

#endif //BOOST_ECHO_CLIENT_ERROR_H
