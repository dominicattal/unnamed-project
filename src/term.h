#ifndef TERM_H
#define TERM_H

#include "board.h"
#include <string>

class Term {
    private:
        std::optional<Board> board;
        void parse(std::string command);
        void clear();
    public:
        enum class Mode { COMMAND, GAME };
        Mode current_mode = Mode::COMMAND;
        Term();
        bool prompt();
};

#endif
