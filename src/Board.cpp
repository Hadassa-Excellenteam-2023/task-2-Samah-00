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
    return (color == Piece::Color::WHITE) ? m_white_pieces : m_black_pieces;
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
    std::pair<char, int> KingTile = GetKingLocation(color);

    if (KingTile.first != NULL) {

        // Create a copy of m_board called board_after_move
        auto board_after_move = m_board;

        // Move the piece from [from_row][from_col] to [to_row][to_col] in board_after_move
        board_after_move[to_row - 'a'][to_col - 1] = board_after_move[from_row - 'a'][from_col - 1];
        board_after_move[from_row - 'a'][from_col - 1] = nullptr;

        // Check if any piece of the opposing color can capture the king
        std::vector<Piece*> attackers = getAttackers(KingTile.first, KingTile.second,
            color == Piece::Color::WHITE ? m_black_pieces : m_white_pieces);
        if (attackers.empty()) {
            return false;
        }

        for (const auto& piece : attackers) {
            const auto& [code, isLegal] = piece->isLegalMove(KingTile.first, KingTile.second, m_board);
            const auto& [codeAfter, isLegalAfter] = piece->isLegalMove(KingTile.first, KingTile.second, board_after_move);
            if (isLegalAfter && !isLegal) {
                return true;
            }
        }
    }
    
    return false;
}

// Find the position of the king of the given color
std::pair<char, int> Board::GetKingLocation(Piece::Color color) const{
    char kingRow = NULL;
    int kingCol = NULL;
    for (const auto& row : m_board) {
        for (const auto& piece : row) {
            if (piece != nullptr && piece->getColor() == color && typeid(*piece) == typeid(King)) {
                kingRow = piece->getRow();
                kingCol = piece->getCol();
                break;
            }
        }
    }
    return std::make_pair(kingRow, kingCol);
}

bool Board::isCheckmate(Piece::Color color, char to_row, size_t to_col) const {
    std::pair<char, int> opposingKingTile = GetKingLocation(color);

    return (opposingKingTile.first == to_row && opposingKingTile.second == to_col);
}

std::vector<Piece*> Board::getAttackers(char row, int col, std::vector<Piece*> pieces) const {
    std::vector<Piece*> attackers;
    for (const auto& piece : pieces) {
        auto result = piece->isLegalMove(row, col, m_board);
        if (result.first == Code::LEGAL_MOVE) {
            // The piece can attack the tile of the king
            attackers.push_back(piece);
        }
    }
    return attackers;
}


