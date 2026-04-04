NAME = push_swap
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS = main.c error_free.c push_command.c simple_sort.c \
		push_swap_init.c reverse_rotate_command.c rotate_command.c \
		stack_init.c stack_utils.c swap_command.c tiny_sort.c disorder.c \
		medium_sort.c complex_sort.c bench.c operation.c
OBJS = $(SRCS:.c=.o)

HEADERS = push_swap.h

LIBFTPRINTF = ft_printf/libftprintf.a
LIBFTFPRINTF = ft_fprintf/libftfprintf.a
LIBFT = libft/libft.a

all : $(NAME)

$(LIBFTPRINTF):
	make -C ft_printf
$(LIBFTFPRINTF):
	make -C ft_fprintf
$(LIBFT):
	make -C libft

$(NAME) : $(OBJS) $(LIBFTPRINTF) $(LIBFTFPRINTF) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -L./ft_printf -lftprintf -L./ft_fprintf -lftfprintf -L./libft -lft -o $(NAME)

clean :
	rm -f $(OBJS)
	rm -f $(LIBFTPRINTF)
	rm -f $(LIBFTFPRINTF)
	rm -f $(LIBFT)


fclean : clean
	make -C ft_printf fclean
	make -C ft_fprintf fclean
	make -C libft fclean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re


