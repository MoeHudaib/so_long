#include "game.h"
/* -------------------------------------------------- */
/* Minilibx constructor/destructor                    */
/* -------------------------------------------------- */

t_minilibx minilibx_constructor(t_map *map, int height, int width, char *label)
{
    t_minilibx data;

    data.height = height;
    data.width = width;
    data.label = label;
    data.map = *map;
    data.mlx = NULL;
    data.win = NULL;
    data.anim_count = 0;
    data.anims = malloc(sizeof(t_anim *) * 25);
    if (!data.anims)
        return (data);
    return data;
}

void minilibx_destructor(t_minilibx *data)
{
    if (!data)
        return;

    if (data->win)
    {
        mlx_destroy_window(data->mlx, data->win);
        data->win = NULL;
    }
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
        data->mlx = NULL;
    }
}

int handle_key(int keycode, t_minilibx *data)
{
    if (keycode == KEY_W)
        move_player(data, 0, -1, UP); // up
    else if (keycode == KEY_A)
        move_player(data, -1, 0, LEFT); // left
    else if (keycode == KEY_S)
        move_player(data, 0, 1, DOWN);  // down
    else if (keycode == KEY_D)
        move_player(data, 1, 0, RIGHT);  // right
    else if (keycode == KEY_ESC)
        close_window(data);
    return (0);
}

void move_player(t_minilibx *data, int dx, int dy, int movement_type)
{
    int old_x = data->map.player.position.x;
    int old_y = data->map.player.position.y;
    int new_x = old_x + dx;
    int new_y = old_y + dy;

    char cell = data->map.grid[new_y][new_x];
    if (cell == '1') // wall
        return;
    if (cell == 'E') // exit
    {
        if (data->map.collectibles == 0)
            game_over(&data->map, 1); // win
        return;
    }
    if (cell == 'N') // enemy
    {
        draw_image_32(data, "srcs/images/up/hurt.xpm", new_x * 32, new_y * 32);
        data->map.player.health -= 50;
        if (data->map.player.health == -50)
        {    
            game_over(&data->map, 0); // lose
            return;
        }
        else if (data->map.player.health == 50)
        {
            draw_image_96x32(data, "srcs/images/health_bar/h2.xpm", data->map.sb_posistion.x * 32, data->map.sb_posistion.y * 32);

        }
        else
            draw_image_96x32(data, "srcs/images/health_bar/h3.xpm", data->map.sb_posistion.x * 32, data->map.sb_posistion.y * 32);

        for (int i = 0; i < data->anim_count; i++)
        {
            t_anim *anim = data->anims[i];
            if (anim && anim->x == new_x && anim->y == new_y)
            {
                free(anim->frames);  // frames are file paths, so just free the array
                free(anim);
                for (int j = i; j < data->anim_count - 1; j++)
                    data->anims[j] = data->anims[j + 1];
                data->anims[data->anim_count - 1] = NULL;
                data->anim_count--;
                break;
            }
        }
        draw_image_32(data, "srcs/images/enemy/N13.xpm", new_x * 32, new_y * 32);
       // usleep(50000);
        draw_image_32(data, "srcs/images/enemy/N14.xpm", new_x * 32, new_y * 32);
       // usleep(50000);
        draw_image_32(data, "srcs/images/enemy/N15.xpm", new_x * 32, new_y * 32);
        //usleep(50000);
        draw_image_32(data, "srcs/images/enemy/N16.xpm", new_x * 32, new_y * 32);
        //usleep(50000);
        draw_image_32(data, "srcs/images/enemy/N17.xpm", new_x * 32, new_y * 32);
        usleep(100000);
        draw_image_32(data, "srcs/images/enemy/N18.xpm", new_x * 32, new_y * 32);
        draw_image_32(data, "srcs/images/up/hurt.xpm", new_x * 32, new_y * 32);
    }
    if (cell == 'C') // collectible
    {
        data->map.collectibles--;

        // Remove the coin animation at this position
        for (int i = 0; i < data->anim_count; i++)
        {
            t_anim *anim = data->anims[i];
            if (anim && anim->x == new_x && anim->y == new_y)
            {
                // Free the animation
                free(anim->frames);  // frames are file paths, so just free the array
                free(anim);

                // Remove from array
                for (int j = i; j < data->anim_count - 1; j++)
                    data->anims[j] = data->anims[j + 1];
                data->anims[data->anim_count - 1] = NULL;
                data->anim_count--;
                break;
            }
        }
    }

    // update map grid
    data->map.grid[old_y][old_x] = '0';
    data->map.grid[new_y][new_x] = 'P';
    data->map.player.position.x = new_x;
    data->map.player.position.y = new_y;
    ++data->map.player.steps;
    printf("steps: %d\n", data->map.player.steps);

    //  Redraw only the changed tiles
    if (movement_type == UP)
        up(data, old_x, old_y, new_x, new_y);
    if (movement_type == DOWN)
        down(data, old_x, old_y, new_x, new_y);
    if (movement_type == LEFT)
        left(data, old_x, old_y, new_x, new_y);
    if (movement_type == RIGHT)
        right(data, old_x, old_y, new_x, new_y);
}