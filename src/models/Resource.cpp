#include "Resource.h"
#include <random>
# include <iostream>

using namespace std;

string Resource::generateUID() {
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    static const int len = 10; // Length of the UID
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);

    string uid;
    for (int i = 0; i < len; ++i) {
        uid += alphanum[dis(gen)];
    }
    return uid;
}

Resource::Resource() {
    this->id = Resource::generateUID();
    this->title = "Unknown";
    this->author = "Unknown";
    this->borrowed = false;
}

Resource::Resource(const string& title, const string& author) {
    this->id = Resource::generateUID();
    this->title = title;
    this->author = author;
    this->borrowed = 0;
}

// Getters
string Resource::getId() {
    return this->id;
}

string Resource::getTitle() {
    return this->title;
}

string Resource::getAuthor() {
    return this->author;
}

bool Resource::getBorrowed() {
    return this->borrowed;
}

// Setters
void Resource::setTitle(const string title) {
    this->title = title;
}

void Resource::setAuthor(const std::string author) {
    this->author = author;
}

void Resource::setBorrowed(const bool borrowed) {
    this->borrowed = borrowed;
}

// Méthodes d'affichage
void Resource::compactedDisplay() const {
    cout << "[" << id << "] " << title << " by " << author
         << (borrowed ? " (Borrowed)" : " (Available)") << endl;
}

void Resource::detailedDisplay() const {
    cout << "Resource ID: " << id << endl;
    cout << "Title: " << title << endl;
    cout << "Author: " << author << endl;
    cout << "Status: " << (borrowed ? "Borrowed" : "Available") << endl;
}

string Resource::toString() const {
    return getType() + ";" + id + ";" + title + ";" + author + ";" + (borrowed ? "1" : "0");
}

// Méthodes de recherche
bool Resource::contains(string search) {
    return (title.find(search) != string::npos) || (author.find(search) != string::npos);
}




