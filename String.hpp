#ifndef _STRING_HPP_
#define _STRING_HPP_
#include <iostream>
#include <fstream>

class String
{
   char* m_text;
   int m_size;
   
  //--helper functions
  void initFrom(const char* text);
  void copyFrom(const String& other);
  void formatToString();
  void deleteatIndex(int index);

  public:
  //--The Big 4--
  	String(const char* text = "");
	String(const char c);
	String(const String& other);
	String& operator=(const String& other);
	~String();

   //--operators redefinition
   bool operator==(String& other);
   char operator[](int index);
   char operator[] (int index) const;


   //--printing & getters --
   
    inline int getSize()const {return m_size;}
 
   //--string manipulations
   //returns boolean value if it has found given char
   bool isChar(const char ch) const;
   int indexOfChar(const char ch) const;
   void deleteChar(const char ch);
   const char* convertToChar() const;
 
};

std::ostream& operator<<(std::ostream& out, String& other);
std::ostream& operator<<(std::ostream& out, String const& other);
String& readStringFromFile(std::ifstream& infile); 

#endif