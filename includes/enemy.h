#ifndef ENEMY_H
#define ENEMY_H

#include "point.h"

typedef struct s_enemy
{
    t_point position;
    int alive;
    int direction;
}	t_enemy;

#endif