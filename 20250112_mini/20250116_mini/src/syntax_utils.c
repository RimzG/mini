/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 20:02:11 by selim             #+#    #+#             */
/*   Updated: 2025/01/16 23:46:18 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' 
		|| c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

int	check_pipe_syntax(char *input, int i)
{
	int	j;

	j = i + 1;
	while (input[j] && is_whitespace(input[j]))
		j++;
	if (!input[j] || input[j] == '|')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	return (0);
}

int	check_logical_and(char *input, int i)
{
	if (!input)
		return (1);
	if ((input[i] == ':') | (input[i] == '!'))
		return (1);
	if (input[i] == '&')
	{
		if (input[i + 1] == '&')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("syntax error near unexpected token `&&'\n", 2);
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("syntax error near unexpected token `&'\n", 2);
		}
		return (1);
	}
	return (0);
}

int	check_redir_syntax(char *input, int i)
{
	int	j;

	j = i;
	if (input[i + 1] == input[i])
		j++;
	j++;
	while (input[j] && is_whitespace(input[j]))
		j++;
	if (!input[j] || input[j] == '<' || input[j] == '>' || input[j] == '|')
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd("syntax error near unexpected token `", 2);
		ft_putchar_fd(input[j], 2);
		ft_putstr_fd("'\n", 2);
		return (1);
	}
	return (0);
}

int	check_redirections(char *input, int i)
{
	if ((input[i] == '<' || input[i] == '>')
		&& !(i > 0 && (input[i - 1] == '/' || input[i - 1] == '.'))
		&& check_redir_syntax(input, i))
		return (1);
	return (0);
}
