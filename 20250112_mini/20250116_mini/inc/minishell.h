/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 22:01:55 by sel-huss          #+#    #+#             */
/*   Updated: 2025/01/17 01:30:12 by rgedeon          ###   ########.fr       */
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
# include <limits.h>

# define PROMPT "minishell$ "
# define MAX_PATH 4096
# define MAX_TOKEN_SIZE 200

extern int	g_signo;

// typedef enum e_token_type
// {
// 	TOKEN_WORD,
// 	TOKEN_PIPE,
// 	TOKEN_REDIR_IN,
// 	TOKEN_REDIR_OUT,
// 	TOKEN_REDIR_APPEND,
// 	TOKEN_REDIR_HEREDOC,
// 	TOKEN_ENV_VAR,
// 	TOKEN_QUOTED,
// 	TOKEN_EXIT_STATUS
// }	t_token_type;

// typedef struct s_token
// {
// 	t_token_type	type;
// 	char			*value;
// 	struct s_token	*next;
// }	t_token;

typedef struct s_env
{
	char			*env_value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	int		exit_status;
	char	*input_start;
	t_env	*envp;	//pointer to the first node of envp
}	t_shell;

typedef struct s_pipe_data
{
	int	prev_pipe;
	int	next_pipe;
	int	cmd_start;
}	t_pipe_data;

typedef struct s_pipeline_data
{
	char	**args;
	t_shell	*shell;
	int		cmd_start;
	int		cmd_end;
	pid_t	*pid;
}	t_pipeline_data;



/*builtins_utils.c*/
int		ft_setenv(char *name, const char *value, t_env *envp);
int	is_builtin(char *cmd);
int	get_var_len(const char *str);

/*echo.c*/
void	ft_echo(char **args);

/* envp.c */
t_env	*create_envp(char **envp);
void	print_envp(t_env *head);
void	free_envp(t_env *head);
t_env	*append_node(t_env *head, char *env_var);

/* execution.c */
int	count_args(char **args);

/* export.c */
int	ft_export(int argc, char **argv, t_env *envp_list);
int	modify_value(const char *var, t_env *envp_list);
int	add_to_env(const char *var, char ***envp);
void	print_export(t_env *envp_list);

/*extrenal_exec.c*/
int	execute_external(char **args, t_env *envp_list);
char	*find_command_path(char *cmd, char **env);

/* initialization.c */
void	initialize_shell(t_shell *shell, char **env);

/* libft.c */
int	ft_strcmp(const char *s1, const char *s2);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);

/* memory_management.c */
void	free_args(char **args);

/*name_validation.c*/
int	is_valid_identifier(const char *str);

/* path.c */
char	*get_env_value(char *var_name, t_env *env_list);
int	ft_cd(char **args, t_env *env_list);
int	ft_pwd(void);
int	ft_exit(char **args);

/* pipe.c and utils.c*/
int	has_pipe(char **args);
int	execute_pipeline(char **args, t_shell *shell, int cmd_start, int cmd_end);
void	handle_child(char **args, t_shell *shell, int next_pipe, int *pipefd);
void	execute_child(char **cmd_args, t_shell *shell);

/* process_input.c */
void	process_input(char *input, t_shell *shell);

/*redirection.c*/
void	restore_io(int saved_stdin, int saved_stdout);
int	handle_command_redirections(char **args);
int	is_valid_redirection_token(char **args, int i);

/* signals.c */
int		process_empty_input(char *input);
void	setup_signals(void);

/* syntax_check.c and syntax_check_cont.c */
int	is_whitespace(char c);
int	check_pipe_syntax(char *input, int i);
int	syntax_error(char *input);
int	check_logical_and(char *input, int i);
int	check_redirections(char *input, int i);

/* get_args.c and get_args_utils.c */
int	is_special_char(char c, char prev_char);
char	**get_args(char *input);

/*unset.c*/
int	ft_unset(int argc, char **argv, t_env *envp);
int	ft_env(t_env *envp);


#endif