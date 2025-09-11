#ifndef GAME_H
#define GAME_H

typedef enum s_tile
{
	WALL,
	FLOOR,
	COLLECTIBLE,
	EXIT
}	t_tile;

typedef struct s_point
{
    int x;
    int y;
    int point_type;
}	t_point;

struct Player
{
    int x;
    int y;
};

struct map
{
    int fd;
    int **matrix;
};

struct game
{
    struct map map_;
};

struct miniLibX
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
    struct game map_;
	int		shift_x;
	int		shift_y;
};

#endif
