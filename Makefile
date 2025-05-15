NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes/ -I libft/
LIBS = -lreadline
RM = rm -rf

SRCS = src/minishell.c \
       src/signal.c \
       src/init.c \
       src/free_minishell.c \
       src/utils/path_utils.c \
       src/parse/parse_input.c \
       src/execute_command.c \
       src/utils/utils.c \
	   src/parse/parse_utils1.c \
	   src/parse/parse_utils2.c \
	   src/parse/copy_quoted.c \
	   src/parse/copy_unquoted.c
OBJS = ${SRCS:.c=.o}

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LIBS)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: re all clean fclean