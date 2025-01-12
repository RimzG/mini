/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check_cont.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-huss <sel-huss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:54:16 by sel-huss          #+#    #+#             */
/*   Updated: 2024/12/27 19:39:09 by sel-huss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirections(char *input, int i)
{
	if ((input[i] == '<' || input[i] == '>')
		&& !(i > 0 && (input[i - 1] == '/' || input[i - 1] == '.'))
		&& check_redir_syntax(input, i))
		return (1);
	return (0);
}

int	parse_input(char *input, int *i, int *in_quotes, char *quote_type)
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

int	syntax_check(char *input)
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
	if (parse_input(input, &i, &in_quotes, &quote_type))
		return (1);
	if (in_quotes)
	{
		ft_putstr_fd("unclosed quotes\n", 2);
		return (1);
	}
	return (0);
}
