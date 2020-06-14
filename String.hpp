#ifndef _STRING_HPP_
#define _STRING_HPP_
#include <iostream>
#include <fstream>
#include "IValue.hpp"

/**
 * Class for String values
 */
class String: public IValue
{
   char *m_text; //!< contains the text of the string
   int m_size; //!< keeps track of num of char in String
   //bool m_null;

   //--helper functions
   void initFrom(const char *text);
   void copyFrom(const String &other);
   // formats the string and checks for correct input
   void formatToString();
   // deletes char at given index
   void deleteatIndex(int index);

public:
   //--The Big 4--

   // constructor creating a null string if not provided with text or text is "NULL"
   // if text provided, creating string from unformatted text
   String(const char *text = "NULL");
   // constructor creating string from already formatted text
   String(const char* formatted_text, int unused);
   // copy constructor for String
   String(const String &other);
   // assignment operator for String
   String &operator=(const String &other);
   // destructor for String
   ~String();

   // returns the size of string
   virtual int getNumofChar()const override;
   // returns the type of the class : "string"
   virtual const char *getType() const override;
   // checks if string is null, returns true if null
   virtual bool isNULL() const override;

   //==getters
   // acts as a conversion operator: impossible conversion
   virtual int getIntValue() const override;
   // acts as a conversion to double operator: impossible conversion
   virtual double getDoubleValue() const override;
   // returns value as a pointer to array of char
   virtual const char *getCharValue() const override;

   //==operators redefinition
   // equivalent to strcmp, returns true if strings are the same
   virtual bool is_equal(IValue *rhs) const override;
   // undefined comparison for string
   virtual bool is_bigger(IValue *rhs) const override;
   // undefined comparison for string
   virtual bool is_smaller(IValue *rhs) const override;

   
   //--operators redefinition
   // returns char at index
   char operator[](int index);
   // returns char at index
   char operator[] (int index) const;

};
// output operator redefinition for string 
std::ostream &operator<<(std::ostream &out, String &other);
std::ostream &operator<<(std::ostream &out, String const &other);


#endif