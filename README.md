# Objectif du projet
L’objectif du projet est de mettre en œuvre les notions appréhendées durant l’enseignement
de ce module. Durant cet enseignement nous avons acquis les notions de base de la
conception/programmation orientée objets appliquées au langage C++.


# Diagramme UML
```mermaid
---
config:
  theme: neo
  look: neo
---
classDiagram
direction TB
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

    Resource <|-- Book
    Resource <|-- VHS
    Resource <|-- DigitalResource
    Book <|-- Review
    VHS <|-- CD
    CD <|-- DVD
    Library "1"<--"*" Resource
    Review *-- Article
```

# Diagramme Usecases
```mermaid
---
config:
theme: neo
look: neo
---
graph TD
%% Acteurs
User[Utilisateur<br/>Bibliothécaire]

    %% Cas d'utilisation principaux
    subgraph "Gestion des ressources"
        UC1[Ajouter une ressource<br/>ADD type]
        UC2[Supprimer une ressource<br/>DELETE id]
        UC3[Consulter les ressources<br/>LIST]
        UC4[Afficher détails ressource<br/>SHOW id]
        UC5[Réinitialiser collection<br/>RESET]
    end
    
    subgraph "Gestion des fichiers"
        UC6[Charger depuis fichier<br/>LOAD filename]
        UC7[Sauvegarder dans fichier<br/>SAVE filename]
    end
    
    subgraph "Recherche"
        UC8[Rechercher ressources<br/>SEARCH chaîne]
        UC9[Effacer résultats recherche<br/>CLEAR]
    end
    
    subgraph "Gestion des emprunts"
        UC10[Emprunter ressource]
        UC11[Rendre ressource]
        UC12[Réserver ressource]
    end
    
    subgraph "Navigation"
        UC13[Quitter application<br/>BYE]
    end
    
    %% Relations
    User --> UC1
    User --> UC2
    User --> UC3
    User --> UC4
    User --> UC5
    User --> UC6
    User --> UC7
    User --> UC8
    User --> UC9
    User --> UC10
    User --> UC11
    User --> UC12
    User --> UC13
    
    %% Extensions et inclusions
    UC8 -.->|extend| UC9
    UC8 -.->|peut conduire à| UC3
    UC1 -.->|peut nécessiter| UC7
    UC6 -.->|remplace| UC3
```

# Diagramme de séquences
```mermaid
---
config:
  theme: redux-color
---
sequenceDiagram
participant Utilisateur
participant Library
participant Resource
participant Fichier

rect rgb(240, 248, 255)
    Note over Utilisateur,Fichier: Scénario ADD: Ajouter une ressource

    Utilisateur->>Library: ADD Book
    activate Library

    Library->>Utilisateur: "Entrez le titre:"
    Utilisateur->>Library: "Design Patterns"

    Library->>Utilisateur: "Entrez l'auteur:"
    Utilisateur->>Library: "Gang of Four"

    Library->>Utilisateur: "Entrez l'année:"
    Utilisateur->>Library: "1994"

    Library->>Utilisateur: "Entrez le nombre de pages:"
    Utilisateur->>Library: "395"

    Library->>Resource: new Book(données)
    activate Resource
    Resource->>Resource: Générer ID unique
    Resource->>Resource: borrowed = false
    Resource-->>Library: Objet Book créé (ID: 123)
    deactivate Resource

    Library->>Library: allResources.add(book)
    Library->>Library: displayedResources.add(book)

    Library-->>Utilisateur: "Livre ajouté avec succès (ID: 123)"
    deactivate Library
end

rect rgb(248, 255, 248)
    Note over Utilisateur,Fichier: Scénario SEARCH: Recherche incrémentale

    Note over Library: Première recherche
    Utilisateur->>Library: SEARCH "Design"
    activate Library

    Library->>Library: resultList = []

    loop Pour chaque ressource dans displayedResources
        Library->>Resource: contains("Design")
        activate Resource
        Resource->>Resource: Vérifier titre/auteur contient "Design"
        alt Contient "Design"
            Resource-->>Library: true
            Library->>Library: resultList.add(resource)
        else Ne contient pas
            Resource-->>Library: false
        end
        deactivate Resource
    end

    Library->>Library: displayedResources = resultList
    Library-->>Utilisateur: "2 ressources trouvées"
    deactivate Library

    Note over Library: Recherche affinée
    Utilisateur->>Library: SEARCH "Patterns"
    activate Library

    Library->>Library: newResultList = []

    loop Pour chaque ressource dans displayedResources (déjà filtré)
        Library->>Resource: contains("Patterns")
        activate Resource
        Resource->>Resource: Vérifier titre/auteur contient "Patterns"
        alt Contient "Patterns"
            Resource-->>Library: true
            Library->>Library: newResultList.add(resource)
        else Ne contient pas
            Resource-->>Library: false
        end
        deactivate Resource
    end

    Library->>Library: displayedResources = newResultList
    Library-->>Utilisateur: "1 ressource trouvée avec critères combinés"
    deactivate Library

    Note over Library: Réinitialisation
    Utilisateur->>Library: CLEAR
    activate Library
    Library->>Library: displayedResources = allResources
    Library-->>Utilisateur: "Recherche réinitialisée"
    deactivate Library
end
```