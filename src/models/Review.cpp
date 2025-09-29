#include "Review.h"
#include <iostream>
#include <sstream>

using namespace std;

// Constructors
Review::Review() : Book() {
    this->editor = "Unknown";
    this->numberArticles = 0;
}
Review::Review(const string& title, const string& author,
               int publicationYear, int numberPages, const string& genre,
               const string& summary, const string& editor, int numberArticles)
    : Book(title, author, publicationYear, numberPages, genre, summary) {
    this->editor = editor;
    this->numberArticles = numberArticles;

    for (int i = 0; i < numberArticles; i++) {
        string articleName;
        std::cout << "Entrez le nom de l'article n°" << i+1 << " : ";
        std::cin.ignore(); // Pour ignorer le caractère de nouvelle ligne restant
        std::getline(std::cin, articleName); // Pour lire le nom complet avec espaces
        articlesName.push_back(articleName); // Ajoute l'article au vecteur
    }

    this->articlesName = articlesName; // Sauvegarde le vecteur dans l'attribut de classe

}

Review::Review(const string &id, const string &title, const string &author, bool borrowed, int publicationYear, int numberPages, const string &genre, const string &summary, const string &editor, int numberArticles)
    : Book(id, title, author, borrowed, publicationYear, numberPages, genre, summary) {
    this->editor = editor;
    this->numberArticles = numberArticles;

    for (int i = 0; i < numberArticles; i++) {
        string articleName;
        std::cout << "Entrez le nom de l'article n°" << i+1 << " : ";
        std::cin.ignore(); // Pour ignorer le caractère de nouvelle ligne restant
        std::getline(std::cin, articleName); // Pour lire le nom complet avec espaces
        articlesName.push_back(articleName); // Ajoute l'article au vecteur
    }

    this->articlesName = articlesName; // Sauvegarde le vecteur dans l'attribut de classe
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
    cout << "Number of Articles: " << to_string(numberArticles) << endl;
}
string Review::toString() const {
    int i = 0;
    for (i; i < numberArticles; i++) {
        // Get the article name
        string name = articlesName[i];
    }
    string articlesConcatenated = "[";
    for (i = 0; i < numberArticles; i++) {
        articlesConcatenated += articlesName[i];
        if (i < numberArticles - 1) {
            articlesConcatenated += ", ";
        }
    }
    articlesConcatenated += "]";
    return Book::toString() + ";" + editor + ";" + to_string(numberArticles) + ";" + articlesConcatenated;
}

bool Review::contains(const std::string &search) {
    return getTitle().find(search) != std::string::npos ||
           getAuthor().find(search) != std::string::npos ||
           editor.find(search) != std::string::npos ||
           getCollection().find(search) != std::string::npos ||
           getSummary().find(search) !=  std::string::npos ;
}



