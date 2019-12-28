//
// Created by topaz on 19/12/2019.
//

#include "SymbolTable.h"
SymbolTable *SymbolTable::symbol_table_ = nullptr;

bool SymbolTable::is_key_exists_in_main_map(const std::string& key) {
  auto iter = this->main_map.find(key);
  return (iter != this->main_map.end());
}

bool SymbolTable::is_key_exists_in_sim_map(const std::string &key) {
  auto iter = this->sim_map.find(key);
  return (iter != this->sim_map.end());
}

VariableData* SymbolTable::get_value_from_main_map(const std::string& key) {
  return this->main_map[key];
}

VariableData* SymbolTable::get_value_from_sim_map(const std::string& key)
{
    return this->sim_map[key];
}

std::map<std::string, VariableData*>& SymbolTable::get_main_map() {
  return this->main_map;
}

/*std::map<std::string, VariableData*>& SymbolTable::get_sim_map()
{
    return this->sim_map;
}*/

void SymbolTable::add_to_main(std::string key, VariableData* variable_data) {
  this->main_map.insert(std::pair<std::string, VariableData*>(key, variable_data));
}

void SymbolTable::add_to_sim(std::string key, VariableData* variable_data) {
  this->sim_map.insert(std::pair<std::string, VariableData*>(key, variable_data));
}

SymbolTable* SymbolTable::get_instance() {
  if (!symbol_table_) {
    symbol_table_= new SymbolTable;
  }
  return symbol_table_;
}

SymbolTable::~SymbolTable() {
    for(auto it = main_map.begin(); it != main_map.end(); it++ )
        delete it->second;
    main_map.clear();

    for(auto it = sim_map.begin(); it != sim_map.end(); it++ )
        delete it->second;
    sim_map.clear();

    delete symbol_table_;
}