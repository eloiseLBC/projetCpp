#include <iostream>
#include <string>
#include "app/utils.hpp"
#include "./app/library.hpp"
#include "models/Resource.hpp"


const std::string menu = 
"***********************************************\n"
"********* BIENVENUE À LA BIBLIOTHÈQUE *********\n"
"***********************************************\n"
"Les commandes à votre disposition sont : \n"
"- ADD type : vous permet d'ajouter un élément de type Type\n"
"- LOAD filename : charge un fichier dans la bibliothèque. Attention: remplace les informations actuelles de la bibliothèque.\n"
"- SAVE filename : sauvegarde la bibliothèque actuelle dans le fichier filename\n"
"- LIST : affiche les données de la base de données ou les résultats d'une recherche\n"
"- SEARCH chaîne : cherche la chaîne de caractères entrée dans les ressources de la bibliothèque\n"
"- CLEAR : réinitialise la bibliothèque après une recherche\n"
"- SHOW id : permet d'afficher les informations détaillées de la ressource sélectionnée\n"
"- BORROW id : emprunte un livre (id)"
"- RETURN id : retour d'un livre (id)"
"- DELETE id : permet de supprimer une ressource selon son id\n"
"- RESET : supprime toutes les ressources de la bibliothèque. La bibliothèque est vide. Il n'y a plus de ressources. Le vide de l'existence et le noir de la nuit.\n"
"- BYE : Quitter l'application.\n"
"***********************************************\n"
"Entrez votre requête :\n"
;

enum class Command { ADD, LOAD, SAVE, LIST, SEARCH, CLEAR, SHOW, DELETE, RESET, BYE, Unknown };
Command toCommand(const string& s) {
    if (s == "ADD") return Command::ADD; 
    if (s == "LOAD") return Command::LOAD; 
    if (s == "SAVE") return Command::SAVE; 
    if (s == "LIST") return Command::LIST; 
    if (s == "SEARCH") return Command::SEARCH; 
    if (s == "CLEAR") return Command::CLEAR; 
    if (s == "SHOW") return Command::SHOW; 
    if (s == "DELETE") return Command::DELETE; 
    if (s == "RESET") return Command::RESET; 
    if (s == "BYE") return Command::BYE; 
    return Command::Unknown;
}

int main() {

    Library library = Library();

    bool running = 1;
    
    std::vector<std::string> userAnswerVector;
    Command command;
    string commandArg;

    while (running) {
        std::cout << menu;
        string userAnswer;
        std::getline(cin, userAnswer);
        userAnswerVector = utils::split(userAnswer, ' ');
        
        if (userAnswerVector.empty()) {
            // Nothing in the input, continue
            continue;
        }
        command = toCommand(userAnswerVector[0]);
        if(userAnswerVector.size()>2 ){
            commandArg = utils::join(userAnswerVector, ' ', 1);
        } else if (userAnswerVector.size() == 2) {
            commandArg = userAnswerVector[1];
        }
        else {
            commandArg = "";
        }

        switch (command) {
            case Command::BYE:
                // Get out of the loop
                running = 0;
                break;
            case Command::ADD:
                // commandArg will be a type
                library.addResource(commandArg);
                break;
            case Command::LOAD:
                library.loadFromFile(commandArg);
                break;
            case Command::SAVE:
                library.saveToFile(commandArg);
                break; 
            case Command::CLEAR:
                if (commandArg != "") {
                    std::cout << "\n Argument inconnu";
                    break;
                }
                library.clearSearch();
                break;
            case Command::LIST:
                if (commandArg != "") {
                    std::cout << "\n Argument inconnu";
                    break;
                }
                library.showDisplayedResources();
                break;
            case Command::SEARCH:
                library.search(commandArg);

                std::cout << "Recherche effectuée."<< to_string(library.getDisplayedElementsSize()) <<" éléments trouvés. Tapez LIST pour voir les résultats de la recherche\n";
                break;
            case Command::SHOW:
            case Command::DELETE:
            case Command::RESET:
            case Command::Unknown:
            default:
            std::cout << "Commande non reconnue. Merci d'entrer une commande valide\n";
            break;
        }
        userAnswer = "";
    }

    std::cout << "Au revoir, à bientôt.\n";

    // TODO nettoyer

    return 0;
}