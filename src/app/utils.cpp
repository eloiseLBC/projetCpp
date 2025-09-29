
#include "utils.h"
#include "../models/Resource.h"
#include "../models/Book.h"
#include "../models/CD.h"
#include "../models/DVD.h"
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
        std::getline(cin, input);      

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

std::vector<std::string> utils::parseArticles(const std::string& s) {
    std::vector<std::string> result;
    if (s.size() < 2 || s.front() != '[' || s.back() != ']')
        throw std::runtime_error("Format d'articles invalide : " + s);

    std::string inside = s.substr(1, s.size() - 2); // enlève les crochets
    std::stringstream ss(inside);
    std::string item;

    while (std::getline(ss, item, ',')) {
        if (!item.empty())
            result.push_back(item);
    }
    return result;
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

        return std::make_shared<Book>(id, title, author, borrowed, year, nbOfpages, collection, summary);
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
        

        return std::make_shared<CD>(id, title, author, borrowed, secondesDuration, numberTracks, productionCompany);
    } else if (type == ResourceType::VHS) {
        // check that we have the right number of tockens
        if (tokens.size() != 7)   // type + 6 parameters
            throw std::runtime_error("Mauvais nombre d’attributs pour VHS");
        const std::string& id  = tokens[1];
        const std::string& title  = tokens[2];
        const std::string& author = tokens[3];
        const bool borrowed = std::stoi(tokens[4]);
        
        int secondesDuration   = std::stoi(tokens[5]);   // conversion string → int
        const std::string& productionCompany = tokens[6];

        return std::make_shared<VHS>(id, title, author, borrowed, secondesDuration, productionCompany);
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
        
        return std::make_shared<DVD>(id, title, author, borrowed, secondesDuration, numberTracks, productionCompany);
    } 
    else if (type == ResourceType::Review) {
        // check that we have the right number of tockens
        if (tokens.size() != 12)   // type + 8 parameters
            throw std::runtime_error("Mauvais nombre d’attributs pour Review");
        const std::string& id  = tokens[1];
        const std::string& title  = tokens[2];
        const std::string& author = tokens[3];
        const bool borrowed = std::stoi(tokens[4]);
        int                 year   = std::stoi(tokens[5]);   // conversion string → int
        int              nbOfpages  = std::stoi(tokens[6]);   // conversion string → double
        const std::string& collection = tokens[7];
        const std::string& summary = tokens[8];
        const std::string& editor = tokens[9];
        int                 nbArticles   = std::stoi(tokens[10]);   // conversion string → int
        std::vector<std::string> articles = parseArticles(tokens[11]);
        return std::make_shared<Review>(id, title, author, borrowed, year, nbOfpages, collection, summary, editor, nbArticles, articles);
    } 
    else if (type == ResourceType::DigitalResource) {
        // check that we have the right number of tockens
        if (tokens.size() != 8)   // type + 7 parameters
            throw std::runtime_error("Mauvais nombre d’attributs pour DigitalResource");
        const std::string& id  = tokens[1];
        const std::string& title  = tokens[2];
        const std::string& author = tokens[3];
        const bool borrowed = std::stoi(tokens[4]);
        const std::string& type = tokens[5];
        int                bytes   = std::stoi(tokens[6]);   // conversion string → int
        const std::string& path = tokens[7];
        
        return std::make_shared<DigitalResource>(id, title, author, borrowed, type, bytes, path);
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