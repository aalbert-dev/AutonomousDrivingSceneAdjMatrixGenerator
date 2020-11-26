#include "json/single_include/nlohmann/json.hpp"
#include <fstream>
#include <iostream>

/**
 * author   Arjun Albert
 * email    aalbert@mit.edu
 * date     11/26/2020
**/

using json = nlohmann::json;

std::string scene_data_file_name = "scene.json";

std::vector<std::string> descriptions;

std::vector<std::vector<std::string>> multi_level_descriptions;

std::vector<std::string> entities;

std::vector<std::string> relationships;

std::string all_entities[] {"with", "before", "after"};

inline void define_relationships()
{
    for (std::string entity: all_entities){
        relationships.push_back(entity);
    }
}


inline int get_entity_level(std::string target_entity)
{
    int i = 0;
    for (i; i < descriptions.size(); i++){
        for (std::string entity: multi_level_descriptions[i]){
            if (target_entity.compare(entity) == 0){
                return i;
            }
        }
    }
    return -1;
}


inline std::string get_relationship(std::string entity_1, std::string entity_2)
{
    int entity_1_level = get_entity_level(entity_1);
    int entity_2_level = get_entity_level(entity_2);
    
    if (entity_1_level == entity_2_level){
        return all_entities[0];
    }else if (entity_1_level < entity_2_level){
        return all_entities[1];
    }else{
        return all_entities[2];
    }
}
