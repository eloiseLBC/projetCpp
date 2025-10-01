# Gestion de bibliothèque - Documentation

## Vue d'ensemble
Système de gestion de bibliothèque en **C++** avec **authentification multi-rôles** (*Administrateur* / *Client*).  
Il permet la gestion complète des **ressources physiques et numériques**.

---

## Authentification et rôles

### Comptes par défaut
- **Administrateur** : `admin / admin123`
- **Client** : `client / client123`

---

### Permissions par rôle

#### Administrateur
**Peut :**
- Ajouter des ressources (`ADD`)
- Supprimer des ressources (`DELETE`)
- Charger / Sauvegarder des fichiers (`LOAD`, `SAVE`)
- Réinitialiser la bibliothèque (`RESET`)
- Consulter et rechercher (`LIST`, `SEARCH`, `SHOW`, `CLEAR`)

**Ne peut pas :**
- Emprunter ou retourner des ressources (`BORROW`, `RETURN`)

---

#### Client
**Peut :**
- Consulter les ressources (`LIST`, `SHOW`)
- Rechercher (`SEARCH`, `CLEAR`)
- Emprunter et retourner (`BORROW`, `RETURN`)

**Ne peut pas :**
- Modifier la bibliothèque (`ADD`, `DELETE`, `RESET`)
- Gérer les fichiers (`LOAD`, `SAVE`)

---

## Commandes disponibles

### Commandes communes
- `LIST` : Afficher les ressources disponibles
- `SEARCH <chaîne>` : Rechercher dans les ressources
- `CLEAR` : Réinitialiser les résultats de recherche
- `SHOW <id>` : Afficher les détails d'une ressource
- `LOGOUT` : Se déconnecter
- `BYE` : Quitter l'application

---

### Commandes administrateur
- `ADD <type>` : Ajouter une ressource (`Book`, `CD`, `DVD`, `Review`, `DigitalResource`, `VHS`)
- `DELETE <id>` : Supprimer une ressource
- `LOAD <filename>` : Charger depuis un fichier
- `SAVE <filename>` : Sauvegarder dans un fichier
- `RESET` : Vider complètement la bibliothèque

---

### Commandes client
- `BORROW <id>` : Emprunter une ressource
- `RETURN <id>` : Retourner une ressource empruntée

---

## Types de ressources
- **Book** : Livres *(année, pages, collection, résumé)*
- **Review** : Revues *(hérite de Book + éditeur, articles)*
- **CD** : Disques audio *(durée, pistes, compagnie de production)*
- **DVD** : Disques vidéo *(hérite de CD)*
- **VHS** : Cassettes vidéo *(durée, compagnie de production)*
- **DigitalResource** : Ressources numériques *(type, taille, chemin)*


## Diagrammes UML
### Diagramme de classes
```mermaid
---
config:
  theme: neo
  look: neo
---
classDiagram
    
direction TB
    class User {
        -String username
        -String password
        -String role
    }
    
    class Library {
        -Array allResources
        -Array displayedResources
        +void addResource()
        +void loadFromFile(String filename)
        +void saveToFile(String filename)
        +void search(String string)
        +void clearSearch()
        +void showDisplayedResources()
        +void showDetailledDisplay(int id)
        +void deleteId(int id)
        +void reset()
        +void borrow(int id)
        +void returnResource(int id)
    }

    class Resource {
        -String id
	    -String title
	    -String author
        -bool borrowed
        +Resource()
        +bool contains(String search)
        +void compactedDisplay()
        +void detailledDisplay()
        +String getType()
        +String toString()
    }

    class Book {
        -int yearPublished
        -int numberPages
        -String collection
        -String summary
    }

    class VHS {
	    -int secondesDuration
	    -String productionCompany
    }
    
    class DigitalResource {
        -String type
        -int bytes
        -String path
    }

    class Review {
        -String editor
        -int numberArticles
    }

    class Article {
        -String name
    }

    class CD {
        -int numberTracks
    }
    
    Library o-- User
    Resource <|-- Book
    Resource <|-- VHS
    Resource <|-- DigitalResource
    Book <|-- Review
    VHS <|-- CD
    CD <|-- DVD
    Library "1"<--"*" Resource
    Review *-- Article
```

