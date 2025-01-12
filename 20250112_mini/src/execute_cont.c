/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cont.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-huss <sel-huss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 02:15:10 by rgedeon           #+#    #+#             */
/*   Updated: 2024/12/26 20:59:09 by sel-huss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_pipe(char **args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "|") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}

int	execute_builtin(char **args, char **env)
{
	if (!args || !args[0])
		return (1);
	if (ft_strcmp(args[0], "echo") == 0)
		return (ft_echo(args, env), 0);
	else if (ft_strcmp(args[0], "cd") == 0)
		return (ft_cd(args, env));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	else if (ft_strcmp(args[0], "export") == 0)
		return (ft_export(count_args(args), args, env));
	else if (ft_strcmp(args[0], "unset") == 0)
		return (ft_unset(count_args(args), args, env));
	else if (ft_strcmp(args[0], "env") == 0)
		return (ft_env(env));
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

int	execute_command(char **args, char **env)
{
	int	saved_stdin;
	int	saved_stdout;
	int	status;
	int	i;

	if (!args || !args[0])
		return (0);
	if (args[0][0] == '\0')
		return (shift_args(args), execute_command(args, env));
	i = count_args(args);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (has_pipe(args))
		status = execute_pipeline(args, env, 0, i);
	else
	{
		if (handle_command_redirections(args) != 0)
			return (restore_io(saved_stdin, saved_stdout), 1);
		if (is_builtin(args[0]))
			status = execute_builtin(args, env);
		else
			status = execute_external(args, env);
	}
	return (restore_io(saved_stdin, saved_stdout), status);
}
