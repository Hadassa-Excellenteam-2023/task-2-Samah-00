#pragma once

#include <vector>
#include "Piece.h"

class Rook : public Piece {
public:
    Rook(Color color, char row, int col) : Piece(color, row, col) {}
    Rook(const Rook& other) : Piece(other.getColor(), other.getRow(), other.getCol()) {}
    std::pair<Code, bool> isLegalMove(char to_row, size_t to_col, const std::vector<std::vector<Piece*>>& board) const override;
    void updatePos(const char to_row, const size_t to_col) override;

private:
    bool isPathClear(char m_row, int m_col, char to_row, int to_col, const std::vector<std::vector<Piece*>>& board) const;
};