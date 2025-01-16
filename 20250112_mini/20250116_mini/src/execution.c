/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 02:15:10 by rgedeon           #+#    #+#             */
/*   Updated: 2025/01/17 01:14:12 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(char **args, t_env *envp_list)
{
	if (!args || !args[0])
		return (1);
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args), 0);
	else if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args, envp_list));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(count_args(args), args, envp_list));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(count_args(args), args, envp_list));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(envp_list));
	else if (ft_strcmp(args[0], "exit") == 0)
		return (ft_exit(args));
	return (1);
}

char	**shift_args(char **args)
{
	int	i;

	if (!args || !args[0])
		return (NULL);
	i = 0;
	while (args[i + 1])
	{
		args[i] = args[i + 1];
		i++;
	}
	args[i] = NULL;
	return (args);
}

int	count_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
		i++;
	return (i);
}

int	execute_command(char **args, t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;
	int	i;

	if (!args || !args[0])
		return (0);
	if (args[0][0] == '\0')
		return (shift_args(args), execute_command(args, shell));
	i = count_args(args);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (has_pipe(args))
		status = execute_pipeline(args, shell, 0, i);
	else
	{
		if (handle_command_redirections(args) != 0)
			return (restore_io(saved_stdin, saved_stdout), 1);
		if (is_builtin(args[0]))
			status = execute_builtin(args, shell->envp);
		else
			status = execute_external(args, shell->envp);
	}
	return (restore_io(saved_stdin, saved_stdout), status);
}
