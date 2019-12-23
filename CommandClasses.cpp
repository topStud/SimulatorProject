//
// Created by topaz on 19/12/2019.
//
#include <thread>
#include <regex>

#include "CommandClasses.h"
#include "SymbolTable.h"
#include "Server.h"
#include "utilities.h"

int OpenServerCommand::execute(std::list<std::string> info)
{
    auto* interpreter = new Interpreter(SymbolTable::get_instance()->get_server_map());
    Expression* e = interpreter->interpret(info.back());
    delete interpreter;
    int port= e->calculate();
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
  // converting the string port to int
  std::stringstream ss(info.back());
  ss >> port;
  Client c(ip, port);
  std::thread client(start_sock, c);
  client.detach();
  return ConnectCommand::args_num;
}

int PrintCommand::execute(std::list<std::string> info) {
  std::cout << info.back() << std::endl;
  return PrintCommand::args_num;
}

int SleepCommand::execute(std::list<std::string> info) {
  // converts number of seconds from string to int
  int mil_sec_n;
  std::stringstream ss(info.back());
  ss >> mil_sec_n;
  std::chrono::milliseconds timespan(mil_sec_n);
  return SleepCommand::args_num;
}

int DefineVarCommand::execute(std::list<std::string> info) {
  // object foe keeping the variable data
  VariableData vd;
  double val;

  auto iter = info.begin();
  std::string key = *iter;
  iter++;

  if (*iter == "->" || *iter == "<-") {
    vd.set_arrow_dir(*iter);
    vd.set_sim(info.back());
  } else if (*iter == "=") {
    if (is_expression(info.back())) {
      vd.set_value(get_exp_value(info.back()));
    } else if (is_number(info.back())){
      std::stringstream ss(info.back());
      ss >> val;
      vd.set_value(val);
    } else {
      // checks if key exists
      if (SymbolTable::get_instance()->key_exists_server_map(info.back())) {
        vd.set_value(SymbolTable::get_instance()->get_key_value_server(info.back()).get_value());
      }
    }
  } else {
    std::cout << "wrong sign for variable";
  }

  //add to map
  SymbolTable::get_instance()->add_to_server(key, vd);

  return DefineVarCommand::args_num;
}

bool DefineVarCommand::is_expression(std::string string) {
  std::regex r("(.*[-+/*].*)*");
  return std::regex_match(string, r);
}

bool DefineVarCommand::is_number(std::string string) {
  std::regex r("-?([0-9]+.[0-9]+|[0-9]+)");
  return std::regex_match(string, r);
}

double DefineVarCommand::get_exp_value(std::string exp) {
  auto* interpreter = new Interpreter(SymbolTable::get_instance()->get_server_map());
  Expression* e = interpreter->interpret(exp);
  delete interpreter;
  return e->calculate();
}

int SetValueCommand::execute(std::list<std::string> info) {
    auto* interpreter = new Interpreter(SymbolTable::get_instance()->get_server_map());
    Expression* e = interpreter->interpret(info.back());
    double val = e->calculate();
    SymbolTable::get_instance()->get_key_value_server(info.front()).set_value(val);
    return SetValueCommand::args_num;
}

int WhileCommand::execute(std::list<std::string> info) {
    string exp1 = info.front();
    info.pop_front();
    string exp2 = info.front();
    info.pop_front();
    string op = info.front();
    info.pop_front();

    auto* interpreter = new Interpreter(SymbolTable::get_instance()->get_server_map());
    Expression* e1 = interpreter->interpret(exp1);
    Expression* e2 = interpreter->interpret(exp2);
    double val1 = e1->calculate();
    double val2 = e2->calculate();

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
    string exp2 = info.front();
    info.pop_front();
    string op = info.front();
    info.pop_front();

    auto* interpreter = new Interpreter(SymbolTable::get_instance()->get_server_map());
    Expression* e1 = interpreter->interpret(exp1);
    Expression* e2 = interpreter->interpret(exp2);
    double val1 = e1->calculate();
    double val2 = e2->calculate();

    info.pop_front(); // remove '{'
    info.pop_back(); // remove '}'

    std::vector<string> vec(info.begin(),info.end());

    if (utilities::calcBoolExp(val1,op,val2))
    {
        utilities::parser(vec,utilities::get_command_map());
    }

    return 0;
}