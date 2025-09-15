#ifndef ENEMY_H
#define ENEMY_H

#include "point.h"

typedef struct s_enemy
{
    t_point position;
    int alive;
    int direction;
}	t_enemy;

// Function prototypes
// Init Enemy (position, direction, alive status)
// Move Enemy (update position based on direction)
// Update Enemy Status (set alive or dead)
// Render Enemy (draw enemy on screen)
// Enemy Attack (handle enemy attack logic)
// Enemy Takes Damage (handle damage logic)
// Check Enemy Status (check if enemy is alive or dead)
// Enemy Destructor (free enemy resources)


#endif