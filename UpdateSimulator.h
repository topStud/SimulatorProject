//
// Created by topaz on 24/12/2019.
//

#ifndef SIMULATORPROJECT__UPDATESIMULATOR_H_
#define SIMULATORPROJECT__UPDATESIMULATOR_H_

#include <queue>
#include <string>

class UpdateSimulator {
  std::queue<std::string> priority_q;
  static UpdateSimulator* update_simulator_;
  UpdateSimulator() = default;
 public:
  static UpdateSimulator* get_instance();
  void add_update(std::string key);
  std::string pop_update();
  bool updates_available();
  ~UpdateSimulator();
};

#endif //SIMULATORPROJECT__UPDATESIMULATOR_H_
