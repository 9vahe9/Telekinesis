#include "Cell.h"

#include <exception>
#include <utility>

std::ostream& operator<<(std::ostream& out, const std::vector<int>& ob)
{
    for (const auto& e : ob)
        std::cout << e << ' ';
    return out;
}

Cell::Cell()
{
}

Cell::Cell(const Cell& rhv)
    : m_Val(rhv.m_Val)
{
}

Cell::Cell(Cell&& rhv) noexcept
    : m_Val(std::move(rhv.m_Val))
{
}

Cell::Cell(int val)
    : m_Val(val)
{
}

Cell::Cell(double val)
    : m_Val(val)
{
}

Cell::Cell(char val)
    : m_Val(val)
{
}

Cell::Cell(bool val)
    : m_Val(val)
{
}

Cell::Cell(std::string val)
    : m_Val(std::move(val))
{
}

Cell::Cell(std::vector<int> vec)
    : m_Val(std::move(vec))
{
}

const Cell& Cell::operator=(const Cell& rhv)
{
    Cell{ rhv }.swap(*this);
    return *this;
}

const Cell& Cell::operator=(Cell&& rhv) noexcept
{
    Cell{ std::move(rhv) }.swap(*this);
    return *this;
}

const Cell& Cell::operator=(int rhv)
{
    Cell{ rhv }.swap(*this);
    return *this;
}

const Cell& Cell::operator=(double rhv)
{
    Cell{ rhv }.swap(*this);
    return *this;
}

const Cell& Cell::operator=(char rhv)
{
    Cell{ rhv }.swap(*this);
    return *this;
}

const Cell& Cell::operator=(bool rhv)
{
    Cell{ rhv }.swap(*this);
    return *this;
}

const Cell& Cell::operator=(std::string rhv)
{
    Cell{ std::move(rhv) }.swap(*this);
    return *this;
}

const Cell& Cell::operator=(std::vector<int> rhv)
{
    Cell{ std::move(rhv) }.swap(*this);
    return *this;
}

Cell::operator int()
{
    if (m_Val.index() == 0)
        return std::get<int>(m_Val);
    throw std::runtime_error("Cell does not hold an int.");
}

Cell::operator double()
{
    if (m_Val.index() == 1)
        return std::get<double>(m_Val);
    throw std::runtime_error("Cell does not hold a double.");
}

Cell::operator char()
{
    if (m_Val.index() == 2)
        return std::get<char>(m_Val);
    throw std::runtime_error("Cell does not hold a char.");
}

Cell::operator bool()
{
    if (m_Val.index() == 3)
        return std::get<bool>(m_Val);
    throw std::runtime_error("Cell does not hold a bool.");
}

Cell::operator std::string()
{
    if (m_Val.index() == 4)
        return std::get<std::string>(m_Val);
    throw std::runtime_error("Cell does not hold a string.");
}

Cell::operator std::vector<int>()
{
    if (m_Val.index() == 5)
        return std::get<std::vector<int>>(m_Val);
    throw std::runtime_error("Cell does not hold a vector.");
}

void Cell::swap(Cell& other) noexcept
{
    std::swap(other.m_Val, m_Val);
}

bool operator==(const Cell& lhv, const Cell& rhv)
{
    return lhv.m_Val == rhv.m_Val;
}

bool operator!=(const Cell& lhv, const Cell& rhv)
{
    return !(lhv == rhv);
}

std::ostream& operator<<(std::ostream& out, const Cell& ob)
{
    std::visit([&out](auto&& e) { out << e; }, ob.m_Val);
    return out;
}

std::istream& operator>>(std::istream& in, Cell& ob)
{
    std::string input;
    in >> input;

    // Trying to convert to int
    try
    {
        ob.m_Val = std::stoi(input);
    }
    catch (...)
    {
    }

    // Trying to convert to double
    try
    {
        ob.m_Val = std::stod(input);
    }
    catch (...)
    {
    }

    // Trying to convert to char
    if (input.size() == 1)
    {
        ob.m_Val = input[0];
    }

    // Trying to convert to bool
    if (input == "true" || input == "false")
        ob.m_Val = (input == "true");

    // Default to string
    ob.m_Val = input;
    return in;
}
