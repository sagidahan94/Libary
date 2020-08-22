//
// Created by hachamto@wincs.cs.bgu.ac.il on 11/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_INVENTORY_H
#define BOOST_ECHO_CLIENT_INVENTORY_H

#include <string>
#include <vector>
#include "Book.h"

using namespace std;

class Inventory {
public:
    Inventory();
    ~Inventory();
    Book* findBook(string bookname);
    void addBook(string name, string genre ,string owner);
    void lendBook(string bookname);
    string returnBook(string bookname);
    void askBook(string bookname);
    void receivedBook(string bookname);
    void setUsername(string username);
    string getUsername();
    string getAvailableBooks(string genre);
    bool isBookInWishList(string bookname);
    void clearInventory();
    void removeFromWishList(string bookname);

private:
   vector<Book*> mybooks;
   vector<string> wishlist;
   string username;
};


#endif //BOOST_ECHO_CLIENT_INVENTORY_H
