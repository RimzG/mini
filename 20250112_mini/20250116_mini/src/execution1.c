/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 22:58:36 by sel-huss          #+#    #+#             */
/*   Updated: 2025/01/17 01:18:19 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**extract_command(char **args, int start, int end)
{
	char	**cmd_args;
	int		i;
	int		j;

	cmd_args = malloc(sizeof(char *) * (end - start + 1));
	if (!cmd_args)
		return (NULL);
	i = start;
	j = 0;
	while (i < end)
	{
		cmd_args[j] = ft_strdup(args[i]);
		if (!cmd_args[j])
		{
			while (--j >= 0)
				free(cmd_args[j]);
			free(cmd_args);
			return (NULL);
		}
		i++;
		j++;
	}
	cmd_args[j] = NULL;
	return (cmd_args);
}

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

void	execute_path(char **env, char **cmd_args)
{
	char	*cmd_path;

	cmd_path = find_command_path(cmd_args[0], env);
	if (!cmd_path)
	{
		free_args(cmd_args);
		exit(127);
	}
	execve(cmd_path, cmd_args, env);
	free(cmd_path);
	exit(127);
}

int	execute_single_command(char **args, t_shell *shell,
		int cmd_start, int *pipefd)
{
	char	**cmd_args;
	pid_t	pid;
	int		next_pipe;

	next_pipe = find_next_command(args, cmd_start, count_args(args));
	cmd_args = extract_command(args, cmd_start, next_pipe);
	if (!cmd_args)
		return (free_envp(shell->envp), -1);
	pid = fork();
	if (pid == -1)
	{
		free_envp(shell->envp);
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
