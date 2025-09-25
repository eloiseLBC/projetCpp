#include "DVD.h"

using namespace std;

// Constructors
DVD::DVD() : CD() {
}
DVD::DVD(const string& title, const string& author,
         int secondesDuration, int numberTracks, const string& productionCompany)
    : CD(title, author, secondesDuration, numberTracks, productionCompany) {
}

DVD::DVD(const std::string &id, const std::string &title, const std::string &author, bool borrowed, int secondesDuration, int numberTracks, const std::string &productionCompany)
    : CD(id, title, author, borrowed, secondesDuration, numberTracks, productionCompany) {
}