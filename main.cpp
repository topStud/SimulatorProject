#include <iostream>
#include <map>

#include "Command.h"
#include "Client.h"
#include "utilities.h"
#include "Server.h"

map<std::string, Command *> utilities::commands_map;

int main(int argc, char *argv[]) {
  if (argc == 1) {
    std::cout << "file name was not delivered" << std::endl;
    return 1;
  }
  std::vector<std::string>* tokens = utilities::lexer(argv[1]);
  utilities::init_command_map();
  utilities::parser(*tokens,utilities::get_command_map());

  flag_stop_communication_client = true;
  flag_stop_communication_server = true;
  utilities::release_command_map();
  delete tokens;

  // after the end of the parser
  sleep(10);
  return 0;
}

