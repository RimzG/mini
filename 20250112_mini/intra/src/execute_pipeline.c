/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-huss <sel-huss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:15:19 by sel-huss          #+#    #+#             */
/*   Updated: 2025/01/13 20:32:22 by sel-huss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	wait_for_children(pid_t last_pid)
{
	pid_t	pid;
	int		status;
	int		last_status;

	last_status = 0;
	while (1)
	{
		pid = waitpid(-1, &status, 0);
		if (pid == -1)
			break ;
		if (pid == last_pid)
			last_status = status;
	}
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	if (WIFSIGNALED(last_status))
		return (128 + WTERMSIG(last_status));
	return (last_status);
}

static int	create_pipes(char **args, int next_pipe, int *pipefd)
{
	if (args[next_pipe] && ft_strcmp(args[next_pipe], "|") == 0)
	{
		if (pipe(pipefd) == -1)
			return (1);
	}
	return (0);
}

void	execute_pipeline_loop(t_pipeline_data *data)
{
	int			pipefd[2];
	int			prev_pipe;
	int			next_pipe;
	t_pipe_data	pipe_data;

	prev_pipe = -1;
	pipefd[0] = -1;
	pipefd[1] = -1;
	while (data->cmd_start < data->cmd_end)
	{
		next_pipe = find_next_command(data->args,
				data->cmd_start, data->cmd_end);
		if (create_pipes(data->args, next_pipe, pipefd))
			return ;
		*(data->pid) = fork();
		if (*(data->pid) == -1)
			return ;
		if (*(data->pid) == 0)
		{
			pipe_data = (t_pipe_data){prev_pipe, next_pipe, data->cmd_start};
			handle_child_process(data->args, data->shell, pipefd, pipe_data);
		}
		handle_parent_pipes(&prev_pipe, pipefd);
		data->cmd_start = next_pipe + 1;
	}
}

int	execute_pipeline(char **args, t_shell *shell, int cmd_start, int cmd_end)
{
	pid_t			pid;
	t_pipeline_data	data;

	data.args = args;
	data.shell = shell;
	data.cmd_start = cmd_start;
	data.cmd_end = cmd_end;
	data.pid = &pid;
	execute_pipeline_loop(&data);
	return (wait_for_children(pid));
}
