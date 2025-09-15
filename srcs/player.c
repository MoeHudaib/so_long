#include "player.h"
#include "input.h"
#include "game.h"

t_player	init_player(t_point point, int health)
{
    t_player    player;

    player.position = point;
    player.health = health;
    player.steps = 0;
    player.collectibles = 0;
    return (player);
}
