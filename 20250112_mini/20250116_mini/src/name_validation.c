/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_validation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 22:08:11 by rgedeon           #+#    #+#             */
/*   Updated: 2024/09/21 22:08:24 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

int	ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else if (c >= '0' && c <= '9')
		return (2);
	else
		return (0);
}

int	is_valid_identifier(const char *str)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (1);
	str++;
	while (*str && *str != '=')
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (1);
		str++;
	}
	return (0);
}
