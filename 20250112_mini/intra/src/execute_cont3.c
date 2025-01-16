/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cont3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:58:36 by sel-huss          #+#    #+#             */
/*   Updated: 2025/01/17 00:27:42 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_single_command(char **args, t_shell *shell,
		int cmd_start, int *pipefd)
{
	char	**cmd_args;
	pid_t	pid;
	int		next_pipe;

	next_pipe = find_next_command(args, cmd_start, count_args(args));
	cmd_args = extract_command(args, cmd_start, next_pipe);
	if (!cmd_args)
		return (free_args(shell->env), -1);
	pid = fork();
	if (pid == -1)
	{
		free_args(shell->env);
		free_args(cmd_args);
		return (-1);
	}
	if (pid == 0)
	{
		handle_child(args, shell, next_pipe, pipefd);
		execute_child(cmd_args, shell);
	}
	return (pid);
}
