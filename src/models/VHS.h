#ifndef PROJETCPP_VHS_H
#define PROJETCPP_VHS_H
#include "Resource.h"


class VHS : public Resource{
    private:
        int secondesDuration;
        std::string productionCompany;
    public:
        using Resource::Resource; // héritage de Resource
        // Constructors
        VHS(); // Default constructor
        VHS(const std::string& title, const std::string& author, bool borrowed,
           int secondesDuration, const std::string& productionCompany);

        // Getters
        int getSecondesDuration() const;
        std::string getProductionCompany() const;

        // Setters
        void setSecondesDuration(int duration);
        void setProductionCompany(const std::string& company);

        // Méthodes d'affichage
        void compactedDisplay() const;
        void detailedDisplay() const;
        std::string toString() const;

        // Méthodes de recherche
        std::string getType() const override {
            return "VHS";
        }

};


#endif //PROJETCPP_VHS_H