NAME = push_swap
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS = main.c error_free.c split.c push_command.c simple_sort.c \
		push_swap_init.c reverse_rotate_command.c rotate_command.c \
		stack_init.c stack_utils.c swap_command.c tiny_sort.c disorder.c \
		medium_sort.c
OBJS = $(SRCS:.c=.o)

HEADERS = push_swap.h

LIBFTPRINTF = ft_printf/libftprintf.a

all : $(NAME)

$(LIBFTPRINTF):
	make -C ft_printf

$(NAME) : $(OBJS) $(LIBFTPRINTF)
	$(CC) $(CFLAGS) $(OBJS) -Lft_printf -lftprintf -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	make -C ft_printf fclean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
