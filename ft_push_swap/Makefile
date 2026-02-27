NAME = push_swap
CC = cc
CFLAGS = -Wall -Werror -Wextra

SRCS = main.c error_free.c split.c push_command.c push_swap_command.c \
		push_swap_init.c reverse_rotate_command.c rotate_command.c \
		stack_init.c stack_utils.c swap_command.c tiny_sort.c
OBJS = $(SRCS:.c=.o)

HEADERS = push_swap.h

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclea re
