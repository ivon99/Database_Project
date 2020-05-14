#ifndef _STRING_COLUMN_HPP_
#define _STRING_COLUMN_HPP_
#include "List.hpp"
#include "String.hpp"
#include "IColumn.hpp"

class StringColumn : public IColumn
{
  List<String> m_stringcolumn;
  char *m_colname;

  void copyFrom(const StringColumn &);

public:
  //==THE BIG 4===
  StringColumn(const char *colname = "[no name]");
  StringColumn(const StringColumn &other);
  StringColumn &operator=(const StringColumn &other);
  virtual ~StringColumn()
  {
    delete[] m_colname;
    std::cout << "StringColumn destructor called" << std::endl;
  }

  //==getter==
  virtual const char *getType() override;
  virtual const char *getNameColumn() override;
  virtual int getSize() override { return m_stringcolumn.getSize(); }

  //==methods==
  virtual int getIntElement(int index) override
  {
    index++;
    return -1;
  }
  virtual double getDoubleElement(int index) override
  {
    index++;
    return -1;
  }
  virtual const char *getStringElement(int index) override
  {
    return m_stringcolumn[index].convertToChar();
  }
  virtual void addElement(int value) override
  {
    value++;
    return;
  }
  virtual void addElement(double value) override
  {
    value++;
    return;
  }
  virtual void addElement(String value) override;

  virtual void updateElement(int index, int value) override
  {
    index--;
    value--;
    return;
  }
  virtual void updateElement(int index, double value) override
  {
    index--;
    value--;
    return;
  }
  virtual void updateElement(int index, String value) override;

  virtual void deleteElement(int index) override;

  void printColumn(); //FIXME: only for now, later to be properly displayed
};

#endif