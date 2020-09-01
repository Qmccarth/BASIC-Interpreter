#ifndef BOOL_EXPRESSION_HPP
#define BOOL_EXPRESSION_HPP

#include <string>
#include <sstream>
#include "arithmetic.h"

class BoolExpression{
    public:
    BoolExpression();
    virtual ~BoolExpression();
    virtual std::string format() const = 0;
    virtual bool getbool(vars &var) = 0;
};

class GreaterThan : public BoolExpression{
    public:
    GreaterThan(NumericExpression* left, NumericExpression* right);
    ~GreaterThan();
    virtual std::string format() const;
    virtual bool getbool(vars &var);
    private:
        NumericExpression* left;
        NumericExpression* right;

};

class LessThan : public BoolExpression{
    public:
    LessThan(NumericExpression* left, NumericExpression* right);
    ~LessThan();
    virtual std::string format() const;
    virtual bool getbool(vars &var);
    private:
        NumericExpression* left;
        NumericExpression* right;
};

class EqualTo : public BoolExpression{
    public:
    EqualTo(NumericExpression* left, NumericExpression* right);
    ~EqualTo();
    virtual std::string format() const;
    virtual bool getbool(vars &var);
    private:
        NumericExpression* left;
        NumericExpression* right;
};


#endif
