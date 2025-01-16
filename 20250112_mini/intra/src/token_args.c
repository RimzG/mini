/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:30:32 by sel-huss          #+#    #+#             */
/*   Updated: 2025/01/14 22:39:53 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

char	**allocate_args(int count)
{
	char	**args;
	int		i;

	args = (char **)malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (i <= count)
	{
		args[i] = NULL;
		i++;
	}
	return (args);
}

int	copy_token_values(char **args, t_token *tokens)
{
	int		i;
	t_token	*current;

	current = tokens;
	i = 0;
	while (current)
	{
		if (current->value == NULL)
			return (0);
		args[i] = ft_strdup(current->value);
		if (!args[i])
			return (0);
		current = current->next;
		i++;
	}
	args[i] = NULL;
	return (1);
}

char	**tokens_to_args(t_token *tokens)
{
	char	**args;
	int		count;

	if (!tokens)
		return (NULL);
	count = count_tokens(tokens);
	args = allocate_args(count);
	if (!args)
		return (NULL);
	if (!copy_token_values(args, tokens))
	{
		free_args(args);
		free_tokens(tokens);
		return (NULL);
	}
	return (args);
}
