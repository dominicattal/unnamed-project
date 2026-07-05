#include "board.h"
#include "term.h"
#include <iostream>
#include <vector>
#include <format>
#include <random>

void run_game()
{
    Board board(7,7,4);
    std::cout << board << '\n';

    std::random_device random_device;
    std::default_random_engine random_engine(random_device());
    std::uniform_int_distribution<int> uniform_dist_row(0, board.num_rows-1);
    std::uniform_int_distribution<int> uniform_dist_col(0, board.num_cols-1);

    Board::GameState cur_state = board.check_game_state();
    while (cur_state == Board::GameState::IN_PROGRESS) {
        int row, col;
        Board::Player moving_player = board.moving_player;
        do {
            row = uniform_dist_row(random_engine);
            col = uniform_dist_col(random_engine);
        } while(board.make_move(row, col) == Board::MoveResult::INVALID);
        std::cout << std::format("Player {} moves to {}, {}\n", static_cast<char>(moving_player), row, col);
        std::cout << board << '\n';
        cur_state = board.check_game_state();
    }

    if (cur_state == Board::GameState::X_WIN)
        std::cout << std::format("Player 1 wins!\n");
    else if (cur_state == Board::GameState::O_WIN)
        std::cout << std::format("Player 2 wins!\n");
    else
        std::cout << std::format("It's a tie!\n");

    std::cout << std::format("Game ended in {} moves\n", board.history.size());
}

int main()
{
    Term term{};
    while (term.prompt())
        ;
}
