#ifndef PROJETCPP_RESOURCE_H
#define PROJETCPP_RESOURCE_H

#include <string>

class Resource {
    private:
        std::string id;
        std::string title;
        std::string author;
        bool borrowed;

        static std::string generateUID();
    public:
        // Constructors
        Resource(); // Default constructor
        Resource(const std::string& title, const std::string& author, bool borrowed);

        // Getters
        std::string getId();
        std::string getTitle();
        std::string getAuthor();
        bool getBorrowed();

        // Setters
        void setTitle(const std::string title);
        void setAuthor(const std::string author);
        void setBorrowed(const bool borrowed);

        // Méthodes d'affichage
        void compactedDisplay() const;
        void detailedDisplay() const;
        std::string toString() const;

        // Méthodes de recherche
        bool contains(std::string search);
        virtual std::string getType() const { return "Resource"; }
};

#endif //PROJETCPP_RESOURCE_H