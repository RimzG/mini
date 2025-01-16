/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 23:35:37 by rgedeon           #+#    #+#             */
/*   Updated: 2025/01/17 00:14:09 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_quotes(char *str)
{
    int i;
    int j;
    int in_quotes;
    char quote_type;

    i = 0;
    j = 0;
    in_quotes = 0;
    quote_type = 0;

    while (str[i])
    {
        if ((str[i] == '"' || str[i] == '\'') && (!in_quotes || quote_type == str[i]))
        {
            if (in_quotes)
                quote_type = 0;
            else
                quote_type = str[i];
            in_quotes = !in_quotes;
            i++;
        }
        else
            str[j++] = str[i++];
    }
    str[j] = '\0';
}

int	count_input_args(char *input)
{
	int		arg_count;
	char	*start;
	int     in_quotes;

	if (!input)
		return (0);
	arg_count = 0;
	start = input;
	while (*start)
	{
		while (*start && is_whitespace(*start))
			start++;
		if (!*start)
			break;
		arg_count++;
        in_quotes = 0;
		while (*start && (in_quotes || !is_whitespace(*start)))
		{
			if (*start == '"' || *start == '\'')
				in_quotes = !in_quotes;
			start++;
		}
	}
	return (arg_count);
}

char	**get_args(char *input)
{
    char    **args;
    char    *start;
    char    *end;
    int     arg_count;
    int     i;
    int     in_quotes;

	if (!input)
		return (NULL);
	arg_count = count_input_args(input);
    args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
    i = 0;
    start = input;
	while (*start && i < arg_count)
    {
        while (*start && is_whitespace(*start))
            start++;
        end = start;
        in_quotes = 0;
        while (*end && (in_quotes || !is_whitespace(*end)))
        {
            if (*end == '"' || *end == '\'')
                in_quotes = !in_quotes;
            end++;
        }
        args[i] = ft_strndup(start, end - start);
        if (!args[i])
            return (free_args(args), NULL);
        remove_quotes(args[i]);
        i++;
        start = end;
    }
    args[i] = NULL;
    return (args);
}




