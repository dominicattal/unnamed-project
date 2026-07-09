#ifndef PLAYER_H
#define PLAYER_H

#include <string_view>

class Game;

class Player {
    private:
        Game* game;

    public:
        std::string_view name;

        Player();
        Player(std::string_view name);

        void set_name(std::string_view name);

        bool join(Game* game);
        bool leave();
};

#endif
