#pragma once

#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(Color color, char row, rsize_t col) : Piece(color, row, col) {}
    ~Bishop() override {}
    std::pair<Code, bool> isLegalMove(char to_row, size_t to_col, const std::vector<std::vector<Piece*>>& board) const override;
    void updatePos(const char to_row, const size_t to_col) override { m_row = std::tolower(to_row); m_col = to_col; }

private:
    std::pair<Code, bool> checkPathClear(const char to_row, const size_t to_col, const std::vector<std::vector<Piece*>>& board) const;
};