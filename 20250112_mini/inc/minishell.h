/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-huss <sel-huss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 22:01:55 by sel-huss          #+#    #+#             */
/*   Updated: 2024/12/16 10:00:00 by sel-huss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <dirent.h>
# include <fcntl.h>
# include <termios.h>
# include <sys/stat.h>

# define PROMPT "minishell$ "
# define MAX_PATH 4096
# define MAX_TOKEN_SIZE 200

/* Error codes */
# define SUCCESS 0
# define ERROR 1
# define EXIT_SYNTAX_ERROR 2
# define CTRL_C_EXIT 130
# define CTRL_BACKSLASH_EXIT 131

extern int	g_signo;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_ENV_VAR,
	TOKEN_QUOTED,
	TOKEN_EXIT_STATUS
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			value[MAX_TOKEN_SIZE];
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	int		exit_status;
	char	**env;
	char	*input_start;
}	t_shell;

typedef struct s_pipe_data
{
	int	prev_pipe;
	int	next_pipe;
	int	cmd_start;
}	t_pipe_data;

/* main.c and main_cont.c */
void			handle_eof(void);
void			initialize_shell(t_shell *shell, char **env);
int				process_empty_input(char *input);
void			process_valid_input(char *input, t_shell *shell);

/* builtins.c and builtins_cont.c */
void			ft_echo(char **args, char **envp);
int				ft_cd(char **args, char **envp);
int				ft_pwd(void);
int				ft_exit(char **args);
int				quote_check(const char *input, char quote_type);
char			*remove_quotess(const char *str, char quote_type);
void			update_pwd(char *var, char *value, char **envp);
int				handle_cd_dash(char **envp);
void			dir_change(char *path);
char			*prepare_env_string(const char *name, const char *value);
int				ft_setenv(char *name, const char *value, char **envp);

/* ft_export.c and ft_export_cont.c */
int				modify_value(const char *var, char **envp);
int				add_to_env(const char *var, char **envp);
int				env_check(const char *var, char **envp);
int				ft_export(int argc, char **argv, char **envp);
void			inval_ident(char *argv);
int				get_var_len(const char *str);

/* ft_unset.c and ft_unset_cont.c */
void			*ft_memmove(void *dest, const void *src, size_t n);
char			**env_shift(char **envp, int i);
int				var_search(const char *var, char **envp, int var_len);
int				remove_env(const char *var, char **envp);
int				ft_unset(int argc, char **argv, char **envp);
int				ft_env(char **envp);
void			invalid_unset(char *argv);

/* execute.c , execute_cont.c and execute_utils.c */
int				execute_command(char **args, char **env);
int				execute_builtin(char **args, char **env);
int				execute_external(char **args, char **env);
int				is_builtin(char *cmd);
int				is_directory(const char *path);
char			*find_command_path(char *cmd, char **env);
int				execute_pipeline(char **args, char **env, int cmd_start,
					int cmd_end);
int				has_pipe(char **args);
char			**shift_args(char **args);
char			**get_path(char **env);
char			*try_direct_path(char *cmd);
char			*try_current_dir(char *cmd);
char			*build_path(char *base_path, char *cmd);
char			*search_in_paths(char **paths, char *cmd);
void			handle_child(char **args, char **env, int next_pipe,
					int *pipefd);
void			handle_parent_pipes(int *prev_pipe, int *pipefd);
void			handle_child_process(char **args, char **env, int *pipefd,
					t_pipe_data data);

/* execute_cont2.c and execute_cont3.c */
char			**extract_command(char **args, int start, int end);
int				find_next_command(char **args, int cmd_start, int cmd_end);
void			execute_path(char **env, char **cmd_args);
int				execute_single_command(char **args, char **env, int cmd_start,
					int *pipefd);
int				execute_cmd(char **args, char **env, char *cmd_path);

/* execute_cont4.c */
void			inexistant_file(char **args);
void			error_is_directory(char **args);
void			unfound_command(char **args);
void			permission_check(char **args, char *cmd_path);

/* heredoc.c */
int				handle_heredoc(const char *delimiter);

/* memory_management.c */
char			**copy_env_safe(char **envp);
void			free_args(char **args);
void			free_tokens(t_token *tokens);

/* redirection.c and redirection_cont.c */
void			remove_redirection(char **args, int start);
int				handle_input_redirection(const char *file);
int				handle_output_redirection(const char *file, int append);
void			restore_io(int saved_stdin, int saved_stdout);
int				handle_command_redirections(char **args);
int				remove_redirec_set(char **args, int i);
char			*not_heredoc_quotes(char **args, int *i);
int				*remove_redir(char **args, int *i);
int				handle_specific_redirection(char **args, int *i, int *status);
int				is_valid_redirection_token(char **args, int i);

/* signals.c, signals_child.c, signals_heredoc.c */
void			setup_signals(void);
void			setup_child_signals(void);
void			setup_heredoc_signals(void);

/* syntax_check.c and syntax_check_cont.c */
int				syntax_check(char *input);
int				check_quotes_state(char *input, int *i, int *in_quotes,
					char *quote_type);
int				check_pipe_syntax(char *input, int i);
int				check_redir_syntax(char *input, int i);
int				check_initial_pipe(char *input, int i);
int				check_logical_and(char *input, int i);
int				check_redirections(char *input, int i);
int				parse_input(char *input, int *i, int *in_quotes,
					char *quote_type);

/* token_process.c, token_next.c, tokenization.c */
t_token			*create_token(const char *value);
void			add_token(t_token **start, t_token *new_token);
t_token_type	check_type(const char *value);
char			**tokens_to_args(t_token *tokens);
char			*handle_env_name(char **input, t_shell *shell);
char			*handle_special_token(char **input);
char			*handle_env_variable(char **input, t_shell *shell);
char			*process_token(char **input, t_shell *shell);
char			*get_next_token(char **input, t_shell *shell);
t_token			*tokenize_input(char *input, t_shell *shell);
char			*get_env_value(char *var_name, char **envp);

/* print_export.c and print_export_cont.c */
int				ft_envsize(char **envp);
void			swap_env_entries(char **a, char **b);
void			sort_env_inner(char **envp, int size);
void			sort_env(char **envp);
char			**copy_env(char **envp);
void			free_envp_copy(char **envp_copy);
void			print_env_entry(char *entry);
void			print_export(char **envp);

/* libft functions */
int				ft_isalpha(int c);
int				ft_isalnum(int c);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strchr(const char *s, int c);
size_t			ft_strlen(const char *s);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *s);
char			*ft_strndup(const char *s, int n);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
char			*ft_substr(const char *s, unsigned int start, size_t len);
int				is_whitespace(char c);
int				is_special_char(char c, char prev_char);
int				is_valid_identifier(const char *str);
char			*remove_quotes(char *str);
char			**ft_split(const char *str, char c);
char			*ft_strcpy(char *dest, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t size);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
char			*ft_itoa(int n);
int				int_length(int n);
int				ft_atoi(const char *str);

/* utils_cont.c */
int				count_args(char **args);
int				is_directory(const char *path);
char			*get_working_dir(void);
void			print_error(char *cmd, char *msg);

#endif