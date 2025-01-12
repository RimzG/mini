/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-huss <sel-huss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 10:00:00 by sel-huss          #+#    #+#             */
/*   Updated: 2024/12/17 10:00:00 by sel-huss         ###   ########.fr       */
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

char	*find_command_path(char *cmd, char **env)
{
	char	**paths;
	char	*full_path;

	if (!cmd)
		return (NULL);
	full_path = try_direct_path(cmd);
	if (full_path)
		return (full_path);
	if (!env)
		return (try_current_dir(cmd));
	paths = get_path(env);
	if (!paths)
		return (try_current_dir(cmd));
	full_path = search_in_paths(paths, cmd);
	free_args(paths);
	return (full_path);
}
