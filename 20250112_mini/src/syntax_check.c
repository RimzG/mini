/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-huss <sel-huss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:48:41 by sel-huss          #+#    #+#             */
/*   Updated: 2024/12/29 22:44:57 by sel-huss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes_state(char *input, int *i,
							int *in_quotes, char *quote_type)
{
	if ((input[*i] == '\'' || input[*i] == '"') && !*in_quotes)
	{
		*in_quotes = 1;
		*quote_type = input[*i];
		return (1);
	}
	else if (*in_quotes && input[*i] == *quote_type)
	{
		*in_quotes = 0;
		*quote_type = 0;
		return (1);
	}
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

int	check_initial_pipe(char *input, int i)
{
	if (!input)
		return (1);
	if (input[i] == '|')
	{
		if (input[i + 1] == '|')
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("syntax error near unexpected token `||'\n", 2);
		}
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		}
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
