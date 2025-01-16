NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

SRCS = $(addprefix $(SRC_DIR)/, main.c \
		builtins.c \
		builtins_cont.c \
		builtins_cont2.c \
		execute.c \
		execute_cont.c \
		execute_cont2.c \
		execute_cont2_utils.c \
		execute_cont3.c \
		execute_cont4.c \
		execute_pipeline.c \
		execute_externals.c \
		ft_export.c \
		ft_export_utils.c \
		ft_export_cont.c \
		ft_split.c \
		ft_unset.c \
		ft_unset_cont.c \
		libft.c \
		libft_cont.c \
		libft_cont2.c \
		libft_cont3.c \
		name_validation.c \
		print_export.c \
		utils.c \
		signals.c \
		redirection.c \
		redirection_cont.c \
		heredoc.c \
		syntax_check.c \
		memory_management.c \
		syntax_check_cont.c \
		tokenization.c \
		token_args.c \
		token_next.c \
		token_process.c \
		signals_child.c \
		signals_heredoc.c \
		print_export_cont.c \
		main_cont.c \
		execute_utils.c \
		utils_cont.c)

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
