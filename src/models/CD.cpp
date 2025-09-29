#include "CD.h"
#include <iostream>
#include <sstream>

using namespace std;

// Constructors
CD::CD() : VHS() {
    this->numberTracks = 0;
}
CD::CD(const string& title, const string& author,
       int secondesDuration, int numberTracks, const string& productionCompany)
    : VHS(title, author, secondesDuration, productionCompany) {
    this->numberTracks = numberTracks;
}

CD::CD(const std::string &id, const std::string &title, const std::string &author, bool borrowed, int secondesDuration, int numberTracks, const std::string &productionCompany)
    : VHS(id, title, author, borrowed, secondesDuration, productionCompany) {
    this->numberTracks = numberTracks;
}


// Getters
int CD::getNumberTracks() const {
    return this->numberTracks;
}

// Setters
void CD::setNumberTracks(int tracks) {
    this->numberTracks = tracks;
}
// Méthodes d'affichage
void CD::compactedDisplay() const {
    VHS::compactedDisplay();
    cout << " - " << to_string(numberTracks) << " tracks" << endl;
}
void CD::detailedDisplay() const {
    VHS::detailedDisplay();
    cout << "Nombre de pistes: " << to_string(numberTracks) << endl;
}
string CD::toString() const {
    return VHS::toString() + ";" + to_string(numberTracks);
}

// Méthodes de recherche
bool CD::contains(const string& search) {
    return VHS::contains(search);
}
