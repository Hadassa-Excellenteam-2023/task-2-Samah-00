#include "Piece.h"

std::pair<Code, bool> Piece::checkSourceAndDest(char to_row, size_t to_col, const std::vector<std::vector<Piece*>>& board) const
{
    // Check if the source tile is empty
    if (board[m_row - 'a'][m_col - 1] == nullptr) {
        return std::make_pair(Code::EMPTY_TILE, false);
    }

    // Check if the piece in the source tile belongs to the opposing player
    if (board[m_row - 'a'][m_col - 1]->getColor() != getColor()) {
        return std::make_pair(Code::ENEMY_PIECE_IN_SOURCE, false);
    }

    // Check if the piece at the destination belongs to the current player
    if (board[to_row - 'a'][to_col - 1] != nullptr &&
        board[to_row - 'a'][to_col - 1]->getColor() == getColor()) {
        return std::make_pair(Code::SELF_PIECE_IN_TARGET, false);
    }

    return std::make_pair(Code::CODE_ZERO, true);
}
