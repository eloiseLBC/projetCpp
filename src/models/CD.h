#ifndef PROJETCPP_CD_H
#define PROJETCPP_CD_H
#include "VHS.h"


class CD : public VHS {
    private:
        int numberTracks;
    public:
        using VHS::VHS; // héritage de VHS
        // Constructors
        CD(); // Default constructor
        CD(const std::string& title, const std::string& author,
           int secondesDuration, int numberTracks, const std::string& productionCompany);

        // Getters
        int getNumberTracks() const;

        // Setters
        void setNumberTracks(int tracks);

        // Méthodes d'affichage
        void compactedDisplay() const;
        void detailedDisplay() const;
        std::string toString() const;

        // Méthodes de recherche
        std::string getType() const override {
            return "CD";
        }
        bool contains(const std::string &search);

};


#endif //PROJETCPP_CD_H