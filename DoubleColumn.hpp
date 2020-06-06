#ifndef _DOUBLE_HPP_
#define _DOUBLE_HPP_
#include <iostream>
#include "IValue.hpp"
using namespace std;

class Double : public IValue
{
    double m_double;
    bool m_null;

public:
    Double();
    Double(double value);
    virtual const char* getType() const override;
    virtual int getNumofChar() const override;
    virtual bool isNULL() const override;

    //==getters
    virtual int getIntValue() const override;
    virtual double getDoubleValue() const override;
    virtual const char *getCharValue() const override;

    //==operators redefinition
    virtual bool is_equal(IValue* rhs) const override;
    virtual bool is_bigger(IValue* rhs)const override;
    virtual bool is_smaller(IValue* rhs)const override;

    friend std::ostream &operator<<(std::ostream &out, const IValue* object);
};

std::ostream &operator<<(std::ostream &out, const IValue* object);

#endif