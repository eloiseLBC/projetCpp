#include "library.hpp"
#include "resource.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include <algorithm>


// ************ RESOURCE TYPE ***************
enum class ResourceType { Unknown, Book, CD, DVD, Review, Article, VHS, DigitalResource };

ResourceType toResourceType(const std::string& s)
{
    if (s == "book" || s == "Book" || s == "BOOK") return ResourceType::Book;
    if (s == "cd"   || s == "CD")   return ResourceType::CD;
    if (s == "dvd"  || s == "DVD")  return ResourceType::DVD;
    return ResourceType::Unknown;
}


// *************** LIBRARY *****************

Library::Library() {}

void Library::addResource(string type) {
    ResourceType typeToCompare = toResourceType(type);

    switch(typeToCompare) {
        case ResourceType::Book:{
            string name;
            std::cout << "Entrez le nom de la resource: ";
            std::cin >> name;
            string author;
            std::cout << "Entrez le nom de l'auteur: ";
            std::cin >> author;
            int yearPublished = utils::readInt("Entrez la date de publication: ");
            
            string collection;
            std::cout << "Entrez le nom de la collection: ";
            std::cin >> collection;
            int nbOfpages = utils::readInt("Entrez le nombre de pages du livre: ");
            
            
            string summary;
            std::cout << "Entrez le résumé du livre: ";
            std::cin >> summary;

            /* Smart pointer rather than new to automatically handle memory and not have memory leaks somewhere  -- https://en.cppreference.com/w/cpp/memory/shared_ptr/make_shared
            Using auto in order for the code to be cleaner -- https://www.w3schools.com/cpp/cpp_auto.asp */
            auto res = std::make_shared<Book>(name, author, yearPublished, nbOfpages, collection, summary);
            allResources.push_back(std::move(res));
            displayedResources.push_back(std::move(res));
            break;
        }
        case ResourceType::CD:
        case ResourceType::DVD:
        case ResourceType::Review:
        case ResourceType::DigitalResource:
        case ResourceType::Article:
        case ResourceType::VHS:
        case ResourceType::Unknown:
        default:
        std::cout << "Type non reconnu.";
        break;
    }

}

void Library::saveToFile(const std::string& fileName) {
            
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

void Library::loadFromFile(const std::string& fileName) {
    // Ouverture du fichier en lecture
    std::ifstream myFile(fileName, std::ios::in);
    if (!myFile) {
        std::cerr << "Erreur : impossible d’ouvrir le fichier « "
                  << fileName << " » en lecture.\n";
        return;
    }

    // empty existing resources
    allResources.clear();

    try {
        std::string line;
        while (std::getline(myFile, line)) {
            // Ignore empty lines
            if (line.empty())
                continue;

            // Convert line into resources
            std::vector<std::string> parametersOfResource = utils::split(line);
            ResourcePtr res = utils::createResourceFromTokens(parametersOfResource);
            if (!res) {
                // Si la fonction retourne nullptr plutôt qu’une exception,
                // on signale le problème mais on continue le chargement.
                std::cerr << "Avertissement : ligne non reconnue et ignorée → "
                          << line << '\n';
                continue;
            }

            // Ajouter l’objet au conteneur
            allResources.emplace_back(std::move(res));
        }

        // Vérifier l’état du flux après la boucle
        if (myFile.bad()) {
            throw std::ios_base::failure("Erreur pendant la lecture");
        }
    }
    catch (const std::ios_base::failure& e) {
        std::cerr << "Erreur lors de la lecture du fichier : "
                  << e.what() << '\n';
    }
    catch (const std::exception& e) {
        // Capture d’éventuelles exceptions provenant de fromString()
        std::cerr << "Erreur lors de la désérialisation d’une ressource : "
                  << e.what() << '\n';
    }

    std::cout << "Fichier chargé, " << allResources.size()
              << " ressources disponibles.\n";

    // Making sure we have the right resources to display.
    clearSearch();
}

void Library::search(string searchString) {
    displayedResources.erase(std::remove_if(displayedResources.begin(), displayedResources.end(), [&](const ResourcePtr& r)
                                  {
                                      // Remove if doesn't contain the searchstring.
                                      return !r->contains(searchString);
                                  }));
}

void Library::clearSearch() {
    displayedResources = allResources;
}

void Library::showDisplayedResources() {
    std::cout << "***** Liste des ressources *****\n";
    
    for(ResourcePtr r : displayedResources) {
       r->compactedDisplay();
    }

}


int Library::getDisplayedElementsSize() {
    return displayedResources.size();
}

