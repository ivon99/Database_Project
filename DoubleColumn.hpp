#ifndef _DOUBLE_COLUMN_HPP_
#define _DOUBLE_COLUMN_HPP_
#include "List.hpp"
#include "IColumn.hpp"
#include "String.hpp"

class DoubleColumn : public IColumn
{
   List<double> m_doublecolumn;
   char* m_colname;

   void copyFrom(const DoubleColumn&);

   public:
   //==THE BIG 4===
   DoubleColumn(const char* colname = "[no name]");
   DoubleColumn(const DoubleColumn& other) ;
   DoubleColumn& operator=(const DoubleColumn& other);
   virtual ~DoubleColumn(){
     delete[] m_colname;
     std::cout<<"DoubleColumn destructor called"<<std::endl;
   }

   //==getter==
   virtual const char* getType() override;
   virtual const char* getNameColumn() override;
   virtual int getSize() override {return m_doublecolumn.getSize();}
   virtual int getIntElement(int index) override 
   {
      index++;
      return -1;
   }
   virtual double getDoubleElement(int index) override 
   {
     return m_doublecolumn[index];
   }
   virtual const char* getStringElement(int index) override 
   {
      index++;
      return "NULL";
   }
   virtual void addElement(int value) override
   {
     value++; 
     return ;
     }
   virtual void addElement(double value)override;
   virtual void addElement(String* value) override 
   {
       value=nullptr; value++;
   }

   virtual void updateElement(int index,int value) override
    {
      index -- ; value--;
      return ;
    }
   virtual void updateElement(int index,double value) override;
   virtual void updateElement(int index,String* value) override
   {
       index--; value=nullptr; value++;
       return ;
   }
   
    virtual void deleteElement(int index) override;

   void printColumn(); //FIXME: only for now, later to be properly displayed
};

#endif