#include "Player.h"

/*
 * c-tor for objects of class Player.
 * creates a vector of Piece pointers for the player's pieces,
 * it creates one King, one Queen, two Rooks, two Bishops, no Knights,
 * and no Pawns, all of the specified color and in the player's side of the board.
 */
Player::Player(Piece::Color color, Row row, Row pawn_row) : m_color(color) {
    m_pieces.reserve(NUM_OF_PIECES);
    m_pieces.push_back(new Rook(color, char(row), int(Column::COLUMN_1)));
    //m_pieces.push_back(new Knight(color, char(row), int(Column::COLUMN_2)));
    m_pieces.push_back(new Bishop(color, char(row), int(Column::COLUMN_3)));
    m_pieces.push_back(new Queen(color, char(row), int(Column::COLUMN_4)));
    m_pieces.push_back(new King(color, static_cast<char>(row), static_cast<int>(Column::COLUMN_5)));
    m_pieces.push_back(new Bishop(color, char(row), int(Column::COLUMN_6)));
    //m_pieces.push_back(new Knight(color, char(row), int(Column::COLUMN_7)));
    m_pieces.push_back(nullptr);
    m_pieces.push_back(new Rook(color, char(row), int(Column::COLUMN_8)));

    for (int i = 0; i < 8; i++) {
        //m_pieces.push_back(new Pawn(color, char(pawn_row), (i + 1)));
    }
}

/*
 * distructor for objects of class Player.
 * deletes all of the Piece objects in the m_pieces vector and clears the vector.
 */
Player::~Player() {
    for (auto piece : m_pieces) {
        delete piece;
    }
    m_pieces.clear();
}

/*
 * this method returns the color of the player.
 */
Piece::Color Player::getColor() const {
    return m_color;
}

/*
 * this method returns a vector of pointers to the player's pieces.
 */
std::vector<Piece*> Player::getPieces() const {
    return m_pieces;
}

std::pair<Code, bool> Player::makeMove(char from_row, int from_col, char to_row, int to_col,
    const std::vector<std::vector<Piece*>>& board) {

    // Check that the move is within the board boundaries
    if (to_row < 'a' || to_row > 'h' || to_col < 1 || to_col > 8 ||
        from_row < 'a' || from_row > 'h' || from_col < 1 || from_col > 8) {
        return std::make_pair(Code::ILLEGAL_MOVE, false);
    }


    // Handle the case where there is no piece at the specified position
    if (board[from_row - 'a'][from_col - 1] == nullptr)
        return std::make_pair<Code, bool>(Code::EMPTY_TILE, false);

    // Find the piece to move
    Piece* piece = nullptr;
    for (auto p : m_pieces) {
        if (p == nullptr) {
            continue; // skip nullptr
        }
        if (p->getRow() == from_row && p->getCol() == from_col) {
            piece = p;
            break;
        }
    }

    // Check if a valid piece was found
    if (!piece) {
        // piece is still pointing to nullptr but there's a piece on the board
        // which means that the piece in the source square belongs to the opposing player
        return std::make_pair<Code, bool>(Code::ENEMY_PIECE_IN_SOURCE, false);
    }

    // Check if the move is legal for the selected piece and return the result
    return piece->isLegalMove(to_row, to_col, board);
    
}

void Player::updatePieces(char from_row, int from_col, char to_row, int to_col) {
    for (auto p : m_pieces) {
        if (p->getRow() == from_row && p->getCol() == from_col) {
            p->setRow(std::tolower(to_row));
            p->setCol(to_col);
            break;
        }
    }
}

void Player::updatePieces(char to_row, int to_col) {
    bool found = false;
    for (auto it = m_pieces.begin(); it != m_pieces.end(); ++it) {
        if (*it == nullptr) {
            continue; // skip nullptr
        }
        if ((*it)->getRow() == to_row && (*it)->getCol() == to_col) {
            delete* it;
            *it = nullptr;
            found = true;
            break;
        }
    }
    if (found) {
        m_pieces.erase(std::remove(m_pieces.begin(), m_pieces.end(), nullptr), m_pieces.end());
    }
}






