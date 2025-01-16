/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_cont.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 02:05:39 by rgedeon           #+#    #+#             */
/*   Updated: 2025/01/14 21:24:15 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inval_ident(char *argv)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

int	env_check(const char *var, t_shell *shell)
{
	if (!var || !shell)
		return (free_args(shell->env), 1);
	if (is_valid_identifier(var) == 1)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd((char *)var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	if (modify_value(var, shell->env) != 0)
	{
		if (add_to_env(var, &shell->env) != 0)
		{
			ft_putstr_fd("minishell: export: Memory allocation error\n", 2);
			return (free_args(shell->env), 1);
		}
	}
	return (0);
}

static int	process_export_arg(char *arg, t_shell *shell)
{
	if (!is_valid_identifier(arg))
	{
		if (env_check(arg, shell) != 0)
			return (free_args(shell->env), 1);
	}
	else
	{
		inval_ident(arg);
		return (free_args(shell->env), 1);
	}
	return (0);
}

int	ft_export(int argc, char **argv, t_shell *shell)
{
	int	i;
	int	ret;

	ret = 0;
	if (argc == 1)
		return (print_export(shell->env), 0);
	i = 1;
	while (i < argc)
	{
		if (process_export_arg(argv[i], shell))
			ret = 1;
		i++;
	}
	return (ret);
}
