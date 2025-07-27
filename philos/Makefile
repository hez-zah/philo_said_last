NAME = philo

SRCS = main.c \
       simulation.c \
       parsing.c \
       routine.c \
       ft_atoi.c \
       utlis_1.c \
       utlis_2.c

HEADER = philo.h

CC = cc
CFLAGS = -Werror -Wextra -Wall -pthread -g3 -fsanitize=thread
RM = rm -f

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re