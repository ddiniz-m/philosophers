# - * - Makefile - * -

SRC_PHI = main.c utils.c

SRCS = $(addprefix src/, $(SRC_PHI))
OBJS = $(patsubst src/%, $(OBJS_DIR)/%, $(SRCS:%.c=%.o))

OBJS_DIR = obj
INC = -lpthread

NAME = philo
CC = @cc
CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
		@$(CC) $(CFLAGS) $(INC) $(SRCS) -o $(NAME)
		@echo "\033[0;32mCompiled!\033[0m"

$(OBJS_DIR)/%.o: $(SRCS)
		@mkdir -p $(OBJS_DIR)
		@$(CC) $(CFLAGS) -o $@ -c $<

clean:
		@$(RM) $(OBJS)

fclean: clean
		@$(RM) $(NAME) $(OBJS_DIR)

re: fclean all

.PHONY: all clean fclean re run val