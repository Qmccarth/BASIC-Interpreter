#include "command.h"
#include "arithmetic.h"

using namespace std;

Command::Command() {

}

Command::~Command() {

}

IfThenCommand::IfThenCommand(BoolExpression* bexp, int line) : Command(), bexp(bexp), line(line){

}

IfThenCommand::~IfThenCommand() {
    delete this->bexp;
    //delete this->jline;

}

string IfThenCommand::format() const {
    return "IF [" + this->bexp->format() + "] THEN <" + to_string(line) + ">";
}

int IfThenCommand::getvalue() const{
    return 0;
}

int IfThenCommand::work(vars &var){
    if(this->bexp->getbool(var))
        return line;
    else
        return -1;
}

PrintCommand::PrintCommand(NumericExpression* nexp) : Command(), nexp(nexp) {

}

PrintCommand::~PrintCommand() {
    delete this->nexp;

}

string PrintCommand::format() const {
    return "Print " + this->nexp->format();
}

int PrintCommand::getvalue() const{
    return 1;
}

int PrintCommand::work(vars &var){
    cout << this->nexp->getvalue(var) << endl;
    return 0;
}


LetCommand::LetCommand(VariableExpression* vexp, NumericExpression* nexp) : Command(), vexp(vexp), nexp(nexp) {

}

LetCommand::~LetCommand() {
    delete this->nexp;
    delete this->vexp;

}

string LetCommand::format() const {
    return "LET " + this->vexp->format() + " " + this->nexp->format();

}

int LetCommand::getvalue() const{
    return 2;
}

int LetCommand::work(vars &var){
    this->vexp->setvalue(this->nexp->getvalue(var), var);
    return 0;
    
}

GOTOCommand::GOTOCommand(int line) : Command(), line(line) {

}

GOTOCommand::~GOTOCommand() {
    //delete this->jline;
}

string GOTOCommand::format() const {
    return "GOTO <"  + to_string(line)  + ">";

}

int GOTOCommand::getvalue() const{
    return 3;
}

int GOTOCommand::work(vars &var){
    return line;
    
}

GOSUBCommand::GOSUBCommand(int line) : Command(), line(line) {

}

GOSUBCommand::~GOSUBCommand() {
    //delete this->jline;
}

string GOSUBCommand::format() const {
    return "GOSUB <" + to_string(line) + ">";

}

int GOSUBCommand::getvalue() const{
    return 4;
}

int GOSUBCommand::work(vars &var){
    return line;
    
}
ReturnCommand::ReturnCommand()  : Command(){

}

ReturnCommand::~ReturnCommand() {

}

string ReturnCommand::format() const {
    return "RETURN";

}

int ReturnCommand::getvalue() const{
    return 5;
}

int ReturnCommand::work(vars &var){
    return -1;
}


EndCommand::EndCommand() : Command(){

}

EndCommand::~EndCommand() {

}

string EndCommand::format() const {
    return "END";

}

int EndCommand::getvalue() const{
    return 6;
}

int EndCommand::work(vars &var){
    return -1;
}


