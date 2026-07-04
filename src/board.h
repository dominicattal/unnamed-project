#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {
    public:
        int num_rows;
        int num_cols;
        std::vector<std::vector<int>> board;

        Board(int num_rows, int num_cols);
        void print();
        void make_move(int player, int row, int col);
};

#endif
