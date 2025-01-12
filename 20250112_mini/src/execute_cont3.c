/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cont3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-huss <sel-huss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:58:36 by sel-huss          #+#    #+#             */
/*   Updated: 2024/12/30 22:33:42 by sel-huss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child(char **cmd_args, char **env)
{
	if (handle_command_redirections(cmd_args) == 0)
	{
		if (is_builtin(cmd_args[0]))
			exit(execute_builtin(cmd_args, env));
		else
			execute_path(env, cmd_args);
	}
	exit(1);
}

int	execute_single_command(char **args, char **env, int cmd_start, int *pipefd)
{
	char	**cmd_args;
	pid_t	pid;
	int		next_pipe;

	next_pipe = find_next_command(args, cmd_start, count_args(args));
	cmd_args = extract_command(args, cmd_start, next_pipe);
	if (!cmd_args)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		free_args(cmd_args);
		return (-1);
	}
	if (pid == 0)
	{
		handle_child(args, env, next_pipe, pipefd);
		execute_child(cmd_args, env);
	}
	free_args(cmd_args);
	return (pid);
}
