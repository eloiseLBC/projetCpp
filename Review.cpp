#include "Review.h"
#include <iostream>
#include <sstream>

using namespace std;

// Constructors
Review::Review() : Book() {
    this->editor = "Unknown";
    this->numberArticles = 0;
}
Review::Review(const string& title, const string& author, bool borrowed,
               int publicationYear, int numberPages, const string& genre,
               const string& summary, const string& editor, int numberArticles)
    : Book(title, author, borrowed, publicationYear, numberPages, genre, summary) {
    this->editor = editor;
    this->numberArticles = numberArticles;
}

// Getters
string Review::getEditor() const {
    return this->editor;
}
int Review::getNumberArticles() const {
    return this->numberArticles;
}

// Setters
void Review::setEditor(const string& editor) {
    this->editor = editor;
}
void Review::setNumberArticles(int numberArticles) {
    this->numberArticles = numberArticles;
}

// Méthodes d'affichage
void Review::compactedDisplay() const {
    Book::compactedDisplay();
    cout << " - Editor: " << editor << ", Articles: " << numberArticles << endl;
}
void Review::detailedDisplay() const {
    Book::detailedDisplay();
    cout << "Editor: " << editor << endl;
    cout << "Number of Articles: " << numberArticles << endl;
}
string Review::toString() const {
    return Book::toString() + "," + editor + "," + to_string(numberArticles);
}


