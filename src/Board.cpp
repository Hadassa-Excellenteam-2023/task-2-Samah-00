#include "Board.h"

Board::Board() {
    // Initialize the board with empty tiles
    m_board.resize(8, std::vector<Piece*>(8, nullptr));
    // Set up the initial pieces on the board for two players
    initialize();
}

void Board::initialize() {
    // Set up the initial pieces on the board
    // Black pieces
    m_board[7][0] = new Rook(Piece::Color::BLACK, char(Row::START_ROW_BLACK), int(Column::COLUMN_1));
    //m_board[7][1] = new Knight(Piece::Color::BLACK, char(Row::START_ROW_BLACK), int(Column::COLUMN_2));
    m_board[7][2] = new Bishop(Piece::Color::BLACK, char(Row::START_ROW_BLACK), int(Column::COLUMN_3));
    m_board[7][3] = new Queen(Piece::Color::BLACK, char(Row::START_ROW_BLACK), int(Column::COLUMN_4));
    m_board[7][4] = new King(Piece::Color::BLACK, char(Row::START_ROW_BLACK), int(Column::COLUMN_5));
    m_board[7][5] = new Bishop(Piece::Color::BLACK, char(Row::START_ROW_BLACK), int(Column::COLUMN_6));
    //m_board[7][6] = new Knight(Piece::Color::BLACK, char(Row::START_ROW_BLACK), int(Column::COLUMN_7));
    m_board[7][7] = new Rook(Piece::Color::BLACK, char(Row::START_ROW_BLACK), int(Column::COLUMN_8));
    /*
    for (int i = 0; i < BOARD_SIZE; i++) {
        m_board[6][i] = new Pawn(Piece::Color::WHITE, char(Row::PAWN_START_ROW_WHITE), i + 1);
    }
    */
    // White pieces
    m_board[0][0] = new Rook(Piece::Color::WHITE, char(Row::START_ROW_WHITE), int(Column::COLUMN_1));
    //m_board[0][1] = new Knight(Piece::Color::WHITE, char(Row::PAWN_START_ROW_WHITE), int(Column::COLUMN_2));
    m_board[0][2] = new Bishop(Piece::Color::WHITE, char(Row::START_ROW_WHITE), int(Column::COLUMN_3));
    m_board[0][3] = new Queen(Piece::Color::WHITE, char(Row::START_ROW_WHITE), int(Column::COLUMN_4));
    m_board[0][4] = new King(Piece::Color::WHITE, char(Row::START_ROW_WHITE), int(Column::COLUMN_5));
    m_board[0][5] = new Bishop(Piece::Color::WHITE, char(Row::START_ROW_WHITE), int(Column::COLUMN_6));
    //m_board[0][6] = new Knight(Piece::Color::WHITE, char(Row::START_ROW_WHITE), int(Column::COLUMN_7));
    m_board[0][7] = new Rook(Piece::Color::WHITE, char(Row::START_ROW_WHITE), int(Column::COLUMN_8));
    /*
    for (int i = 0; i < BOARD_SIZE; i++) {
        m_board[1][i] = new Pawn(Piece::Color::WHITE, char(Row::PAWN_START_ROW_WHITE), i + 1);
    }
    */

    // fill in m_black_pieces and m_white_pieces.
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (m_board[i][j] != nullptr) {
                if (m_board[i][j]->getColor() == Piece::Color::BLACK) {
                    m_black_pieces.push_back(m_board[i][j]);
                }
                else {
                    m_white_pieces.push_back(m_board[i][j]);
                }
            }
        }
    }

}

// Return a vector of pointers to all the pieces on the board with the given color
std::vector<Piece*> Board::getPieces(Piece::Color color) const {
    std::vector<Piece*> pieces;
    for (const auto& row : m_board) {
        for (const auto& piece : row) {
            if (piece && piece->getColor() == color) {
                pieces.push_back(piece);
            }
        }
    }
    return pieces;
}

void Board::movePiece(const char from_row, const int from_col, const char to_row, const int to_col) {
    // Update the piece's position
    Piece* piece = m_board[from_row - 'a'][from_col - 1];
    piece->updatePos(to_row, to_col);

    // Update the board state
    m_board[from_row - 'a'][from_col - 1] = nullptr;
    m_board[to_row - 'a'][to_col - 1] = piece;
}

std::vector<std::vector<Piece*>> Board::getPieces() const {
    return m_board;
}

