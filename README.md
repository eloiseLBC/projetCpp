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
+void return(int id)
}

    class Resource {
        -int id
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

    class CD {
	    -int secondesDuration
	    -int numberTracks
	    -String productionCompany
    }

    class VHS {
	    -int secondesDuration
	    -int numberTracks
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

    class DVD {
        -int numberTracks
    }

    Resource <|-- Book
    Resource <|-- CD
    Resource <|-- VHS
    Resource <|-- DigitalResource
    Book <|-- Review
    VHS <|-- DVD
    Library <|-- Resource
    Review *-- Article
```