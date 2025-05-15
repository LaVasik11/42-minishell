NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes/ -I libft/
LIBS = -lreadline
RM = rm -rf

SRCDIR = src
SRCS = $(SRCDIR)/minishell.c $(SRCDIR)/signal.c $(SRCDIR)/init.c $(SRCDIR)/free_minishell.c $(SRCDIR)/parse_input.c $(SRCDIR)/execute_command.c $(SRCDIR)/utils/utils.c $(SRCDIR)/utils/path_utils.c
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