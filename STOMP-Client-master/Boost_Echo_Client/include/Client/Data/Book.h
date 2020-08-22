//
// Created by hachamto@wincs.cs.bgu.ac.il on 11/01/2020.
//

#ifndef BOOST_ECHO_CLIENT_BOOK_H
#define BOOST_ECHO_CLIENT_BOOK_H
#include <string>

using namespace std;

class Book {
public:
    Book(string name, string genre,string owner);
    ~Book();

private:
public:
    const string &getName() const;

    void setName(const string &name);

    void setGenre(const string &genre);

    const string &getOwner() const;

    void setOwner(const string &owner);

    bool isAvailability() const;

    void setAvailability(bool availability);

private:
    string name;
    string genre;
public:
    const string &getGenre() const;

private:
    string owner;
    bool availability;

};


#endif //BOOST_ECHO_CLIENT_BOOK_H
