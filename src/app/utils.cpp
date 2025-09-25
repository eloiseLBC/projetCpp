
#include "utils.hpp"
#include "../models/Resource.h"
#include "../models/Book.h"
#include "../models/CD.h"
#include "../models/DVD.h"
#include "../models/Article.h"
#include "../models/Review.h"
#include "../models/VHS.h"
#include "../models/DigitalResource.h"
#include "../models/ResourceType.h"
#include <iostream>
#include <string>
#include <stdexcept>

#include <sstream> 
#include <memory>


/* Asks the query to the user, reads it and validates that it's an int, 
 then returns the int entered by the user. */
int utils::readInt(const string& query)
{
    std::string input;
    while (true) {
        std::cout << query;
        std::cin >> input;           

        try {
            int year = std::stoi(input);   // can throw invalid_argument / out_of_range
            return year;
        }
        catch (const std::invalid_argument&) {
            std::cout << "Veuillez saisir uniquement des chiffres\n";
        }
        catch (const std::out_of_range&) {
            std::cout << "Valeur hors limites pour un entier. Réessayez.\n";
        }
    }
}

/* params : entry string, delimiter ; 
Splits the entry string on the delimiter character
then returns the array of strings.
*/
std::vector<std::string> utils::split(const std::string& s,
                                      char delimiter)
{
    std::vector<std::string> elems;
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delimiter))
        elems.push_back(item);
    return elems;
}

/* Resource factory : takes in an array of strings : [typeofResource, parameters...]
Returns a pointer to a new resource of type typeOfResource, with the parameters from the array. 
*/

ResourcePtr utils::createResourceFromTokens(const std::vector<std::string>& tokens)
{
    if (tokens.empty())
        throw std::invalid_argument("ligne vide");

    const std::string& typeStr = tokens[0];

    ResourceType type = toResourceType(typeStr);

    // BOOK
    if (type == ResourceType::Book) {
        // check that we have the right number of tockens
        if (tokens.size() != 9)   // type + 8 parameters
            throw std::runtime_error("Mauvais nombre d’attributs pour Book");
        const std::string& id  = tokens[1];
        const std::string& title  = tokens[2];
        const std::string& author = tokens[3];
        const bool borrowed = std::stoi(tokens[4]);
        int                 year   = std::stoi(tokens[5]);   // conversion string → int
        int              nbOfpages  = std::stoi(tokens[6]);   // conversion string → double
        const std::string& collection = tokens[7];
        const std::string& summary = tokens[8];

        return std::make_shared<Book>(title, author, year, nbOfpages, collection, summary);
    } else if (type == ResourceType::CD) {
        // check that we have the right number of tockens
        if (tokens.size() != 8)   // type + 8 parameters
            throw std::runtime_error("Mauvais nombre d’attributs pour CD");
        const std::string& id  = tokens[1];
        const std::string& title  = tokens[2];
        const std::string& author = tokens[3];
        const bool borrowed = std::stoi(tokens[4]);
        int                 secondesDuration   = std::stoi(tokens[5]);   // conversion string → int
        const std::string& productionCompany = tokens[6];
        int              numberTracks  = std::stoi(tokens[7]);   // conversion string → double
        

        return std::make_shared<CD>(title, author, secondesDuration, numberTracks, productionCompany);
    } else if (type == ResourceType::VHS) {
        // check that we have the right number of tockens
        if (tokens.size() != 7)   // type + 6 parameters
            throw std::runtime_error("Mauvais nombre d’attributs pour VHS");
        const std::string& id  = tokens[1];
        const std::string& title  = tokens[2];
        const std::string& author = tokens[3];
        const bool borrowed = std::stoi(tokens[4]);
        int                 secondesDuration   = std::stoi(tokens[5]);   // conversion string → int
        const std::string& productionCompany = tokens[6];

        return std::make_shared<VHS>(title, author, secondesDuration, productionCompany);
    }
    else if (type == ResourceType::DVD) {
        // check that we have the right number of tockens
        if (tokens.size() != 8)   // type + 8 parameters
            throw std::runtime_error("Mauvais nombre d’attributs pour DVD");
        const std::string& id  = tokens[1];
        const std::string& title  = tokens[2];
        const std::string& author = tokens[3];
        const bool borrowed = std::stoi(tokens[4]);
        int                 secondesDuration   = std::stoi(tokens[5]);   // conversion string → int
        const std::string& productionCompany = tokens[6];
        int              numberTracks  = std::stoi(tokens[7]);   // conversion string → double
        
        return std::make_shared<DVD>(title, author, secondesDuration, productionCompany);
    } 
    else if (type == ResourceType::Review) {
        // check that we have the right number of tockens
        if (tokens.size() != 11)   // type + 8 parameters
            throw std::runtime_error("Mauvais nombre d’attributs pour Review");
        const std::string& id  = tokens[1];
        const std::string& title  = tokens[2];
        const std::string& author = tokens[3];
        const bool borrowed = std::stoi(tokens[4]);
        int                 year   = std::stoi(tokens[5]);   // conversion string → int
        int              nbOfpages  = std::stoi(tokens[6]);   // conversion string → double
        const std::string& collection = tokens[7];
        const std::string& summary = tokens[8];
        const std::string& editor = tokens[8];
        int                 nbArticles   = std::stoi(tokens[5]);   // conversion string → int
        return std::make_shared<Review>(title, author, year, nbOfpages, collection, summary);
    } 
    else if (type == ResourceType::DigitalResource) {
        // check that we have the right number of tockens
        if (tokens.size() != 8)   // type + 7 parameters
            throw std::runtime_error("Mauvais nombre d’attributs pour DigitalResource");
        const std::string& id  = tokens[1];
        const std::string& title  = tokens[2];
        const std::string& author = tokens[3];
        const bool borrowed = std::stoi(tokens[4]);
        const std::string& type = tokens[7];
        int                bytes   = std::stoi(tokens[5]);   // conversion string → int
        const std::string& path = tokens[8];
        
        return std::make_shared<DigitalResource>(title, author, type, bytes, path);
    } 
    else if (type == ResourceType::Article) {
        // check that we have the right number of tockens
        if (tokens.size() != 11)   // type + 10 parameters
            throw std::runtime_error("Mauvais nombre d’attributs pour Article");
        const std::string& id  = tokens[1];
        const std::string& title  = tokens[2];
        const std::string& author = tokens[3];
        const bool borrowed = std::stoi(tokens[4]);
        int                 year   = std::stoi(tokens[5]);   // conversion string → int
        int              nbOfpages  = std::stoi(tokens[6]);   // conversion string → double
        const std::string& collection = tokens[7];
        const std::string& summary = tokens[8];
        const std::string& editor = tokens[8];
        int                 nbArticles   = std::stoi(tokens[5]);   // conversion string → int
        return std::make_shared<Article>(title, author, year, nbOfpages, collection, summary);
    } 

    
    // OTHERS (todo)
    else {
        throw std::runtime_error("Type de ressource inconnu");
    }
}

/* reverse split, returns a string from a vector */
std::string utils::join(const std::vector<std::string>& elems,
                            char delim,
                            std::size_t start,
                            std::size_t end)
{
    if (elems.empty()) return {};

    // Adjust start and end
    if (start >= elems.size()) return {};
    if (end == static_cast<std::size_t>(-1) || end > elems.size())
        end = elems.size();

    std::ostringstream oss;
    oss << elems[start];    

    for (std::size_t i = start + 1; i < end; ++i) {
        oss << delim << elems[i];
    }
    std::cout << oss.str();
    return oss.str();
}