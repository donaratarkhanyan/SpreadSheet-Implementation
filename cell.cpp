#include <sstream>
#include <iostream>
#include "cell.h"

Cell::Cell() 
    : m_cell("")
{}

Cell::Cell(int rhv) 
    : m_cell{std::to_string(rhv)}
{}

Cell::Cell(double rhv)
    : m_cell{std::to_string(rhv)}
{}

Cell::Cell(std::string rhv) 
    : m_cell{rhv}
{}

Cell::Cell(bool rhv)
    : m_cell{rhv ? "true" : "false"}
{}

Cell::Cell(char rhv)
    : m_cell {std::string(1, rhv)}
{}

Cell::Cell(const std::vector<int>& rhv)
{
    m_cell = "{";
    for (int i = 0; i < rhv.size(); ++i) {
        m_cell += std::to_string(rhv[i]) + " ,";
    }
    m_cell.pop_back();
    m_cell += "}";
}

Cell::Cell(const Cell& rhv)
    : m_cell{rhv.m_cell}
{}

Cell::Cell(Cell&& rhv) noexcept
    : m_cell(std::move(rhv.m_cell))
{}


Cell::operator int() 
{
    try {
        int x = std::stoi(m_cell);
        return x;
    } catch (...) {
        return 0;
    }
}
        
Cell::operator double() 
{
    try {
        double d = std::stod(m_cell);
        return d;
    } catch (...) {
        return 0.0;
    }
}

Cell::operator std::string() const
{
    return m_cell;
}

Cell::operator bool()
{
    return !m_cell.empty();
}

Cell::operator char() 
{
    if (!m_cell.empty()) {
        return m_cell[0];
    } else {
        return '\0';
    }
}

Cell::operator std::vector<int>() 
{
    std::vector<int> result;
    std::string tmp = m_cell;
    for (int i = 0; i < tmp.size(); ++i) {
        if (tmp[i] == '{' || tmp[i] == '}' || tmp[i] == ','){
            tmp[i] = ' ';
        }
    }
    std::stringstream ss(tmp);
    int num;
    while (ss >> num) {
        result.push_back(num);
    }
    return result;
}

Cell& Cell::operator= (const Cell& rhv)
{
    if (this != &rhv) {
        m_cell = rhv.m_cell;
    }
    return *this;
}

Cell& Cell::operator= (Cell&& rhv) noexcept
{
    if (this != &rhv) {
        m_cell = std::move(rhv.m_cell);
    }
    return *this;
}

Cell& Cell::operator= (int val)
{
    m_cell = (int)val;
    return *this;
}

Cell& Cell::operator= (double val)
{
    m_cell = (double)val;
    return *this;
}

Cell& Cell::operator= (std::string str)
{
    m_cell = str;
    return *this;
}

Cell& Cell::operator=(char rhv)
{
    m_cell = rhv;
    return *this;
}

Cell& Cell::operator= (bool rhv)
{
    m_cell = rhv ? "true" : "false";
    return *this;
}

Cell& Cell::operator= (const std::vector<int>& rhv)
{
    m_cell = "{";
    for (int i = 0; i < rhv.size(); ++i) {
        m_cell += std::to_string(rhv[i]) + " ,";
    }
    m_cell.pop_back();
    m_cell += "}";
    return *this;
}

bool operator== (const Cell& other1, const Cell& other2)
{
    return 1;// (std::string(other1) == std::string(other2));
}

bool operator!= (const Cell& other1, const Cell& other2) 
{
    return 1;//!(std::string(other1) == std::string(other2));
}


std::ostream& operator<< (std::ostream& out, const Cell& ob)
{
    out << std::string(ob);
    return out;
}


std::istream& operator>> (std::istream& in, Cell& ob)
{
    std::string s;
    in >> s;
    ob = Cell(s);
    return in;
}
