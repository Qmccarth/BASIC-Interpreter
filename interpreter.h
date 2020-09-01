#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <map>
#include <stack>
#include "command.h"
#include "arithmetic.h"
#include "bool_expression.h"

class Interpreter {
public:
    Interpreter(std::istream& in, std::map<int, Command*> &prog);
    ~Interpreter();
    std::map<int,Command*> m;
    std::stack<int> lineTracker;
    void write(std::ostream& out);
    int execute(std::map<int, Command*>::iterator &it, std::map<int, Command*> &m);
    vars var;


private:
    std::string const line;
    void parse(std::istream& in, std::map<int, Command*> &prog);
    Command* parse_command(std::stringstream &ss);
    //line_number* parse_line_number(string const line);
    NumericExpression* parse_numeric_expression(std::stringstream &ss);
    BoolExpression* parse_bool_expression(std::stringstream &ss);
    ConstantExpression* parse_constant_expression(std::stringstream &ss);
    VariableExpression* parse_variable_expression(std::stringstream &ss);
};

#endif
