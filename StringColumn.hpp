#ifndef _STRING_COLUMN_HPP_
#define _STRING_COLUMN_HPP_
#include "List.hpp"
#include "String.hpp"
#include "IColumn.hpp"
#include "IValue.hpp"

class StringColumn : public IColumn
{
    List<String*> m_stringcolumn;
    char *m_colname;
    unsigned int m_max_row_width;

    void copyFrom(const StringColumn &);

public:
    //==THE BIG 4===
    StringColumn(const char *colname = "[string no name]", int rows=0);
    StringColumn(const StringColumn &other);
    StringColumn &operator=(const StringColumn &other);
    virtual ~StringColumn()
    {
        delete[] m_colname;
        std::cout << "StringColumn destructor called" << std::endl;
    }

    //==getter==
    
    virtual const char *getType() const override;
    virtual const char *getNameColumn() const override;
    virtual int getMaxRowWidth() const override;
    virtual int getSize() const override;

    virtual IValue *getElement(int index) override;
    virtual void addNullElement() override;
    virtual void addElement(IValue *value) override;
    virtual void updateElement(int index, IValue *value) override;
    virtual void deleteElement(int index) override;
};

#endif