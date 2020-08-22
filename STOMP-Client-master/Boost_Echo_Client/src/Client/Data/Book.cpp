//
// Created by hachamto@wincs.cs.bgu.ac.il on 11/01/2020.
//

#include <Client/Data/Book.h>

Book::Book(string name, string genre ,string owner):name(name), genre(genre) ,owner(owner), availability(true) {}

const string &Book::getName() const {
    return name;
}

void Book::setName(const string &name) {
    Book::name = name;
}

const string &Book::getOwner() const {
    return owner;
}

void Book::setOwner(const string &owner) {
    Book::owner = owner;
}

bool Book::isAvailability() const {
    return availability;
}

void Book::setAvailability(bool availability) {
    Book::availability = availability;
}

const string &Book::getGenre() const {
    return genre;
}

Book::~Book() {
}
