/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 21:41:16 by rgedeon           #+#    #+#             */
/*   Updated: 2025/01/17 00:11:48 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_var_len(const char *str)
{
	char	*equal_sign;
	size_t	var_len;

	equal_sign = ft_strchr(str, '=');
	if (equal_sign)
		var_len = equal_sign - str;
	else
		var_len = ft_strlen(str);
	return (var_len);
}

int	ft_setenv(char *name, const char *value, t_env *envp)
{
	char	*new_env;
	char	*temp;
	t_env	*current;
	size_t	len;

	temp = ft_strjoin(name, "=");
	if (!temp)
		return (1);
	new_env = ft_strjoin(temp, value);
	free(temp);
	if (!new_env)
		return (1);
    current = envp;
	while (current)
	{
		len = get_var_len(current->env_value);
		if (ft_strlen(name) == len && ft_strncmp(current->env_value, name, len) == 0)
		{
			free(current->env_value);
			current->env_value = new_env;
			return (0);
		}
		current = current->next;
	}
	return (free(new_env), 1);
}

int	is_builtin(char *cmd)
{
	return (ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0);
}
