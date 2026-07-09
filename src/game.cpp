#include "game.h"
#include "player.h"
#include <iostream>
#include <vector>

Game::Game(int num_rows, int num_cols)
    : num_rows(num_rows), num_cols(num_cols), win_condition(3), board(num_rows * num_cols, this->empty_cell)
{}

Game::Game(int num_rows, int num_cols, int win_condition)
    : num_rows(num_rows), num_cols(num_cols), win_condition(win_condition), board(num_rows * num_cols, this->empty_cell)
{}

bool Game::start()
{
    return false;
}

bool Game::end()
{
    return false;
}

char Game::get_cell_state(int row, int col) const
{
    return this->board[row * this->num_cols + col];
}

void Game::set_cell_state(int row, int col, char state)
{
    this->board[row * this->num_cols + col] = state;
}

Player* Game::get_player_from_state(char state)
{
    if (this->players[0].second == state)
        return this->players[0].first;
    else if (this->players[1].second == state)
        return this->players[1].first;
    return NULL;
}

char Game::get_state_from_player(Player* player)
{
    if (this->players[0].first == player)
        return this->players[0].second;
    if (this->players[1].first == player)
        return this->players[1].second;
    return '\0';
}

bool Game::check_win_from_cell(int row, int col)
{
    static int row_offsets[4] = { 0, 1, 1, 1 };
    static int col_offsets[4] = { 1, 0, 1, -1 };

    char test_state = this->get_cell_state(row, col);

    if (test_state == this->empty_cell)
        return false;

    for (int i = 0; i < 4; i++) {
        int row_offset = row_offsets[i];
        int col_offset = col_offsets[i];
        // start at this cell
        int count = 1;
        int cur_row = row + row_offset;
        int cur_col = col + col_offset;
        while (this->check_cell_in_bounds(cur_row, cur_col) && this->get_cell_state(cur_row, cur_col) == test_state) {
            cur_row += row_offset;
            cur_col += col_offset;
            count++;
        }
        cur_row = row - row_offset;
        cur_col = col - col_offset;
        while (this->check_cell_in_bounds(cur_row, cur_col) && this->get_cell_state(cur_row, cur_col) == test_state) {
            cur_row -= row_offset;
            cur_col -= col_offset;
            count++;
        }
        if (count >= this->win_condition)
            return true;
    }

    return false;
}

bool Game::check_cell_in_bounds(int row, int col)
{
    return row >= 0 && row < this->num_rows && col >= 0 && col < this->num_cols;
}

Game::MoveResult Game::make_move(int row, int col)
{
    if (!this->check_cell_in_bounds(row, col))
        return MoveResult::INVALID;
    if (this->get_cell_state(row, col) != this->empty_cell)
        return MoveResult::INVALID;

    this->history.emplace_back(row, col);

    if (this->moving_player == this->players[0].first) {
        this->set_cell_state(row, col, this->players[0].second);
        this->moving_player = this->players[1].first;
    } else {
        this->set_cell_state(row, col, this->players[1].second);
        this->moving_player = this->players[0].first;
    }

    this->update_game_state();

    return MoveResult::VALID;
}

Game::GameState Game::update_game_state()
{
    bool all_cells_occupied = true;
    for (int row = 0; row < this->num_rows; row++) {
        for (int col = 0; col < this->num_cols; col++) {
            if (this->check_win_from_cell(row, col)) {
                this->winning_player = this->get_player_from_state(this->get_cell_state(row, col));
                this->current_state = GameState::ENDED;
                return this->current_state;
            }
            all_cells_occupied = all_cells_occupied && this->get_cell_state(row, col) != this->empty_cell;
        }
    }
    if (all_cells_occupied) {
        this->winning_player = NULL;
        this->current_state = GameState::ENDED;
    }
    return this->current_state;
}

std::ostream& print_lobby(std::ostream& out, const Game& game)
{
    out << "In Lobby\n";
    if (game.players[0].first != NULL)
        out << std::format("Player 1: {} ({})\n", game.players[0].first->name, game.players[0].second);
    else
        out << "Waiting for Player 1\n";
    if (game.players[1].first != NULL)
        out << std::format("Player 2: {} ({})\n", game.players[1].first->name, game.players[1].second);
    else
        out << "Waiting for Player 2\n";
    return out;
}

std::ostream& print_game(std::ostream& out, const Game& game)
{
    for (int row = 0; row < 2 * game.num_rows - 1; row++) {
        if (row % 2 == 0) {
            for (int col = 0; col < 2 * game.num_cols - 1; col++) {
                if (col % 2 == 0) {
                    if (game.cursor == std::pair<int,int>{ row>>1, col>>1 })
                        out << "\033[48;2;100;100;100m";
                    char state = game.get_cell_state(row>>1, col>>1);
                    if (state == game.players[0].second)
                        out << "\033[31m";
                    else if (state == game.players[1].second)
                        out << "\033[34m";
                    out << state;
                    out << "\033[39m\033[49m";
                } else {
                    out << '|';
                }
            }
        } else {
            for (int col = 0; col < 2 * game.num_cols - 1; col++) {
                out << ((col % 2 == 0) ? '-' : '+');
            }
        }
        out << '\n';
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const Game& game)
{
    switch (game.current_state) {
        case Game::GameState::LOBBY:
            return print_lobby(out, game);
        case Game::GameState::PLAYING:
            return print_game(out, game);
        default:
            return out;
    }
}
