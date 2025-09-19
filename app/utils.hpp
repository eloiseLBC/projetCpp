#pragma once
#include "resource.hpp"
#include <string>

#include <vector>
#include <memory>
#include <string>
#include <memory>

using namespace std;

using ResourcePtr = std::shared_ptr<Resource>;

class utils {
public:
    static int readInt(const std::string& query);
    static std::vector<std::string> split(const std::string& s,
                                          char delimiter = ';');
    static ResourcePtr createResourceFromTokens(const std::vector<std::string>& tokens);
    static std::string join(const std::vector<std::string>& elems,
                            char delim,
                            std::size_t start = 0,
                            std::size_t end   = static_cast<std::size_t>(-1));
};

