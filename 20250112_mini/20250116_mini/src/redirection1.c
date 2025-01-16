/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_cont.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 21:06:50 by rgedeon           #+#    #+#             */
/*   Updated: 2025/01/13 22:50:07 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*not_heredoc_quotes(char **args, int *i)
{
	char	*expanded_file;

	expanded_file = NULL;
	if ((ft_strcmp(args[*i], "<") == 0 || ft_strcmp(args[*i], ">") == 0
			|| ft_strcmp(args[*i], ">>") == 0) && args[*i + 1])
		expanded_file = remove_quotes(args[*i + 1]);
	return (expanded_file);
}

int	*remove_redir(char **args, int *i)
{
	if ((ft_strcmp(args[*i], "<") == 0 || ft_strcmp(args[*i], ">") == 0
			|| ft_strcmp(args[*i], ">>") == 0 || ft_strcmp(args[*i], "<<") == 0)
		&& args[*i + 1])
		*i = remove_redirec_set(args, *i);
	return (i);
}

int	handle_specific_redirection(char **args, int *i, int *status)
{
	char	*expanded_file;

	expanded_file = not_heredoc_quotes(args, i);
	if (ft_strcmp(args[*i], "<") == 0 && args[*i + 1])
	{
		if (handle_input_redirection(expanded_file) != 0)
			return (*status = 1, -1);
	}
	else if (ft_strcmp(args[*i], ">>") == 0 && args[*i + 1])
	{
		if (handle_output_redirection(expanded_file, 0) != 0)
			return (*status = 1, -1);
	}
	else if (ft_strcmp(args[*i], ">") == 0 && args[*i + 1])
	{
		if (handle_output_redirection(expanded_file, 1) != 0)
			return (*status = 1, -1);
	}
	else if (ft_strcmp(args[*i], "<<") == 0 && args[*i + 1])
	{
		if (handle_heredoc(args[*i + 1]) != 0)
			return (*status = 1, -1);
	}
	i = remove_redir(args, i);
	return (0);
}

int	is_valid_redirection_token(char **args, int i)
{
	return ((args[i][0] == '<' || args[i][0] == '>')
			&& (i == 0 || (args[i - 1][strlen(args[i - 1]) - 1] != '.'
			&& args[i - 1][strlen(args[i - 1]) - 1] != '/')));
}

int	handle_command_redirections(char **args)
{
	int	i;
	int	status;
	int	saved_stdin;
	int	saved_stdout;

	i = 0;
	status = 0;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	while (args[i])
	{
		if (is_valid_redirection_token(args, i))
		{
			if (handle_specific_redirection(args, &i, &status) != 0)
				break ;
		}
		if (i < 0)
			i = 0;
		else
			i++;
	}
	if (status != 0 || !args[0])
		restore_io(saved_stdin, saved_stdout);
	return (status);
}
