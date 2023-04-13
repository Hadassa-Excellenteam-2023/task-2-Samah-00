#include "Game.h"

Game::Game() : m_player1(Piece::Color::WHITE, Row::START_ROW_WHITE, Row::PAWN_START_ROW_WHITE),
               m_player2(Piece::Color::BLACK, Row::START_ROW_BLACK, Row::PAWN_START_ROW_BLACK),
               m_board(), m_gameOver(false), m_player1Turn(true) {
    initialize();
}

void Game::initialize() {
    // TODO: initialize the game, e.g., set up the board and the players
}

void Game::switchTurn() {
    m_player1Turn = !m_player1Turn;
}

int Game::play(std::string input) {
    if (!m_gameOver) {
        // Extract the positions from the input string
        char from_row = std::tolower(input[0]);
        int from_col = input[1] - '0';
        char to_row = std::tolower(input[2]);
        int to_col = input[3] - '0';

        // Get the player whose turn it is
        Player* currentPlayer = m_player1Turn ? &m_player1 : &m_player2;
        Player* opposingPlayer = m_player1Turn ? &m_player2 : &m_player1;

        std::pair<Code, bool> moveResult = currentPlayer->makeMove(from_row, from_col, to_row, to_col,
            m_board.getPieces());

        switch (moveResult.first)
        {
        case Code::CODE_11:
            return 11;

        case Code::CODE_12:
            return 12;

        case Code::CODE_13:
            return 13;

        case Code::CODE_ZERO:   // code zero is returned when trying to move the knight or the pawn pieces which aren't implemented in this program
        case Code::CODE_21:
            return 21;

        case Code::CODE_42:
            if (m_board.isKingInCheck(currentPlayer->getColor(), from_row, from_col, to_row, to_col))
                return 31;
            if (m_board.isKingInCheck(currentPlayer->getColor(), from_row, from_col, to_row, to_col))
            {
                if (m_board.isCheckmate(opposingPlayer->getColor()))
                    m_gameOver == true; // there's a checkmate
                preformMove(from_row, from_col, to_row, to_col);
                return 41;
            }
            preformMove(from_row, from_col, to_row, to_col);
            return 42;

        default:
            break;
        }

    }
    else {
        // game's over
        return 41;
    }
        
}

void Game::preformMove(const char from_row, const int from_col, const char to_row, const int to_col) {
    Player* currentPlayer = m_player1Turn ? &m_player1 : &m_player2;
    Player* opposingPlayer = m_player1Turn ? &m_player2 : &m_player1;

    // update the board and the players' pieces.
    m_board.movePiece(from_row, from_col, to_row, to_col);
    currentPlayer->updatePieces(from_row, from_col, to_row, to_col);
    opposingPlayer->updatePieces(to_row, to_col);

    // Switch to the other player's turn
    switchTurn();
}