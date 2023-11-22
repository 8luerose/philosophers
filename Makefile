CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I.

RM = rm -f
NAME = philo

SRCS = cleaning.c               \
       ft_atoi.c                \
       init.c                   \
       main.c                   \
       monitoring.c             \
       philo.c                  \
       utils.c

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
