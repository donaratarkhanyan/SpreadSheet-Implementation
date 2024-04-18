#include "spread_sheet.h"

SpreadSheet::SpreadSheet()
    : SpreadSheet(2, 2)
{}

SpreadSheet::SpreadSheet(size_t size)
    : SpreadSheet(size, size)
{}

SpreadSheet::SpreadSheet(size_t row, size_t col)
    : m_row{row}
    , m_col{col}
    , m_arr{new Cell*[m_row]}
{
    for(int i = 0; i < m_row; ++i) {
        m_arr[i] = new Cell[m_col];
    }
}

SpreadSheet::SpreadSheet(const SpreadSheet& rhv)
    : m_row{rhv.m_row}
    , m_col{rhv.m_col}
    , m_arr{new Cell*[m_row]}
{
    for(int i = 0; i < m_row; ++i) {
        m_arr[i] = new Cell[m_col];
    }
    for(int i = 0; i < m_row; ++i) {
        for(int j = 0; j < m_col; ++j) {
            m_arr[i][j] = rhv.m_arr[i][j];
        }
    }
}

SpreadSheet::SpreadSheet (SpreadSheet&& rhv)
    : m_row{rhv.m_row}
    , m_col{rhv.m_col}
    , m_arr{new Cell*[m_row]}
{
    rhv.m_row = 0;
    rhv.m_col = 0;
    rhv.m_arr = nullptr;
}

const SpreadSheet& SpreadSheet::operator= (const SpreadSheet& rhv)
{
    if (this != &rhv) {
        for (int i = 0; i < m_row; ++i) {
            delete[] m_arr[i];   
        }
        delete m_arr;
        m_row = rhv.m_row;
        m_col = rhv.m_col;
        m_arr = new Cell*[m_row];

        for(int i = 0; i < m_row; ++i) {
            m_arr[i] = new Cell[m_col];
        }

        for(int i = 0; i < m_row; ++i) {
            for(int j = 0; j < m_col; ++i) {
                m_arr[i][j] = rhv.m_arr[i][j];
            }
        }
    }
    return *this;
}

const SpreadSheet& SpreadSheet::operator= (SpreadSheet&& rhv)
{
    if (this != &rhv) {
        for (int i = 0; i < m_row; ++i) {
            delete[] m_arr[i];
        }
        delete m_arr;
        m_row = rhv.m_row;
        m_col = rhv.m_col;
        m_arr = rhv.m_arr;
        rhv.m_arr = nullptr;
    }
    return *this;
}

void SpreadSheet::clear() noexcept 
{
    for (int i = 0; i < m_row; ++i) {
        delete[] m_arr[i];
    }
    delete[] m_arr;
    m_arr = nullptr;
    m_col = 0; 
    m_row = 0;
}

size_t SpreadSheet::row() const 
{
    return m_row;
}

size_t SpreadSheet::col() const 
{
    return m_col;
}

void SpreadSheet::resize_row(int new_row, int value)
{
    int size = m_row + new_row;
    Cell** tmp = new Cell*[size];
    for(int i = 0; i < size; ++i){
        tmp[i] = new Cell[m_col];
    }
    for(int i = 0; i < m_row; ++i){
        for(int j = 0; j < m_col; ++j){
            tmp[i][j] = m_arr[i][j];
        }
    }
    for(int i = m_row; i < size; ++i){
        for(int j = 0; j < m_col; ++j){
            tmp[i][j] = value;
        }
    }
    for(int i = 0; i < m_row; ++i){
        delete[] m_arr[i];
    }
    delete[] m_arr;
    m_arr = tmp;
    m_row = size;
    tmp = nullptr;
}

void SpreadSheet::resize_col(int new_col, int value)
{
    int size = m_col + new_col;
    Cell** tmp = new Cell*[m_row];
    for(int i = 0; i < m_row; ++i){
        tmp[i] = new Cell[size];
    }
    for(int i = 0; i < m_row; ++i){
        for(int j = 0; j < m_col; ++j){
            tmp[i][j] = m_arr[i][j];
        }
    }
    for(int i = 0; i < m_row; ++i){
        for(int j = m_col; j < size; ++j){
            tmp[i][j] = value;
        }
    }
    for(int i = 0; i < m_row; ++i){
        delete[] m_arr[i];
    }
    delete[] m_arr;
    m_arr = tmp;
    m_col = size;
    tmp = nullptr;
}

void SpreadSheet::resize(int new_row, int new_col, int value)
{
    resize_row(new_row, value);
    resize_col(new_col, value);
}

void SpreadSheet::mirrorH() 
{
    for(int i = 0; i < m_row / 2; ++i) { 
        for(int j = 0; j < m_col; ++j) {
            std::swap(m_arr[i][j], m_arr[m_row - i - 1][j]);
        }
    }
}

void SpreadSheet::mirrorV()
{
    for(int i = 0; i < m_row; ++i) {
        for(int j = 0; j < m_col / 2; ++j) {
            std::swap(m_arr[i][j], m_arr[i][m_col - j - 1]); 
        }
    }
}

