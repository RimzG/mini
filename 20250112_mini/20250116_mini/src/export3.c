/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:31:21 by sel-huss          #+#    #+#             */
/*   Updated: 2025/01/17 01:09:46 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_entry(char *entry)
{
	char	*equal_sign;

	equal_sign = ft_strchr(entry, '=');
	if (equal_sign != NULL)
	{
		if (ft_strncmp(entry, "_", equal_sign - entry) != 0)
		{
			printf("declare -x %.*s=\"%s\"\n",
				(int)(equal_sign - entry),
				entry, equal_sign + 1);
		}
	}
	else if (ft_strncmp(entry, "_", ft_strlen(entry)) != 0)
		printf("declare -x %s\n", entry);
}

int	count_envp(t_env *envp_list)
{
	int		count;
	t_env	*current;

	count = 0;
	current = envp_list;
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

char	**envp_to_args(t_env *envp_list)
{
	char	**args;
	int		count;

	if (!envp_list)
		return (NULL);
	count = count_envp(envp_list);	
	args = allocate_args(count);
	if (!args)
		return (NULL);
	if (!copy_token_values(args, envp_list))
	{
		free_args(args);
		free_envp(envp_list);
		return (NULL);
	}
	return (args);
}

void	print_export(t_env *envp_list)
{
	int		i;
	char	**envp_copy;

	envp_copy = envp_to_args(envp_list);
	if (!envp_copy)
		return ;
	sort_env(envp_copy);
	while (envp_list)
	{
		print_env_entry(envp_copy[i]);
		envp_list = envp_list->next;
	}
	free_args(envp_copy);
}
