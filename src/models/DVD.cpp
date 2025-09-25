#include "DVD.h"

using namespace std;

// Constructors
DVD::DVD() : CD() {
}
DVD::DVD(const string& title, const string& author,
         int secondesDuration, int numberTracks, const string& productionCompany)
    : CD(title, author, secondesDuration, numberTracks, productionCompany) {
}