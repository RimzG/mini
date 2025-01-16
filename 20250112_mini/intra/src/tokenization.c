/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-huss <sel-huss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:30:32 by sel-huss          #+#    #+#             */
/*   Updated: 2024/11/27 21:15:50 by sel-huss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	check_type(const char *value)
{
	if (!value)
		return (TOKEN_WORD);
	if (ft_strcmp(value, "|") == 0)
		return (TOKEN_PIPE);
	if (ft_strcmp(value, "<") == 0)
		return (TOKEN_REDIR_IN);
	if (ft_strcmp(value, ">") == 0)
		return (TOKEN_REDIR_OUT);
	if (ft_strcmp(value, ">>") == 0)
		return (TOKEN_REDIR_APPEND);
	if (ft_strcmp(value, "<<") == 0)
		return (TOKEN_REDIR_HEREDOC);
	return (TOKEN_WORD);
}

t_token	*create_token(const char *value)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = ft_strdup(value);
	if (!new_token->value)
	{
		free(new_token);
		return (NULL);
	}
	new_token->type = check_type(value);
	new_token->next = NULL;
	return (new_token);
}

void	add_token(t_token **start, t_token *new_token)
{
	t_token	*temp;

	if (!start || !new_token)
		return ;
	if (*start == NULL)
	{
		*start = new_token;
		return ;
	}
	temp = *start;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_token;
}

t_token	*tokenize_input(char *input, t_shell *shell)
{
	t_token	*start;
	t_token	*new_token;
	char	*token_str;
	char	*working_input;

	if (!input)
		return (NULL);
	start = NULL;
	working_input = input;
	while (*working_input)
	{
		token_str = get_next_token(&working_input, shell);
		if (!token_str)
			continue ;
		new_token = create_token(token_str);
		free(token_str);
		if (!new_token)
		{
			free_tokens(start);
			return (NULL);
		}
		add_token(&start, new_token);
	}
	return (start);
}
