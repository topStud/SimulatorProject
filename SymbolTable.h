//
// Created by topaz on 19/12/2019.
//

#ifndef MILESTONE1__SYMBOLTABLE_H_
#define MILESTONE1__SYMBOLTABLE_H_

#include <map>
#include "VariableData.h"

class SymbolTable {
  std::map<std::string, VariableData*> sim_map;
  std::map<std::string, VariableData*> main_map;
  static SymbolTable* symbol_table_;
  SymbolTable() : sim_map{}, main_map{} {}
 public:
  bool is_key_exists_in_main_map(const std::string& key);
  bool is_key_exists_in_sim_map(const std::string& key);
  VariableData* get_value_from_main_map(const std::string& key);
  VariableData* get_value_from_sim_map(const std::string& key);
  std::map<std::string, VariableData*>& get_main_map();
  //std::map<std::string, VariableData*>& get_sim_map();
  void add_to_main(std::string key, VariableData* variable_data);
  void add_to_sim(std::string key, VariableData* variable_data);
  static SymbolTable* get_instance();
  ~SymbolTable();
};

#endif //MILESTONE1__SYMBOLTABLE_H_
