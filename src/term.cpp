#include "term.h"
#include <iostream>
#include <sstream>
#include <format>

Term::Term()
{
    std::cout << "Welcome to TicTacToe\n";
}

void Term::clear()
{
    std::cout << "\033[2J\033[1;1H";
}

bool Term::prompt()
{
    std::string command;
    std::cout << "ttt> ";
    std::getline(std::cin, command);
    if (command.compare("exit") == 0)
        return false;
    this->parse(command);
    return true;
}

void Term::parse(std::string command)
{
    std::istringstream cmd_stream{command};
    std::string arg{};
    if (!static_cast<bool>(cmd_stream >> arg)) {
        if (arg.length() != 0)
            std::cout << "Failed getting command\n";
        return;
    }
    switch (this->current_mode) {
        case Mode::COMMAND: {
            if (arg.compare("start") == 0) {
                int num_rows{}, num_cols{}, win_condition{};

                if (!static_cast<bool>(cmd_stream >> num_rows)) {
                    num_rows = 3;
                    num_cols = 3;
                    win_condition = 3;
                } else if (!static_cast<bool>(cmd_stream >> num_cols)) {
                    std::cout << "start [num_rows num_cols] [win_condition]\n";
                    break;
                } else if (!static_cast<bool>(cmd_stream >> win_condition)) {
                    win_condition = 3;
                }

                this->clear();
                this->current_mode = Mode::GAME;
                this->board.emplace(num_rows, num_cols, win_condition);
                std::cout << *this->board;
                return;
            } else {
                std::cout << "Unrecognized command\n";
            }
            break;
        } case Mode::GAME: {
            Board& board = *this->board;
            if (arg.compare("end") == 0) {
                this->clear();
                this->current_mode = Mode::COMMAND;
                this->board.reset();
                break;
            } else if (arg.compare("w") == 0)
                board.cursor.first = std::max(0, board.cursor.first - 1);
            else if (arg.compare("s") == 0)
                board.cursor.first = std::min(board.num_rows - 1, board.cursor.first + 1);
            else if (arg.compare("a") == 0)
                board.cursor.second = std::max(0, board.cursor.second - 1);
            else if (arg.compare("d") == 0)
                board.cursor.second = std::min(board.num_rows - 1, board.cursor.second + 1);
            else if (arg.compare("x") == 0) {
                Board::MoveResult move_result = board.make_move(board.cursor.first, board.cursor.second);
                if (move_result == Board::MoveResult::INVALID) {
                    std::cout << "Invalid move\n";
                    break;
                }
                Board::GameState state = board.check_game_state();
                if (state != Board::GameState::IN_PROGRESS) {
                    this->clear();
                    std::cout << board;
                    if (state == Board::GameState::X_WIN)
                        std::cout << "X wins!\n";
                    else if (state == Board::GameState::O_WIN)
                        std::cout << "O wins!\n";
                    else if (state == Board::GameState::TIE)
                        std::cout << "Tie!\n";
                    this->current_mode = Mode::COMMAND;
                    this->board.reset();
                    break;
                }
            } else {
                std::cout << "Unrecognized command\n";
                break;
            }
            this->clear();
            std::cout << board;
            break;
        }
    }
}
