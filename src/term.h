#ifndef TERM_H
#define TERM_H

#include "game.h"
#include "player.h"
#include <optional>
#include <string_view>

class Term {
    private:
        Player player;
        std::optional<Game> game;
        void parse_game(std::istringstream& cmd_stream);
        void parse_command(std::istringstream& cmd_stream);
        void parse(std::string command);
        void clear();
    public:
        enum class Mode { COMMAND, GAME };
        Mode current_mode = Mode::COMMAND;
        Term();
        bool prompt();
};

#endif
