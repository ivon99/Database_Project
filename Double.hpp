#ifndef _DOUBLE_HPP_
#define _DOUBLE_HPP_
#include <iostream>
using namespace std;

class Double
{
    double m_double;
    bool m_null;
    
    public:
    Double();
    Double(double value);
    bool isNULL() const;
    double getValue() const;

    //==operators redefinition
    bool operator==(Double& other);
    bool operator>(Double& other);
    bool operator<(Double& other);

    //==conversion operators
    operator double();

    friend std::ostream& operator<<(std::ostream& out,const Double& object);
};

std::ostream& operator<<(std::ostream& out,const Double& object);

#endif