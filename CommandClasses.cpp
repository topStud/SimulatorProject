//
// Created by topaz on 19/12/2019.
//
#include <thread>
#include <regex>
#include "CommandClasses.h"
#include "SymbolTable.h"
#include "Server.h"
#include "utilities.h"
#include "UpdateSimulator.h"

int OpenServerCommand::execute(std::list<std::string> info)
{
    auto* interpreter = new Interpreter(SymbolTable::get_instance()->get_main_map());
    Expression* e = interpreter->interpret(info.back());
    delete interpreter;
    int port= e->calculate();
    delete e;
    Server s(port);
    s.createSocket();
    s.bindSocket();
    s.listenAndAccept();
    std::thread serverThread(runServer,s);
    serverThread.detach();
    return OpenServerCommand::args_num;
}

int ConnectCommand::execute(std::list<std::string> info) {
  int port;
  std::string ip = *info.begin();
  ip.erase(std::remove(ip.begin(), ip.end(), '\"'), ip.end());
  // converting the string port to int
  std::stringstream ss(info.back());
  ss >> port;
  Client c(ip, port);
  std::thread client(start_sock, c);
  client.detach();
  return ConnectCommand::args_num;
}

int PrintCommand::execute(std::list<std::string> info) {
  if (info.back()[0] == '\"') {
    std::cout << info.back() << std::endl;
  } else {
    auto *i = new Interpreter(SymbolTable::get_instance()->get_main_map());
    Expression* e = i->interpret(info.back());
    std::cout << e->calculate() << std::endl;
    delete i;
    delete e;
  }
  return PrintCommand::args_num;
}

int SleepCommand::execute(std::list<std::string> info) {
  // converts number of seconds from string to int
  int mil_sec_n;
  auto *i = new Interpreter(SymbolTable::get_instance()->get_main_map());
  Expression* e = i->interpret(info.back());
  mil_sec_n = (int) e->calculate();
  std::chrono::milliseconds timespan(mil_sec_n);
  delete i;
  delete e;
  return SleepCommand::args_num;
}

int DefineVarCommand::execute(std::list<std::string> info) {
  // object foe keeping the variable data
  VariableData* vd= new VariableData();
  double val;
  bool is_regular_set = false;
  auto iter = info.begin();
  std::string key_main = *iter;
  std::string key_sim = info.back();
  iter++;

  if (*iter == "->" || *iter == "<-")
  {
    vd->set_arrow_dir(*iter);
    vd->set_sim(info.back());
    is_regular_set = false;
  }
  else if (*iter == "=")
  {
      is_regular_set = true;
      vd->set_value(get_exp_value(info.back()));
  }
  else
  {
    throw "wrong sign for variable";
  }

  //add to map
  if (vd->get_arrow() == "<-" || vd->get_arrow() == "->")
  {
      SymbolTable::get_instance()->add_to_sim(key_sim, vd);
  }
    SymbolTable::get_instance()->add_to_main(key_main, vd);

  return is_regular_set ? DefineVarCommand::args_num-1 : DefineVarCommand::args_num;
}

double DefineVarCommand::get_exp_value(std::string exp) {
  auto* interpreter = new Interpreter(SymbolTable::get_instance()->get_main_map());
  Expression* e = interpreter->interpret(exp);
  delete interpreter;
  double val = e->calculate();
  delete e;
  return val;
}

int SetValueCommand::execute(std::list<std::string> info) {
    auto* interpreter = new Interpreter(SymbolTable::get_instance()->get_main_map());
    Expression* e = interpreter->interpret(info.back());
    delete interpreter;
    double val = e->calculate();
    delete e;
    SymbolTable::get_instance()->get_value_from_main_map(info.front())->set_value(val);
    // inform the simulator of the value placement
    UpdateSimulator::get_instance()->add_update(info.front());
    return SetValueCommand::args_num;
}

int WhileCommand::execute(std::list<std::string> info) {
    string exp1 = info.front();
    info.pop_front();
    string op = info.front();
    info.pop_front();
    string exp2 = info.front();
    info.pop_front();

    auto* interpreter = new Interpreter(SymbolTable::get_instance()->get_main_map());
    Expression* e1 = interpreter->interpret(exp1);
    Expression* e2 = interpreter->interpret(exp2);
    delete interpreter;
    double val1 = e1->calculate();
    double val2 = e2->calculate();
    delete e1;
    delete e2;
    info.pop_front(); // remove '{'
    info.pop_back(); // remove '}'

    std::vector<string> vec(info.begin(),info.end());

    while (utilities::calcBoolExp(val1,op,val2))
    {
        utilities::parser(vec,utilities::get_command_map());
    }

    return 0;
}

int IfCommand::execute(std::list<std::string> info) {
    string exp1 = info.front();
    info.pop_front();
    string op = info.front();
    info.pop_front();
    string exp2 = info.front();
    info.pop_front();

    auto* interpreter = new Interpreter(SymbolTable::get_instance()->get_main_map());
    Expression* e1 = interpreter->interpret(exp1);
    Expression* e2 = interpreter->interpret(exp2);
    delete interpreter;
    double val1 = e1->calculate();
    double val2 = e2->calculate();
    delete e1;
    delete e2;
    info.pop_front(); // remove '{'
    info.pop_back(); // remove '}'

    std::vector<string> vec(info.begin(),info.end());

    if (utilities::calcBoolExp(val1,op,val2))
    {
        utilities::parser(vec,utilities::get_command_map());
    }

    return 0;
}