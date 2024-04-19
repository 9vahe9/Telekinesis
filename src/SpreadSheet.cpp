#include "SpreadSheet.h"

#include <iterator>
#include <utility>

SpreadSheet::SpreadSheet() = default;

SpreadSheet::SpreadSheet(const SpreadSheet& rhv)     = default;
SpreadSheet::SpreadSheet(SpreadSheet&& rhv) noexcept = default;

SpreadSheet::SpreadSheet(size_t size)
    : SpreadSheet(size, size)
{
}

SpreadSheet::Column SpreadSheet::operator[](size_t pos)
{
    return Column{ m_Board[pos] };
}

const SpreadSheet::Column SpreadSheet::operator[](size_t pos) const
{
    return Column{ const_cast<std::vector<Cell>&>(m_Board[pos]) };
}

SpreadSheet::SpreadSheet(size_t row, size_t col)
{
    m_RowCount = row;
    m_ColCount = col;

    m_Board.resize(row);
    for (auto& e : m_Board)
        e.resize(col);
}

SpreadSheet::~SpreadSheet() noexcept
{
    m_RowCount = 0;
    m_ColCount = 0;
}

void SpreadSheet::swap(SpreadSheet& other) noexcept
{
    std::swap(m_Board, other.m_Board);
    std::swap(m_RowCount, other.m_RowCount);
    std::swap(m_ColCount, other.m_ColCount);
}

void SpreadSheet::clear() noexcept
{
    m_Board.clear();
    m_RowCount = 0;
    m_ColCount = 0;
}

void SpreadSheet::mirrorH() noexcept
{
    std::reverse(m_Board.begin(), m_Board.end());
}

void SpreadSheet::mirrorV() noexcept
{
    for (auto& e : m_Board)
        std::reverse(e.begin(), e.end());
}

void SpreadSheet::mirrorD() noexcept
{
    for (auto i = 0; i < m_RowCount; ++i)
        for (auto j = 0; j < i; ++j)
            std::swap(m_Board[i][j], m_Board[j][i]);
}

void SpreadSheet::mirrorSD() noexcept
{
}

void SpreadSheet::rotate(int cnt) noexcept
{
    cnt %= 4;
    while (cnt--)
    {
        mirrorD();
        mirrorH();
    }
}

std::ostream& operator<<(std::ostream& out, const SpreadSheet& ob) noexcept
{
    for (const auto& e : ob.m_Board)
    {
        for (const auto& e2 : e)
            std::cout << e2 << ' ';
        std::cout << std::endl;
    }
    return out;
}

SpreadSheet::Column::Column(std::vector<Cell>& col) noexcept
    : m_Col(col)
{
}

Cell& SpreadSheet::Column::operator[](size_t pos)
{
    return m_Col[pos];
}

const Cell& SpreadSheet::Column::operator[](size_t pos) const
{
    return m_Col[pos];
}

bool operator==(const SpreadSheet& lhv, const SpreadSheet& rhv)
{
    return lhv.m_Board == rhv.m_Board;
}

bool operator!=(const SpreadSheet& lhv, const SpreadSheet& rhv)
{
    return !(lhv == rhv);
}

void SpreadSheet::removeRow(size_t row)
{
    m_Board.erase(m_Board.begin() + row);
    --m_RowCount;
}

void SpreadSheet::removeRows(std::initializer_list<size_t> rows)
{
    for (const auto e : rows)
        removeRow(e);
}

void SpreadSheet::removeCol(size_t col)
{
    for (auto& e : m_Board)
        e.erase(e.begin() + col);
    --m_ColCount;
}

void SpreadSheet::removeCols(std::initializer_list<size_t> cols)
{
    for (const auto col : cols)
        removeCol(col);
}

void SpreadSheet::resizeRow(size_t r)
{
    m_Board.resize(r, std::vector<Cell>{ m_ColCount });
    m_RowCount = r;
}

void SpreadSheet::resizeCol(size_t c)
{
    for (auto& row : m_Board)
        row.resize(c);
    m_ColCount = c;
}

void SpreadSheet::resize(size_t r, size_t c)
{
    resizeRow(r);
    resizeCol(c);
}

SpreadSheet SpreadSheet::slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols)
{
    SpreadSheet new_sheet{ rows.size(), cols.size() };
    auto        i = 0, j = 0;
    for (const auto row : rows)
    {
        for (const auto col : cols)
        {
            new_sheet[i][j] = m_Board[row][col];
            ++j;
        }
        j = 0;
        ++i;
    }
    return new_sheet;
}
