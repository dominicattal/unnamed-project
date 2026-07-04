#include "board.h"
#include <iostream>
#include <vector>

Board::Board(int num_rows, int num_cols)
{
    this->num_rows = num_rows;
    this->num_cols = num_cols;
    this->board = std::vector<std::vector<int>>(num_rows, std::vector<int>(num_cols, 0));
}

void Board::print()
{
    static const char types[3] = {' ', 'X', 'O'};
    for (int row = 0; row < 2 * this->num_rows - 1; row++) {
        if (row % 2 == 0) {
            for (int col = 0; col < 2 * this->num_cols - 1; col++) {
                if (col % 2 == 0) {
                    std::cout << types[this->board[row>>1][col>>1]];
                } else {
                    std::cout << '|';
                }
            }
        } else {
            for (int col = 0; col < 2 * this->num_cols - 1; col++) {
                std::cout << ((col % 2 == 0) ? '-' : '+');
            }
        }
        std::cout << '\n';
    }
}

void Board::make_move(int player, int row, int col)
{
    this->board[row][col] = player;
}
