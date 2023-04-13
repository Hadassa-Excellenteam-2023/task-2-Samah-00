#include "Piece.h"

std::pair<Code, bool> Piece::checkSourceAndDest(char to_row, int to_col, const std::vector<std::vector<Piece*>>& board) const
{
    // Check if the source tile is empty
    if (board[m_row - 'a'][m_col - 1] == nullptr) {
        return std::make_pair(Code::CODE_11, false);
    }

    // Check if the piece in the source tile belongs to the opposing player
    if (board[m_row - 'a'][m_col - 1]->getColor() != getColor()) {
        return std::make_pair(Code::CODE_12, false);
    }

    // Check if the piece at the destination belongs to the current player
    if (board[to_row - 'a'][to_col - 1] != nullptr &&
        board[to_row - 'a'][to_col - 1]->getColor() == getColor()) {
        return std::make_pair(Code::CODE_13, false);
    }

    return std::make_pair(Code::CODE_ZERO, true);
}
