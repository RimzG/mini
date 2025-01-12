/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:02:22 by sel-huss          #+#    #+#             */
/*   Updated: 2025/01/04 22:20:51 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_heredoc(const char *delimiter)
{
	char	*line;
	int		pipe_fd[2];

	setup_heredoc_signals();
	if (pipe(pipe_fd) == -1)
		return (perror("minishell"), 1);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(pipe_fd[1], line, ft_strlen(line));
		write(pipe_fd[1], "\n", 1);
		free(line);
	}
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) == -1)
	{
		perror("minishell");
		return (close(pipe_fd[0]), 1);
	}
	return (close(pipe_fd[0]), 0);
}
