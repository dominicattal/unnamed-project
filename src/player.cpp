#include "player.h"
#include "game.h"

Player::Player()
    : name("noname")
{}

Player::Player(std::string_view name)
    : name(name)
{}


void Player::set_name(std::string_view name)
{
    this->name = name;
}

bool Player::join(Game* game)
{
    if (game->players[0].first == NULL) {
        game->players[0] = { this, 'X' };
        return true;
    }
    if (game->players[1].first == NULL) {
        game->players[1] = { this, 'O' };
        return true;
    }
    return false;
}

bool Player::leave()
{
    return false;
}
