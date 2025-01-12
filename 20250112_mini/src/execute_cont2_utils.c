/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cont2_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-huss <sel-huss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:58:36 by sel-huss          #+#    #+#             */
/*   Updated: 2024/12/30 23:06:24 by sel-huss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_child(char **args, char **env, int next_pipe, int *pipefd)
{
	(void)env;
	if (args[next_pipe] && ft_strcmp(args[next_pipe], "|") == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
			exit(1);
		close(pipefd[1]);
	}
}

void	execute_child(char **cmd_args, char **env)
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

void	handle_child_process(char **args, char **env, int *pipefd,
		t_pipe_data data)
{
	char	**cmd_args;

	setup_child_signals();
	if (data.prev_pipe != -1)
	{
		dup2(data.prev_pipe, STDIN_FILENO);
		close(data.prev_pipe);
	}
	if (args[data.next_pipe] && ft_strcmp(args[data.next_pipe], "|") == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	cmd_args = extract_command(args, data.cmd_start, data.next_pipe);
	if (!cmd_args)
		exit(1);
	if (handle_command_redirections(cmd_args) == 0)
	{
		if (is_builtin(cmd_args[0]))
			exit(execute_builtin(cmd_args, env));
		else
			execute_path(env, cmd_args);
	}
	exit(1);
}

void	handle_parent_pipes(int *prev_pipe, int *pipefd)
{
	if (*prev_pipe != -1)
		close(*prev_pipe);
	if (pipefd[1] != -1)
		close(pipefd[1]);
	*prev_pipe = pipefd[0];
}
