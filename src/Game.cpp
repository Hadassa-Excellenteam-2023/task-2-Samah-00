#include "Game.h"

Game::Game() : m_player1(Piece::Color::WHITE, Row::START_ROW_WHITE, Row::PAWN_START_ROW_WHITE),
               m_player2(Piece::Color::BLACK, Row::START_ROW_BLACK, Row::PAWN_START_ROW_BLACK),
               m_board(), m_gameOver(false), m_player1Turn(true) {
}

void Game::switchTurn() {
    m_player1Turn = !m_player1Turn;
}

int Game::play(std::string input) {
    if (!m_gameOver && !input.empty()) {
        // Extract the positions from the input string
        char from_row = std::tolower(input[0]);
        int from_col = input[1] - '0';
        char to_row = std::tolower(input[2]);
        int to_col = input[3] - '0';

        Player* currentPlayer = m_player1Turn ? &m_player1 : &m_player2;
        Player* opposingPlayer = m_player1Turn ? &m_player2 : &m_player1;

        std::pair<Code, bool> moveResult = currentPlayer->makeMove(from_row, from_col, to_row, to_col,
            m_board.getPieces());

        if (moveResult.second) {
            if (m_board.isKingInCheck(currentPlayer->getColor(), from_row, from_col, to_row, to_col))
                return int(Code::SELF_CHECK);

            if (m_board.isCheckmate(opposingPlayer->getColor(), to_row, to_col)) {
                m_gameOver = true;
                preformMove(from_row, from_col, to_row, to_col);
                return int(Code::CHECKMATE);
            }

            if (m_board.isKingInCheck(opposingPlayer->getColor(), from_row, from_col, to_row, to_col)) {
                preformMove(from_row, from_col, to_row, to_col);
                return int(Code::CHECK);
            }

            preformMove(from_row, from_col, to_row, to_col);
            return int(Code::LEGAL_MOVE);
        }
        else {
            return int(moveResult.first);
        }
    }
    else if (input.empty())
        // no input received -> illegal move.
        return int(Code::ILLEGAL_MOVE);
    else {
        // game's over
        return int(Code::CHECKMATE);
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