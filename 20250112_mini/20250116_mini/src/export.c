/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 02:05:39 by rgedeon           #+#    #+#             */
/*   Updated: 2025/01/17 01:28:43 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inval_ident(char *argv)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	env_check(char *var, t_env *envp_list)
{
	if (!var || !envp_list)
		return (free_envp(envp_list), 1);
	if (is_valid_identifier(var) == 1)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd((char *)var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	if (modify_value(var, envp_list) != 0)
	{
		if (append_node(envp_list, var) != NULL)
		{
			ft_putstr_fd("minishell: export: Memory allocation error\n", 2);
			return (free_envp(envp_list), 1);
		}
	}
	return (0);
}

static int	process_export_arg(char *arg, t_env *envp_list)
{
	if (!is_valid_identifier(arg))
	{
		if (env_check(arg, envp_list) != 0)
			return (free_envp(envp_list), 1);
	}
	else
	{
		inval_ident(arg);
		return (free_envp(envp_list), 1);
	}
	return (0);
}

int	ft_export(int argc, char **argv, t_env *envp_list)
{
	int	i;
	int	ret;

	ret = 0;
	if (argc == 1)
		return (print_export(envp_list), 0);
	i = 1;
	while (i < argc)
	{
		if (process_export_arg(argv[i], envp_list))
			ret = 1;
		i++;
	}
	return (ret);
}
