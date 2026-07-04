#include "board.h"
#include <iostream>
#include <vector>

Board::Board(int num_rows, int num_cols, int win_condition)
{
    this->num_rows = num_rows;
    this->num_cols = num_cols;
    this->win_condition = win_condition;
    this->moving_player = PLAYER_X;
    this->board = std::vector<std::vector<int>>(num_rows, std::vector<int>(num_cols, 0));
}

bool Board::check_win_from_cell(int row, int col)
{
    static int row_offsets[3] = { 0, 1, 1 };
    static int col_offsets[3] = { 1, 0, 1 };

    int player = this->board[row][col];

    if (player == UNOCCUPIED)
        return false;

    for (int i = 0; i < 3; i++) {
        int row_offset = row_offsets[i];
        int col_offset = col_offsets[i];
        // start at this cell
        int count = 1;
        int cur_row = row + row_offset;
        int cur_col = col + col_offset;
        while (this->check_cell_in_bounds(cur_row, cur_col) && this->board[cur_row][cur_col] == player) {
            cur_row += row_offset;
            cur_col += col_offset;
            count++;
        }
        cur_row = row - row_offset;
        cur_col = col - col_offset;
        while (this->check_cell_in_bounds(cur_row, cur_col) && this->board[cur_row][cur_col] == player) {
            cur_row -= row_offset;
            cur_col -= col_offset;
            count++;
        }
        if (count >= this->win_condition)
            return true;
    }

    return false;
}

bool Board::check_cell_in_bounds(int row, int col)
{
    return row >= 0 && row < this->num_rows && col >= 0 && col < this->num_cols;
}

int Board::make_move(int row, int col)
{
    if (!this->check_cell_in_bounds(row, col))
        return INVALID_MOVE;
    if (this->board[row][col] != UNOCCUPIED)
        return INVALID_MOVE;

    this->board[row][col] = this->moving_player;

    if (this->moving_player == PLAYER_X)
        this->moving_player = PLAYER_O;
    else
        this->moving_player = PLAYER_X;

    return VALID_MOVE;
}

int Board::check_game_state()
{
    bool all_cells_occupied = true;
    for (int row = 0; row < this->num_rows; row++) {
        for (int col = 0; col < this->num_cols; col++) {
            if (this->check_win_from_cell(row, col))
                return ((this->board[row][col] == PLAYER_X) ? PLAYER_X_WIN : PLAYER_O_WIN);
            all_cells_occupied = all_cells_occupied && this->board[row][col] != UNOCCUPIED;
        }
    }
    return ((all_cells_occupied) ? TIE : IN_PROGRESS);
}

std::ostream& operator<<(std::ostream& out, const Board& board)
{
    static const char types[3] = {' ', 'X', 'O'};
    for (int row = 0; row < 2 * board.num_rows - 1; row++) {
        if (row % 2 == 0) {
            for (int col = 0; col < 2 * board.num_cols - 1; col++) {
                if (col % 2 == 0) {
                    out << types[board.board[row>>1][col>>1]];
                } else {
                    out << '|';
                }
            }
        } else {
            for (int col = 0; col < 2 * board.num_cols - 1; col++) {
                out << ((col % 2 == 0) ? '-' : '+');
            }
        }
        out << '\n';
    }
    return out;
}

