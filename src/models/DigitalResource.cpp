#include "DigitalResource.h"
#include <iostream>
#include <sstream>
using namespace std;

// Constructors
DigitalResource::DigitalResource() : Resource() {
    this->type = "Unknown";
    this->bytes = 0;
    this->path = "Unknown";
}

DigitalResource::DigitalResource(const string& title, const string& author, const string& type, int bytes, const string& path) : Resource(title, author) {
    this->type = type;
    this->bytes = bytes;
    this->path = path;
}

// Getters
string DigitalResource::getTypeDigitalResource() const {
    return this->type;
}
int DigitalResource::getBytes() const {
    return this->bytes;
}
string DigitalResource::getPath() const {
    return this->path;
}

// Setters
void DigitalResource::setTypeDigitalResource(const string& type) {
    this->type = type;
}
void DigitalResource::setBytes(int bytes) {
    this->bytes = bytes;
}
void DigitalResource::setPath(const string& path) {
    this->path = path;
}

// Méthodes d'affichage
void DigitalResource::compactedDisplay() const {
    Resource::compactedDisplay();
    cout << " - " << type << ", " << bytes << " bytes" << endl;
}
void DigitalResource::detailedDisplay() const {
    Resource::detailedDisplay();
    cout << "Type: " << type << endl;
    cout << "Size (bytes): " << bytes << endl;
    cout << "Path: " << path << endl;
}
string DigitalResource::toString() const {
    return Resource::toString() + ";" + type + ";" + to_string(bytes) + ";" + path;
}

bool DigitalResource::contains(const string& search) {
    return Resource::contains(search) ||
           type.find(search) != string::npos ||
           path.find(search) != string::npos ;
}
