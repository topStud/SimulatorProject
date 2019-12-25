//
// Created by topaz on 18/12/2019.
//

#include "VariableData.h"

// -1 for left, 1 for right
std::string VariableData::get_arrow() const {
  return this->arrow_dir;
}

std::string VariableData::get_sim() const {
  return this->sim;
}

double VariableData::get_value() const {
  return this->value;
}

// 0 refers to left, 1 refers to right
void VariableData::set_arrow_dir(std::string arrow) {
  this->arrow_dir = arrow;
}

void VariableData::set_sim(std::string sim_str) {
  this->sim = sim_str;
}

void VariableData::set_value(double val) {
  this->value = val;
}