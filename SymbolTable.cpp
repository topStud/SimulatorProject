//
// Created by topaz on 19/12/2019.
//

#include "SymbolTable.h"
SymbolTable *SymbolTable::symbol_table_ = nullptr;
bool SymbolTable::key_exists_server_map(const std::string& key) {
  auto iter = this->server_to_simulator.find(key);
  return (iter != this->server_to_simulator.end());
}

bool SymbolTable::key_exists_sim_map(const std::string &key) {
  auto iter = this->sim_to_server.find(key);
  return (iter != this->sim_to_server.end());
}

VariableData& SymbolTable::get_key_value_server(const std::string& key) {
  return this->server_to_simulator[key];
}

std::map<std::string, VariableData> SymbolTable::get_server_map() {
  return this->server_to_simulator;
}

void SymbolTable::add_to_server(std::string key, VariableData variable_data) {
  this->server_to_simulator.insert(std::pair<std::string, VariableData>(key, variable_data));
}

void SymbolTable::add_to_sim(std::string key, VariableData variable_data) {
  this->sim_to_server.insert(std::pair<std::string, VariableData>(key, variable_data));
}

SymbolTable* SymbolTable::get_instance() {
  if (!symbol_table_) {
    symbol_table_= new SymbolTable;
  }
  return symbol_table_;
}

SymbolTable::~SymbolTable() {
  delete symbol_table_;
}