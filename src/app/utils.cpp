
#include "utils.hpp"
#include "../models/Resource.h"
#include "../models/Book.h"
#include "../models/CD.h"
#include "../models/DVD.h"
#include "../models/Review.h"
#include "../models/VHS.h"
#include "../models/DigitalResource.h"
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

    const std::string& type = tokens[0];

    // BOOK
    if (type == "Book") {
        // check that we have the right number of tockens
        if (tokens.size() != 7)   // type + 4 parameters
            throw std::runtime_error("Mauvais nombre d’attributs pour Book");
        const std::string& title  = tokens[1];
        const std::string& author = tokens[2];
        int                 year   = std::stoi(tokens[3]);   // conversion string → int
        int              nbOfpages  = std::stoi(tokens[4]);   // conversion string → double
        const std::string& collection = tokens[5];
        const std::string& summary = tokens[6];

        return std::make_shared<Book>(title, author, year, nbOfpages, collection, summary);
    } else if (type == "CD") {
        // check that we have the right number of tockens
        if (tokens.size() != 6)   // type + 4 parameters
            throw std::runtime_error("Mauvais nombre d’attributs pour Book");
        const std::string& title  = tokens[1];
        const std::string& author = tokens[2];
        int                 secondesDuration   = std::stoi(tokens[3]);   // conversion string → int
        int              numberTracks  = std::stoi(tokens[4]);   // conversion string → double
        const std::string& productionCompany = tokens[5];

        return std::make_shared<CD>(title, author, secondesDuration, numberTracks, productionCompany);
    }

    
    // OTHERS (todo)
    else {
        throw std::runtime_error("Type inconnu de ressource : " + type);
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
