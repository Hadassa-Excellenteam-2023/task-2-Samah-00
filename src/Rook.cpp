#include "Rook.h"

std::pair<Code, bool> Rook::isLegalMove(const char to_row, const int to_col, const std::vector<std::vector<Piece*>>& board) const {

    // Check the source and the destination tiles
    auto source_tile_check = checkSourceAndDest(to_row, to_col, board);
    if (source_tile_check.first != Code::CODE_ZERO) {
        return source_tile_check;
    }

    // Check if the move is legal for a rook (vertical or horizental)
    if (m_row != to_row && m_col != to_col)
        return std::make_pair(Code::CODE_21, false);

    // Check if the path to the destination is clear
    if (!isPathClear(m_row, m_col, to_row, to_col, board))
        return std::make_pair(Code::CODE_21, false);

    // Otherwise, it's a legal move
    return std::make_pair(Code::CODE_42, true);
}

// Check if there are any pieces blocking the path between the rook's current position and the destination
bool Rook::isPathClear(char m_row, int m_col, char to_row, int to_col, const std::vector<std::vector<Piece*>>& board) const
{
    if (m_row == to_row)
    {
        int step = m_col < to_col ? 1 : -1;
        for (int col = m_col + step; col != to_col; col += step)
        {
            if (board[m_row - 'a'][col] != nullptr)
                return false;
        }
    }
    else // m_col == to_col
    {
        int step = m_row < to_row ? 1 : -1;
        for (char row = m_row + step; row != to_row; row += step)
        {
            if (board[row - 'a'][m_col] != nullptr)
                return false;
        }
    }
    return true;
}

void Rook::updatePos(const char to_row, const int to_col) {
    // Update the piece's position
    setRow(to_row);
    setCol(to_col);
}