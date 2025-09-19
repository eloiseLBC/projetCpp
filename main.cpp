#include <iostream>
#include "app/library.hpp"
#include "app/resource.hpp"
int main() {

    Library* pLibrary = new Library();

    pLibrary->addResource("Book");


    string fileName = "library1.txt";
    pLibrary->saveToFile(fileName);

    

    return 0;
}