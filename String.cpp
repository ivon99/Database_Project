#include "String.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

//--helper functions--
 void String::initFrom(const char* text)
 {
     if(text==nullptr)
     {
         text= (char*)"NULL";
         m_size=0;
         m_null=true;
        return ;
     }
    if(strcmp(text,"NULL")==0)
        m_null=true;
     else m_null=false; 

     m_size = strlen(text);
     cout<<"input text size is "<<m_size<<"and last char is "<<text[m_size-1];
     if((text[0]=='"')&&(text[m_size-1]=='"'))
     {
         m_text = new char[m_size];
        for(int i=0; i<m_size; i++)
        {
         m_text[i]=text[i];
        }
        cout<<"I've copied it!"<<endl;
        //formatToString();
        cout<<"size now is "<<m_size;
     }
     else 
     {
         cout<<"String should be enclosed in brackets!"<<endl;
         return ;
     }
 }

void String::copyFrom(const String& other)
{
    if(other.m_text==nullptr)
    {
        m_text= (char*)"";
        m_size=0;
        m_null=true;
        return ;
    }
    m_null=other.m_null;
    m_size=other.m_size;
    m_text= new char[m_size];
    for(int i=0; i<m_size; i++)
    {
        m_text[i]= other.m_text[i];
    }
}

void String::deleteatIndex(int index)
{
    m_size--;                         //"shrinks" the list by 1
   for(int i=index; i<m_size; i++)   //shifts all elements > index
    {
      m_text[i] = m_text[i+1];
    }
}

void String::formatToString()
{
    if((m_text[0]=='"') &&(m_text[m_size-1]=='"')) //truncates enclosing ""
    {
       deleteatIndex(0);
       deleteatIndex(m_size-1);
    }
   for(int i=0;i<m_size;i++)
   {
       if(m_text[i]=='"')
       {
           if(m_text[i-1]=='\\')
           {
               deleteatIndex(i-1);
           }
           if(m_text[i-1]!='\\')
           {
               deleteatIndex(i);
               cout<<"Incorrect inclusion of \" inside the string. The symbol will be truncated."<<endl; 
           }
       }
       if(m_text[i]=='\\')
       {
           if(m_text[i+1]=='\"')
           {
              ;
           }
           if(m_text[i+1]=='\\')
           {
               deleteatIndex(i+1);
           }
           if(m_text[i+1]!='\\')
           {
               deleteatIndex(i);
               cout<<"Incorrect inclusion of '\\' inside the string. The symbol will be truncated"<<endl;
           }
       }
   }
  cout<<"I've formatted it"<<endl;
} 

//--The big 4--
String::String(const char* text)
{
  initFrom(text);
  if(strcmp(text,"NULL")==0)
    m_null=true;
  else m_null=false; 
  cout<<"String constructor called"<<endl;
}

String::String(const char ch)
{
  
  initFrom(&ch);
}

String::String(const String& other)
{
   if(this!=&other)
   {
       copyFrom(other);
   }
}

String& String::operator=(const String& other)
{
    cout<<"String operator= inside"<<endl;
  if(this!=&other)
  {
      cout<<"This is different from other"<<endl;
    delete[] m_text;
    cout<<"Ive deleted the pointer or sth"<<endl;
    copyFrom(other);
  }
  cout<<"String operator= called"<<endl;
  return *this;
}

String::~String()
{
  delete[] m_text;
}

bool String::isNULL()const
{
    return m_null;
}

bool String::isChar(const char ch) const
{
   for(int i=0; i<m_size; i++)
   {
       if(m_text[i]==ch) return true;
   }
   return false;
}

int String::indexOfChar(const char ch) const
{
    for(int i=0; i<m_size; i++)
   {
       if(m_text[i]==ch) return i;
   }
   return -1;
}

void String::deleteChar(const char ch)
{
    int index= indexOfChar(ch);
    if(index==-1)
    {
        cout<<"Not able to find this char"<<endl;
        return ;
    }
    m_size--;                         //"shrinks" the list by 1
   for(int i=index; i<m_size; i++)   //shifts all elements > index
    {
      m_text[i] = m_text[i+1];
    }
}

bool String::operator==(String& other)
{
    if(other.m_size!=m_size) return false;
    for(int i=0; i<m_size;i++)
    {
        if(m_text[i]!=other.m_text[i])
        {
              return false;
        }
    }
    return true;
}

char String::operator[](int index)
{
    return m_text[index];
}

char String::operator[](int index) const
{
    return m_text[index];
}


std::ostream& operator<<(std::ostream& out,String& other)
{
    for(int i=0; i<other.getSize();i++)
    {
      out<<other[i];
    }
    return out;
}

std::ostream& operator<<(std::ostream& out,String const& other)
{
    for(int i=0; i<other.getSize();i++)
    {
      out<<other[i];
    }
    return out;
}

String& readStringFromFile(std::ifstream& infile)
{
    char* text=nullptr;
    infile>>text;
    String* str_ptr = new String(text);
    return *str_ptr;
}

const char* String::convertToChar() const
{
    char* ch_array=new char[m_size+1];
	for(int i=0;i <m_size; i++)
	{
		ch_array[i]= m_text[i];
	}
	ch_array[m_size] = 0;
	return ch_array;   
}