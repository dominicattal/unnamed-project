#ifndef GAME_H
#define GAME_H

#include <vector>
#include <fstream>
#include <iostream>

class Player;

class Game {
    public:
        enum class MoveResult { VALID, INVALID };
        enum class GameState { LOBBY, PLAYING, ENDED };

        int num_rows;
        int num_cols;
        int win_condition;
        GameState current_state { GameState::LOBBY };
        Player* winning_player {};
        std::pair<int, int> cursor {};
        std::pair<Player*, char> players[2] {};

        Game(int num_rows, int num_cols);
        Game(int num_rows, int num_cols, int win_condition);

        bool start();
        bool end();

        MoveResult make_move(int row, int col);

    private:

        static constexpr char empty_cell{' '};

        Player* moving_player {};
        std::vector<char> board;
        std::vector<std::pair<int, int>> history;

        Game::GameState update_game_state();
        bool check_win_from_cell(int row, int col);
        bool check_cell_in_bounds(int row, int col);

        Player* get_player_from_state(char state);
        char get_state_from_player(Player* player);

        char get_cell_state(int row, int col) const;
        void set_cell_state(int row, int col, char state);

        friend std::ostream& operator<<(std::ostream& out, const Game& game);
        friend std::ostream& print_lobby(std::ostream& out, const Game&);
        friend std::ostream& print_game(std::ostream& out, const Game& game);
};


#endif
