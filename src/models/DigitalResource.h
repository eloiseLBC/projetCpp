#ifndef PROJETCPP_DIGITALRESOURCE_H
#define PROJETCPP_DIGITALRESOURCE_H
#include <string>
#include "Resource.h"


class DigitalResource : public Resource {
    private:
        std::string type;
        int bytes;
        std::string path;
    public:
        // Constructors
        DigitalResource();
        DigitalResource(const std::string& title, const std::string& author,
            const std::string& type, int bytes, const std::string& path);

        // Getters
        std::string getTypeDigitalResource() const;
        int getBytes() const;
        std::string getPath() const;

        // Setters
        void setTypeDigitalResource(const std::string& type);
        void setBytes(int bytes);
        void setPath(const std::string& path);

        // Méthodes d'affichage
        void compactedDisplay() const;
        void detailedDisplay() const;
        std::string toString() const;

        // Méthodes de recherche
        std::string getType() const override {
            return "Digital Resource";
        }
        bool contains(const std::string& search);
};


#endif //PROJETCPP_DIGITALRESOURCE_H