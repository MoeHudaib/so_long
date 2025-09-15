# Compiler and flags
CC = cc
CFLAGS = -g 
MLX_FLAGS = -Lminilibx-linux -lmlx_Linux -lXext -lX11 -lm

# Source files
SRCS = srcs/game/game.c \
	   srcs/game/game_init.c \
	   srcs/game/game_utils.c \
	   srcs/game/game_movement.c \
	   srcs/game/render.c \
	   srcs/map/map.c \
	   srcs/map/map_hw.c \
	   srcs/map/get_next_line.c \
	   srcs/map/get_next_line_utils.c \
	   srcs/map/map_grid.c \
	   srcs/map/map_validator.c \
	   srcs/player.c

# Libraries
LIBFT = includes/libft/libft.a

# Includes
INCLUDES = -Iincludes -Iminilibx-linux

ss: $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(INCLUDES) $(MLX_FLAGS) -o ss

do: ss
	valgrind --leak-check=full --show-leak-kinds=definite,possible --track-origins=yes --errors-for-leak-kinds=definite,possible -s ./ss

clean:
	rm -f ss

fclean: clean

re: fclean ss

.PHONY: all clean fclean re do