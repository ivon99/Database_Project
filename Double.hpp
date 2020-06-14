#ifndef _DOUBLE_HPP_
#define _DOUBLE_HPP_
#include <iostream>
#include "IValue.hpp"
using namespace std;

/**
 * Class for double values, inherits IValue
 */
class Double : public IValue
{
    double m_double; //!< saves the value of the object
   // bool m_null;

public:
    // default constructor creating a null double value
    // sets null to true
    Double();
    // constructor creating object with provided double value
    // sets null to false
    Double(double value);
    // returns the type of object value : "double"
    virtual const char* getType() const override;
    // returns how many characters the double value consists of
    virtual int getNumofChar() const override;
    // returns true if a null object, and false if assigned a value
    virtual bool isNULL() const override;

    //==getters
    // acts as a conversion operator to int
    virtual int getIntValue() const override;
    // returns value
    virtual double getDoubleValue() const override;
    // returns converted to int value as a char
    virtual const char *getCharValue() const override;

    //==operators redefinition
    // compares two Double values using epsilon comparison 
    // returns true if they are equal
    virtual bool is_equal(IValue* rhs) const override;
    // compares two Dobule values, returns true if lhs is bigger than rhs
    virtual bool is_bigger(IValue* rhs)const override;
    // compares two Double values, returns true if lhs is smaller than rhs
    virtual bool is_smaller(IValue* rhs)const override;

    friend std::ostream &operator<<(std::ostream &out, const IValue* object);
};

std::ostream &operator<<(std::ostream &out, const IValue* object);

#endif