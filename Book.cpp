#include "Book.h"
#include <iostream>
#include <sstream>

using namespace std;

// Constructors
Book::Book() : Resource() {
    this->yearPublished = 0;
    this->numberPages = 0;
    this->collection = "Unknown";
    this->summary = "No summary available.";
}

Book::Book(const string& title, const string& author, bool borrowed,
           int yearPublished, int numberPages, const string& collection, const string& summary)
    : Resource(title, author, borrowed) {
    this->yearPublished = yearPublished;
    this->numberPages = numberPages;
    this->collection = collection;
    this->summary = summary;
}

// Getters
int Book::getYearPublished() const {
    return this->yearPublished;
}
int Book::getNumberPages() const {
    return this->numberPages;
}
string Book::getCollection() const {
    return this->collection;
}
string Book::getSummary() const {
    return this->summary;
}

// Setters
void Book::setYearPublished(int year) {
    this->yearPublished = year;
}
void Book::setNumberPages(int pages) {
    this->numberPages = pages;
}
void Book::setCollection(const string& collection) {
    this->collection = collection;
}
void Book::setSummary(const string& summary) {
    this->summary = summary;
}

// Méthodes d'affichage
void Book::compactedDisplay() const {
    Resource::compactedDisplay();
    cout << " - " << yearPublished << ", " << numberPages << " pages"
         << ", Collection: " << collection << endl;
}
void Book::detailedDisplay() const {
    Resource::detailedDisplay();
    cout << "Year Published: " << yearPublished << endl;
    cout << "Number of Pages: " << numberPages << endl;
    cout << "Collection: " << collection << endl;
    cout << "Summary: " << summary << endl;
}
string Book::toString() const {
    ostringstream oss;
    oss << Resource::toString() << "," << yearPublished << "," << numberPages
        << "," << collection << "," << summary;
    return oss.str();
}