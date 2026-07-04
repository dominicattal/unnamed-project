#include "board.h"
#include <iostream>
#include <vector>
#include <stdlib.h>

int main()
{
    srand(time(NULL));

    Board board(5, 5, 3);
    std::cout << board << '\n';

    int cur_state = board.check_game_state();
    while (cur_state == IN_PROGRESS) {
        int row, col;
        int moving_player = board.moving_player;
        do {
            row = rand() % board.num_rows;
            col = rand() % board.num_cols;
        } while(board.make_move(row, col) == INVALID_MOVE);
        std::cout << std::format("Player {} moves to {}, {}\n", moving_player, row, col);
        std::cout << board << '\n';
        cur_state = board.check_game_state();
    }

    if (cur_state == PLAYER_X_WIN)
        std::cout << std::format("Player 1 wins!\n");
    else if (cur_state == PLAYER_O_WIN)
        std::cout << std::format("Player 2 wins!\n");
    else
        std::cout << std::format("It's a tie!");
}
