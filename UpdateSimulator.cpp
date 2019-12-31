//
// Created by topaz on 24/12/2019.
//

#include "UpdateSimulator.h"

UpdateSimulator *UpdateSimulator::update_simulator_ = nullptr;

/**
 * add_update function of class UpdateSimulator.
 * adds key to the queue.
 */
void UpdateSimulator::add_update(std::string key) {
  this->priority_q.push(key);
}

/**
 * updates_available function of class UpdateSimulator.
 * returns true if the queue is not empty.
 */
bool UpdateSimulator::updates_available() {
  return !this->priority_q.empty();
}

/**
 * destructor of class UpdateSimulator.
 * releases the memory of the single instance of the class.
 */
UpdateSimulator::~UpdateSimulator() {
  delete update_simulator_;
}

/**
 * pop_update function of class UpdateSimulator.
 * pops a value from the queue and returns it.
 */
std::string UpdateSimulator::pop_update() {
  std::string key = this->priority_q.front();
  this->priority_q.pop();
  return key;
}

/**
 * get_instance function of class UpdateSimulator.
 * creates new instance of the class if does not exists yet.
 * returns it.
 */
UpdateSimulator* UpdateSimulator::get_instance() {
  if (!update_simulator_) {
    update_simulator_= new UpdateSimulator;
  }
  return update_simulator_;
}