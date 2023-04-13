#pragma once

#include "Piece.h"


class Knight : public Piece {
public:
    Knight(Color color, char row, int col) : Piece(color, row, col) {}
    std::pair<Code, bool> isLegalMove(char to_row, int to_col, const std::vector<std::vector<Piece*>>& board) const override {
        return std::make_pair(Code::CODE_ZERO, true);
    }
    void updatePos(const char to_row, const int to_col) override {
        setRow(to_row);
        setCol(to_col);
    }
};
