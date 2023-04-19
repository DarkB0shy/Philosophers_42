SRCS = child_process.c errors.c init.c main.c sem_utils.c

OBJS	= $(SRCS:.c=.o)

NAME	= philo_bonus

CLANG	= clang

FLAGS	= -Wall -Wextra -Werror -g

INCLUDE	= -pthread

HEADER	= philo_bonus.h

all:	$(NAME)

.PHONY:	clean fclean re bonus bench bclean

$(NAME): $(OBJS)
	$(CLANG) $(INCLUDE) $(FLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS)

re: fclean all

%.o: %.c $(HEADER)
	$(CLANG) $(FLAGS) -c $<  -o $(<:.c=.o)