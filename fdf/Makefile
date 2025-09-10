NAME = fdf

SRCS = src/main.c src/draw.c src/parser.c src/color.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -g -Wall -Wextra -Werror -Iincludes

MLX_DIR = minilibx-linux
MLX_LIB = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
LIBFT = libft/libft.a

GNL = GNL/get_next_line.c GNL/get_next_line_utils.c

GNL_OBJS = $(GNL:.c=.o)

all: $(NAME)

$(NAME):
	$(CC) $(CFLAGS) $(SRCS) $(GNL) $(LIBFT) $(MLX_LIB) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
