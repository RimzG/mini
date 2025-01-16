/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:00:00 by sel-huss          #+#    #+#             */
/*   Updated: 2025/01/17 01:20:02 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

char	*try_direct_path(char *cmd)
{
	if (!cmd || ft_strlen(cmd) == 0)
		return (NULL);
	if (cmd[0] == '/' || (cmd[0] == '.' && cmd[1] == '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
	}
	return (NULL);
}

char	*try_current_dir(char *cmd)
{
	if (!cmd)
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	return (NULL);
}
