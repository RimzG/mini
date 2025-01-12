/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-huss <sel-huss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:25:50 by sel-huss          #+#    #+#             */
/*   Updated: 2024/12/28 00:43:22 by sel-huss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_redirection(char **args, int start)
{
	int	i;

	i = start;
	while (args[i + 2])
	{
		args[i] = args[i + 2];
		i++;
	}
	args[i] = NULL;
	args[i + 1] = NULL;
}

int	handle_input_redirection(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)file, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	handle_output_redirection(const char *file, int append)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (!append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(file, flags, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd((char *)file, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

void	restore_io(int saved_stdin, int saved_stdout)
{
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, STDIN_FILENO);
		close(saved_stdin);
	}
	if (saved_stdout != -1)
	{
		dup2(saved_stdout, STDOUT_FILENO);
		close(saved_stdout);
	}
}

int	remove_redirec_set(char **args, int i)
{
	remove_redirection(args, i);
	return (-1);
}
