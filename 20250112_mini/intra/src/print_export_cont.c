/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export_cont.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:31:21 by sel-huss          #+#    #+#             */
/*   Updated: 2025/01/14 21:30:09 by rgedeon          ###   ########.fr       */
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

void	print_export(char **envp)
{
	int		i;
	char	**envp_copy;

	envp_copy = copy_env(envp);
	if (!envp_copy)
		return ;
	sort_env(envp_copy);
	i = 0;
	while (envp_copy[i] != NULL)
	{
		print_env_entry(envp_copy[i]);
		i++;
	}
	free_args(envp_copy);
}
