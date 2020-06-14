#ifndef _IVALUE_HPP_
#define _IVALUE_HPP_

/**
 * Abstract class describing a value
 */
class IValue
{
protected:
    // determines if a value is null
    bool m_null;

public:
    // returns type of value
    virtual const char *getType() const = 0;
    // returns number of char in a value
    virtual int getNumofChar() const = 0;
    // returns true if value is null
    virtual bool isNULL() const = 0;

    //returns int value
    //acts as a conversion method for non int values
    virtual int getIntValue() const = 0;
    //returns double value
    //acts as a conversion method for non int values
    virtual double getDoubleValue() const = 0;
    //returns pointer to array of characters for value
    virtual const char *getCharValue() const = 0;

    // returns true if two values are equal
    virtual bool is_equal(IValue *rhs) const = 0;
    // returns true if value is bigger that <rhs>
    virtual bool is_bigger(IValue *rhs) const = 0;
    // returns true is value is smaller than <rhs>
    virtual bool is_smaller(IValue *rhs) const = 0;
};

#endif