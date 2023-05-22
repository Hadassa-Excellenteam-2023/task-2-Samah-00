
#include "King.h"

std::pair<Code, bool> King::isLegalMove(char to_row, size_t to_col, const std::vector<std::vector<Piece*>>& board) const {

    // Check the source and the destination tiles
    auto source_tile_check = checkSourceAndDest(to_row, to_col, board);
    if (source_tile_check.first != Code::CODE_ZERO) {
        return source_tile_check;
    }

    // Check if the move is not legal for the king
    int row_diff = to_row - getRow();
    int col_diff = to_col - getCol();
    if (!((row_diff == 1 && col_diff == 0) || (row_diff == 0 && col_diff == 1) || (row_diff == 1 && col_diff == 1))) {
        return std::make_pair(Code::ILLEGAL_MOVE, false);
    }

    /*
    // Make a copy of the board and perform the move on the copy
    std::vector<std::vector<Piece*>> new_board = board;
    new_board[getRow() - 'a'][getCol() - 1] = nullptr;
    new_board[to_row - 'a'][to_col - 1] = const_cast<King*>(this);

    // Check if the move results in check
    bool in_check = false;
    for (const auto& piece : board[to_row - 'a'][to_col - 1]->getColor() == Piece::Color::WHITE ?
        black_pieces : white_pieces) {
        auto result = piece->isLegalMove(m_row, m_col, board, black_pieces, white_pieces);
        if (result.first == Code::CODE_31) {
            in_check = true;
            break;
        }
    }

    if (in_check) {
        return std::make_pair(Code::CODE_41, true);
    }
    else {
        return std::make_pair(Code::CODE_42, true);
    }
    */

    // Otherwise, it's a legal move
    return std::make_pair(Code::LEGAL_MOVE, true);
    
}


void King::updatePos(const char to_row, const size_t to_col) {
    // Update the piece's position
    setRow(std::tolower(to_row));
    setCol(to_col);
}


