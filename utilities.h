//
// Created by sigalit on 23.12.2019.
//

#ifndef SIMULATORPROJECT_UTILITIES_H
#define SIMULATORPROJECT_UTILITIES_H

#include <iostream>
// lexer
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <algorithm>
#include <map>

#include "CommandClasses.h"

class utilities {
  static std::string add_brackets_to_var(std::string);
  static int is_exp(string str);
  static void lexer_helper(const string &str, vector<std::string> *tokens);
  static map<std::string, Command *> commands_map;

public:
  static vector<std::string>* lexer(const char *file_name);
  static void parser(vector<std::string> vec, map<std::string, Command *> commandMap);
  static void init_command_map();
  static void release_command_map();
  static const map<std::string, Command *> &get_command_map() {return commands_map;}
  static  bool calcBoolExp(double exp1, string op, double exp2);
};


#endif //SIMULATORPROJECT_UTILITIES_H
