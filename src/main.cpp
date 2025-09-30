#include <iostream>
#include <string>
#include <map>
#include "app/utils.h"
#include "./app/library.h"

// Énumération pour les rôles utilisateur
enum class UserRole { ADMIN, CLIENT, NONE };

// Structure pour représenter un utilisateur
struct User {
    string username;
    string password;
    UserRole role;
};

// Base de données d'utilisateurs (en dur pour la simplicité)
std::map<string, User> users = {
    {"admin", {"admin", "admin123", UserRole::ADMIN}},
    {"client", {"client", "client123", UserRole::CLIENT}}
};

const std::string loginMenu =
"***********************************************\n"
"********* BIENVENUE À LA BIBLIOTHÈQUE *********\n"
"***********************************************\n"
"Veuillez vous connecter pour continuer.\n"
"Identifiant : ";

const std::string adminMenu =
"***********************************************\n"
"********* MODE ADMINISTRATEUR *****************\n"
"***********************************************\n"
"- ADD type : ajouter une ressource\n"
"- LOAD filename : charger un fichier\n"
"- SAVE filename : sauvegarder dans un fichier\n"
"- LIST : afficher les ressources\n"
"- SEARCH chaîne : rechercher\n"
"- CLEAR : réinitialiser la recherche\n"
"- SHOW id : afficher les détails d'une ressource\n"
"- DELETE id : supprimer une ressource\n"
"- RESET : vider la bibliothèque\n"
"- LOGOUT : se déconnecter\n"
"- BYE : quitter l'application\n"
"***********************************************\n"
"Entrez votre commande :\n";

const std::string clientMenu =
"***********************************************\n"
"************* MODE CLIENT *********************\n"
"***********************************************\n"
"- LIST : afficher les ressources disponibles\n"
"- SEARCH chaîne : rechercher des ressources\n"
"- CLEAR : réinitialiser la recherche\n"
"- SHOW id : afficher les détails d'une ressource\n"
"- BORROW id : emprunter une ressource\n"
"- RETURN id : retourner une ressource\n"
"- LOGOUT : se déconnecter\n"
"- BYE : quitter l'application\n"
"***********************************************\n"
"Entrez votre commande :\n";

enum class Command {
    ADD, LOAD, SAVE, LIST, SEARCH, CLEAR, SHOW,
    DELETE, RESET, BYE, BORROW, RETURN, LOGOUT, Unknown
};

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
    if (s == "BORROW") return Command::BORROW;
    if (s == "RETURN") return Command::RETURN;
    if (s == "LOGOUT") return Command::LOGOUT;
    if (s == "BYE") return Command::BYE;
    return Command::Unknown;
}

// Fonction d'authentification
User* authenticate() {
    string username, password;

    std::cout << loginMenu;
    std::getline(cin, username);

    std::cout << "Mot de passe : ";
    std::getline(cin, password);

    auto it = users.find(username);
    if (it != users.end() && it->second.password == password) {
        std::cout << "\nConnexion réussie ! Bienvenue " << username << ".\n";
        return &(it->second);
    }

    std::cout << "\nIdentifiant ou mot de passe incorrect.\n";
    return nullptr;
}

// Vérifier si une commande est autorisée pour un rôle
bool isCommandAllowed(Command cmd, UserRole role) {
    if (role == UserRole::ADMIN) {
        // Admin peut tout faire SAUF emprunter/retourner
        return cmd != Command::BORROW && cmd != Command::RETURN;
    } else if (role == UserRole::CLIENT) {
        // Client peut seulement consulter et emprunter
        return cmd == Command::LIST || cmd == Command::SEARCH ||
               cmd == Command::CLEAR || cmd == Command::SHOW ||
               cmd == Command::BORROW || cmd == Command::RETURN ||
               cmd == Command::LOGOUT || cmd == Command::BYE;
    }
    return false;
}

int main() {
    Library library = Library();
    bool running = true;
    User* currentUser = nullptr;

    while (running) {
        // Authentification si pas connecté
        if (currentUser == nullptr) {
            currentUser = authenticate();
            if (currentUser == nullptr) {
                std::cout << "Voulez-vous réessayer ? (O/N) : ";
                string retry;
                std::getline(cin, retry);
                if (retry != "O" && retry != "o") {
                    running = false;
                }
                continue;
            }
        }

        // Afficher le menu approprié
        std::cout << (currentUser->role == UserRole::ADMIN ? adminMenu : clientMenu);

        // Lire la commande
        string userAnswer;
        std::getline(cin, userAnswer);

        std::vector<std::string> userAnswerVector = utils::split(userAnswer, ' ');

        if (userAnswerVector.empty()) {
            continue;
        }

        Command command = toCommand(userAnswerVector[0]);
        string commandArg = "";

        if (userAnswerVector.size() > 2) {
            commandArg = utils::join(userAnswerVector, ' ', 1);
        } else if (userAnswerVector.size() == 2) {
            commandArg = userAnswerVector[1];
        }

        // Vérifier les permissions
        if (!isCommandAllowed(command, currentUser->role)) {
            std::cout << "⚠️  Accès refusé : vous n'avez pas les permissions pour cette commande.\n";
            continue;
        }

        // Exécuter la commande
        switch (command) {
            case Command::BYE:
                running = false;
                break;

            case Command::LOGOUT:
                std::cout << "Déconnexion...\n";
                currentUser = nullptr;
                break;

            case Command::ADD:
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
                    std::cout << "Argument inconnu\n";
                    break;
                }
                library.clearSearch();
                std::cout << "Recherche réinitialisée.\n";
                break;

            case Command::LIST:
                if (commandArg != "") {
                    std::cout << "Argument inconnu\n";
                    break;
                }
                library.showDisplayedResources();
                break;

            case Command::SEARCH:
                library.search(commandArg);
                std::cout << "Recherche effectuée. " << library.getDisplayedElementsSize()
                         << " éléments trouvés. Tapez LIST pour voir les résultats.\n";
                break;

            case Command::SHOW:
                library.showDetailedDisplay(commandArg);
                break;

            case Command::DELETE:
                library.deleteId(commandArg);
                break;

            case Command::RESET:
                library.reset();
                std::cout << "Bibliothèque vidée.\n";
                break;

            case Command::BORROW:
                library.borrow(commandArg);
                break;

            case Command::RETURN:
                library.returnResource(commandArg);
                break;

            case Command::Unknown:
            default:
                std::cout << "Commande non reconnue.\n";
                break;
        }
    }

    std::cout << "Au revoir, à bientôt.\n";
    return 0;
}