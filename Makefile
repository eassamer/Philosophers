NAME = philo

GCC = gcc
FLAGS = -Wall -Wextra -Werror

SRCS = main.c \
	mutex.c \
	thread.c \
	time.c \
	utils.c \

OBJS = $(SRCS:.c=.o)


HEADER = philo.h

all: $(NAME)

$(NAME) : $(OBJS) $(HEADER)
		$(GCC) $(CFLAGS) $(OBJS) -o $(NAME)
		@echo "\x1B[36m\n\t"------rah tcompila------

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re