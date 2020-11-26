#include "json/single_include/nlohmann/json.hpp"
#include <fstream>
#include <iostream>

/**
 * author   Arjun Albert
 * email    aalbert@mit.edu
 * date     11/26/2020
**/

using json = nlohmann::json;

std::vector<std::string> entities;

std::vector<std::string> relationships;

inline void define_relationships()
{
    relationships.push_back("with");
    relationships.push_back("before");
    relationships.push_back("after");
}
