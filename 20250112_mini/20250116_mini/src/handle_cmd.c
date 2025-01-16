/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 19:50:29 by sel-huss          #+#    #+#             */
/*   Updated: 2025/01/17 00:28:18 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_cmd_error(pid_t pid, char *cmd_path)
{
	if (pid == -1)
	{
		free(cmd_path);
		perror("minishell");
	}
}

static int	handle_cmd_status(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGQUIT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		return (128 + WTERMSIG(status));
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (status);
}

int	execute_cmd(char **args, char **env, char *cmd_path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	handle_cmd_error(pid, cmd_path);
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		setup_child_signals();
		execve(cmd_path, args, env);
		free(cmd_path);
		exit(127);
	}
	free(cmd_path);
	waitpid(pid, &status, 0);
	return (handle_cmd_status(status));
}
