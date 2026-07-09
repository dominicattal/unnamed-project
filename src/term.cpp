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

void Term::parse_command(std::istringstream& cmd_stream)
{
    std::string arg{};

    if (!static_cast<bool>(cmd_stream >> arg))
        return;

    if (arg.compare("ttt") == 0) {
        int num_rows{}, num_cols{}, win_condition{};

        if (!static_cast<bool>(cmd_stream >> num_rows)) {
            num_rows = 3;
            num_cols = 3;
            win_condition = 3;
        } else if (!static_cast<bool>(cmd_stream >> num_cols)) {
            std::cout << "ttt [num_rows num_cols] [win_condition]\n";
            return;
        } else if (!static_cast<bool>(cmd_stream >> win_condition)) {
            win_condition = 3;
        }

        this->clear();
        this->current_mode = Mode::GAME;
        this->game.emplace(num_rows, num_cols, win_condition);
        this->player.join(&(*this->game));
        std::cout << *this->game;
    } else {
        std::cout << "Unrecognized command\n";
    }
}

void Term::parse_game(std::istringstream& cmd_stream)
{
    std::string arg{};

    if (!static_cast<bool>(cmd_stream >> arg))
        return;

    Game& game = *this->game;
    if (arg.compare("end") == 0) {
        this->clear();
        this->current_mode = Mode::COMMAND;
        this->game.reset();
        return;
    } else if (arg.compare("w") == 0)
        game.cursor.first = std::max(0, game.cursor.first - 1);
    else if (arg.compare("s") == 0)
        game.cursor.first = std::min(game.num_rows - 1, game.cursor.first + 1);
    else if (arg.compare("a") == 0)
        game.cursor.second = std::max(0, game.cursor.second - 1);
    else if (arg.compare("d") == 0)
        game.cursor.second = std::min(game.num_rows - 1, game.cursor.second + 1);
    else if (arg.compare("x") == 0) {
        Game::MoveResult move_result = game.make_move(game.cursor.first, game.cursor.second);
        if (move_result == Game::MoveResult::INVALID) {
            std::cout << "Invalid move\n";
            return;
        }
        Game::GameState state = game.current_state;
        if (state != Game::GameState::PLAYING) {
            //Player* winning_player = game.winning_player;
            this->clear();
            std::cout << game;
            this->current_mode = Mode::COMMAND;
            this->game.reset();
            return;
        }
    } else {
        std::cout << "Unrecognized command\n";
        return;
    }
    this->clear();
    std::cout << game;
}

void Term::parse(std::string command)
{
    std::istringstream cmd_stream{command};
    switch (this->current_mode) {
        case Mode::COMMAND: {
            this->parse_command(cmd_stream);
            break;
        } case Mode::GAME: {
            this->parse_game(cmd_stream);
            break;
        }
    }
}
