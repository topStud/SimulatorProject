//
// Created by topaz on 03/11/2019.
//

#ifndef EX1_EX1_H
#define EX1_EX1_H

#include <string>
#include "Expression.h"
#include "Interpreter.h"

class Value : public Expression {
  double val;
 public:
  explicit Value(double value) : val(value) {}
  double calculate() override;
  ~Value() override;
};

class BinaryOperator : public Expression {
 protected:
  Expression *left;
  Expression *right;
 public:
  BinaryOperator(Expression *e1, Expression *e2) : left(e1), right(e2) {}
  ~BinaryOperator() override;
};

class Variable : public Expression {
  std::string name;
  double value;
 public:
  Variable(std::string varName, double val) : name(std::move(varName)), value(val) {}
  Variable &operator++();
  Variable &operator++(int);
  Variable &operator--();
  Variable &operator--(int);
  Variable &operator+=(double val);
  Variable &operator-=(double val);
  double calculate() override;
  ~Variable() override;
};

class UnaryOperator : public Expression {
 protected:
  Expression *e;
 public:
  explicit UnaryOperator(Expression *exp) : e(exp) {}
  ~UnaryOperator() override;
};

// binary operator------------------------------------------------

class Plus : public BinaryOperator {
 public:
  Plus(Expression *e1, Expression *e2) : BinaryOperator(e1, e2) {}
  double calculate() override;
};

class Minus : public BinaryOperator {
 public:
  Minus(Expression *e1, Expression *e2) : BinaryOperator(e1, e2) {}
  double calculate() override;
};

class Mul : public BinaryOperator {
 public:
  Mul(Expression *e1, Expression *e2) : BinaryOperator(e1, e2) {}
  double calculate() override;
};

class Div : public BinaryOperator {
 public:
  Div(Expression *e1, Expression *e2) : BinaryOperator(e1, e2) {}
  double calculate() override;
};

// unary operator-----------------------------------------------

class UPlus : public UnaryOperator {
 public:
  explicit UPlus(Expression *exp) : UnaryOperator(exp) {}
  double calculate() override;
};

class UMinus : public UnaryOperator {
 public:
  explicit UMinus(Expression *exp) : UnaryOperator(exp) {}
  double calculate() override;
};
#endif //EX1_EX1_H
