/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 01:19:35 by rgedeon           #+#    #+#             */
/*   Updated: 2025/01/17 01:01:41 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *envp)
{
	int		i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strchr(envp[i], '=') != NULL)
			printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

void	invalid_unset(char *argv)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	ft_unset(int argc, char **argv, char **envp)
{
	int	i;
	int	ret;

	ret = 0;
	i = 1;
	if (argc == 1)
		return (0);
	while (i < argc)
	{
		if (!is_valid_identifier(argv[i]))
		{
			if (remove_env(argv[i], envp) != 0)
			{
				ret = 1;
				break ;
			}
		}
		else
		{
			invalid_unset(argv[i]);
			ret = 1;
		}
		i++;
	}
	return (ret);
}
