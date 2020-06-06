#ifndef _STRING_HPP_
#define _STRING_HPP_
#include <iostream>
#include <fstream>
#include "IValue.hpp"

class String: public IValue
{
   char *m_text;
   int m_size;
   bool m_null;

   //--helper functions
   void initFrom(const char *text);
   void copyFrom(const String &other);
   void formatToString();
   void deleteatIndex(int index);

public:
   //--The Big 4--
   String(const char *text = "NULL");
   String(const char* formatted_text, int unused);
   String(const char c);
   String(const String &other);
   String &operator=(const String &other);
   ~String();

   virtual int getNumofChar()const override;
   virtual const char *getType() const override;
   virtual bool isNULL() const override;

   //==getters
   virtual int getIntValue() const override;
   virtual double getDoubleValue() const override;
   virtual const char *getCharValue() const override;

   //==operators redefinition
   virtual bool is_equal(IValue *rhs) const override;
   virtual bool is_bigger(IValue *rhs) const override;
   virtual bool is_smaller(IValue *rhs) const override;

   
   //--operators redefinition
  // bool operator==(String& other);
   char operator[](int index);
   char operator[] (int index) const;


   //--printing & getters --
  // bool isNULL()const;
    //inline int getSize()const {return m_size;} */

   //--string manipulations
   //returns boolean value if it has found given char
   bool isChar(const char ch) const;
   int indexOfChar(const char ch) const;
   void deleteChar(const char ch);
   const char *convertToChar() const;
};

std::ostream &operator<<(std::ostream &out, String &other);
std::ostream &operator<<(std::ostream &out, String const &other);
String &readStringFromFile(std::ifstream &infile);

#endif