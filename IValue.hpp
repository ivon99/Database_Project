#ifndef _IVALUE_HPP_
#define _IVALUE_HPP_

class IValue
{
    public:
    virtual const char* getType() const=0;
    virtual int getNumofChar() const=0;
    virtual bool isNULL() const =0;

    virtual int getIntValue()const =0;
    virtual double getDoubleValue() const =0;
    virtual const char *getCharValue() const =0;

    virtual bool is_equal(IValue* rhs) const =0;
    virtual bool is_bigger(IValue* rhs)const =0;
    virtual bool is_smaller(IValue* rhs)const =0;
};

#endif