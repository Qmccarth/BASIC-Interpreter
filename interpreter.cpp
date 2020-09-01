#include "interpreter.h"
using namespace std;

Command* parse_command(std::stringstream &ss);
//line_number* parse_line_number(std::stringstream &ss);
NumericExpression* parse_numeric_expression(std::stringstream &ss);
BoolExpression* parse_bool_expression(std::stringstream &ss);
ConstantExpression* parse_constant_expression(std::stringstream &ss);
VariableExpression* parse_variable_expression(std::stringstream &ss);


void skip_WS(std::stringstream &ss){
    ss >> ws;
}

Interpreter::Interpreter(std::istream& in, std::map<int, Command*> &prog) {
    this->parse(in, prog);
}

Interpreter::~Interpreter() {
 

}

void Interpreter::parse(std::istream& in, std::map<int, Command*> &prog) {
    string line;
    while (getline(in, line)) {
        int lineNumber;
        stringstream ss(line);
        ss >> lineNumber;
        skip_WS(ss);
        Command* com = parse_command(ss);
        prog.insert(pair<int, Command*>(lineNumber, com));
    }
}

int Interpreter::execute(map<int, Command*>::iterator &it, map<int, Command*> &m){
    int tracker;
    //map<int, Command*>::iterator it = m.begin();
    do{
        tracker = it->second->getvalue();  
        if(tracker == 0){ //ifthen
    
            int buf;
            buf = it->second->work(var);
            
            map<int, Command*>::iterator mit = m.begin();
            mit = m.find(buf);
            if(buf == -1)
                ++it;
            else if(mit == m.end()){
                throw invalid_argument(": IF jump to non-existent line " + to_string(buf));
            }
            else{
            it = mit;
            }
        }
        else if(tracker ==1){ //print
            it->second->work(var);
            ++it;
        }
        else if(tracker ==2){ //let
            it->second->work(var);
            ++it;
        }
        else if(tracker ==3){ //goto
        
            int buf;
            buf = it->second->work(var);
            
            
            map<int, Command*>::iterator mit = m.begin();
            mit = m.find(buf);
            if(mit == m.end()){
                throw invalid_argument(": GOTO to non-existent line " + to_string(buf));
                return -1;
            }
            else{
                it = mit;
            }
        }
        else if(tracker ==4){ //Gosub
            int buf;
            int line = it->first;
            
            buf = it->second->work(var);        
            map<int, Command*>::iterator mit = m.begin();
            mit = m.find(buf);
            if(mit == m.end()){
                throw invalid_argument(": GOSUB to non-existent line " + to_string(buf));
                return -1;
            }
            else{
                it = mit;
                lineTracker.push(line);
            }
        }
        else if(tracker ==5){ //return
            if(lineTracker.empty()) {
                throw invalid_argument(": No matching GOSUB for RETURN");
                return -1;
            }
            int buf;
            buf = lineTracker.top();

            map<int, Command*>::iterator mit = m.begin();
            mit = m.find(buf);
            if(mit == m.end()){
                return -1;
            }
            else{
                it = ++mit;
                lineTracker.pop();
            }
        }
    } while(tracker != -1 && it != m.end());
    return -1;
}

Command* Interpreter::parse_command(std::stringstream &ss){
    skip_WS(ss);
    string command;
    ss >> command;
    skip_WS(ss);
   if(command == "IF"){
       int lineNumber;
       skip_WS(ss);
       BoolExpression* bexp = parse_bool_expression(ss);
       skip_WS(ss);
       string then;
       ss >> then;
       ss >> lineNumber;
       Command* com = new IfThenCommand(bexp, lineNumber);
       return com;

    }
    else if(command == "PRINT"){
        skip_WS(ss);
        NumericExpression* nexp = parse_numeric_expression(ss);
        Command* com = new PrintCommand(nexp);
        return com;
    }
    else if(command == "LET"){
        VariableExpression* vexp = parse_variable_expression(ss);
        skip_WS(ss);
        
        NumericExpression* nexp = parse_numeric_expression(ss);
           Command* com = new LetCommand(vexp, nexp);
           return com;       
        }
    else if(command == "GOTO"){ 
        int lineNumber;
        ss >> lineNumber;
        Command* com = new GOTOCommand(lineNumber);
        return com;
    }
    else if(command == "GOSUB"){
        int lineNumber;
        ss >> lineNumber;
        Command* com = new GOSUBCommand(lineNumber);
        return com;
    }
    else if(command == "RETURN"){
        Command* com = new ReturnCommand();
        return com;
    }
    else if(command == "END"){
        Command* com = new EndCommand();
        return com;
    } 
    else{
        return nullptr;
    }
}

NumericExpression* Interpreter::parse_numeric_expression(std::stringstream &ss){
char peek = ss.peek();
skip_WS(ss);
if(isdigit(peek) || peek == '-'){ //check if it is a constanst 
    return parse_constant_expression(ss);
}
else if(isalpha(peek)){
    return parse_variable_expression(ss);
}
else if(peek == '('){
    ss >> peek;
    skip_WS(ss);
    NumericExpression* left = parse_numeric_expression(ss);
    char endbra = ss.peek();
    if(endbra == ']' || endbra == ')')
        ss >> endbra;
    skip_WS(ss);
    char op;
    ss >> op;
    skip_WS(ss);
    NumericExpression* right = parse_numeric_expression(ss);
    skip_WS(ss);
    char endpar = ss.peek();
    if(endpar == ')' || endpar == ']'){
        ss >> endpar;
    }
    if(op == '+'){ //find operater
        return new AdditionExpression(left, right);
    }
    else if(op == '*'){
        return new MultiplicationExpression(left, right);
    }
    else if(op == '-'){
        return new SubtractionExpression(left, right);
    }
    else if(op == '/'){
        return new DivisionExpression(left, right);
    }

    }

    return NULL;

}




BoolExpression* Interpreter::parse_bool_expression(std::stringstream &ss){
skip_WS(ss);
NumericExpression* left = parse_numeric_expression(ss);
char endbra = ss.peek();
if(endbra == ']' || endbra == ')')
    ss >> endbra;
skip_WS(ss);
char op;
ss >> op;
skip_WS(ss);
NumericExpression* right = parse_numeric_expression(ss);
    if(op == '<'){ //find the operater
        return new LessThan(left, right);
        }
    else if(op == '>'){
        return new GreaterThan(left, right);
        }
    else if(op == '='){
        return new EqualTo(left, right);
        }
        else{
            return nullptr;
        }
}

ConstantExpression* Interpreter::parse_constant_expression(std::stringstream &ss){
int con;
ss >> con;
return new ConstantExpression(con);
}


VariableExpression* Interpreter::parse_variable_expression(std::stringstream &ss){
string buf = "";
char peek = ss.peek();
while(isalpha(peek)){
    ss >> peek;
    buf += peek;
    peek = ss.peek();
}
skip_WS(ss);
char array = ss.peek();
if(array == '['){
    ss >> array;
    skip_WS(ss);
    ArrayVariableExpression* a = new ArrayVariableExpression(buf, parse_numeric_expression(ss));
    char endpar;
    ss>> endpar;
    skip_WS(ss);
    return a;
}
else{
    IntVariableExpression* i = new IntVariableExpression(buf);
    return i;
}

}


void Interpreter::write(std::ostream& out) {
map<int, Command*>::iterator it;
    for(it = m.begin(); it != m.end(); ++it){
        out << to_string(it->first) + " " + it->second->format() << endl;
    }
}

