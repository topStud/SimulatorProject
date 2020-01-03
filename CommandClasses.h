//
// Created by topaz on 13/12/2019.
//

#ifndef MILESTONE1__COMMANDCLASSES_H_
#define MILESTONE1__COMMANDCLASSES_H_
#include <list>
#include "Command.h"
#include "Client.h"
#include "VariableData.h"
#include "Expression.h"
#include "Interpreter.h"
#include "SymbolTable.h"
#include "Server.h"
#include "utilities.h"
#include "UpdateSimulator.h"

class OpenServerCommand: public Command {
 public:
  static const int args_num = 1;
  OpenServerCommand()= default;
  int execute(std::list<std::string> info) override;
  int getNumOfArgs() const override { return args_num;}
};

class ConnectCommand: public Command {
 public:
  static const int args_num = 2;
  ConnectCommand()= default;
  int execute(std::list<std::string> info) override;
  int getNumOfArgs() const override { return args_num;}
};

class DefineVarCommand: public Command {
 public:
  static const int args_num = 4;
  DefineVarCommand()= default;
  int execute(std::list<std::string> info) override;
  double get_exp_value(std::string exp);
  int getNumOfArgs() const override { return args_num;}
};

class PrintCommand: public Command {
 public:
  static const int args_num = 1;
  PrintCommand()= default;
  int execute(std::list<std::string> info) override;
  int getNumOfArgs() const override { return args_num;}
};

class SleepCommand: public Command {
 public:
  static const int args_num = 1;
  SleepCommand()= default;
  int execute(std::list<std::string> info) override;
  int getNumOfArgs() const override { return args_num;}
};

class SetValueCommand: public Command {
 public:
  static const int args_num = 3;
  SetValueCommand()= default;
  int execute(std::list<std::string> info) override;
  int getNumOfArgs() const override { return args_num;}
};

class WhileCommand: public Command {
public:
    WhileCommand()= default;
    int execute(std::list<std::string> info) override;
    int getNumOfArgs() const override { return 0;}
};

class IfCommand: public Command {
public:
    IfCommand()= default;
    int execute(std::list<std::string> info) override;
    int getNumOfArgs() const override { return 0;}
};

#endif //MILESTONE1__COMMANDCLASSES_H_
