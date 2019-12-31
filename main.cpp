#include "Command.h"
#include "Client.h"
#include "utilities.h"
#include "Server.h"

// for each type of command keeps the name of the command with the appropriate command object
map<std::string, Command *> utilities::commands_map;

/**
 * main function of the program.
 * the function receives the name of the file it needs to interpret.
 * calls the lexer and then the parser,
 * at the end responsible for stopping the threads.
 * returns 0 if the program ran successfully.
 */
int main(int argc, char *argv[]) {
  // gets the name of the file as an input
  if (argc == 1) {
    std::cout << "file name was not delivered" << std::endl;
    return 1;
  }
  std::vector<std::string>* tokens = utilities::lexer(argv[1]);
  utilities::init_command_map();
  utilities::parser(*tokens,utilities::get_command_map());

  // terminates the threads
  flag_stop_communication_client = true;
  flag_stop_communication_server = true;
  // memory release
  utilities::release_command_map();
  delete tokens;

  return 0;
}

