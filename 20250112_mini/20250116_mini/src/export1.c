/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:54:05 by rgedeon           #+#    #+#             */
/*   Updated: 2025/01/17 01:31:32 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_env_entries(char **new_env, char **envp, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			return (free(new_env), 1);
		}
		i++;
	}
	return (0);
}

int	add_new_entry(char **new_env, const char *var, int size)
{
	new_env[size] = ft_strdup(var);
	if (!new_env[size])
		return (1);
	new_env[size + 1] = NULL;
	return (0);
}

int	add_to_env(const char *var, char ***envp)
{
	int		size;
	char	**new_env;

	if (!var || !envp || !*envp)
		return (1);
	size = 0;
	while ((*envp)[size])
		size++;
	new_env = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_env)
		return (1);
	if (copy_env_entries(new_env, *envp, size))
		return (1);
	if (add_new_entry(new_env, var, size))
		return (free_args(new_env), 1);
	free_args(*envp);
	*envp = new_env;
	return (0);
}

int	update_existing_var(const char *var, t_env *envp_list, int i)
{
	char	*new_env;

	if (ft_strchr(var, '=') == NULL)
		return (0);
	new_env = ft_strdup(var);
	if (!new_env)
		return (1);
	envp_list = new_env;
	return (0);
}

int	modify_value(const char *var, t_env *envp_list)
{
	int		i;
	size_t	var_len;
	size_t	var_len_env;

	if (!var || !envp_list)
		return (1);
	var_len = get_var_len(var);
	i = 0;
	while (envp_list)
	{
		var_len_env = get_var_len(envp_list);
		if (var_len == var_len_env && ft_strncmp(envp_list, var, var_len) == 0)
			return (update_existing_var(var, envp_list, i));
		envp_list = envp_list->next;
	}
	return (1);
}