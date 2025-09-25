#ifndef PROJETCPP_DVD_H
#define PROJETCPP_DVD_H
#include "CD.h"


class DVD : public CD{
    public:
        using CD::CD; // héritage de CD
        // Constructors
        DVD(); // Default constructor
        DVD(const std::string& title, const std::string& author,
           int secondesDuration, int numberTracks, const std::string& productionCompany);
        // Méthodes de recherche
        std::string getType() const override {
            return "DVD";
        }
};


#endif //PROJETCPP_DVD_H