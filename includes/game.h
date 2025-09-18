#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "../minilibx-linux/mlx.h"
#include "../minilibx-linux/mlx_int.h"


typedef struct s_anim
{
    char    **frames;      // array of file paths
    int      frame_count;  // total number of frames
    int      frame;        // current frame index
    int      speed;        // ticks per frame
    int      counter;      // internal counter for speed
    int      x;            // tile X position
    int      y;            // tile Y position
}   t_anim;


typedef struct s_minlibx
{
	void	*mlx;
	void	*win;
	int		width;
	int		height;
	char	*label;
	t_map	map;
	t_anim	**anims;
	int		anim_count;
	int		shift_x;
	int		shift_y;
}	t_minilibx;

typedef struct s_image_data {
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;
    int     line_length;
    int     endian;
} t_image_data;


/*		Minilibx Constr-Destr		*/
t_minilibx  minilibx_constructor(t_map *map, int height, int width, char *label);
void	    minilibx_destructor(t_minilibx *data);

/*		xpm processing		*/
int				draw_image_32(t_minilibx *data, char *filename, int x, int y);
t_image_data	load_and_scale_xpm(void *mlx, char *filename);
t_image_data    load_and_scale_xpm_96x32(void *mlx, char *filename);
int             draw_image_96x32(t_minilibx *data, char *filename, int x, int y);



/*		Events Handler			*/
int handle_key(int keycode, t_minilibx *data);

/*		Map Initializer			*/
int draw_map(t_minilibx *data);

/*		Ending Methods	*/
int game_over(t_minilibx *data, int win);
int close_window(t_minilibx *data);

/*		Game Movement	*/
void	    move_player(t_minilibx *data, int dx, int dy, int movement_type);
void        down(t_minilibx *data, int old_x, int old_y, int new_x, int new_y);
void        left(t_minilibx *data, int old_x, int old_y, int new_x, int new_y);
void        right(t_minilibx *data, int old_x, int old_y, int new_x, int new_y);
void        up(t_minilibx *data, int old_x, int old_y, int new_x, int new_y);
t_anim      *init_anim(char **files, int frame_count, int speed, int x, int y);
void        render_anim(t_minilibx *data, t_anim *anim);
void        update_anim(t_minilibx *data, t_anim *anim);
int         animate_all(t_minilibx *data);


#endif