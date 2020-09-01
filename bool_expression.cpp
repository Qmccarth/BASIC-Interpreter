#include "bool_expression.h"

using namespace std;

BoolExpression::BoolExpression() {
    
}

BoolExpression::~BoolExpression() {

}

GreaterThan::GreaterThan(NumericExpression* left, NumericExpression* right) : left(left), right(right) {

}

GreaterThan::~GreaterThan() {
    delete this->left;
    delete this->right;
}

string GreaterThan::format() const {
    return this->right->format() + " < " + this->left->format();
}

bool GreaterThan::getbool(vars &var) {
    if(this->left->getvalue(var) > this->right->getvalue(var))
        return true;
    else{
        return false;
    }
}

LessThan::LessThan(NumericExpression* left, NumericExpression* right) : left(left), right(right) {

}

LessThan::~LessThan() {
    delete this->left;
    delete this->right;
}

string LessThan::format() const {
    return this->left->format() + " < " + this->right->format();
}

bool LessThan::getbool(vars &var){
    if(this->left->getvalue(var) < this->right->getvalue(var))
        return true;
    else{
        return false;
    }
}

EqualTo::EqualTo(NumericExpression* left, NumericExpression* right) : left(left), right(right) {

}

EqualTo::~EqualTo() {
    delete this->left;
    delete this->right;
}

string EqualTo::format() const {
    return this->left->format() + " = " + this->right->format();
}

bool EqualTo::getbool(vars &var){
    if(this->left->getvalue(var) == this->right->getvalue(var))
        return true;
    else{
        return false;
    }
}
