#pragma once

#include "Piece.h"

class King : public Piece {
public:
    King(Color color, char row, int col) : Piece(color, row, col) {}
    King(const King& other) : Piece(other.getColor(), other.getRow(), other.getCol()) {}
    std::pair<Code, bool> isLegalMove(char to_row, int to_col, const std::vector<std::vector<Piece*>>& board) const override;
    void updatePos(const char to_row, const int to_col) override;

private:

};
