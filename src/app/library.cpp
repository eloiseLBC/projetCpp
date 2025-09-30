#include "library.h"
#include "utils.h"
#include <iostream>
#include <string>
#include <memory>
#include <algorithm>
#include "../models/ResourceType.h"


// *************** LIBRARY *****************
Library::Library() {}

void Library::addResource(string type) {
    ResourceType typeToCompare = toResourceType(type);

    switch(typeToCompare) {
        case ResourceType::Book:{
            string name;
            std::cout << "Entrez le nom de la resource: ";
            std::getline(cin, name);
            string author;
            std::cout << "Entrez le nom de l'auteur: ";
            std::getline(cin, author);
            int yearPublished = utils::readInt("Entrez la date de publication: ");
            string collection;
            std::cout << "Entrez le nom de la collection: ";
            std::getline(cin, collection);
            int nbOfpages = utils::readInt("Entrez le nombre de pages du livre: ");
            
            string summary;
            std::cout << "Entrez le résumé du livre: ";
            std::getline(cin, summary);


            auto res = std::make_shared<Book>(name, author, yearPublished, nbOfpages, collection, summary);
            // allResources.push_back(std::move(res));
            // displayedResources.push_back(std::move(res));
            allResources.push_back(res);
            break;
        }
        case ResourceType::CD: {
            string name;
            std::cout << "Entrez le nom de la resource: ";
            std::getline(cin, name);
            string author;
            std::cout << "Entrez le nom de l'auteur: ";
            std::getline(cin, author);
            int secondesDuration = utils::readInt("Entrez la durée en secondes: ");
            string productionCompany;
            std::cout << "Entrez la companie de production: ";
            std::getline(cin, productionCompany);
            int numberTracks = utils::readInt("Entrez le nombre de pistes du CD: ");
            auto res = std::make_shared<CD>(name, author, secondesDuration, numberTracks, productionCompany);
            // allResources.push_back(std::move(res));
            // displayedResources.push_back(std::move(res));
            allResources.push_back(res);
            break;
        }
        case ResourceType::DVD: {
            string name;
            std::cout << "Entrez le nom de la resource: ";
            std::getline(cin, name);
            string author;
            std::cout << "Entrez le nom de l'auteur: ";
            std::getline(cin, author);
            int secondesDuration = utils::readInt("Entrez la durée en secondes: ");
            string productionCompany;
            std::cout << "Entrez la companie de production: ";
            std::getline(cin, productionCompany);
            int numberTracks = utils::readInt("Entrez le nombre de pistes du DVD: ");
            auto res = std::make_shared<DVD>(name, author, secondesDuration, numberTracks, productionCompany);
            // allResources.push_back(std::move(res));
            allResources.push_back(res);
            break;
        }
        case ResourceType::Review:{
            string name;
            std::cout << "Entrez le nom de la resource: ";
            std::getline(cin, name);
            string author;
            std::cout << "Entrez le nom de l'auteur: ";
            std::getline(cin, author);
            int yearPublished = utils::readInt("Entrez la date de publication: ");
            string collection;
            std::cout << "Entrez le nom de la collection: ";
            std::getline(cin, collection);
            int nbOfpages = utils::readInt("Entrez le nombre de pages : ");
            string summary;
            std::cout << "Entrez le résumé : ";
            std::getline(cin, summary);
            string editor;
            std::cout << "Entrez l'éditeur : ";
            std::getline(cin, editor);
            int numberArticles = utils::readInt("Entrez le nombre d'articles : ");
            auto res = std::make_shared<Review>(name, author, yearPublished, nbOfpages, collection, summary, editor, numberArticles);
            // allResources.push_back(std::move(res));
            allResources.push_back(res);
            break;
        }
        case ResourceType::DigitalResource: {
            string name;
            std::cout << "Entrez le nom de la resource: ";
            std::getline(cin, name);
            string author;
            std::cout << "Entrez le nom de l'auteur: ";
            std::getline(cin, author);
            string typeOfDigitalResource;
            std::cout << "Entrez le type de ressource digitale (ex: audio, video, image, document, etc.): ";
            std::getline(cin, typeOfDigitalResource);
            int bytes = utils::readInt("Entrez la taille en bytes: ");
            string path;
            std::cout << "Entrez le chemin d'accès: ";
            std::getline(cin, path);
            auto res = std::make_shared<DigitalResource>(name, author, typeOfDigitalResource, bytes, path);
            // allResources.push_back(std::move(res));
            allResources.push_back(res);
            break;
        }
        case ResourceType::VHS: {
            string name;
            std::cout << "Entrez le nom de la resource: ";
            std::getline(cin, name);
            string author;
            std::cout << "Entrez le nom de l'auteur: ";
            std::getline(cin, author);
            int secondesDuration = utils::readInt("Entrez la durée en secondes: ");
            string productionCompany;
            std::cout << "Entrez la companie de production: ";
            std::getline(cin, productionCompany);
            auto res = std::make_shared<VHS>(name, author, secondesDuration, productionCompany);
            // allResources.push_back(std::move(res));
            allResources.push_back(res);
            break;
        }
        case ResourceType::Unknown:
        default:
        std::cout << "Type non reconnu.\n";
        break;
    }
    clearSearch();

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
    std::cout<< "\nFichier sauvegardé\n";

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
                  << e.what() <<'\n';
    }

    std::cout << "Fichier chargé, " << allResources.size()
              << " ressources disponibles.\n";

    // Making sure we have the right resources to display.
    clearSearch();
}

