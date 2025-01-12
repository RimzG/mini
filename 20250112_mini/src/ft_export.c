/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:54:05 by rgedeon           #+#    #+#             */
/*   Updated: 2024/10/30 19:57:31 by rgedeon          ###   ########.fr       */
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

static int	update_existing_var(const char *var, char **envp, int i)
{
	char	*new_env;

	if (ft_strchr(var, '=') == NULL)
		return (0);
	new_env = ft_strdup(var);
	if (!new_env)
		return (1);
	free(envp[i]);
	envp[i] = new_env;
	return (0);
}

int	modify_value(const char *var, char **envp)
{
	int		i;
	size_t	var_len;
	size_t	var_len_env;

	if (!var || !envp)
		return (1);
	var_len = get_var_len(var);
	i = 0;
	while (envp[i])
	{
		var_len_env = get_var_len(envp[i]);
		if (var_len == var_len_env && ft_strncmp(envp[i], var, var_len) == 0)
			return (update_existing_var(var, envp, i));
		i++;
	}
	return (1);
}

int	add_to_env(const char *var, char **envp)
{
	int	size;

	if (!var || !envp)
		return (1);
	size = 0;
	while (envp[size])
		size++;
	envp[size] = ft_strdup(var);
	if (!envp[size])
		return (1);
	envp[size] = NULL;
	return (0);
}
