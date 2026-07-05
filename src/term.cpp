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
    std::istringstream cmd_stream(command);
    std::string arg;
    bool res;
    res = static_cast<bool>(cmd_stream >> arg);
    if (!res) {
        std::cout << "Failed getting command\n";
        return;
    }
    switch (this->current_mode) {
        case Mode::COMMAND: {
            if (arg.compare("start") == 0) {
                this->clear();
                this->current_mode = Mode::GAME;
                this->board.emplace(3, 3, 3);
                std::cout << *this->board;
                return;
            } else {
                std::cout << "Unrecognized command\n";
            }
            break;
        } case Mode::GAME: {
            Board& board = *this->board;
            if (arg.compare("w") == 0)
                board.cursor.first = std::max(0, board.cursor.first - 1);
            else if (arg.compare("s") == 0)
                board.cursor.first = std::min(board.num_rows - 1, board.cursor.first + 1);
            else if (arg.compare("a") == 0)
                board.cursor.second = std::max(0, board.cursor.second - 1);
            else if (arg.compare("d") == 0)
                board.cursor.second = std::min(board.num_rows - 1, board.cursor.second + 1);
            else if (arg.compare("x") == 0)
                board.make_move(board.cursor.first, board.cursor.second);
            else {
                std::cout << "Unrecognized command\n";
                break;
            }
            this->clear();
            std::cout << board;
            break;
        }
    }
}
