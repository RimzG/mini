/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-huss <sel-huss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 22:01:55 by sel-huss          #+#    #+#             */
/*   Updated: 2024/12/12 15:55:50 by sel-huss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_eof(void)
{
	write(STDOUT_FILENO, "exit\n", 5);
	rl_clear_history();
	exit(0);
}

void	initialize_shell(t_shell *shell, char **env)
{
	int		i;
	char	*shlvl_str;
	int		level;
	char	*new_level;

	shell->exit_status = 0;
	shell->env = copy_env(env);
	if (!shell->env)
		return ;
	i = 0;
	while (shell->env && shell->env[i]
		&& ft_strncmp(shell->env[i], "SHLVL=", 6))
		i++;
	if (!shell->env || !shell->env[i])
		return ;
	shlvl_str = shell->env[i] + 6;
	level = ft_atoi(shlvl_str) + 1;
	new_level = ft_itoa(level);
	if (!new_level)
		return(free_args(shell->env)) ;
	if (ft_setenv("SHLVL", new_level, shell->env) != 0)
		perror("setenv");
	free(new_level);
	setup_signals();
}

int	process_empty_input(char *input)
{
	if (!input)
		handle_eof();
	if (!input[0] || input[0] == ':' || input[0] == '!')
	{
		free(input);
		return (1);
	}
	return (0);
}

void	process_valid_input(char *input, t_shell *shell)
{
	t_token	*tokens;
	char	**args;

	add_history(input);
	if (!syntax_check(input))
	{
		shell->input_start = input;
		tokens = tokenize_input(input, shell);
		if (tokens)
		{
			args = tokens_to_args(tokens);
			if (args)
			{
				shell->exit_status = execute_command(args, shell);
				free_args(args);
			}
			free_tokens(tokens);
		}
	}
	else
		shell->exit_status = 2;
}
