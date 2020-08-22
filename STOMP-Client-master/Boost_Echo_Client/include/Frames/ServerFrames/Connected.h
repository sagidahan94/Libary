//
// Created by hachamto@wincs.cs.bgu.ac.il on 04/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_CONNECTED_H
#define BOOST_ECHO_CLIENT_CONNECTED_H

#include <string>
#include <Frames/AbstractFrame.h>

using namespace std;

class Connected: public AbstractFrame {
public:

    Connected(string version);//,string user_id);
    void process() override;
    virtual ~Connected();
private:

};


#endif //BOOST_ECHO_CLIENT_CONNECTED_H
