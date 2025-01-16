NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

SRCS = $(addprefix $(SRC_DIR)/, main.c \
    builtins_utils.c \
	echo.c \
	envp.c \
	execution.c \
	execution1.c \
	export.c \
	export1.c \
	export2.c \
	export3.c \
	external_exec.c \
	ft_split.c \
	get_args_utils.c \
	get_args.c \
	handle_cmd.c \
	heredoc.c \
	initialization.c \
    libft_0.c \
    libft_1.c \
    libft_2.c \
	libft_3.c \
	memory_management.c \
	name_validation.c \
	path.c \
	path1.c \
	pipe_utils.c \
	pipe.c \
	process_input.c \
	redirection.c \
	redirection1.c \
	signals_child.c \
	signals_heredoc.c \
	signals.c \
	syntax_utils.c \
	syntax.c \
	unset.c \
	unset1.c)

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBS = -lreadline

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
