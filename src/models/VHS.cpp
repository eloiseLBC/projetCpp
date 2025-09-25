#include "VHS.h"
#include <iostream>
#include <sstream>

using namespace std;

// Constructors
VHS::VHS() : Resource() {
    this->secondesDuration = 0;
    this->productionCompany = "Unknown";
}
VHS::VHS(const string& title, const string& author,
         int secondesDuration, const string& productionCompany)
    : Resource(title, author) {
    this->secondesDuration = secondesDuration;
    this->productionCompany = productionCompany;
}

// Getters
int VHS::getSecondesDuration() const {
    return this->secondesDuration;
}
string VHS::getProductionCompany() const {
    return this->productionCompany;
}

// Setters
void VHS::setSecondesDuration(int duration) {
    this->secondesDuration = duration;
}
void VHS::setProductionCompany(const string& company) {
    this->productionCompany = company;
}

// Méthodes d'affichage
void VHS::compactedDisplay() const {
    Resource::compactedDisplay();
    cout << " - " << secondesDuration << " sec" << endl;
}
void VHS::detailedDisplay() const {
    Resource::detailedDisplay();
    cout << "Duration (sec): " << secondesDuration << endl;
    cout << "Production Company: " << productionCompany << endl;
}
string VHS::toString() const {
    return Resource::toString() + ";" + to_string(secondesDuration) + ";" + productionCompany;
}

// Méthodes de recherche
bool VHS::contains(const string& search) {
    return Resource::contains(search) ||
           productionCompany.find(search) != string::npos;
}