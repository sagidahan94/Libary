//
// Created by hachamto@wincs.cs.bgu.ac.il on 04/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_RECEIPT_H
#define BOOST_ECHO_CLIENT_RECEIPT_H


#include <string>
#include "Frames/AbstractFrame.h"

using namespace std;

class Receipt :public AbstractFrame{

public:
    Receipt(string receipt);
    ~Receipt();
    void process() override;
};


#endif //BOOST_ECHO_CLIENT_RECEIPT_H
