#include <iostream>
#include <map>
#include "Command.h"
#include "utilities.h"

// for each type of command keeps the name of the command with the appropriate command object
map<std::string, Command *> utilities::commands_map;
bool utilities::flag_stop_communication = false;
mutex utilities::server_mutex;
mutex utilities::client_mutex;

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
  utilities::flag_stop_communication = true;
  // memory release
  utilities::release_command_map();
  delete tokens;
  utilities::server_mutex.lock();
  utilities::client_mutex.lock();
  utilities::server_mutex.unlock();
  utilities::client_mutex.unlock();
  return 0;
}

