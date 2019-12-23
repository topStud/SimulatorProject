//
// Created by topaz on 12/12/2019.
//

#ifndef MILESTONE1__COMMAND_H_
#define MILESTONE1__COMMAND_H_

#include <list>

class Command {
 public:
  virtual int execute(std::list<std::string> info) = 0;
  virtual int getNumOfArgs() const = 0;
};

#endif //MILESTONE1__COMMAND_H_
