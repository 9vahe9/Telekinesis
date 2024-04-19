#ifndef __SPREADSHEET__H__
#define __SPREADSHEET__H__

#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Cell.h"

class SpreadSheet
{
private:
    std::vector<std::vector<Cell>> m_Board;
    size_t                         m_RowCount = 0;
    size_t                         m_ColCount = 0;

private:
    class Column;

public:
    SpreadSheet();
    SpreadSheet(const SpreadSheet& rhv);
    SpreadSheet(SpreadSheet&& rhv) noexcept;
    SpreadSheet(size_t size);
    SpreadSheet(size_t row, size_t col);
    ~SpreadSheet() noexcept;

public:
    constexpr size_t row() const noexcept { return m_RowCount; }
    constexpr size_t col() const noexcept { return m_ColCount; }

public:
    SpreadSheet& operator=(const SpreadSheet& rhv) = default;
    SpreadSheet& operator=(SpreadSheet&& rhv)      = default;

public:
    Column       operator[](size_t pos);
    const Column operator[](size_t pos) const;

public:
    void swap(SpreadSheet& other) noexcept;
    void clear() noexcept;

    void mirrorH() noexcept;
    void mirrorV() noexcept;
    void mirrorD() noexcept;
    void mirrorSD() noexcept;
    void rotate(int cnt) noexcept;

    void removeRow(size_t row);
    void removeRows(std::initializer_list<size_t> rows);
    void removeCol(size_t col);
    void removeCols(std::initializer_list<size_t> cols);
    void resizeRow(size_t r);
    void resizeCol(size_t c);
    void resize(size_t r, size_t c);

    SpreadSheet slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols);

public:
    friend std::ostream& operator<<(std::ostream& out, const SpreadSheet& ob) noexcept; // beauty output using iomanip
                                                                                        // library
    friend bool operator==(const SpreadSheet& lhv, const SpreadSheet& rhv);
    friend bool operator!=(const SpreadSheet& lhv, const SpreadSheet& rhv);
};

class SpreadSheet::Column
{
private:
    std::vector<Cell>& m_Col;

public:
    explicit Column(std::vector<Cell>& col) noexcept;

public:
    Column()              = delete;
    Column(const Column&) = delete;
    Column(Column&&)      = delete;

public:
    const Column& operator=(const Column&) = delete;
    const Column& operator=(Column&&)      = delete;

public:
    Cell&       operator[](size_t pos);
    const Cell& operator[](size_t pos) const;
};

#endif //__SPREADSHEET__H__