#ifndef _INTCOLUMN_HPP_
#define _INTCOLUMN_HPP_
#include "List.hpp"
#include "IValue.hpp"
#include "IColumn.hpp"
#include "Int.hpp"
#include <iostream>
using namespace std;

class IntColumn : public IColumn
{
   List<Int> m_intcolumn;
   char* m_colname;
   int m_max_row_width;
    
   void copyFrom(const IntColumn& other); 
   public:
   //==THE BIG 4===
   IntColumn(const char* colname = "[no name]");
   IntColumn(const IntColumn& other) ;
   IntColumn& operator=(const IntColumn& other);
   virtual ~IntColumn(){
     delete[] m_colname;
     std::cout<<"IntColumn destructor called"<<std::endl;
   }

   virtual const char* getType()const override;
   virtual const char* getNameColumn()const override;
   virtual int getMaxRowWidth() const override;
   virtual int getSize()const override;

   virtual IValue* getElement(int index)override;
   virtual void addNullElement()override;
   virtual void addElement(IValue* value)override;
   virtual void updateElement(int index,IValue* value)override;
   virtual void deleteElement(int index)override;
};

#endif 