#include "game.h"
#include "term.h"
#include <iostream>
#include <vector>
#include <format>
#include <random>

/*
void run_game()
{
    Game game(7,7,4);
    std::cout << game << '\n';

    std::random_device random_device;
    std::default_random_engine random_engine(random_device());
    std::uniform_int_distribution<int> uniform_dist_row(0, game.num_rows-1);
    std::uniform_int_distribution<int> uniform_dist_col(0, game.num_cols-1);

    Game::GameState cur_state = game.check_game_state();
    while (cur_state == Game::GameState::IN_PROGRESS) {
        int row, col;
        Game::CellState moving_player = game.moving_player;
        do {
            row = uniform_dist_row(random_engine);
            col = uniform_dist_col(random_engine);
        } while(game.make_move(row, col) == Game::MoveResult::INVALID);
        std::cout << std::format("CellState {} moves to {}, {}\n", static_cast<char>(moving_player), row, col);
        std::cout << game << '\n';
        cur_state = game.check_game_state();
    }

    if (cur_state == Game::GameState::X_WIN)
        std::cout << std::format("CellState 1 wins!\n");
    else if (cur_state == Game::GameState::O_WIN)
        std::cout << std::format("CellState 2 wins!\n");
    else
        std::cout << std::format("It's a tie!\n");

    std::cout << std::format("Game ended in {} moves\n", game.history.size());
}
*/

int main()
{
    Term term{};
    while (term.prompt())
        ;
}
