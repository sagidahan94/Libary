//
// Created by hachamto@wincs.cs.bgu.ac.il on 09/01/2020.
//

#include "Frames/AbstractFrame.h"

#ifndef BOOST_ECHO_CLIENT_UNSUBSCRIBE_H
#define BOOST_ECHO_CLIENT_UNSUBSCRIBE_H

#endif //BOOST_ECHO_CLIENT_UNSUBSCRIBE_H
using namespace std;

class Unsubscribe: public AbstractFrame {
public:
    Unsubscribe(string id, string receipt, string channel);
    ~Unsubscribe();
    void process() override;
    const string &getChannel() const;
private:
    string channel;
};