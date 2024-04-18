#ifndef SPREADSHEET
#define SPREADSHEET
#include <cstddef>
#include <iostream>
#include <iomanip>
#include "cell.h"


class Proxy 
{
public:
    explicit Proxy(Cell* ptr);

public:    
    Cell& operator[] (size_t index);
    const Cell& operator[] (size_t index) const;

private:
    Cell* m_ptr;
};


class SpreadSheet
{
public: 
   SpreadSheet();
   SpreadSheet(size_t size);
   SpreadSheet(size_t row, size_t col);
   SpreadSheet(const SpreadSheet& rhv);
   SpreadSheet(SpreadSheet&& rhv);
   const SpreadSheet& operator= (const SpreadSheet& rhv);
   const SpreadSheet& operator= (SpreadSheet&& rhv);
   ~SpreadSheet(); 

   Proxy operator[] (size_t index);
   const Proxy operator[] (size_t index) const;
   
   void clear() noexcept;
   size_t row() const;
   size_t col() const;
   void resize_row(int new_row, int value = 0);
   void resize_col(int new_col, int value = 0);
   void resize(int new_row, int new_col, int value = 0);

   void mirrorH();
   void mirrorV();
   void mirrorD();
   void mirrorSD();
   void rotate(size_t count);
   void removeRow(size_t row);
   void removeRows(std::initializer_list<size_t> rows);
   void removeCol(size_t col);
   void removeCols(std::initializer_list<size_t> cols);
   SpreadSheet slice(std::initializer_list<size_t> rows, 
                    std::initializer_list<size_t> cols);

private:
   size_t m_row;
   size_t m_col;
   Cell** m_arr;
};

std::ostream& operator<<(std::ostream& out, const SpreadSheet& ob);
bool operator==(const SpreadSheet& lhs, const SpreadSheet& rhs);
bool operator!=(const SpreadSheet& lhs, const SpreadSheet& rhs);

#endif // SPREADSHEET
