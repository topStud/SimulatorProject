//
// Created by topaz on 03/11/2019.
//

#include "Operators.h"

// Variable
Variable &Variable::operator++() {
  this->value++;
  return *this;
}

Variable &Variable::operator++(int) {
  this->value++;
  return *this;
}

Variable &Variable::operator--() {
  this->value--;
  return *this;
}

Variable &Variable::operator--(int) {
  this->value--;
  return *this;
}

Variable &Variable::operator+=(double val) {
  this->value += val;
  return *this;
}

double Variable::calculate() {
  return this->value;
}

Variable &Variable::operator-=(double val) {
  this->value -= val;
  return *this;
}

Variable::~Variable() = default;

//------------------------------------------

// Value
double Value::calculate() {
  return this->val;
}

Value::~Value() = default;

//------------------------------------------

// Binary Operator
BinaryOperator::~BinaryOperator() {
  delete this->right;
  delete this->left;
}

double Plus::calculate() {
  return left->calculate() + right->calculate();
}

double Minus::calculate() {
  return left->calculate() - right->calculate();
}

double Mul::calculate() {
  return left->calculate() * right->calculate();
}

double Div::calculate() {
  if (right->calculate() != 0) {
    return left->calculate() / right->calculate();
  } else {
    throw "you cannot divide by zero";
  }
}

//------------------------------------------

// Unary Operator
UnaryOperator::~UnaryOperator() {
  delete this->e;
}

double UPlus::calculate() {
  return e->calculate();
}

double UMinus::calculate() {
  return -e->calculate();
}
