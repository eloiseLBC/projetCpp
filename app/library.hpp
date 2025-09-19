#pragma once
#include "resource.hpp"
#include <array>
#include <vector>
#include <memory>
#include <string>
#include <memory>
#include <fstream>
using namespace std ;

class Library{
    private:
    std::vector<std::unique_ptr<Resource>> allResources;
    std::vector<std::unique_ptr<Resource>> displayedResources; 

    public:
    Library();
    void addResource(string type);
    void loadFromFile(const std::string& fileName);
    void saveToFile(string &fileName);
    void search(string searchString);
    void clearSearch();
    void showDisplayedResources(); // LIST command
    void showDetailedDisplay(string id); // SHOW id command : shows only
    void deleteId(string id); // DELETE id command
    void reset();
    void borrow(string id);
    void returnResource(string id);
};