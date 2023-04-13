#pragma once

#include <vector>
#include <memory>
#include "King.h"
#include "Bishop.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Pawn.h"

class Board {

public:
    static const int BOARD_SIZE = 8;

    Board();
    void initialize();
    std::vector<std::vector<Piece*>> getPieces() const;
    std::vector<Piece*> getPieces(Piece::Color color) const;
    void movePiece(const char from_row, const int from_col, const char to_row, const int to_col);
    bool isKingInCheck(Piece::Color color, char from_row, int from_col, char to_row, int to_col) const;
    bool isCheckmate(Piece::Color color) const;

private:
    std::vector<Piece*> getAttackers(char row, int col, std::vector<Piece*> pieces) const;

    std::vector<std::vector<Piece*>> m_board;
    std::vector<Piece*> m_black_pieces;
    std::vector<Piece*> m_white_pieces;

};