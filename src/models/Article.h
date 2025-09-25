#ifndef PROJETCPP_ARTICLE_H
#define PROJETCPP_ARTICLE_H
#include "Review.h"


class Article : public Review {
    private:
        std::string name;
    public:
        using Review::Review; // héritage de Review
        // Constructors
        Article();
        Article(const std::string& title, const std::string& author,
                int publicationYear, int numberPages, const std::string& genre,
                const std::string& summary, const std::string& editor, int numberArticles,
                const std::string& name);
        Article(const std::string& id, const std::string& title, const std::string& author, bool borrowed,
                int publicationYear, int numberPages, const std::string& genre,
                const std::string& summary, const std::string& editor, int numberArticles,
                const std::string& name);


        // Getters
        std::string getName() const;

        // Setters
        void setName(const std::string& name);

        // Méthodes d'affichage
        void compactedDisplay() const;
        void detailedDisplay() const;
        std::string toString() const;

        // Méthodes de recherche
        std::string getType() const override {
            return "Article";
        }
        bool contains(const std::string& search);

};


#endif