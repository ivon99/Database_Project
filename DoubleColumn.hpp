#ifndef _DOUBLE_COLUMN_HPP_
#define _DOUBLE_COLUMN_HPP_
#include "List.hpp"
#include "IColumn.hpp"
#include "Double.hpp"

class DoubleColumn : public IColumn
{
   List<Double> m_doublecolumn;
   char* m_colname;
   unsigned int m_max_row_width;

   void copyFrom(const DoubleColumn&);

   public:
   //==THE BIG 4===
   DoubleColumn(const char* colname = "[double no name]",int rows=0);
   DoubleColumn(const DoubleColumn& other) ;
   DoubleColumn& operator=(const DoubleColumn& other);
   virtual ~DoubleColumn(){
     delete[] m_colname;
     std::cout<<"DoubleColumn destructor called"<<std::endl;
   }

   //==getter==
   
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