void SpreadSheet::mirrorD()
{
    for(int i = 1; i < m_row; ++i) {
        for(int j = 0; j < i; ++j) {
            std::swap(m_arr[i][j], m_arr[j][i]);        
        }
    }
}

void SpreadSheet::mirrorSD()
{
     for(int i = 0; i < m_row; ++i) {
        for(int j = 0; j < m_col - i; ++j) {
            std::swap(m_arr[i][j], m_arr[m_row - 1 - j][m_col - 1 - i]);
        }
    }
}

void SpreadSheet::rotate(size_t count)
{
    bool flag = false;
    if (count < 0) {
        flag = true;
        count *= -1;
    }
    count = count % 4;
    if (count == 0) {
        return;
    }
    if (!flag) {
        for(int i = 0; i < count; ++i) {
            mirrorH();
            mirrorD();
        }
    } else {
        for(int i = 0; i < count; ++i) {  
            mirrorV();
            mirrorD();
        }
    }
}

void SpreadSheet::removeRow(size_t row)
{
    if (row >= m_row) {
        throw std::out_of_range("Invalid index.");
    }

    row -= 1;
    Cell** temp = new Cell*[m_row - 1];
    for (int i = 0, k = 0; i < m_row; ++i) {
        if (i == row) {
            continue;
        }
        temp[k] = new Cell[m_col];
        for (int j = 0; j < m_col; ++j) {
            temp[k][j] = m_arr[i][j];
        }
        ++k;
    }

    for (int i = 0; i < m_row; ++i) {
        delete[] m_arr[i];
    }
    delete[] m_arr;

    m_arr = temp;
    --m_row;
}

void SpreadSheet::removeRows(std::initializer_list<size_t> rows)
{
    auto it = rows.end(); 
    while (it != rows.begin()) {
        --it; 
        removeRow(*it); 
    }
}

void SpreadSheet::removeCol(size_t col)
{
    if (col >= m_col) {
        throw std::out_of_range("Invalid index.");  
    }

    col -= 1;
    Cell** temp = new Cell*[m_row];
    for (int i = 0; i < m_row; ++i) {
        temp[i] = new Cell[m_col - 1];
        for (int j = 0, k = 0; j < m_col; ++j) {
            if (j == col) {
                continue;
            }
            temp[i][k++] = m_arr[i][j];
        }
    }

    for (int i = 0; i < m_row; ++i) {
        delete[] m_arr[i];
    }
    delete[] m_arr;

    m_arr = temp;
    --m_col;
}

void SpreadSheet::removeCols(std::initializer_list<size_t> cols)
{
    auto it = cols.end();
    while (it != cols.begin()) {
        --it;
        removeCol(*it);
    }
}

SpreadSheet SpreadSheet::slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols)
{
    SpreadSheet slicedSheet;
    size_t numRows = rows.size();
    size_t numCols = cols.size();

    slicedSheet.m_row = numRows;
    slicedSheet.m_col = numCols;
    slicedSheet.m_arr = new Cell*[numRows];

    size_t rowIndex = 0;
    for (auto row : rows) {
        size_t colIndex = 0;
        slicedSheet.m_arr[rowIndex] = new Cell[numCols];
        for (auto col : cols) {
            slicedSheet.m_arr[rowIndex][colIndex] = m_arr[row - 1][col - 1];
            colIndex++;
        }
        rowIndex++;
    }
    return slicedSheet;    
}

SpreadSheet::~SpreadSheet()
{
    clear();
}

Proxy SpreadSheet::operator[] (size_t index)
{ 
    return  Proxy(m_arr[index]);
}

const Proxy SpreadSheet::operator[] (size_t index) const
{
    return Proxy(m_arr[index]);
}

Proxy::Proxy (Cell* ptr) 
    : m_ptr {ptr}
{}

Cell& Proxy::operator[] (size_t index) 
{
    return m_ptr[index];
}

const Cell& Proxy::operator[] (size_t index) const 
{
    return m_ptr[index];
}

std::ostream& operator<<(std::ostream& out, const SpreadSheet& rhv)
{
    int width = 8;
    double width_table = rhv.col() * 9.1;
    int h_line = 1;
    for (size_t i = 0; i < rhv.row(); ++i)
    {
        for(size_t k = 0; k < width_table; ++k)
        {
            out << std::setw(1) << "-";
        }
        out << "\n";
        for(size_t j = 0; j < rhv.col(); ++j)
       	{
            out << std::setw(h_line) << "|" << std::setw(width) << std::left << rhv[i][j];
        }
        out << std::setw(h_line) << "|";
        out << "\n";
    }
    for(size_t k = 0; k < width_table; ++k)
    {
        out << std::setw(1) << "-";
    }
    out << "\n";
    return out;
}

bool operator==(const SpreadSheet& lhs, const SpreadSheet& rhs)
{
    if ((lhs.col() != rhs.col()) || (lhs.row() != rhs.row())) {
        return false;
    }
    for (int i = 0; i < lhs.row(); ++i) {
        for (int j = 0; j < lhs.col(); ++j) {
            if (lhs[i][j] != rhs[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const SpreadSheet& lhs, const SpreadSheet& rhs)
{
    return !(lhs == rhs);
}


