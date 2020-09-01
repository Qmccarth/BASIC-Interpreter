#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <string>
#include <sstream>
#include "bool_expression.h"
//#include "line_number.h"
#include "arithmetic.h"

class Command {
public:
    virtual std::string format() const = 0;
    Command();
    virtual ~Command();
    virtual int getvalue() const = 0;
    virtual int work(vars &var) = 0;
    //string word;

private:
    
};

class PrintCommand : public Command{
    public:
    PrintCommand(NumericExpression* nexp);
    ~PrintCommand();
    virtual std::string format() const;
    virtual int getvalue() const;
    virtual int work(vars &var);
    private:
    NumericExpression* nexp;
    
};

class LetCommand : public Command{
    public:
    LetCommand(VariableExpression* vexp, NumericExpression* nexp);
    ~LetCommand();
    virtual std::string format() const;
    virtual int getvalue() const;
    virtual int work(vars &var);
    private:
    VariableExpression* vexp;
    NumericExpression* nexp;
    
};


class GOTOCommand : public Command{
    public:
    GOTOCommand(int line);
    ~GOTOCommand();
    virtual std::string format() const;
    virtual int getvalue() const;
    virtual int work(vars &var);
    private:
    int line;
};

class IfThenCommand : public Command{
    public:
    IfThenCommand(BoolExpression* bexp, int line);
    ~IfThenCommand();
    virtual std::string format() const;
    virtual int getvalue() const;
    virtual int work(vars &var);
    private:
       BoolExpression* bexp;
       int line;
    
};

class GOSUBCommand : public Command{
    public:
    GOSUBCommand(int line);
    ~GOSUBCommand();
    virtual std::string format() const;
    virtual int getvalue() const;
    virtual int work(vars &var);
    private:
    int line;
    //line_number* oline;

};

class ReturnCommand : public Command{
    public:
    ReturnCommand();
    ~ReturnCommand();
    virtual std::string format() const;
    virtual int getvalue() const;
    virtual int work(vars &var);
    private:
    //line_number* jline;
};

class EndCommand : public Command{
    public:
    EndCommand();
    ~EndCommand();
    virtual std::string format() const;
    virtual int getvalue() const;
    virtual int work(vars &var);
};

#endif
