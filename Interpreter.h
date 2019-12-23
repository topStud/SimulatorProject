//
// Created by topaz on 03/11/2019.
//

#ifndef EX1_INTERPRETER_H
#define EX1_INTERPRETER_H

#include <string>
#include <map>
#include <stack>
#include <queue>
#include <iostream>

#include "Expression.h"
#include "VariableData.h"

class Interpreter {
  std::map<string, VariableData> *varData;
  stack<Expression *> numbers;
  static bool isNumber(const string &str);
  static bool isNumber(char i);
  static bool isVariable(const string &str);
  static bool isVariableChar(char i);
  static bool isOperator(const string &str);
  static bool isOperator(char str);
  static int precedence(const string &op);
  void createExpression(queue<string> &q);
  static vector<string> fromStringsToTokens(const string &strExp);
  static void checkBrackets(vector<string> v);
 public:
  Interpreter(std::map<std::string, VariableData> var_data);
  Expression *interpret(const std::string &strExp);
  ~Interpreter();
};

#endif //EX1_INTERPRETER_H
