#include "Bishop.h"

std::pair<Code, bool> Bishop::isLegalMove(char to_row, size_t to_col, const std::vector<std::vector<Piece*>>& board) const {

    // Check the source and the destination tiles
    auto source_tile_check = checkSourceAndDest(to_row, to_col, board);
    if (source_tile_check.first != Code::CODE_ZERO) {
        return source_tile_check;
    }

    // Check if the bishop is moving diagonally
    if (std::abs(to_row - m_row) != std::abs(int(to_col) - int(m_col))) {
        return std::make_pair(Code::ILLEGAL_MOVE, false);
    }

    // Check if the path is clear
    std::pair<Code, bool> path_clear_check = checkPathClear(to_row, to_col, board);
    if (!path_clear_check.second) {
        return path_clear_check;
    }

    //in_check and cause_check

    // The move is legal
    return std::make_pair(Code::LEGAL_MOVE, true);
}

std::pair<Code, bool> Bishop::checkPathClear(const char to_row, const size_t to_col, const std::vector<std::vector<Piece*>>& board) const
{
    int step_row = (to_row > m_row) ? 1 : -1;
    int step_col = (to_col > m_col) ? 1 : -1;
    int row = m_row + step_row;
    int col = m_col + step_col;
    while (row != to_row && col != to_col) {
        if (board[row - 'a'][col - 1] != nullptr) {
            return std::make_pair(Code::ILLEGAL_MOVE, false);
        }
        row += step_row;
        col += step_col;
    }
    return std::make_pair(Code::CODE_ZERO, true);
}
