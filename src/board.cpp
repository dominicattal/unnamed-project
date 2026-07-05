#include "board.h"
#include <iostream>
#include <vector>

Board::Board(int num_rows, int num_cols, int win_condition)
    : num_rows(num_rows), num_cols(num_cols), win_condition(win_condition), board(num_rows * num_cols, Player::NONE)
{}

Board::Player Board::get_cell_state(int row, int col) const
{
    return this->board[row * this->num_cols + col];
}

void Board::set_cell_state(int row, int col, Player player)
{
    this->board[row * this->num_cols + col] = player;
}

bool Board::check_win_from_cell(int row, int col)
{
    static int row_offsets[4] = { 0, 1, 1, 1 };
    static int col_offsets[4] = { 1, 0, 1, -1 };

    Player player = this->get_cell_state(row, col);

    if (player == Player::NONE)
        return false;

    for (int i = 0; i < 4; i++) {
        int row_offset = row_offsets[i];
        int col_offset = col_offsets[i];
        // start at this cell
        int count = 1;
        int cur_row = row + row_offset;
        int cur_col = col + col_offset;
        while (this->check_cell_in_bounds(cur_row, cur_col) && this->get_cell_state(cur_row, cur_col) == player) {
            cur_row += row_offset;
            cur_col += col_offset;
            count++;
        }
        cur_row = row - row_offset;
        cur_col = col - col_offset;
        while (this->check_cell_in_bounds(cur_row, cur_col) && this->get_cell_state(cur_row, cur_col) == player) {
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

Board::MoveResult Board::make_move(int row, int col)
{
    if (!this->check_cell_in_bounds(row, col))
        return MoveResult::INVALID;
    if (this->get_cell_state(row, col) != Player::NONE)
        return MoveResult::INVALID;

    this->set_cell_state(row, col, this->moving_player);
    this->history.emplace_back(row, col);

    if (this->moving_player == Player::X)
        this->moving_player = Player::O;
    else
        this->moving_player = Player::X;

    return MoveResult::VALID;
}

Board::GameState Board::check_game_state()
{
    bool all_cells_occupied = true;
    for (int row = 0; row < this->num_rows; row++) {
        for (int col = 0; col < this->num_cols; col++) {
            if (this->check_win_from_cell(row, col))
                return ((this->get_cell_state(row, col) == Player::X) ? GameState::X_WIN : GameState::O_WIN);
            all_cells_occupied = all_cells_occupied && this->get_cell_state(row, col) != Player::NONE;
        }
    }
    return ((all_cells_occupied) ? GameState::TIE : GameState::IN_PROGRESS);
}

std::ostream& operator<<(std::ostream& out, const Board& board)
{
    for (int row = 0; row < 2 * board.num_rows - 1; row++) {
        if (row % 2 == 0) {
            for (int col = 0; col < 2 * board.num_cols - 1; col++) {
                if (col % 2 == 0) {
                    if (board.cursor == std::pair<int,int>{ row>>1, col>>1 })
                        out << "\033[48;2;100;100;100m";
                    Board::Player player = board.get_cell_state(row>>1, col>>1);
                    if (player == Board::Player::X)
                        out << "\033[31m";
                    else if (player == Board::Player::O)
                        out << "\033[34m";
                    out << static_cast<char>(player);
                    out << "\033[39m\033[49m";
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