### Diagramme Usecases
```mermaid
---
config:
theme: neo
look: neo
---
graph TB
    Admin[Administrateur]
Client[Client]

subgraph "Gestion des ressources"
UC1[ADD - Ajouter ressource]
UC2[DELETE - Supprimer ressource]
UC3[RESET - Vider bibliothèque]
end

subgraph "Gestion des fichiers"
UC4[LOAD - Charger fichier]
UC5[SAVE - Sauvegarder fichier]
end

subgraph "Consultation"
UC6[LIST - Lister ressources]
UC7[SHOW - Afficher détails]
UC8[SEARCH - Rechercher]
UC9[CLEAR - Réinitialiser recherche]
end

subgraph "Gestion des emprunts"
UC10[BORROW - Emprunter]
UC11[RETURN - Retourner]
end

subgraph "Authentification"
UC12[LOGIN - Se connecter]
UC13[LOGOUT - Se déconnecter]
end

Admin --> UC1
Admin --> UC2
Admin --> UC3
Admin --> UC4
Admin --> UC5
Admin --> UC6
Admin --> UC7
Admin --> UC8
Admin --> UC9
Admin --> UC12
Admin --> UC13

Client --> UC6
Client --> UC7
Client --> UC8
Client --> UC9
Client --> UC10
Client --> UC11
Client --> UC12
Client --> UC13

UC8 -.->|peut conduire à| UC6
UC1 -.->|peut nécessiter| UC5
```

### Diagramme de séquences - Authentification et ADD
```mermaid
---
config:
theme: neo
look: neo
---
sequenceDiagram
    participant U as Utilisateur
    participant M as Main
    participant A as Auth
    participant L as Library
    participant R as Resource

    rect rgb(240, 248, 255)
        Note over U,R: Scénario : Connexion et ajout de ressource (Admin)

        U->>M: Démarrage application
        M->>U: Menu initial (1. Connexion / 2. Quitter)
        U->>M: Choix "1"

        M->>A: authenticate()
        activate A
        A->>U: "Identifiant :"
        U->>A: "admin"
        A->>U: "Mot de passe :"
        U->>A: "admin123"

        A->>A: Vérifier credentials
        alt Authentification réussie
            A-->>M: User* (role=ADMIN)
            A->>U: "Connexion réussie ! Bienvenue admin"
        else Échec authentification
            A-->>M: nullptr
            A->>U: "Identifiant ou mot de passe incorrect"
        end
        deactivate A

        M->>U: Afficher adminMenu

        U->>M: "ADD Book"
        M->>M: isCommandAllowed(ADD, ADMIN)

        alt Commande autorisée
            M->>L: addResource("Book")
            activate L

            L->>U: "Entrez le titre :"
            U->>L: "Design Patterns"
            L->>U: "Entrez l'auteur :"
            U->>L: "Gang of Four"
            L->>U: "Entrez l'année :"
            U->>L: "1994"

            L->>R: new Book(données)
            activate R
            R->>R: generateUID()
            R->>R: borrowed = false
            R-->>L: Book créé (ID: xyz123)
            deactivate R

            L->>L: allResources.push_back(book)
            L->>L: clearSearch() // Synchronise displayedResources
            L-->>U: "Ressource ajoutée"
            deactivate L
        else Commande non autorisée
            M->>U: "⚠️ Accès refusé"
        end

        U->>M: "LOGOUT"
        M->>M: currentUser = nullptr
        M->>U: "Déconnexion..."
        M->>U: Retour au menu initial
    end
```

### Diagramme de séquences - Emprunt et retour (Client)
```mermaid
---
config:
theme: neo
look: neo
---
sequenceDiagram
    participant C as Client
    participant M as Main
    participant L as Library
    participant R as Resource

    rect rgb(248, 255, 248)
        Note over C,R: Scénario : Client emprunte une ressource

        C->>M: Connexion (client/client123)
        M->>C: Afficher clientMenu

        C->>M: "LIST"
        M->>M: isCommandAllowed(LIST, CLIENT) ✓
        M->>L: showDisplayedResources()
        activate L

        loop Pour chaque ressource
            L->>R: compactedDisplay()
            R-->>C: "[ID] Titre by Auteur (Available/Borrowed)"
        end
        deactivate L

        C->>M: "BORROW xyz123"
        M->>M: isCommandAllowed(BORROW, CLIENT) ✓
        M->>L: borrow("xyz123")
        activate L

        L->>L: Rechercher ressource avec ID xyz123

        alt Ressource trouvée et disponible
            L->>R: getBorrowed()
            R-->>L: false
            L->>R: setBorrowed(true)
            L->>R: compactedDisplay()
            L-->>C: "Vous avez bien emprunté la ressource"
        else Ressource déjà empruntée
            L-->>C: "Cette ressource a déjà été empruntée"
        else Ressource non trouvée
            L-->>C: "Pas de ressource à cet identifiant"
        end
        deactivate L

        Note over C,R: Plus tard...

        C->>M: "RETURN xyz123"
        M->>L: returnResource("xyz123")
        activate L
        L->>R: setBorrowed(false)
        L-->>C: "Vous avez bien retourné la ressource"
        deactivate L
    end
```

