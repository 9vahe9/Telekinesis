#ifndef __CELL__H__
#define __CELL__H__

#include <iostream>
#include <vector>
#include <string>
#include <variant>

std::ostream& operator<<(std::ostream& out, const std::vector<int>& ob);

class Cell
{
private:
    std::variant<int, double, char, bool, std::string, std::vector<int>> m_Val;

public:
    Cell();
    Cell(const Cell& rhv);
    Cell(Cell&& rhv) noexcept;
    Cell(int val);
    Cell(double val);
    Cell(char val);
    Cell(bool val);
    Cell(std::string val);
    Cell(std::vector<int> val);

    const Cell& operator=(const Cell& rhv);
    const Cell& operator=(Cell&& rhv) noexcept;
    const Cell& operator=(int rhv);
    const Cell& operator=(double rhv);
    const Cell& operator=(char rhv);
    const Cell& operator=(bool rhv);
    const Cell& operator=(std::string rhv);
    const Cell& operator=(std::vector<int> rhv);

    operator int();
    operator double();
    operator char();
    operator bool();
    operator std::string();
    operator std::vector<int>();

    void swap(Cell& other) noexcept;

    friend bool operator==(const Cell& lhv, const Cell& rhv);
    friend std::ostream& operator<<(std::ostream& out, const Cell& ob);
    friend std::istream& operator>>(std::istream& in, Cell& ob);
};

bool operator==(const Cell& lhv, const Cell& rhv);
bool operator!=(const Cell& lhv, const Cell& rhv);

std::ostream& operator<<(std::ostream& out, const Cell& ob);
std::istream& operator>>(std::istream& in, Cell& ob);

#endif //__CELL__H__