//
// Created by topaz on 19/12/2019.
//

#ifndef MILESTONE1__SYMBOLTABLE_H_
#define MILESTONE1__SYMBOLTABLE_H_

#include <map>
#include "VariableData.h"

class SymbolTable {
  std::map<std::string, VariableData> sim_to_server;
  std::map<std::string, VariableData> server_to_simulator;
  static SymbolTable* symbol_table_;
  SymbolTable() : sim_to_server{}, server_to_simulator{} {}
 public:
  bool key_exists_server_map(const std::string& key);
  bool key_exists_sim_map(const std::string& key);
  VariableData& get_key_value_server(const std::string& key);
  std::map<std::string, VariableData> get_server_map();
  void add_to_server(std::string key, VariableData variable_data);
  void add_to_sim(std::string key, VariableData variable_data);
  static SymbolTable* get_instance();
  ~SymbolTable();
};

#endif //MILESTONE1__SYMBOLTABLE_H_