void Library::search(string searchString) {
    std::vector<ResourcePtr> results;
    for (const auto& r : displayedResources) {
        if (r && r->contains(searchString)) {
            results.push_back(r);
        }
    }
    displayedResources = results;
}

void Library::clearSearch() {
    displayedResources = allResources;
}

void Library::showDisplayedResources() {
    std::cout << "***** Liste des ressources *****\n";
    
    if (displayedResources.empty()) {
        std::cout << "Aucune ressource à afficher.\n";
        return;
    }

    for(const auto& r : displayedResources) {
        if (r) {  // Vérifier que le pointeur n'est pas null
            r->compactedDisplay();
        } else {
            std::cout << "Erreur : pointeur null détecté\n";
        }
    }
}

void Library::showDetailedDisplay(string id) {
    for (const auto& resPtr : allResources) {
        if (resPtr->getId() == id) {
            resPtr->detailedDisplay();
            return;
        }
    }
    cout << "Pas de ressource avec l'identifiant " << id << ".";
}


void Library::deleteId(string id) {
    bool wasDeleted = false;

    // Supprimer de allResources avec les bons itérateurs
    allResources.erase(
        std::remove_if(allResources.begin(), allResources.end(),
            [&](const ResourcePtr& r) {
                if(r->getId() == id) {
                    cout << "Ressource supprimée :\n";
                    r->compactedDisplay();
                    wasDeleted = true;
                    return true;  // Marquer pour suppression
                }
                return false;
            }
        ),
        allResources.end()  // ⚠️ IMPORTANT : ne pas oublier ce second paramètre !
    );

    // Si supprimé de allResources, supprimer aussi de displayedResources
    if (wasDeleted) {
        displayedResources.erase(
            std::remove_if(displayedResources.begin(), displayedResources.end(),
                [&](const ResourcePtr& r) {
                    return r->getId() == id;
                }
            ),
            displayedResources.end()  // ⚠️ IMPORTANT : ne pas oublier ce second paramètre !
        );
    }

    // Informer l'utilisateur si rien n'a été trouvé
    if (!wasDeleted) {
        cout << "La ressource avec l'identifiant " << id << " n'a pas été trouvée. Aucune action effectuée.\n";
    }
}

void Library::borrow(string id) {
    shared_ptr<Resource> toBorrow;
    for (const auto& resPtr : allResources) {
        if (resPtr->getId() == id ) {
            toBorrow = resPtr;
        }     
    }
    if (toBorrow == NULL) {
        cout << "Pas de ressource à cet identifiant. Aucune action effectuée\n";
    } else if (toBorrow->getBorrowed()) {
        cout << "Cette ressource a déjà été empruntée. Aucune action effectuée\n";
    } else {
        toBorrow->setBorrowed(true);
        toBorrow->compactedDisplay();
        cout << "Vous avez bien emprunté la ressource.\n";
    }
}

void Library::returnResource(string id) {
    shared_ptr<Resource> toReturn;
    for (const auto& resPtr : allResources) {
        if (resPtr->getId() == id ) {
            toReturn = resPtr;
        }     
    }
    if (toReturn == NULL) {
        cout << "Pas de ressource à cet identifiant. Aucune action effectuée\n";
    } else if (!toReturn->getBorrowed()) {
        cout << "Cette ressource n'a pas été empruntée. Aucune action effectuée\n";
    } else {
        toReturn->setBorrowed(false);
        toReturn->compactedDisplay();
        cout << "Vous avez bien retourné la ressource à la bibliothèque.\n";
    }
}

/* Utility method to find the size of the array to display */
int Library::getDisplayedElementsSize() {
    return displayedResources.size();
}




