#ifndef _ICOLUMN_HPP_
#define _ICOLUMN_HPP_
#include <iostream>
#include "IValue.hpp"

class IColumn 
{
   public:
   //returns type of column
   virtual const char* getType()const =0;
   // returns name of column
   virtual const char* getNameColumn()const =0;
   //returns the max row width of column
   virtual int getMaxRowWidth() const=0; 
   // returns number of rows
   virtual int getSize()const=0;

   // returns element at row index
   virtual IValue* getElement(int index)=0;
   // adds new row with null element
   virtual void addNullElement()=0;
   // adds a new row with given value
   virtual void addElement(IValue* value)=0;
   // changes row value at given index with <value>
   virtual void updateElement(int index,IValue* value)=0;
   // deletes row at index
   virtual void deleteElement(int index)=0;

   virtual ~IColumn()
   {
     // std::cout<<"IColumn destructor called"<< std::endl;
   }
}; 

#endif