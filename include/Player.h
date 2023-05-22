#pragma once

#include <vector>
#include "King.h"
#include "Queen.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include "Rook.h"

class Player {
public:
    static const int NUM_OF_PIECES = 6; // discluding the knights and the pawns.
    Player(Piece::Color color, Row row, Row pawn_row);
    ~Player();
    Piece::Color getColor() const;
    std::vector<Piece*> getPieces() const;
    std::pair<Code, bool> makeMove(char from_row, int from_col, char to_row, int to_col, const std::vector<std::vector<Piece*>>& board);
    void updatePieces(char from_row, int from_col, char to_row, int to_col);
    void updatePieces(char to_row, int to_col);

private:
    Piece::Color m_color;
    std::vector<Piece*> m_pieces;
};
