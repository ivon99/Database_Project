#ifndef _ICOLUMN_HPP_
#define _ICOLUMN_HPP_
#include <iostream>
#include "String.hpp"

class IColumn 
{
   public:
   virtual const char* getType() =0;
   virtual const char* getNameColumn() =0;
   virtual int getSize()=0;
   virtual int getIntElement(int index)=0;
   virtual double getDoubleElement(int index)=0;
   virtual const char* getStringElement(int index)=0;
   virtual void addElement(int value)=0;
   virtual void addElement(double value)=0;
   virtual void addElement(String value)=0;
   virtual ~IColumn()
   {
      std::cout<<"IColumn destructor called"<< std::endl;
   }
}; 

#endif