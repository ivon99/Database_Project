#ifndef _INT_HPP_
#define _INT_HPP_
#include <iostream>
#include "IValue.hpp"

/**
 * Class for Int values , inherits IValue
 */
class Int: public IValue
{
    //! value of the object
    int m_int;
   // bool m_null;

    public:
    // default constructor creating a null int value
    // sets null to true
    Int();
    // constructor creating object with provided int value
    // sets null to false
    Int(int value);
    // returns the type of object value : "int"
    virtual const char* getType() const override;
    // returns how many characters the int value consists of
    virtual int getNumofChar() const override;
    // returns true if a null object, and false if assigned a value
    virtual bool isNULL() const override;
   
    //==getters
    // returns the int value
    virtual int getIntValue()const override;
    // returns converted to double value , acts as a conversion operator
    virtual double getDoubleValue() const override;
    // returns int value as a char
    virtual const char* getCharValue() const override;

    //==operators redefinition
    // compares two Int values, returns true if they are equal
    virtual bool is_equal(IValue* rhs)const override;
    // compares two Int values, returns true if lhs is bigger than rhs
    virtual bool is_bigger(IValue* rhs)const override;
    // compares two Int values, returns true if lhs is smaller than rhs
    virtual bool is_smaller(IValue* rhs)const override;
};

#endif