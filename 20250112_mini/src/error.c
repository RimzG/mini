/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:02:22 by sel-huss          #+#    #+#             */
/*   Updated: 2024/12/12 21:35:36 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_error(const char *cmd, const char *arg, const char *message)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd((char *)cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd((char *)arg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (message)
		ft_putstr_fd((char *)message, 2);
	ft_putchar_fd('\n', 2);
}
