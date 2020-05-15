#ifndef _INT_HPP_
#define _INT_HPP_
#include <iostream>

class Int
{
    int m_int;
    bool m_null;

    public:
    Int();
    Int(int value);
    bool isNULL() const;

    //==operators redefinition
    bool operator==(Int& other);
    bool operator>(Int& other);
    bool operator<(Int& other);

    //==conversion operators
    operator int();

    friend std::ostream& operator<<(std::ostream& out,const Int& object);
};

 std::ostream& operator<<(std::ostream& out,const Int& object);

#endif