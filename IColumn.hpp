#ifndef _ICOLUMN_HPP_
#define _ICOLUMN_HPP_
#include <iostream>
#include "String.hpp"
#include "Double.hpp"
#include "Int.hpp"

class IColumn 
{
   public:
   virtual const char* getType() =0;
   virtual const char* getNameColumn() =0;
   virtual int getSize()=0;

   virtual Int getIntElement(int index)=0;
   virtual Double getDoubleElement(int index)=0;
   virtual const char* getStringElement(int index)=0;

   virtual void addNullInt()=0;
   virtual void addNullDouble()=0;
   virtual void addElement(int value)=0;
   virtual void addElement(double value)=0;
   virtual void addElement(String* value)=0;

   virtual void updateElement(int index,int value)=0;
   virtual void updateElement(int index,double value)=0;
   virtual void updateElement(int index,String* value)=0;

   virtual void deleteElement(int index)=0;

   virtual ~IColumn()
   {
      std::cout<<"IColumn destructor called"<< std::endl;
   }
}; 

#endif