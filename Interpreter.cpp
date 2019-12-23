//
// Created by topaz on 03/11/2019.
//

#include <cstring>
#include <algorithm>
#include <regex>

#include "Interpreter.h"
#include "Operators.h"

Interpreter::Interpreter(std::map<std::string, VariableData> symbol_table) {
  varData = new std::map<std::string, VariableData>(symbol_table);
}

Expression *Interpreter::interpret(const std::string &strExp) {
  stack<string> operators;
  queue<string> q;
  bool lastStrOp = false;
  bool numInBrackets = false;
  bool lastStrClosingBracket = false;
  string temp;
  // separates the string to tokens
  vector<string> token_v = fromStringsToTokens(strExp);
  checkBrackets(token_v);

  // interpret
  for (const string &str : token_v) {
    // init
    temp = "";
    // number goes to queue
    if (isNumber(str) || isVariable(str)) {
      if (!operators.empty() && operators.top() == "(")
        numInBrackets = true;
      lastStrOp = false;
      lastStrClosingBracket = false;
      q.push(str);
    }
      // operator goes to stack
    else if (isOperator(str)) {
      lastStrOp = true;
      // checking precedence of the operators
      while (!operators.empty() && (operators.top() != "(") &&
          (precedence(operators.top()) >= precedence(str))) {
        q.push(operators.top());
        operators.pop();
      }
      operators.push(str);
    }
      // a left bracket goes to stack
    else if (str == "(") {
      if (lastStrOp) {
        temp += operators.top();
        operators.pop();
        // first token/ between two braces
        if ((operators.empty() && q.empty()) || (!numInBrackets && !operators.empty()
            && operators.top() == "(" && !lastStrClosingBracket)) {
          if (temp == "+" || temp == "-") {
            temp += "#";
          } else {
            throw "bad input";
          }
        }
        operators.push(temp);
      }
      lastStrClosingBracket = false;
      operators.push(str);
    }
      // a right bracket removes from stack until the left bracket shows
    else if (str == ")") {
      lastStrClosingBracket = true;
      numInBrackets = false;
      if (lastStrOp) {
        throw "bad input";
      }
      lastStrOp = false;
      while (operators.top() != "(") {
        q.push(operators.top());
        operators.pop();
      }
      operators.pop();
    } else {
      throw "bad input";
    }
  }
  // moves all the operators left in the stack to the queue
  while (!operators.empty()) {
    q.push(operators.top());
    operators.pop();
  }
  createExpression(q);
  return numbers.top();
}

vector<string> Interpreter::fromStringsToTokens(const string &strExp) {
  // prepare variables
  bool isNumMin;

  string concat;
  int opCounter = 0;
  // for converting arr of chars to string
  string temp;

  //  an array of chars of the given input
  char *arr = new char[strExp.length() + 1];
  std::strcpy(arr, strExp.c_str());
  vector<string> token_v;

  for (unsigned i = 0; i < strExp.length(); i++) {
    // init bool
    if (i + 1 < strExp.length()) {
      // decides if the minus belongs to a number
      isNumMin = (arr[i] == '-' && isNumber(arr[i + 1]) && i == 0)
          || (arr[i] == '-' && isNumber(arr[i + 1]) && i != 0 && arr[i - 1] == '(');
    } else {
      isNumMin = false;
    }

    // concat variables and numbers
    if (isNumber(arr[i]) || isNumMin || isVariableChar(arr[i]) || arr[i] == '.') {
      // counts number of operators in a row
      if (arr[i] == '-')
        opCounter++;
      else
        opCounter = 0;
      concat += arr[i];
    } else {
      if (!concat.empty()) {
        token_v.push_back(concat);
        concat.erase();
      }

      // watching over the amount of operators in a row
      if (isOperator(arr[i])) {
        // can not have minus and than the variable without ()
        if (((arr[i] == '-' && i == 0) || (i + 1 < strExp.length() && arr[i - 1] == '('))
            && isVariableChar(arr[i + 1])) {
          throw "bad input";
        }
        opCounter++;
      } else {
        opCounter = 0;
      }

      // checking if there were more than one operator in a row
      if (opCounter > 1) {
        throw "bad input";
      }

      // casting from char to string
      temp.push_back(arr[i]);
      token_v.push_back(temp);
      temp.erase();
    }
  }
  // if the number did not enter the vector
  if (!concat.empty()) {
    token_v.push_back(concat);
  }

  delete[]arr;
  return token_v;
}

void Interpreter::checkBrackets(vector<string> v) {
  stack<int> stack;
  for (const string &s : v) {
    if (s == "(") {
      stack.push(1);
    } else if (s == ")") {
      if (stack.empty()) {
        throw "bad input";
      } else {
        stack.pop();
      }
    }
  }
  if (!stack.empty()) {
    throw "bad input";
  }
}

void Interpreter::createExpression(queue<string> &q) {
  // useful variables
  Expression *e = nullptr, *left = nullptr, *right = nullptr;

  while (!q.empty()) {
    // moving numbers to stack
    if (!isOperator(q.front())) {
      if (q.front() == "-#") {
        e = numbers.top();
        numbers.pop();
        numbers.push(new UMinus(e));
      } else if (q.front() == "+#") {
        e = numbers.top();
        numbers.pop();
        numbers.push(new UPlus(e));
      } else if (isNumber(q.front())) {
        numbers.push(new Value(strtod(q.front().c_str(), nullptr)));
        // string to double
      } else if (isVariable(q.front())) {
        if (varData->find(q.front()) != varData->end()) {
          numbers.push(new Variable(q.front(), varData->find(q.front())->second.get_value()));
        } else {
          throw "variable was not set";
        }
      }
      q.pop();
    } else {
      // taking out the expressions needed for the operator.
      right = numbers.top();
      numbers.pop();
      left = numbers.top();
      numbers.pop();
      if (q.front() == "*") {
        numbers.push(new Mul(left, right));
      } else if (q.front() == "/") {
        numbers.push(new Div(left, right));
      } else if (q.front() == "+") {
        numbers.push(new Plus(left, right));
      } else if (q.front() == "-") {
        numbers.push((new Minus(left, right)));
      } else if (q.front() == "-#") {
        numbers.push(new UMinus(e));
      } else if (q.front() == "+#") {
        numbers.push(new UPlus(e));
      }
      q.pop();
    }
  }
}

bool Interpreter::isNumber(const string &i) {
  regex r("-?([0-9]+.[0-9]+|[0-9]+)");
  return regex_match(i, r);
}

bool Interpreter::isNumber(char i) {
  return i <= 57 && i >= 48;
}

bool Interpreter::isVariable(const string &str) {
  regex r("(_*[a-zA-Z]|_[0-9])[0-9a-zA-Z_]*");
  return regex_match(str, r);
}

bool Interpreter::isVariableChar(char i) {
  return (i == '_') || (i >= 65 && i <= 90) || (i >= 97 && i <= 122);
}

bool Interpreter::isOperator(char x) {
  return x == '+' || x == '-' || x == '*' || x == '/';
}

bool Interpreter::isOperator(const string &str) {
  return str == "+" || str == "-" || str == "*" || str == "/";
}

int Interpreter::precedence(const string &op) {
  if (op == "*" || op == "/")
    return 1;
  else if (op == "-#" || op == "+#")
    return 2;
  else
    return 0;
}

Interpreter::~Interpreter() {
  delete varData;
}
