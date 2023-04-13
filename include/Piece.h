#pragma once

#include"Column.h"
#include"Row.h"
#include "Code.h"
#include<cctype> // for std::tolower
#include <utility>
#include <vector>


class Piece {
public:
    static enum class Color { WHITE, BLACK };

    Piece(Color color, char row, int col) : m_color(color),
        m_row(std::tolower(row)),
        m_col(static_cast<int>(col)) {}
    Piece(const Piece& other)
        : m_color(other.m_color), m_row(other.m_row), m_col(other.m_col) {}
    virtual ~Piece() {}
    virtual std::pair<Code, bool> isLegalMove(char to_row, int to_col, const std::vector<std::vector<Piece*>>& board) const = 0;
    virtual void updatePos(const char to_row, const int to_col) = 0;
    Color getColor() const { return m_color; }
    char getRow() const { return m_row; }
    int getCol() const { return m_col; }
    void setRow(char row) { m_row = row; }
    void setCol(int col) { m_col = col; }
    std::pair<Code, bool> checkSourceAndDest(char to_row, int to_col, const std::vector<std::vector<Piece*>>& board) const;
protected:
    Piece::Color m_color;
    char m_row;
    int m_col;
};
