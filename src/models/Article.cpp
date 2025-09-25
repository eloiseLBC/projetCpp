#include "Article.h"
#include <iostream>
#include <sstream>

using namespace std;

// Constructors
Article::Article() : Review() {
    this->name = "Unknown";
}
Article::Article(const string& title, const string& author,
                 int publicationYear, int numberPages, const string& genre,
                 const string& summary, const string& editor, int numberArticles,
                 const string& name)
    : Review(title, author, publicationYear, numberPages, genre, summary, editor, numberArticles) {
    this->name = name;
}

Article::Article(const std::string &id, const std::string &title, const std::string &author, bool borrowed, int publicationYear, int numberPages, const std::string &genre, const std::string &summary, const std::string &editor, int numberArticles, const std::string &name)
    : Review(id, title, author, borrowed, publicationYear, numberPages, genre, summary, editor, numberArticles) {
    this->name = name;
}


// Getters
string Article::getName() const {
    return this->name;
}
// Setters
void Article::setName(const string& name) {
    this->name = name;
}
// Méthodes d'affichage
void Article::compactedDisplay() const {
    Review::compactedDisplay();
    cout << " - Article Name: " << name << endl;
}

void Article::detailedDisplay() const {
    Review::detailedDisplay();
    cout << "Article Name: " << name << endl;
}
string Article::toString() const {
    return Review::toString() + ";" + name;
}

bool Article::contains(const string& search) {
    return getTitle().find(search) != std::string::npos ||
            getAuthor().find(search) != std::string::npos ||
            getEditor().find(search) !=  std::string::npos ||
            getCollection().find(search) !=  std::string::npos ||
            name.find(search) != std::string::npos ||
            getSummary().find(search) != std::string::npos;
}