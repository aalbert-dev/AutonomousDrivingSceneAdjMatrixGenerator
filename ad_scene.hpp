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

std::string all_entities[] {"with", "before", "after", "none", "self"};

struct labelledAdjacencyGraph{
    std::string name;
    std::vector<std::string> headers;
    std::vector<std::vector<std::string>> adjacency_matrix;
    std::vector<std::string> values;
};


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

    if (entity_1.compare(entity_2) == 0){
        return all_entities[4];
    }
    if (entity_1_level < 0 || entity_2_level < 0){
        return all_entities[3];
    }

    if (entity_1_level == entity_2_level){
        return all_entities[0];
    }else if (entity_1_level < entity_2_level){
        return all_entities[1];
    }else{
        return all_entities[2];
    }
}


inline std::vector<std::vector<std::string>> calculate_adjacency_matrix(){
    std::vector<std::vector<std::string>> adjacency_matrix;
    for (std::string s1: entities){
        std::vector<std::string> matrix_row;
        for (std::string s2: entities){
            std::string relation = get_relationship(s1, s2);
            matrix_row.push_back(relation);
        }
        adjacency_matrix.push_back(matrix_row);
    }
    return adjacency_matrix;
}


inline labelledAdjacencyGraph form_knowledge_graph()
{
    labelledAdjacencyGraph non_embedded_knowledge_graph;
    non_embedded_knowledge_graph.name = "Non embedded";
    non_embedded_knowledge_graph.headers = entities;
    for (std::string value: all_entities){
        non_embedded_knowledge_graph.values.push_back(value);
    }
    non_embedded_knowledge_graph.adjacency_matrix = calculate_adjacency_matrix();
    return non_embedded_knowledge_graph;
}


inline float score_entity_with_relation(labelledAdjacencyGraph graph, std::string entity, std::string relation)
{
    return 0.0;
}


inline float score_relationship(labelledAdjacencyGraph graph, std::string entity_1, std::string entity_2)
{
    std::string relation = get_relationship(entity_1, entity_2);
    return 0.0;
}


inline labelledAdjacencyGraph embed_knowledge_graph(labelledAdjacencyGraph graph)
{
    labelledAdjacencyGraph embedded_knowledge_graph;
    return embedded_knowledge_graph;
}


inline void calculate_embedding(std::string entity)
{
    float margin = 0;

    float pos_h_e = 0;
    float pos_t_e = 0;
    float pos_r_e = 0;

    float neg_h_e = 0;
    float neg_t_e = 0;
    float neg_r_e = 0;

    float pos_norm = 0;
    float neg_norm = 0;

    float pos = pow(pos_h_e + pos_r_e - pos_t_e, 2);
    float neg = pow(neg_h_e + neg_r_e - neg_t_e, 2);

    float loss = std::max(pos - neg + margin, (float) 0.0);
}
