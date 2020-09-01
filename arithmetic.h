#ifndef ARITHMETIC_HPP
#define ARITHMETIC_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <map>
#include <stack>

struct vars {
    std::map<std::string, int> int_var;
    std::map<std::string, std::map<int,int>> arr_var;
    
};

class NumericExpression {
public:
    virtual ~NumericExpression() {}
    virtual std::string format() const = 0;
    virtual int getvalue(vars &var) const = 0;
};

class ConstantExpression : public NumericExpression {
    public:
    ConstantExpression(int);
    ~ConstantExpression();
    virtual std::string format() const;
    virtual int getvalue(vars &var) const;
    private:
    int value;
};

class VariableExpression : public NumericExpression {
    public:
    VariableExpression();
    ~VariableExpression();
    virtual std::string format() const = 0;
    virtual int getvalue(vars &var) const = 0;
    virtual void setvalue(int val, vars &var) const = 0;
};

class IntVariableExpression : public VariableExpression {
    public:

    IntVariableExpression(std::string);
    ~IntVariableExpression();
    virtual std::string format() const;
    virtual int getvalue(vars &var) const;
    virtual void setvalue(int val, vars &var) const;

    private:
    std::string name;
    NumericExpression* value;
};

class ArrayVariableExpression : public VariableExpression {
    public:
    ArrayVariableExpression(std::string, NumericExpression*);
    ~ArrayVariableExpression();
    virtual std::string format() const;
    virtual int getvalue(vars &var) const;
    virtual void setvalue(int val, vars &var) const;

    private:
    NumericExpression* index;
    NumericExpression* value;
    std::string name;
};

class AdditionExpression : public NumericExpression {
public:
    AdditionExpression(NumericExpression* left, NumericExpression* right);
    ~AdditionExpression();
    virtual std::string format() const;
    virtual int getvalue(vars &var) const;

private:
    NumericExpression* left;
    NumericExpression* right;
};

class SubtractionExpression : public NumericExpression {
public:
    SubtractionExpression(NumericExpression* left, NumericExpression* right);
    ~SubtractionExpression();
    virtual std::string format() const;
    virtual int getvalue(vars &var) const;

private:
    NumericExpression* left;
    NumericExpression* right;
};

class DivisionExpression : public NumericExpression {
public:
    DivisionExpression(NumericExpression* left, NumericExpression* right);
    ~DivisionExpression();
    virtual std::string format() const;
    virtual int getvalue(vars &var) const;

private:
    NumericExpression* left;
    NumericExpression* right;
};

class MultiplicationExpression : public NumericExpression {
public:
    MultiplicationExpression(NumericExpression* left, NumericExpression* right);
    ~MultiplicationExpression();
    virtual std::string format() const;
    virtual int getvalue(vars &var) const;

private:
    NumericExpression* left;
    NumericExpression* right;
};


#endif
