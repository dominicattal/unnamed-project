#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <fstream>
#include <iostream>

class Board {
    private:
        bool check_win_from_cell(int row, int col);
        bool check_cell_in_bounds(int row, int col);

    public:
        enum class Player : char { NONE = ' ', X = 'X', O = 'O' };
        enum class MoveResult { VALID, INVALID };
        enum class GameState { IN_PROGRESS, X_WIN, O_WIN, TIE };

        int num_rows;
        int num_cols;
        int win_condition;
        std::pair<int, int> cursor { 0, 0 };
        Player moving_player = Player::X;
        std::vector<Player> board;
        std::vector<std::pair<int, int>> history;

        Board(int num_rows, int num_cols, int win_condition);
        Player get_cell_state(int row, int col) const;
        void set_cell_state(int row, int col, Player player);
        MoveResult make_move(int row, int col);
        Board::GameState check_game_state();
};

extern std::ostream& operator<<(std::ostream& out, const Board& board);

#endif
