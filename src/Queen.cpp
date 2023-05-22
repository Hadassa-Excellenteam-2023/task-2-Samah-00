#include "Queen.h"

std::pair<Code, bool> Queen::isLegalMove(char to_row, size_t to_col, const std::vector<std::vector<Piece*>>& board) const {

    // Check the source and the destination tiles
    auto source_tile_check = checkSourceAndDest(to_row, to_col, board);
    if (source_tile_check.first != Code::CODE_ZERO) {
        return source_tile_check;
    }

    // Check if the movement is legal for the queen (i.e., rook or bishop movement)
    std::pair<Code, bool> rook_move_result = checkRookMove(to_row, to_col, board);
    std::pair<Code, bool> bishop_move_result = checkBishopMove(to_row, to_col, board);
    if (rook_move_result.second) {
        return rook_move_result;
    }
    if (bishop_move_result.second) {
        return bishop_move_result;
    }

    // The move is legal
    return std::make_pair(Code::LEGAL_MOVE, true);
}

void Queen::updatePos(const char to_row, const size_t to_col) {
    setRow(to_row);
    setCol(to_col);
}

std::pair<Code, bool> Queen::checkRookMove(char to_row, int to_col, const std::vector<std::vector<Piece*>>& board) const {
    // Check if the movement is horizontal or vertical
    if (to_row != getRow() && to_col != getCol()) {
        return std::make_pair(Code::ILLEGAL_MOVE, false);
    }

    // Check if there are any pieces blocking the path to the destination
    if (isBlockedPath(to_row, to_col, board))
        return std::make_pair(Code::ILLEGAL_MOVE, false);

    return std::make_pair(Code::LEGAL_MOVE, true); // legal move
}

std::pair<Code, bool> Queen::checkBishopMove(char to_row, int to_col, const std::vector<std::vector<Piece*>>& board) const {
    // Check if the movement is legal for a bishop
    if (std::abs(m_row - to_row) != std::abs(int(m_col - to_col))) {
        return std::make_pair(Code::ILLEGAL_MOVE, false);
    }

    // Check if there are any pieces blocking the path to the destination
    if (isBlockedPath(to_row, to_col, board))
        return std::make_pair(Code::ILLEGAL_MOVE, false);

    return std::make_pair(Code::LEGAL_MOVE, true); // legal move
}

bool Queen::isBlockedPath(char to_row, int to_col, const std::vector<std::vector<Piece*>>& board) const {
    int step_row = (to_row > m_row) ? 1 : -1;
    int step_col = (to_col > m_col) ? 1 : -1;
    int row = m_row + step_row;
    int col = m_col + step_col;
    while (row != to_row && col != to_col) {
        if (row < 'a' || row > 'h' || col < 1 || col > 8) {
            // The position (row, col) is out of bounds, return true to indicate a blocked path
            return true;
        }
        if (board[row - 'a'][col - 1] != nullptr) {
            // The position (row, col) contains a piece, return true to indicate a blocked path
            return true;
        }
        row += step_row;
        col += step_col;
    }
    return false;
}
