# Compiler and flags
CC = cc
CFLAGS = -g 
MLX_FLAGS = -Lminilibx-linux -lmlx_Linux -lXext -lX11 -lm
NAME=so_long
# Source files
SRCS = main.c \
       srcs/game/game.c \
	   srcs/game/game_init.c \
	   srcs/game/game_utils.c \
	   srcs/game/game_movement.c \
	   srcs/game/draw_map.c \
	   srcs/game/load_and_scale_xpm.c \
	   srcs/game/load_and_scale_96.c \
	   srcs/game/render.c \
	   srcs/game/move.c \
	   srcs/map/map.c \
	   srcs/map/map_hw.c \
	   srcs/map/get_next_line.c \
	   srcs/map/get_next_line_utils.c \
	   srcs/map/map_grid.c \
	   srcs/map/map_validator.c \
	   srcs/map/map_validator_utils.c \
	   srcs/DFS/dfs.c \
	   srcs/player.c

MAP =  srcs/map/map.c \
	   srcs/map/map_hw.c \
	   srcs/map/get_next_line.c \
	   srcs/map/get_next_line_utils.c \
	   srcs/map/map_grid.c \
	   srcs/map/map_validator.c \
	   srcs/DFS/dfs.c \
	   srcs/player.c

# Libraries
LIBFT = includes/libft/libft.a includes/ft_printf/libftprintf.a

# Includes
INCLUDES = -Iincludes -Iminilibx-linux

all: $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(INCLUDES) $(MLX_FLAGS) -o $(NAME)

memory: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=definite,possible --track-origins=yes --errors-for-leak-kinds=definite,possible --suppressions=minilibx-linux/mlx.supp ./$(NAME) maps/test.ber

map:$(MAP) $(LIBFT)
	$(CC) $(CFLAGS) $(MAP) $(LIBFT) $(INCLUDES) $(MLX_FLAGS) -o kk

clean:
	

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re do
