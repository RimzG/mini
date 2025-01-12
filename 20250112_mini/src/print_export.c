/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-huss <sel-huss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 22:09:21 by sel-huss          #+#    #+#             */
/*   Updated: 2024/12/12 15:30:50 by sel-huss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_envsize(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return (0);
	while (envp[i] != NULL)
		i++;
	return (i);
}

void	swap_env_entries(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_env_inner(char **envp, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size - 1)
	{
		j = 0;
		while (j < size - i - 1)
		{
			if (ft_strcmp(envp[j], envp[j + 1]) > 0)
				swap_env_entries(&envp[j], &envp[j + 1]);
			j++;
		}
		i++;
	}
}

void	sort_env(char **envp)
{
	int	size;

	if (!envp)
		return ;
	size = ft_envsize(envp);
	sort_env_inner(envp, size);
}

char	**copy_env(char **envp)
{
	int		i;
	char	**envp_copy;
	int		size;

	i = 0;
	size = ft_envsize(envp);
	envp_copy = (char **)malloc(sizeof(char *) * (size + 1));
	if (!envp_copy)
		return (NULL);
	while (i < size)
	{
		envp_copy[i] = ft_strdup(envp[i]);
		if (!envp_copy[i])
		{
			while (i > 0)
				free(envp_copy[--i]);
			free(envp_copy);
			return (NULL);
		}
		i++;
	}
	envp_copy[size] = NULL;
	return (envp_copy);
}
