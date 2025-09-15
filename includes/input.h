#ifndef INPUT_H
# define INPUT_H

# include <stddef.h>

/* forward */
typedef struct s_game t_game;


// int		loop_hook(void *param);

/* Default keycodes (adjust for platform) */
typedef enum e_key
{
    KEY_W = 119,
    KEY_A = 97,
    KEY_S = 115,
    KEY_D = 100,
    KEY_ESC = 65307
} t_key;

#endif
