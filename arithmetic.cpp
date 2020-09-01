#include "arithmetic.h"

using namespace std;




AdditionExpression::AdditionExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {

}

AdditionExpression::~AdditionExpression() {
    delete this->left;
    delete this->right;
}

string AdditionExpression::format() const {
    return "(" + this->left->format() + " + " + this->right->format() + ")";
}

int AdditionExpression::getvalue(vars &var) const {
    int x;
    x= (this->left->getvalue(var) + this->right->getvalue(var));
    return x;
}

SubtractionExpression::SubtractionExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {

}

SubtractionExpression::~SubtractionExpression() {
    delete this->left;
    delete this->right;
}

string SubtractionExpression::format() const {
    return "(" + this->left->format() + " - " + this->right->format() + ")";
}

int SubtractionExpression::getvalue(vars &var) const {
    int x;
    x= (this->left->getvalue(var) - this->right->getvalue(var));
    return x;
}

MultiplicationExpression::MultiplicationExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {

}

MultiplicationExpression::~MultiplicationExpression() {
    delete this->left;
    delete this->right;
}

string MultiplicationExpression::format() const {
    return "(" + this->left->format() + " * " + this->right->format() + ")";
}

int MultiplicationExpression::getvalue(vars &var) const {
    int x;
    x= (this->left->getvalue(var) * this->right->getvalue(var));
    return x;
}

DivisionExpression::DivisionExpression(NumericExpression* left, NumericExpression* right) : left(left), right(right) {

}

DivisionExpression::~DivisionExpression() {
    delete this->left;
    delete this->right;
}

string DivisionExpression::format() const {
    return "(" + this->left->format() + " / " + this->right->format() + ")";
}

int DivisionExpression::getvalue(vars &var) const {
    int x;
    if(this->right->getvalue(var)==0)
        throw invalid_argument(": Division by 0: " + this->left->format() + "=" + to_string(this->left->getvalue(var)) + "," + this->right->format() + "=0"); //throw error
    x= (this->left->getvalue(var) / this->right->getvalue(var));
    return x;
}

VariableExpression::VariableExpression() {

}

VariableExpression::~VariableExpression() {
    
}


IntVariableExpression::IntVariableExpression(std::string name) : name(name){

}

IntVariableExpression::~IntVariableExpression() {
    
}

string IntVariableExpression::format() const {
return name;
 }

int IntVariableExpression::getvalue(vars &var) const {
    map<string, int>::const_iterator it = var.int_var.begin();
    it = var.int_var.find(name);
    if(it == var.int_var.end())
        return 0;
    return it->second;
}

void IntVariableExpression::setvalue(int val, vars &var) const {
    var.int_var[name] = val;
}

ArrayVariableExpression::ArrayVariableExpression(std::string name, NumericExpression* index) : name(name), index(index) {

}

ArrayVariableExpression::~ArrayVariableExpression() {
    delete this->index;
}

string ArrayVariableExpression::format() const {
    return name + "[" + this->index->format() + "]";
}

int ArrayVariableExpression::getvalue(vars &var) const {
    map<std::string, std::map<int,int>>::iterator it = var.arr_var.begin();
    it = var.arr_var.find(name);
    if(it == var.arr_var.end())
        return 0;
    map<int, int>::iterator cit = it->second.begin();
    cit = it->second.find(this->index->getvalue(var));
    if(cit == it->second.end())
        return 0;
    return it->second[this->index->getvalue(var)];
}

void ArrayVariableExpression::setvalue(int input, vars &var) const {
    var.arr_var[name][this->index->getvalue(var)] = input;
}

ConstantExpression::ConstantExpression(int value) : value(value){

}

ConstantExpression::~ConstantExpression(){

}

string ConstantExpression::format() const{
    return to_string(value);
}

int ConstantExpression::getvalue(vars &var) const {
    return value;
}
