/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-huss <sel-huss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:02:22 by rgedeon           #+#    #+#             */
/*   Updated: 2024/12/12 20:16:50 by sel-huss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_env_safe(char **envp)
{
	int		i;
	char	**new_env;
	int		size;

	if (!envp)
		return (NULL);
	size = 0;
	while (envp[size])
		size++;
	new_env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			while (--i >= 0)
				free(new_env[i]);
			return (free(new_env), NULL);
		}
		i++;
	}
	return (new_env[size] = NULL, new_env);
}

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
