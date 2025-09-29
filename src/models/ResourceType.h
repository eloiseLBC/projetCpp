#ifndef RESOURCETYPE_H
#define RESOURCETYPE_H

#include <string>

// Define the enum
enum class ResourceType {
    Unknown,
    Book,
    CD,
    DVD,
    Review,
    Article,
    VHS,
    DigitalResource
};

// Declare the conversion function
ResourceType toResourceType(const std::string& s);

#endif // RESOURCETYPE_H
