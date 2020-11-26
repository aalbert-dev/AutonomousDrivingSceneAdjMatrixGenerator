#include "ad_scene.hpp"

/**
 * author   Arjun Albert
 * email    aalbert@mit.edu
 * date     11/26/2020
**/


json read_json(std::string file_name)
{
    std::ifstream file_in(file_name);
    json json_out;
    file_in >> json_out;
    return json_out;
}


std::string get_scene_description(json element)
{
    std::string element_description;
    element_description = element["description"];
    return element_description;
}


std::vector<std::string> get_objects_from_description(std::string description)
{
    std::string delimiter = ",";
    std::vector<std::string> objects;

    size_t pos = 0;
    std::string token;
    while ((pos = description.find(delimiter)) != std::string::npos) {
        token = description.substr(0, pos);
        objects.push_back(token);
        description.erase(0, pos + delimiter.length());
    }
    return objects;
}


bool is_duplicate_entity(std::string object)
{
    for (auto& element : entities) {
        if (element.compare(object) == 0){
            return true;
        }
    }
    return false;
}


int main()
{
    
    json j = read_json(scene_data_file_name);
    
    for (auto& element : j) {
        std::string description = get_scene_description(element);
        descriptions.push_back(description);
    }
    

    for (auto& description : descriptions) {
        std::vector<std::string> objects = get_objects_from_description(description);
        multi_level_descriptions.push_back(objects);
        for (auto& object : objects){
            bool result = is_duplicate_entity(object);
            if (!result){
                entities.push_back(object);
            }
        }
    }

    define_relationships(); 
    labelledAdjacencyGraph non_embedded_graph = form_knowledge_graph();

    labelledAdjacencyGraph embedded_graph = embed_knowledge_graph(non_embedded_graph);
}