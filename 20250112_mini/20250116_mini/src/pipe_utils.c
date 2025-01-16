/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 00:17:46 by rgedeon           #+#    #+#             */
/*   Updated: 2025/01/17 00:21:16 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_next_command(char **args, int cmd_start, int cmd_end)
{
	int	next_pipe;

	if (!args)
		return (cmd_start);
	next_pipe = cmd_start;
	while (args[next_pipe] && next_pipe < cmd_end)
	{
		if (ft_strcmp(args[next_pipe], "|") == 0)
			break ;
		next_pipe++;
	}
	return (next_pipe);
}

void	handle_child(char **args, t_shell *shell, int next_pipe, int *pipefd)
{
	(void)shell;
	if (args[next_pipe] && ft_strcmp(args[next_pipe], "|") == 0)
	{
		close(pipefd[0]);
		if (dup2(pipefd[1], STDOUT_FILENO) == -1)
		{
			free_envp(shell->envp);
			exit(1);
		}
		close(pipefd[1]);
	}
}

void	execute_child(char **cmd_args, t_shell *shell)
{
	if (handle_command_redirections(cmd_args) == 0)
	{
		if (is_builtin(cmd_args[0]))
			exit(execute_builtin(cmd_args, shell));
		else
			exit(execute_external(cmd_args, shell->envp));
	}
	exit(1);
}

void	handle_child_process(char **args, t_shell *shell, int *pipefd,
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
	{
		free_envp(shell->envp);
		free_args(cmd_args);
		exit(1);
	}
	execute_child(cmd_args, shell);
}

void	handle_parent_pipes(int *prev_pipe, int *pipefd)
{
	if (*prev_pipe != -1)
		close(*prev_pipe);
	if (pipefd[1] != -1)
		close(pipefd[1]);
	*prev_pipe = pipefd[0];
}
