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
