//
// Created by topaz on 24/12/2019.
//

#include "UpdateSimulator.h"
UpdateSimulator *UpdateSimulator::update_simulator_ = nullptr;
void UpdateSimulator::add_update(std::string key) {
  this->priority_q.push(key);
}

bool UpdateSimulator::updates_available() {
  return !this->priority_q.empty();
}

UpdateSimulator::~UpdateSimulator() {
  delete update_simulator_;
}

std::string UpdateSimulator::pop_update() {
  std::string key = this->priority_q.front();
  this->priority_q.pop();
  return key;
}

UpdateSimulator* UpdateSimulator::get_instance() {
  if (!update_simulator_) {
    update_simulator_= new UpdateSimulator;
  }
  return update_simulator_;
}