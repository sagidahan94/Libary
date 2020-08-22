//
// Created by hachamto@wincs.cs.bgu.ac.il on 11/01/2020.
//

#include <iostream>
#include "Client/Data/Inventory.h"

Inventory::Inventory():mybooks(vector<Book*>()), wishlist(vector<string>()), username(""){}
Inventory::~Inventory() {
    for(auto book: mybooks){
        if(book!= nullptr){
        delete book;}
    }
    mybooks.clear();
    wishlist.clear();
}


void Inventory::addBook(string name, string genre,string owner) {
    mybooks.emplace_back(new Book(name,genre ,owner));
}

//changing the availability flag to false;
void Inventory::lendBook(string bookname) {
    for(auto book : mybooks){
        if(book->getName()==bookname){
            book->setAvailability(false);
        }
    }
}
void Inventory::receivedBook(string bookname) {
    for (auto book : mybooks) {
        if (book->getName() == bookname) {
            book->setAvailability(true);
        }
    }
}

//removing the book from the inventory
    string Inventory::returnBook(string bookname) {
    int index = 0;
    bool found = false;
    for (int i=0;i<mybooks.size() && !found;i++) {
        Book* book = mybooks.at(i);
        if (book->getName() == bookname && book->isAvailability()) {
            found = true;
            index=i;
        }
    }
    if (found) {
        Book *todelete = mybooks.at(index);
        if (todelete != nullptr) {
            if(todelete->getOwner()!=this->username) {
                mybooks.erase(mybooks.begin() + index);
                delete todelete;
                return todelete->getOwner();
            }
            else{cout<<"You cannot return book of yours"<<endl;}
        }
    }
    else{cout<<"Book is not found, are you sure it's in the inventory?"<<endl;}
    return "";
}
    void Inventory::askBook(string bookname) {
        wishlist.emplace_back(bookname);
    }
    bool Inventory::isBookInWishList(string bookname) {
        for (auto book:wishlist) {
            if (book == bookname) { return true; }
        }
        return false;
    }

Book * Inventory::findBook(string bookname) {
    for (auto book:mybooks) {
        if (book->getName() == bookname) {
            if(book->isAvailability()) {
                return book;
            }
        }
    }
    return nullptr;
}

void Inventory::setUsername(string username) {
    this->username=username;
}

string Inventory::getUsername() {
    return this->username;
}

string Inventory::getAvailableBooks(string genre) {
    string output= username+ ":";
    for(auto book:mybooks){
        if(book->isAvailability() && book->getGenre()==genre){
            output= output+ book->getName() +",";
        }
    }
    return output.substr(0,output.size()-1);
}

void Inventory::clearInventory() {
    for(auto book:mybooks){
        delete book;
    }
    wishlist.clear();

}

void Inventory::removeFromWishList(string bookname) {
    for(int i=0; i<wishlist.size();i++){
        if(wishlist.at(i)==bookname){
            wishlist.erase(wishlist.begin()+i);
        }
    }
}


//TODO: make a function that clear the inventory upon logout of the user


