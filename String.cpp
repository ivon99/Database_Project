#include "String.hpp"
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

//--helper functions--
void String::initFrom(const char *text)
{
    if (text == nullptr)
    {
        text = (char *)"NULL";
        m_size = 0;
        m_null = true;
        return;
    }
    if (strcmp(text, "NULL") == 0)
        m_null = true;
    else
        m_null = false;

    m_size = strlen(text);
    m_text = new char[m_size + 1];
    for (int i = 0; i < m_size; i++)
    {
        m_text[i] = text[i];
    }
    formatToString();
    m_text[m_size] = '\0';
    m_size++;
}

void String::copyFrom(const String &other)
{
    if (other.m_text == nullptr)
    {
        m_text = (char *)"";
        m_size = 0;
        m_null = true;
        return;
    }
    m_null = other.m_null;
    m_size = other.m_size;
    m_text = new char[m_size];
    for (int i = 0; i < m_size; i++)
    {
        m_text[i] = other.m_text[i];
    }
}

void String::deleteatIndex(int index)
{
    m_size--;                            //"shrinks" the list by 1
    for (int i = index; i < m_size; i++) //shifts all elements > index
    {
        m_text[i] = m_text[i + 1];
    }
}

void String::formatToString()
{
    if ((m_text[0] == '"') && (m_text[m_size - 1] == '"')) //truncates enclosing ""
    {
        deleteatIndex(0);
        deleteatIndex(m_size - 1);
    }
    else
    {
        cout << "String should be enclosed in brackets!" << endl;
        return;
    }
    for (int i = 0; i < m_size; i++)
    {
        if (m_text[i] == '"')
        {
            int correct_index = 0;
            if (m_text[i - 1] == '\\')
            {
                deleteatIndex(i - 1);
                correct_index = i;
                continue;
            }
            if (m_text[i - 1] != '\\')
            {
                if (i != correct_index)
                {
                    deleteatIndex(i);
                    cout << "Incorrect inclusion of \" inside the string. The symbol will be truncated." << endl;
                }

                continue;
            }
            continue;
        }
        if (m_text[i] == '\\')
        {
            int index_correct = 0;
            if (m_text[i + 1] == '\"')
            {
                continue;
            }
            if (m_text[i + 1] == '\\')
            {
                index_correct = i;
                deleteatIndex(i + 1);
                continue;
            }
            if (m_text[i + 1] != '\\')
            {
                if (i != index_correct)
                {
                    deleteatIndex(i);
                    cout << "Incorrect inclusion of '\\' inside the string. The symbol will be truncated" << endl;
                }
                continue;
            }
            continue;
        }
    }
}

//--The big 4--
String::String(const char *text)
{
    initFrom(text);
    if (strcmp(text, "NULL") == 0)
        m_null = true;
    else
        m_null = false;
   // cout << "String constructor called" << endl;
}

String::String(const char *formatted_text, int unused)
{
    unused++;
    m_size = strlen(formatted_text);
    m_text = new char[m_size + 1];
    strcpy(m_text, formatted_text);
    m_null = false;
}

String::String(const String &other)
{
    if (this != &other)
    {
        copyFrom(other);
    }
}

String &String::operator=(const String &other)
{
    if (this != &other)
    {
        delete[] m_text;
        copyFrom(other);
    }
    //cout << "String operator= called" << endl;
    return *this;
}

String::~String()
{
    delete[] m_text;
}

int String::getNumofChar() const
{
    return m_size;
}

const char *String::getType() const
{
    return "string";
}

bool String::isNULL() const
{
    return m_null;
}

//==getters
int String::getIntValue() const
{
    cout << "Unable to convert string to int value." << endl;
    return -1;
}

double String::getDoubleValue() const
{
    cout << "Unable to convert string to double value." << endl;
    return -1;
}
const char *String::getCharValue() const
{
    return m_text;
}

//==operators redefinition
bool String::is_equal(IValue *rhs) const
{
    const char *rhs_text = rhs->getCharValue();
    int rhs_size = strlen(rhs_text);
    if (rhs_size != m_size)
        return false;
    for (int i = 0; i < m_size; i++)
    {
        if (m_text[i] != rhs_text[i])
        {
            return false;
        }
    }
    return true;
}

bool String::is_bigger(IValue *rhs) const
{
    IValue *unused = rhs;
    unused++;
    cout << "Unable to compare strings!" << endl;
    return false;
}
bool String::is_smaller(IValue *rhs) const
{
    IValue *unused = rhs;
    unused++;
    cout << "Unable to compare string!" << endl;
    return false;
}

char String::operator[](int index)
{
    return m_text[index];
}

char String::operator[](int index) const
{
    return m_text[index];
}

std::ostream &operator<<(std::ostream &out, String &other)
{
    for (int i = 0; i < other.getNumofChar(); i++)
    {
        out << other[i];
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, String const &other)
{
    for (int i = 0; i < other.getNumofChar(); i++)
    {
        out << other[i];
    }
    return out;
}
