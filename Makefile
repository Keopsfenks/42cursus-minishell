SRCS = ./srcs/main.c \
		./srcs/parser/parser_process.c \
		./srcs/parser/utils.c			\
		./srcs/parser/removed_space_quot.c
NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -lreadline
RM = rm -rf
LIBFT = ./srcs/libary/libft/libft.a
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	@gcc $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME)
	@echo "************************"
	@echo "   MINISHELL CREATED"
	@echo "************************"

$(LIBFT) :
	@make -C ./srcs/libary/libft
	@make bonus -C ./srcs/libary/libft

clean:
	$(RM) $(OBJS)
	@make fclean -C ./srcs/libary/libft

fclean: clean
	$(RM) $(NAME)
	@make fclean -C ./srcs/libary/libft

re: fclean all

.PHONY: all bonus clean fclean re .c.o