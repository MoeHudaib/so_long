#ifndef PLAYER_H
#define PLAYER_H

#include "point.h"
#include "libft/libft.h"


typedef struct s_player
{
	t_point position;
	int steps;
	int collectibles;
	int health;
	int	last_movement;
}	t_player;

typedef enum e_movement_type
{
	UP = 888,
	DOWN = 777,
	LEFT = 666,
	RIGHT = 555
}	t_movement_type;

// Function prototypes
// init Player (position, health, steps, direction)
// Move Player (update position based on direction)
// Update Player Health (increase or decrease health)
// Increment Steps (increase step count)
// Reset Player (reset to initial state)
// Render Player (draw player on screen)
// Player Attack (handle player attack logic)
// Player Collect Item (handle item collection logic)
// Player Takes Damage (handle damage logic)
// Check Player Status (check if player is alive or dead)
// Player Interact (handle interactions with game elements)
// Player Die (handle player death logic)
// Player Win (handle win condition logic)
// Player Destructor (free player resources)
t_player	init_player(t_point point, int health);


#endif