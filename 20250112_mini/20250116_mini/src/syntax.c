/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:54:16 by sel-huss          #+#    #+#             */
/*   Updated: 2025/01/16 23:30:53 by rgedeon          ###   ########.fr       */
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

int	check_syntax(char *input, int *i, int *in_quotes, char *quote_type)
{
	if (!input || !i || !in_quotes || !quote_type)
		return (-1);
	while (input[*i])
	{
		if (!check_quotes_state(input, i, in_quotes, quote_type) && !*in_quotes)
		{
			if (input[*i] == '|' && check_pipe_syntax(input, *i))
				return (1);
			if (check_logical_and(input, *i))
				return (1);
			if (check_redirections(input, *i))
				return (1);
		}
		(*i)++;
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

int	syntax_error(char *input)
{
	int		i;
	int		in_quotes;
	char	quote_type;

	i = 0;
	in_quotes = 0;
	quote_type = 0;
	if (!input)
		return (1);
	while (input[i] && is_whitespace(input[i]))
		i++;
	if (!input[i])
		return (0);
	if (check_initial_pipe(input, i))
		return (1);
	if (check_syntax(input, &i, &in_quotes, &quote_type))
		return (1);
	if (in_quotes)
	{
		ft_putstr_fd("unclosed quotes\n", 2);
		return (1);
	}
	return (0);
}
