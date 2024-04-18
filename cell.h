#ifndef CELL_H
#define CELL_H
#include <string>
#include <vector>

class Cell 
{
public:
    explicit Cell();
    explicit Cell(int rhv);
    explicit Cell(double rhv);
    explicit Cell(std::string rhv);
    explicit Cell(bool rhv);
    explicit Cell(char rhv);
    explicit Cell(const std::vector<int>& rhv);
    explicit Cell(const Cell& rhv);
    Cell(Cell&& rhv) noexcept;

    Cell& operator= (const Cell& rhv);
    Cell& operator= (Cell&& rhv) noexcept;
    Cell& operator= (int rhv);
    Cell& operator= (double rhv);
    Cell& operator= (char rhv);
    Cell& operator= (bool rhv);
    Cell& operator= (std::string rhv); 
    Cell& operator= (const std::vector<int>& rhv);
    
    operator int();
    operator double();
    operator std::string() const;
    operator bool(); 
    operator char(); 
    operator std::vector<int>();

private:
    std::string m_cell;
};

bool operator== (const Cell& lhv, const Cell& rhv);
bool operator!= (const Cell& lhv, const Cell& rhv);

std::ostream& operator<< (std::ostream& out, const Cell& ob);
std::istream& operator>> (std::istream& in, Cell& ob);

#endif // CELL_H
