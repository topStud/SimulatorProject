//
// Created by topaz on 18/12/2019.
//

#include "VariableData.h"

/**
 * get_arrow function of class VariableData.
 * returns the arrow.
 */
std::string VariableData::get_arrow() const {
  return this->arrow_dir;
}

/**
 * get_sim function of class VariableData.
 * returns the sim.
 */
std::string VariableData::get_sim() const {
  return this->sim;
}

/**
 * get_get_value function of class VariableData.
 * returns the value.
 */
double VariableData::get_value() const {
  return this->value;
}

/**
 * set_arrow_dir function of class VariableData.
 * sets the value of the arrow;
 */
void VariableData::set_arrow_dir(std::string arrow) {
  this->arrow_dir = arrow;
}

/**
 * set_sim function of class VariableData.
 * sets the value of the sim;
 */
void VariableData::set_sim(std::string sim_str) {
  this->sim = sim_str;
}

/**
 * set_value function of class VariableData.
 * sets the value of the value;
 */
void VariableData::set_value(double val) {
  this->value = val;
}