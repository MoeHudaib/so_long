CC = cc
CFLAGS = -Wall -Wextra -Werror
LINK = ../libft/libft.a -I../libft
SRC = ft_printf.c ft_printptr.c ft_printunbr.c ft_printstr.c ft_printnbr.c ft_inttohexalow.c ft_inttohexaup.c
NAME = libftprintf.a
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)
fclean : clean
	rm -f $(NAME)

re : fclean all
