# CC = cc
# CFLAGS = -Wall -Wextra -Werror
# INCLUDES = -I.

# RM = rm -f
# NAME = philo

# SRCS = main.c                   \
#        ft_atoi.c                \
#        utils.c					\
#        init.c                   \
#        philo.c                  \
#        monitoring.c             \
# 	   cleaning.c               \

# OBJS = $(SRCS:.c=.o)

# %.o : %.c
# 	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# all : $(NAME)

# $(NAME) : $(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# clean:
# 	$(RM) $(OBJS)

# fclean: clean
# 	$(RM) $(NAME)

# re: fclean all

# .PHONY: all clean fclean re

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread
INCLUDES = -I.

RM = rm -f
NAME = philo

SRCS = main.c                   \
       ft_atoi.c                \
       utils.c                  \
       init.c                   \
       philo.c                  \
       monitoring.c             \
       cleaning.c               \

OBJS = $(SRCS:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
