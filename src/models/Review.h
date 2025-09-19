#ifndef PROJETCPP_REVIEW_H
#define PROJETCPP_REVIEW_H
#include "Book.h"


class Review : public Book {
    private:
        std::string editor;
        int numberArticles;
    public:
        using Book::Book; // héritage de Book
        // Constructors
        Review();
        Review(const std::string& title, const std::string& author, bool borrowed,
               int publicationYear, int numberPages, const std::string& genre,
               const std::string& summary, const std::string& editor, int numberArticles);
        // Getters
        std::string getEditor() const;
        int getNumberArticles() const;

        // Setters
        void setEditor(const std::string& editor);
        void setNumberArticles(int numberArticles);

        // Méthodes d'affichage
        void compactedDisplay() const;
        void detailedDisplay() const;
        std::string toString() const;

        // Méthodes de recherche
        std::string getType() const override {
            return "Review";
        }
        bool contains(const std::string& search);

};

#endif //PROJETCPP_REVIEW_H