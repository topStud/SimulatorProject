//
// Created by topaz on 18/12/2019.
//

#ifndef MILESTONE1__VARIABLEDATA_H_
#define MILESTONE1__VARIABLEDATA_H_

#include <string>

class VariableData {
  std::string sim;
  double value;
  int arrow_dir;
 public:
  VariableData() : sim{}, value(0), arrow_dir(0) {}
  std::string get_sim() const;
  double get_value() const;
  int get_arrow() const;
  void set_value(double val);
  void set_arrow_dir(std::string arrow);
  void set_sim(std::string sim_str);
};

#endif //MILESTONE1__VARIABLEDATA_H_
