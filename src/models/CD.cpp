#include "CD.h"
#include <iostream>
#include <sstream>

using namespace std;

// Constructors
CD::CD() : VHS() {
    this->numberTracks = 0;
}
CD::CD(const string& title, const string& author, bool borrowed,
       int secondesDuration, int numberTracks, const string& productionCompany)
    : VHS(title, author, borrowed, secondesDuration, productionCompany) {
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
    cout << " - " << numberTracks << " tracks" << endl;
}
void CD::detailedDisplay() const {
    VHS::detailedDisplay();
    cout << "Number of Tracks: " << numberTracks << endl;
}
string CD::toString() const {
    return VHS::toString() + ";" + to_string(numberTracks);
}

// Méthodes de recherche
bool CD::contains(const string& search) {
    return VHS::contains(search);
}
