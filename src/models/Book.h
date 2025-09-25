#ifndef PROJETCPP_BOOK_H
#define PROJETCPP_BOOK_H
#include "Resource.h"


class Book : public Resource {
    private:
        int yearPublished;
        int numberPages;
        std::string collection;
        std::string summary;
    public:
        using Resource::Resource; // héritage de Resource
        // Constructors
        Book(); // Default constructor
        Book(const std::string& title, const std::string& author,
             int yearPublished, int numberPages, const std::string& collection, const std::string& summary);
        Book(const std::string& id, const std::string& title, const std::string& author, bool borrowed,
            int yearPublished, int numberPages, const std::string& collection, const std::string& summary);

        // Getters
        int getYearPublished() const;
        int getNumberPages() const;
        std::string getCollection() const;
        std::string getSummary() const;

        // Setters
        void setYearPublished(int year);
        void setNumberPages(int pages);
        void setCollection(const std::string& collection);
        void setSummary(const std::string& summary);

        // Méthodes d'affichage
        void compactedDisplay() const;
        void detailedDisplay() const;
        std::string toString() const;

        // Méthodes de recherche
        std::string getType() const override {
            return "Book";
        }
        bool contains(const std::string& search);
};
#endif //PROJETCPP_BOOK_H