### Diagramme de séquences - Recherche incrémentale
```mermaid
---
config:
theme: neo
look: neo
---
sequenceDiagram
    participant U as Utilisateur
    participant L as Library
    participant R as Resource

    rect rgb(255, 248, 240)
        Note over U,R: Scénario : Recherche avec filtrage progressif
        
        Note over L: État initial : 10 ressources
        
        U->>L: SEARCH "Design"
        activate L
        
        loop Pour chaque ressource dans displayedResources
            L->>R: contains("Design")
            activate R
            R->>R: Vérifier titre/auteur
            alt Contient "Design"
                R-->>L: true
            else Ne contient pas
                R-->>L: false
            end
            deactivate R
        end
        
        L->>L: Filtrer displayedResources
        L-->>U: "3 ressources trouvées"
        deactivate L
        
        Note over L: displayedResources contient maintenant 3 éléments
        
        U->>L: SEARCH "Patterns"
        activate L
        
        Note over L: Recherche dans les 3 résultats précédents
        
        loop Pour chaque ressource dans displayedResources (déjà filtré)
            L->>R: contains("Patterns")
            R-->>L: true/false
        end
        
        L->>L: Affiner displayedResources
        L-->>U: "1 ressource trouvée"
        deactivate L
        
        Note over L: displayedResources contient 1 élément<br/>avec "Design" ET "Patterns"
        
        U->>L: CLEAR
        activate L
        L->>L: displayedResources = allResources
        L-->>U: "Recherche réinitialisée"
        deactivate L
        
        Note over L: Retour aux 10 ressources initiales
    end
```

## Flux d'utilisation

### Première utilisation (Administrateur)
1. Démarrer l'application.
2. Se connecter avec les identifiants : `admin / admin123`
3. Ajouter des ressources (`Book`, `CD`, `DVD`) ou charger un fichier (exemple : `library.txt`) :
    - `ADD Book`
    - `ADD CD`
    - `LOAD library.txt`
4. Sauvegarder si nécessaire : `SAVE bibliotheque.txt`
5. Se déconnecter : `LOGOUT` ou quitter : `BYE`

---

### Utilisation par un client
1. Se connecter avec : `client / client123`
2. Consulter : `LIST`
3. Rechercher : `SEARCH <titre>`
4. Emprunter : `BORROW <id>`
5. Retourner : `RETURN <id>`

---

## Format de sauvegarde
Les ressources sont sauvegardées **ligne par ligne**, avec des **champs séparés par `;`**.
```text
Book;id;titre;auteur;0;année;pages;collection;résumé
CD;id;titre;auteur;0;durée;pistes;compagnie
Review;id;titre;auteur;0;année;pages;collection;résumé;éditeur;nbArticles;Article1,Article2
```

## Compilation et exécution
### Avec CMake 
Le projet utilise **CMake** pour la gestion de la compilation. Voici la structure :
```text
ProjetCpp/
├── CMakeLists.txt
├── src/
│   ├── main.cpp
│   ├── app/
│   │   ├── library.cpp
│   │   └── utils.cpp
│   └── models/
│       ├── Resource.cpp
│       ├── Book.cpp
│       ├── Review.cpp
│       ├── CD.cpp
│       ├── DVD.cpp
│       ├── VHS.cpp
│       ├── DigitalResource.cpp
│       └── ResourceType.cpp
└── test/
└── (fichiers de tests)
```
#### Commandes de compilation
```bash
# Créer le dossier de build
mkdir build
cd build

# Configurer le projet avec CMake
cmake ..

# Compiler
cmake --build .

# Exécuter l'application
./ProjetCpp

# Exécuter les tests
./tests
```
### Compilation manuelle
Si vous préférez compiler manuellement sans CMake :
```bash
# Compiler tous les fichiers source
g++ -std=c++20 \
    src/main.cpp \
    src/app/library.cpp \
    src/app/utils.cpp \
    src/models/Resource.cpp \
    src/models/Book.cpp \
    src/models/Review.cpp \
    src/models/CD.cpp \
    src/models/DVD.cpp \
    src/models/VHS.cpp \
    src/models/DigitalResource.cpp \
    src/models/ResourceType.cpp \
    -I./include \
    -o bibliotheque

# Exécution
./bibliotheque
```
### Prérequis
- **Compilateur** : g++ 9.0+ ou clang++ 10.0+ (support C++20)
- **CMake** : version 4.0 ou supérieure
- **Système d'exploitation** : Linux, macOS, ou Windows (avec MinGW/MSYS2)


## Améliorations futures possibles
- Interface graphique
- Support de base de données
- Logging des actions
- Hashage des mots de passe
- Persistance des utilisateurs dans un fichier
- Système d'inscription pour nouveaux clients
- Historique des emprunts par utilisateur
- Limitation du nombre d'emprunts simultanés
- Dates d'emprunt et de retour
- Système de réservation
- Pénalités pour retards