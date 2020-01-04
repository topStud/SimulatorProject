//
// Created by sigalit on 23.12.2019.
//

#include "utilities.h"

/**
 * is_exp function of class utilities.
 * returns true of the string is an expression.
 */
int utilities::is_exp(std::string str) {
    std::regex r("([a-zA-Z0-9]*[ ]?[*/+-][ ]?[a-zA-Z0-9]*[ ]?)*");
    return std::regex_match(str, r);
}

/**
 * lexer_helper function of class utilities.
 * the function receives a string and the vector of tokens.
 * the function handles cases of expressions and strings.
 */
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
            tokens->push_back(add_brackets_to_var(temp_s));
            return;
        }
        temp_s.clear();

        // checks if the token is part of a bigger string
        if (((token[0] == '"') ^ (token[token.length() - 1] == '"')) || part_of_str) {
            build_s += (token + " ");
            // beginning of string
            if (token[0] == '"'  && !part_of_str) {
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

/**
 * lexer function of class utilities.
 * the function gets a file name and opens a file according to it.
 * reads it and returns the tokens of the text.
 */
std::vector<std::string>* utilities::lexer(const char* file_name) {
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
    std::string bool_exp{};
    std::string bool_op{};
    std::string line_part{};
    // regex for identifying words
    std::regex words("[\ta-zA-Z>< -]+");
    // regex for bool expressions
    std::regex rgx ("[!=><]+");
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

        if (line.find("Print") != std::string::npos && line.find(',') != std::string::npos) {
          std::replace(line.begin(), line.end(), '(', ' ');
          std::replace(line.begin(), line.end(), ')', ' ');
          lexer_helper(line, tokens);
          continue;
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
            }
            // handles the while and the if option - with or without spaces
            else if (line.find("while") != -1 || line.find("if") != -1) {
                int index_key_word = line.find(' ');
                // enters the key_word "while" / "if"
                tokens->push_back(line.substr(0, index_key_word));
                //handles expression
                bool_exp = line.substr(index_key_word + 1, line.find('{') - index_key_word - 1);
                //regex
                std::sregex_token_iterator iter(bool_exp.begin(), bool_exp.end(), rgx, -1);
                std::sregex_token_iterator end;
                // first exp
                token = *iter;
                token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
                tokens->push_back(add_brackets_to_var(token));
                // finding op
                bool_op = bool_exp.substr(token.length(), bool_exp.length() - token.length() - (*++iter).length());
                bool_op.erase(std::remove(bool_op.begin(), bool_op.end(), ' '), bool_op.end());
                tokens->push_back(bool_op);
                // second exp
                token = *iter;
                token.erase(std::remove(token.begin(), token.end(), ' '), token.end());
                tokens->push_back(add_brackets_to_var(token));
                tokens->push_back("{");
                continue;
            } else if ((index = line.find('=')) != -1) {
                // in case there was tab before
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
                    // if a variable is declared with '='
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
            // continues to the next check
            lexer_helper(line_part, tokens);
        }
    }
    in_file.close();
    return tokens;
}

/**
 * add_brackets_to_var function of class utilities.
 * the function adds brackets to each variable (not declared, but variables in expressions)
 * returns the new expression after the brackets addition.
 */
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
  for (char i : expression) {
    if ((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z')) {
      if (!part_of_str) {
        new_exp += "(";
        part_of_str = true;
      }
    } else {
      // numbers can be part of the variable
      if (part_of_str && !(i >= '0' && i <= '9')) {
        new_exp += ")";
        part_of_str = false;
      }
    }
    new_exp += i;
  }
  if (part_of_str) {
    new_exp += ")";
  }
  return new_exp;
}

/**
 * init_command_map function of class utilities.
 * initializes the command map.
 */
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

/**
 * parser function of class utilities.
 * receives a vector of tokens and the command map.
 * goes through the tokens and generates the correct command each iteration.
 */
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
                int numOfArgs;
                if(vec[i]=="var" && vec[i+2]== "=")
                {
                    numOfArgs = 3;
                }
                else {
                    numOfArgs = c->getNumOfArgs();
                }
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

/**
 * calcBoolExp function of class utilities.
 * receives two values and a boolean operator.
 * compares the values according to the operator.
 * returns the result of the comparison - true/ false.
 */
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

/**
 * release_command_map function of class utilities.
 * releases all the allocated memory of the command map.
 */
void utilities::release_command_map() {
    for(auto & it : utilities::commands_map)
        delete it.second;
    utilities::commands_map.clear();
}
