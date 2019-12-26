//
// Created by sigalit on 23.12.2019.
//

#include "utilities.h"


int utilities::is_exp(std::string str) {
    std::regex r("([a-zA-Z0-9]*[ ]?[*/+-][ ]?[a-zA-Z0-9]*[ ]?)*");
    return std::regex_match(str, r);
}

// gets a string  without brackets. [not expression]
void utilities::lexer_helper(const std::string& str, std::vector<std::string>* tokens) {
    // helpful variables
    std::stringstream ss(str);
    std::string token{};
    std::string temp_s{};
    std::string build_s{};
    bool part_of_str = false;

    // check if string and handle it
    while(getline(ss, token, ' ')) {
        // check if expression
        temp_s = str.substr(str.find(token));
        if ((is_exp(temp_s))) {
            // erases all the spaces
            temp_s.erase(std::remove(temp_s.begin(), temp_s.end(), ' '), temp_s.end());
            tokens->push_back(temp_s);
            return;
        }
        temp_s.clear();

        // checks if the token is part of a bigger string
        if (((token[0] == '"') ^ (token[token.length() - 1] == '"')) || part_of_str) {
            build_s += (token + " ");
            // beginning of string
            if (token[0] == '"') {
                part_of_str = true;
            }
                // end of string
            else if (token[token.length() - 1] == '"') {
                part_of_str = false;
                tokens->push_back(build_s);
                build_s.clear();
            }
            continue;
        }
        if (!token.empty())
            tokens->push_back(token);
    }
}

std::vector<std::string> utilities::lexer(const char* file_name) {
    std::ifstream in_file {file_name};
    auto* tokens = new std::vector<std::string>;

    // check if opened successfully
    if (!in_file.is_open()) {
        throw "file was not opened successfully";
    }

    // helper variables
    std::string line{};
    std::string token{};
    std::string variable{};
    std::string expresion{};
    std::string line_part{};
    std::regex words("[\ta-zA-Z>< -]+");
    int index;

    while(!in_file.eof()) {
        std::getline(in_file, line);

        // deletes all the tabs
        std::replace(line.begin(), line.end(), '\t', ' ');
        // adds space before and after an arrow if needed
        if ((index = line.find("->")) != std::string::npos) {
            if (line[index - 1] != ' ')
                line = std::regex_replace(line, std::regex("->"), " ->");
            if (line[index + 1] != ' ')
                line = std::regex_replace(line, std::regex("->"), "-> ");
        } else if ((index = line.find("<-")) != std::string::npos) {
            if (line[index - 1] != ' ')
                line = std::regex_replace(line, std::regex("<-"), " <-");
            if (line[index + 1] != ' ')
                line = std::regex_replace(line, std::regex("<-"), "<- ");
        }
        std::stringstream ss1(line);
        while (getline(ss1, line_part, ',')) {
            // prevents empty strings to enter the vector
            if (line_part.empty()) {
                continue;
            }

            std::stringstream ss(line_part);
            // handles brackets
            getline(ss, token, '(');
            if(std::regex_match(token, words)){
                std::replace(line.begin(), line.end(), '(', ' ');
                std::replace(line.begin(), line.end(), ')', ' ');
                ss1 << line;
                std::replace(line_part.begin(), line_part.end(), '(', ' ');
                std::replace(line_part.begin(), line_part.end(), ')', ' ');
            } else if ((index = line.find('=')) != -1 && line.find("while") == -1 && line.find("if") == -1) {
                if (line[0] == ' ')
                    variable = line.substr(1, index - 1);
                else
                    variable = line.substr(0, index);
                expresion = line.substr(index + 1);
                expresion.erase(std::remove(expresion.begin(), expresion.end(), ' '), expresion.end());
                int idx;
                if ((idx = variable.find(' '))!= -1)
                {
                    string tmp_variable = variable.substr(0, idx);
                    if(tmp_variable == "var")
                    {
                        tokens->push_back(tmp_variable);
                        variable = variable.substr(idx +1);
                    }
                }
                variable.erase(std::remove(variable.begin(), variable.end(), ' '), variable.end());
                tokens->push_back(variable);
                tokens->push_back("=");
                tokens->push_back(add_brackets_to_var(expresion));
                continue;
            }

            lexer_helper(line_part, tokens);
        }
    }

    in_file.close();
    return *tokens;
}

std::string utilities::add_brackets_to_var(std::string expression) {
  // vars for the check
  std::regex r("(.*[a-zA-Z]+.*)*");
  // vars for the loop
  bool part_of_str = false;
  std::string new_exp{};

  // checks if there are characters in the expression
  if (!std::regex_match(expression, r)) {
    return expression;
  }

  // adds brackets around vars
  for (int i = 0; i < expression.length(); i++) {
    if ((expression[i] >= 'a' && expression[i] <= 'z') || (expression[i] >= 'A' && expression[i] <= 'Z')) {
      if (!part_of_str) {
        new_exp += "(";
        part_of_str = true;
      }
    } else {
      // numbers can be part of the variable
      if (part_of_str && !(expression[i] >= '0' && expression[i] <= '9')) {
        new_exp += ")";
        part_of_str = false;
      }
    }
    new_exp += expression[i];
  }
  if (part_of_str) {
    new_exp += ")";
  }
  return new_exp;
}

void utilities::init_command_map() {
    utilities::commands_map["openDataServer"] = new OpenServerCommand();
    utilities::commands_map["connectControlClient"] = new ConnectCommand();
    utilities::commands_map["var"] = new DefineVarCommand();
    utilities::commands_map["Print"] = new PrintCommand();
    utilities::commands_map["Sleep"] = new SleepCommand();
    utilities::commands_map["Set"] = new SetValueCommand();
    utilities::commands_map["while"] = new WhileCommand();
    utilities::commands_map["if"] = new IfCommand();
}

void utilities::parser(std::vector<std::string> vec,std::map<std::string, Command*> commandMap)
{
    int i = 0;
    while(i< vec.size())
    {
        if(commandMap.find(vec[i]) != commandMap.end())
        {
            Command* c= commandMap[vec[i]];
            std::list<std::string> args;
            if(vec[i] == "while" || vec[i] == "if")
            {
                i++;
                while (vec[i] != "}")
                {
                    args.push_back(vec[i]);
                    i++;
                }
                args.push_back(vec[i]);
            }
            else {
                int numOfArgs = c->getNumOfArgs();
                for (int k = 0; k < numOfArgs; k++) {
                    args.push_back(vec[i + 1 + k]);
                }
            }
            i+= c->execute(args)+1;
        }
        else
        {
            Command* c= commandMap["Set"];
            std::list<std::string> args;
            for(int k=0; k<3; k++)
            {
                args.push_back(vec[i+k]);
            }
            i+= c->execute(args);
        }
    }
}

bool utilities::calcBoolExp(double val1, string op, double val2)
{
    if(op == "<")
    {
        return val1 < val2;
    }
    else if(op == ">")
    {
        return val1 > val2;
    }
    else if(op == "<=")
    {
        return val1 <= val2;
    }
    else if(op == ">=")
    {
        return val1 >= val2;
    }
    else if(op == "==")
    {
        return val1 == val2;
    }
    else if(op == "!=")
    {
        return val1 != val2;
    }
    else
    {
        throw "unknown boolean operation";
    }
}