#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <fstream>
#include <iostream>

#define VALID_MOVE   0
#define INVALID_MOVE 1

#define UNOCCUPIED   0
#define PLAYER_X     1
#define PLAYER_O     2

#define IN_PROGRESS     0
#define PLAYER_X_WIN    1
#define PLAYER_O_WIN    2
#define TIE             3

class Board {
    private:
        bool check_win_from_cell(int row, int col);
        bool check_cell_in_bounds(int row, int col);

    public:
        int num_rows;
        int num_cols;
        int win_condition;
        int moving_player;
        std::vector<std::vector<int>> board;

        Board(int num_rows, int num_cols, int win_condition);
        void print();
        int make_move(int row, int col);
        int check_game_state();
};

extern std::ostream& operator<<(std::ostream& out, const Board& board);

#endif
