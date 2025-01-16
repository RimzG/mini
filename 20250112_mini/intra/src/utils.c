/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selim <selim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 20:02:11 by selim             #+#    #+#             */
/*   Updated: 2024/11/06 20:02:11 by selim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

int	is_special_char(char c, char prev_char)
{
	if ((c == '|' || c == '<' || c == '>')
		&& (prev_char != '.' && prev_char != '/'))
		return (1);
	return (0);
}

void	free_single_token(t_token *token)
{
	if (!token)
		return ;
	free(token->value);
	free(token);
}

void free_tokens(t_token *tokens)
{
    t_token *current;
    t_token *next;

    current = tokens;
    while (current)
    {
        next = current->next;
        free(current);  // Free each token
        current = next;
    }
}
