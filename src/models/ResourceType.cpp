#include "ResourceType.h"
#include <algorithm>

ResourceType toResourceType(const std::string& s) {
    std::string lower = s;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);

    if (lower == "book") return ResourceType::Book;
    if (lower == "cd") return ResourceType::CD;
    if (lower == "dvd") return ResourceType::DVD;
    if (lower == "review") return ResourceType::Review;
    if (lower == "article") return ResourceType::Article;
    if (lower == "vhs") return ResourceType::VHS;
    if (lower == "digitalresource" || lower == "digital resource") return ResourceType::DigitalResource;

    return ResourceType::Unknown;
}
