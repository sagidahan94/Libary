//
// Created by hachamto@wincs.cs.bgu.ac.il on 04/01/2020.
//

#include <vector>
#include <Frames/ServerFrames/Receipt.h>

Receipt::Receipt(string receipt) : AbstractFrame("RECEIPT") {
    vector<pair<string,string>> headers;
    headers.emplace_back("receipt-id:",receipt);
    setHeaders(headers);
}
Receipt::~Receipt() {

}

void Receipt::process() {
}


