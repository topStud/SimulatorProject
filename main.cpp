#include <iostream>

// command map
#include <map>
#include "Command.h"
#include "CommandClasses.h"
#include "Client.h"
#include "utilities.h"
#include "Server.h"

map<std::string, Command *> utilities::commands_map;

int main(int argc, char *argv[]) {
  if (argc == 1) {
    std::cout << "file name was not delivered" << std::endl;
    return 1;
  }
  std::vector<std::string> tokens = utilities::lexer(argv[1]);
  for(const std::string& s: tokens) {
    std::cout << s << std::endl;
  }
  //tokens.clear();
  utilities::init_command_map();
  utilities::parser(tokens,utilities::get_command_map());

  flag_stop_communication_client = true;
  flag_stop_communication_server = true;

/*
  Command* var_c = new DefineVarCommand();
  std::list<std::string> var_l = {"roll", "=", "5"};
  std::list<std::string> var_l1 = {"alt", "=", "roll/70"};
  var_c->execute(var_l);
  var_c->execute(var_l1);
*/
    /*OpenServerCommand* serverCommand = new OpenServerCommand();
    std::list<std::string> inp = {"5400"};

    serverCommand->execute(inp);
*/
  // check sleep
/*  Command* slp = new SleepCommand();
  std::list<std::string> slp_list = {"3"};
  slp->execute(slp_list);
*/
  // print check
/*  Command* c = new PrintCommand();
  std::list<std::string> list = {"print something to the screen"};
  c->execute(list);
*/
  // connection check
/*
  Command* c1 = new ConnectCommand();
  std::list<std::string> list1 = {"127.0.0.1", "5402"};
  c1->execute(list1);

  // after the end of the parser
  sleep(5);
  flag_stop_communication = true;
*/
  return 0;
}

