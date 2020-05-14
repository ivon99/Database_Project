#ifndef _INTCOLUMN_HPP_
#define _INTCOLUMN_HPP_
#include "List.hpp"
#include "IColumn.hpp"
#include "String.hpp"

class IntColumn : public IColumn
{
   List<int> m_intcolumn;
   char* m_colname;
    
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

   //==getter==
   virtual const char* getType() override;
   virtual const char* getNameColumn() override;
   virtual int getSize() override {return m_intcolumn.getSize();}

   //==methods==

   virtual void addElement(int value) override;
   virtual void addElement(double value)override 
   {
     value++; 
     return ;
     }
   virtual void addElement(String value) override 
   {
    value="NULL";  
    return;
   }
   virtual int getIntElement(int index)override { return m_intcolumn[index]; }
   virtual double getDoubleElement(int index)override 
   { index++;
     return -1;
     }
   virtual const char* getStringElement(int index) override 
   { index++;
     return "NULL";
     }

    virtual void updateElement(int index,int value) override; 
   virtual void updateElement(int index,double value) override
   {
        index--; value--;
        return ;
   }
   virtual void updateElement(int index,String value) override
   {
       index--; value="NULL";
       return ;
   }


   virtual void deleteElement(int index) override;
   void printColumn(); //FIXME: only for now, later to be properly displayed
};


#endif 