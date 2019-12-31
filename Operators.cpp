//
// Created by topaz on 03/11/2019.
//

#include "Operators.h"

/**
 * operator++ function of class Variable.
 * returns the value incremented by one.
 */
Variable &Variable::operator++() {
  this->value++;
  return *this;
}

/**
 * operator++ function of class Variable.
 * returns the value incremented by one.
 */
Variable &Variable::operator++(int) {
  this->value++;
  return *this;
}

Variable &Variable::operator--() {
  this->value--;
  return *this;
}

/**
 * operator-- function of class Variable.
 * returns the value decremented by one.
 */
Variable &Variable::operator--(int) {
  this->value--;
  return *this;
}

/**
 * operator+= function of class Variable.
 * returns the result of the addition of the
 * current value with the given val.
 */
Variable &Variable::operator+=(double val) {
  this->value += val;
  return *this;
}

/**
 * calculate function of class Variable.
 * return the value of the variable.
 */
double Variable::calculate() {
  return this->value;
}

/**
 * operator-= function of class Variable.
 * returns the result of the subtraction of the
 * given val of the current value.
 */
Variable &Variable::operator-=(double val) {
  this->value -= val;
  return *this;
}

//------------------------------------------

/**
 * calculate function of the class Value.
 * returns the value.
 */
double Value::calculate() {
  return this->val;
}

//------------------------------------------

/**
 * destructor of the class BinaryOperator.
 * releases the memory of the two expressions.
 */
BinaryOperator::~BinaryOperator() {
  delete this->right;
  delete this->left;
}

/**
 * calculate function of class Plus.
 * returns the addition of the two expressions.
 */
double Plus::calculate() {
  return left->calculate() + right->calculate();
}

/**
 * calculate function of the class Minus.
 * returns the subtraction of the two expressions.
 */
double Minus::calculate() {
  return left->calculate() - right->calculate();
}

/**
 * calculate function of class Mul.
 * returns the multiplication of the two expressions.
 */
double Mul::calculate() {
  return left->calculate() * right->calculate();
}

/**
 * calculate function of class Div.
 * returns the division of the two expressions.
 * if the second expression equals to zero throws an exception.
 */
double Div::calculate() {
  if (right->calculate() != 0) {
    return left->calculate() / right->calculate();
  } else {
    throw "you cannot divide by zero";
  }
}

//------------------------------------------

/**
 * destructor of class UnaryOperator.
 * deletes the expression that used as the function field.
 */
UnaryOperator::~UnaryOperator() {
  delete this->e;
}

/**
 * calculate function of class UPlus.
 * returns the result of the calculation of the expression.
 */
double UPlus::calculate() {
  return e->calculate();
}

/**
 * calculate function of class UMinus.
 * returns the result of the calculation of
 * the expression with the opposite sign.
 */
double UMinus::calculate() {
  return -e->calculate();
}
