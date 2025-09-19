#include "library.hpp"
#include "resource.hpp"
#include <iostream>
#include <string>


enum class ResourceType { Unknown, Book, CD, DVD, Review, Article, VHS, DigitalResource };

ResourceType toResourceType(const std::string& s)
{
    if (s == "book" || s == "Book") return ResourceType::Book;
    if (s == "cd"   || s == "CD")   return ResourceType::CD;
    if (s == "dvd"  || s == "DVD")  return ResourceType::DVD;
    return ResourceType::Unknown;
}


int readInt(string query)
{
    std::string input;
    while (true) {
        std::cout << query;
        std::cin >> input;                 // lecture d’une chaîne (pas d’espaces)

        try {
            int year = std::stoi(input);   // peut lancer invalid_argument / out_of_range
            return year;                   // succès → on sort de la boucle
        }
        catch (const std::invalid_argument&) {
            std::cout << "Veuillez saisir uniquement des chiffres\n";
        }
        catch (const std::out_of_range&) {
            std::cout << "Valeur hors limites pour un entier. Réessayez.\n";
        }
    }
}


Library::Library() {}
void Library::addResource(string type) {
    ResourceType typeToCompare = toResourceType(type);

    string name;
    std::cout << "Entrez le nom de la resource: ";
    std::cin >> name;
    string author;
    std::cout << "Entrez le nom de l'auteur: ";
    std::cin >> author;
    

    switch(typeToCompare) {
        case ResourceType::Book:{
            int yearPublished = readInt("Entrez la date de publication: ");
            
            string collection;
            std::cout << "Entrez le nom de la collection: ";
            std::cin >> collection;
            int nbOfpages = readInt("Entrez le nombre de pages du livre: ");
            
            
            string summary;
            std::cout << "Entrez le résumé du livre: ";
            std::cin >> summary;

            /* Smart pointer plutôt que new pour gérer automatiquement la mémoire et ne pas oublier d'appeler delete quelque part  -- https://en.cppreference.com/w/cpp/memory/unique_ptr/make_unique*/
            /* Utilisation de auto pour que le code soit plus propre -- https://www.w3schools.com/cpp/cpp_auto.asp */
            auto res = std::make_unique<Book>(name, author, yearPublished, nbOfpages, collection, summary);
            allResources.push_back(std::move(res));
            break;
        }
        case ResourceType::CD:
        case ResourceType::DVD:
        case ResourceType::Review:
        case ResourceType::DigitalResource:
        case ResourceType::Article:
        case ResourceType::VHS:

        default:
        std::cout << "Type non reconnu.";
        break;
    }

}

void Library::saveToFile(string& fileName) {
            
    std::ofstream myFile(fileName,
                        std::ios::out | std::ios::trunc);
    if (!myFile) {
        std::cerr << "Erreur : impossible d’ouvrir le fichier « "
                    << fileName << " » en écriture.\n";
        return;                     
    }
        
    try{
        for (const auto& resPtr : allResources) {
            cout << resPtr->toString();
            myFile << resPtr->toString();   
             myFile << '\n';
        }
        if (!myFile) {
                throw std::ios_base::failure("Écriture échouée");
            }
        
    }
    catch(const std::ios_base::failure& e) {
        std::cerr << "Erreur d’E/S lors de l’écriture du fichier : "
                  << e.what() << '\n';
        
    }
    std::cout<< "Fichier sauvegardé";

}

