#pragma once

#include "Piece.h"

class Queen : public Piece {
public:
    Queen(Color color, char row, int col) : Piece(color, row, col) {}
    virtual ~Queen() {}
    std::pair<Code, bool> isLegalMove(char to_row, int to_col, const std::vector<std::vector<Piece*>>& board) const override;
    virtual void updatePos(const char to_row, const int to_col) override;

private:
    std::pair<Code, bool> checkRookMove(char to_row, int to_col, const std::vector<std::vector<Piece*>>& board) const;
    std::pair<Code, bool> checkBishopMove(char to_row, int to_col, const std::vector<std::vector<Piece*>>& board) const;
    bool isBlockedPath(char to_row, int to_col, const std::vector<std::vector<Piece*>>& board) const;
};