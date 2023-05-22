#pragma once

#include "Player.h"
#include "Board.h"
#include "Code.h"
#include <string>


class Game {
public:
    Game();
    int play(std::string input);

    void preformMove(const char from_row, const int from_col, const char to_row, const int to_col);

private:
    Player m_player1;
    Player m_player2;
    Board m_board;
    bool m_gameOver;
    bool m_player1Turn;

    void switchTurn();
};