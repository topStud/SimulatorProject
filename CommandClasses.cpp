//
// Created by topaz on 19/12/2019.
//

#include <regex>
#include <thread>
#include "CommandClasses.h"

/**
 * execute function of class OpenServerCommand.
 * receives a list of strings as a parameter which contains an expression
 * interpreters the expression which is the port with it we create the server.
 * serverThread will run separately.
 * returns the number of strings we expect in the list - 1
 */
int OpenServerCommand::execute(std::list<std::string> info)
{
    int port = (int) Interpreter::get_exp_value(info.back(), SymbolTable::get_instance()->get_main_map());
    Server s(port);
    s.createSocket();
    s.bindSocket();
    s.listenAndAccept();
    std::thread server_thread(runServer,s);
    server_thread.detach();
    return OpenServerCommand::args_num;
}

/**
 * execute function of class ConnectCommand.
 * receives a list of strings as a parameter which contains an ip and port.
 * creates a client with the ip and port.
 * creates a thread with the name client which will run separately.
 * returns the number of strings we expect in the list - 2
 */
int ConnectCommand::execute(std::list<std::string> info) {
  std::string ip = *info.begin();
  ip.erase(std::remove(ip.begin(), ip.end(), '\"'), ip.end());
  int port = (int) Interpreter::get_exp_value(info.back(), SymbolTable::get_instance()->get_main_map());
  Client c(ip, port);
  std::thread client_thread(start_sock, c);
  client_thread.detach();
  return ConnectCommand::args_num;
}

/**
 * execute function of class PrintCommand.
 * receives a list of strings as a parameter which contains expression/ message
 * prints the message to the console.
 * returns the number of strings we expect in the list - 1
 */
int PrintCommand::execute(std::list<std::string> info) {
  // checks if a string or expression
  if (info.back()[0] == '\"') {
    std::cout << info.back() << std::endl;
  } else {
    std::cout << Interpreter::get_exp_value(info.back(), SymbolTable::get_instance()->get_main_map()) << std::endl;
  }
  return PrintCommand::args_num;
}

/**
 * execute function of class SleepCommand.
 * receives a list of strings as a parameter which contains expression.
 * makes the main thread to wait according to the expression given in the list.
 * the expression will be in milliseconds.
 * returns the number of strings we expect in the list - 1
 */
int SleepCommand::execute(std::list<std::string> info) {
  int mil_sec_n = (int) Interpreter::get_exp_value(info.back(), SymbolTable::get_instance()->get_main_map());
  std::chrono::milliseconds timespan(mil_sec_n);
  std::this_thread::sleep_for(timespan);
  return SleepCommand::args_num;
}

/**
 * execute function of class DefineVarCommand.
 * receives a list of strings as a parameter which contains a
 * declaration of a variable separated to tokens.
 * enters the variables to the symbol table.
 * main map will contain all declared variables and the sim map will
 * contain the variables which connect in some way to the simulator.
 * returns the number of strings we expect in the list - 4/5
 */
int DefineVarCommand::execute(std::list<std::string> info) {
  // object for keeping the variable data
  auto* vd= new VariableData();
  bool is_regular_set = false;
  std::string sim{};

  auto iter = info.begin();
  std::string key_main = *iter;
  std::string key_sim;
  iter++;

  // relates to simulator
  if (*iter == "->" || *iter == "<-")
  {
    vd->set_arrow_dir(*iter);
    sim = info.back();
    sim.erase(std::remove(sim.begin(), sim.end(), '\"'), sim .end());
    key_sim = sim;
    vd->set_sim(sim);
    is_regular_set = false;
  }
  // some var declared, not relates to the simulator
  else if (*iter == "=")
  {
      is_regular_set = true;
      vd->set_value(Interpreter::get_exp_value(info.back(), SymbolTable::get_instance()->get_main_map()));
  }
  else
  {
    throw "wrong sign for variable";
  }

  //add to map
  if (vd->get_arrow() == "<-")
  {
      SymbolTable::get_instance()->add_to_sim(key_sim, vd);
  }
  SymbolTable::get_instance()->add_to_main(key_main, vd);

  return is_regular_set ? DefineVarCommand::args_num-1 : DefineVarCommand::args_num;
}

/**
 * execute function of class SetValueCommand.
 * receives a list of strings as a parameter which contains name of var, =, and expression.
 * the function updates the value of the Variable and notifies that the simulator needs to be updated.
 * returns the number of strings we expect in the list - 3
 */
int SetValueCommand::execute(std::list<std::string> info) {
    double val = Interpreter::get_exp_value(info.back(), SymbolTable::get_instance()->get_main_map());
    SymbolTable::get_instance()->get_value_from_main_map(info.front())->set_value(val);
    // inform the simulator of the value placement
    UpdateSimulator::get_instance()->add_update(info.front());
    return SetValueCommand::args_num;
}

/**
 * execute function of class WhileCommand.
 * receives a list of strings as a parameter which contains the condition and the commands in the brackets.
 * checks if the condition holds and acts accordingly.
 * returns 0 (the calculation happens in the parser)
 */
int WhileCommand::execute(std::list<std::string> info) {
    string exp1 = info.front();
    info.pop_front();
    string op = info.front();
    info.pop_front();
    string exp2 = info.front();
    info.pop_front();

    double val1 = Interpreter::get_exp_value(exp1, SymbolTable::get_instance()->get_main_map());
    double val2 = Interpreter::get_exp_value(exp2, SymbolTable::get_instance()->get_main_map());

    info.pop_front(); // remove '{'
    info.pop_back(); // remove '}'

    std::vector<string> vec(info.begin(),info.end());

    while (utilities::calcBoolExp(val1,op,val2))
    {
        utilities::parser(vec,utilities::get_command_map());
        val1 = Interpreter::get_exp_value(exp1, SymbolTable::get_instance()->get_main_map());
        val2 = Interpreter::get_exp_value(exp2, SymbolTable::get_instance()->get_main_map());
    }
    return 0;
}

/**
 * execute function of class IfCommand.
 * receives a list of strings as a parameter which contains the condition and the commands in the brackets.
 * checks if the condition holds and acts accordingly.
 * returns 0 (the calculation happens in the parser)
 */
int IfCommand::execute(std::list<std::string> info) {
    string exp1 = info.front();
    info.pop_front();
    string op = info.front();
    info.pop_front();
    string exp2 = info.front();
    info.pop_front();

    double val1 = Interpreter::get_exp_value(exp1, SymbolTable::get_instance()->get_main_map());
    double val2 = Interpreter::get_exp_value(exp2, SymbolTable::get_instance()->get_main_map());

    info.pop_front(); // remove '{'
    info.pop_back(); // remove '}'

    std::vector<string> vec(info.begin(),info.end());

    if (utilities::calcBoolExp(val1,op,val2))
    {
        utilities::parser(vec,utilities::get_command_map());
    }
    return 0;
}