bool Board::isKingInCheck(Piece::Color color, char from_row, int from_col, char to_row, int to_col) const {
    // Create a copy of m_board called board_after_move
    auto board_after_move = m_board;

    // Move the piece from [from_row][from_col] to [to_row][to_col] in board_after_move
    board_after_move[to_row - 'a'][to_col - 1] = board_after_move[from_row - 'a'][from_col - 1];
    board_after_move[from_row - 'a'][from_col - 1] = nullptr;

    // Find the position of the king of the given color
    char kingRow;
    int kingCol;
    for (const auto& row : m_board) {
        for (const auto& piece : row) {
            if (piece != nullptr && piece->getColor() == color && typeid(*piece) == typeid(King)) {
                kingRow = piece->getRow();
                kingCol = piece->getCol();
                break;
            }
        }
    }

    // Check if any piece of the opposing color can capture the king
    const auto& opposingPieces = (color == Piece::Color::WHITE) ? m_black_pieces : m_white_pieces;
    for (const auto& piece : opposingPieces) {
        const auto& [code, isLegal] = piece->isLegalMove(kingRow, kingCol, m_board);
        const auto& [code2, isLegal2] = piece->isLegalMove(kingRow, kingCol, board_after_move);
        if (isLegal2 && !isLegal) {
            return true;
        }
    }

    // If no opposing piece can capture the king, the king is not in check
    return false;
}



bool Board::isCheckmate(Piece::Color color) const {
    // Find the king of the given color
    King* king = nullptr;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (m_board[i][j] != nullptr && m_board[i][j]->getColor() == color &&
                dynamic_cast<King*>(m_board[i][j]) != nullptr) {
                king = dynamic_cast<King*>(m_board[i][j]);
                break;
            }
        }
        if (king != nullptr) {
            break;
        }
    }

    // Check if the king is in check
    std::vector<Piece*> attackers = getAttackers(king->getRow(), king->getCol(),
        king->getColor() == Piece::Color::WHITE ?
        m_black_pieces : m_white_pieces);
    if (attackers.empty()) {
        return false;
    }

    // Check if the king can move out of check
    for (int i = king->getRow() - 1; i <= king->getRow() + 1; i++) {
        for (int j = king->getCol() - 1; j <= king->getCol() + 1; j++) {
            if (i >= 'a' && i <= 'h' && j >= 1 && j <= 8) {
                auto result = king->isLegalMove(i, j, m_board);
                if (result.first == Code::CODE_42) {
                    // The king can move out of check
                    return false;
                }
            }
        }
    }

    // Check if any friendly piece can block the attack
    if (attackers.size() == 1) {
        Piece* attacker = attackers[0];
        int row_diff = attacker->getRow() - king->getRow();
        int col_diff = attacker->getCol() - king->getCol();
        int row_dir = row_diff > 0 ? 1 : -1;
        int col_dir = col_diff > 0 ? 1 : -1;
        char row = king->getRow() + row_dir;
        int col = king->getCol() + col_dir;
        while (row >= 'a' && row <= 'h' && col >= 1 && col <= 8) {
            for (const auto& piece : color == Piece::Color::WHITE ? m_white_pieces : m_black_pieces) {
                if (piece != king && piece->getRow() == row && piece->getCol() == col) {
                    auto result = piece->isLegalMove(attacker->getRow(), attacker->getCol(), m_board);
                    if (result.first == Code::CODE_42) {
                        // The attack can be blocked
                        return false;
                    }
                }
            }
            row += row_dir;
            col += col_dir;
        }
    }

    // Check if any friendly piece can capture the attacking piece
    for (const auto& piece : color == Piece::Color::WHITE ? m_white_pieces : m_black_pieces) {
        if (piece != king) {
            for (const auto& attacker : attackers) {
                auto result = piece->isLegalMove(attacker->getRow(), attacker->getCol(), m_board);
                if (result.first == Code::CODE_42) {
                    // The attacking piece can be captured
                    return false;
                }
            }
        }
    }

    // The king is in checkmate
    return true;
}

std::vector<Piece*> Board::getAttackers(char row, int col, std::vector<Piece*> pieces) const {
    std::vector<Piece*> attackers;
    for (const auto& piece : pieces) {
        auto result = piece->isLegalMove(row, col, m_board);
        if (result.first == Code::CODE_42) {
            // The piece can attack the given row and column
            attackers.push_back(piece);
        }
    }
    return attackers;
}


