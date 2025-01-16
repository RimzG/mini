/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 19:50:15 by sel-huss          #+#    #+#             */
/*   Updated: 2025/01/14 22:39:01 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	if (!s1 || !s2)
		return (NULL);
	result = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (result);
}

int	handle_quotes_state(char **input, int *in_quotes, char *quote_type)
{
	if ((**input == '"' || **input == '\'') && !*in_quotes)
	{
		*in_quotes = 1;
		*quote_type = **input;
		(*input)++;
		return (1);
	}
	if (*in_quotes && **input == *quote_type)
	{
		*in_quotes = 0;
		*quote_type = 0;
		(*input)++;
		return (1);
	}
	return (0);
}

char	*process_token(char **input, t_shell *shell)
{
	char	*result;
	char	*temp;
	int		in_quotes;
	char	quote_type;

	result = ft_strdup("");
	in_quotes = 0;
	quote_type = 0;
	while (**input)
	{
		if (!in_quotes && shell->input_start != *input && (is_whitespace(**input)
				|| is_special_char(**input, *(*input - 1))))
			break ;
		if (handle_quotes_state(input, &in_quotes, &quote_type))
			continue ;
		if (**input == '$' && (!in_quotes || quote_type == '"'))
			temp = handle_env_variable(input, shell);
		else
		{
			temp = ft_substr(*input, 0, 1);
			(*input)++;
		}
		result = join_and_free(result, temp);
	}
	return (result);
}
