/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_next.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 19:50:03 by sel-huss          #+#    #+#             */
/*   Updated: 2025/01/02 18:22:21 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_env_name(char **input, t_shell *shell)
{
	int		len;
	char	*var_name;
	char	*value;
	char	*result;

	len = 0;
	while ((*input)[len] && (ft_isalnum((*input)[len]) || (*input)[len] == '_'))
		len++;
	if (len == 0)
		return (ft_strdup("$"));
	var_name = ft_substr(*input, 0, len);
	if (!var_name)
		return (NULL);
	value = get_env_value(var_name, shell->env);
	free(var_name);
	*input += len;
	if (value)
		result = ft_strdup(value);
	else
		result = ft_strdup("");
	return (result);
}

char	*get_env_value(char *var_name, char **envp)
{
	int		i;
	size_t	len;

	if (!var_name || !envp)
		return (NULL);
	i = 0;
	len = ft_strlen(var_name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	*handle_special_token(char **input)
{
	char	*temp;

	temp = *input;
	(*input)++;
	if (is_special_char(**input, *temp) && **input == *temp)
		(*input)++;
	return (ft_substr(temp, 0, *input - temp));
}

char	*handle_env_variable(char **input, t_shell *shell)
{
	char	*temp;

	if (!*input || !(*input)[0])
		return (ft_strdup("$"));
	(*input)++;
	if (!(*input)[0] || (*input)[0] == ' ' ||
		(*input)[0] == '"' || (*input)[0] == '\'')
		return (ft_strdup("$"));
	if ((*input)[0] == '?')
	{
		temp = ft_itoa(shell->exit_status);
		(*input)++;
		return (temp);
	}
	return (handle_env_name(input, shell));
}

char	*get_next_token(char **input, t_shell *shell)
{
	while (**input && is_whitespace(**input))
		(*input)++;
	if (!**input)
		return (NULL);
	if (shell->input_start != *input && is_special_char(**input, *(*input - 1)))
		return (handle_special_token(input));
	else if (is_special_char(**input, '\0'))
		return (handle_special_token(input));
	return (process_token(input, shell));
}
