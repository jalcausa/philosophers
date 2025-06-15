GREEN = \033[0;32m
YELLOW = \033[0;33m
RESET = \033[0m

NAME	= philo
CC = cc
CFLAGS	= -Wall -Wextra -Werror

HEADERS = -I ./includes

SRCS =	src/main.c			\
		src/parsing.c		\
		src/init.c			\
		src/utils.c			\
		src/simulation.c	\
		src/simulation2.c	\
		src/monitor.c		\
		src/cleanup.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	@echo "$(GREEN)Linking $@$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) -o $(NAME)
	@echo "$(GREEN)Compilation complete, executable created!$(RESET)"

clean:
	@rm -rf $(OBJS)
	@echo "$(YELLOW)Cleaning object files...$(RESET)"
	@echo "$(GREEN)Basic clean complete, executable remaining!$(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(YELLOW)Cleaning executable...$(RESET)"
	@echo "$(GREEN)Full clean complete!$(RESET)"

re: fclean all

.PHONY: all clean fclean re libft