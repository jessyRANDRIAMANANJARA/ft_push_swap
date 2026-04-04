NAME = libftfprintf.a

CC = cc

CFLAGS = -Wall -Werror -Wextra

SRCS = ft_fprintf.c ft_fputstr.c ft_fputchar.c ft_fputnbr.c \
		ft_count_len.c ft_fputfloat.c

OBJ = $(SRCS:.c=.o)

HEADER = ft_fprintf.h 

all: $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -c $(SRCS) -I $(HEADER)
	ar rc $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all  re clean fclean
