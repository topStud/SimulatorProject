//
// Created by topaz on 19/12/2019.
//

#include "SymbolTable.h"
SymbolTable *SymbolTable::symbol_table_ = nullptr;

/**
 * is_key_exists_in_main_map function of class SymbolTable.
 * receives as a parameter a string that represents the name of the var - key to the map.
 * returns true if the key exists in the main map.
 */
bool SymbolTable::is_key_exists_in_main_map(const std::string& key) {
  auto iter = this->main_map.find(key);
  return (iter != this->main_map.end());
}

/**
 * is_key_exists_in_sim_map function of class SymbolTable.
 * receives as a parameter a string that represents the name of the var - key to the map.
 * returns true if the key exists in the sim map.
 */
bool SymbolTable::is_key_exists_in_sim_map(const std::string &key) {
  auto iter = this->sim_map.find(key);
  return (iter != this->sim_map.end());
}

/**
 * get_value_from_main_map function of class SymbolTable.
 * returns the value of the variable of the name - key.
 */
VariableData* SymbolTable::get_value_from_main_map(const std::string& key) {
  return this->main_map[key];
}

/**
 * get_value_from_sim_map function of class SymbolTable.
 * returns the value of the variable of the name - key.
 */
VariableData* SymbolTable::get_value_from_sim_map(const std::string& key) {
    return this->sim_map[key];
}

/**
 * get_main_map function of class SymbolTable.
 * returns the main map.
 */
std::map<std::string, VariableData*>& SymbolTable::get_main_map() {
  return this->main_map;
}

/**
 * get_sim_map function of class SymbolTable.
 * returns the sim map.
 */
std::map<std::string, VariableData*>& SymbolTable::get_sim_map()
{
    return this->sim_map;
}

/**
 * add_to_main function of class SymbolTable.
 * adds a new pair to the map according to the key and the value received as input.
 */
void SymbolTable::add_to_main(std::string key, VariableData* variable_data) {
  this->main_map.insert(std::pair<std::string, VariableData*>(key, variable_data));
}

/**
 * add_to_sim function of class SymbolTable.
 * adds a new pair to the map according to the key and the value received as input.
 */
void SymbolTable::add_to_sim(std::string key, VariableData* variable_data) {
  this->sim_map.insert(std::pair<std::string, VariableData*>(key, variable_data));
}

/**
 * get_instance function of class SymbolTable.
 * returns an instance of the class. there can only exists one.
 * we used a singleton pattern.
 * returns the instance.
 */
SymbolTable* SymbolTable::get_instance() {
  if (!symbol_table_) {
    symbol_table_= new SymbolTable;
  }
  return symbol_table_;
}

/**
 * destructor of class SymbolTable.
 * releases both maps and the instance of the calss.
 */
SymbolTable::~SymbolTable() {
    for(auto & it : main_map)
        delete it.second;
    main_map.clear();

    for(auto & it : sim_map)
        delete it.second;
    sim_map.clear();

    delete symbol_table_;
}