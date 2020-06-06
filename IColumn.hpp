#ifndef _ICOLUMN_HPP_
#define _ICOLUMN_HPP_
#include <iostream>
#include "IValue.hpp"

class IColumn 
{
   public:
   virtual const char* getType()const =0;
   virtual const char* getNameColumn()const =0;
   virtual int getMaxRowWidth() const=0; //TODO:
   virtual int getSize()const=0;

   virtual IValue* getElement(int index)=0;
   virtual void addNullElement()=0;
   virtual void addElement(IValue* value)=0;
   virtual void updateElement(int index,IValue* value)=0;
   virtual void deleteElement(int index)=0;

   virtual ~IColumn()
   {
      std::cout<<"IColumn destructor called"<< std::endl;
   }
}; 

#endif