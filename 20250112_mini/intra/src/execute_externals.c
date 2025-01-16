/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_externals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-huss <sel-huss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 19:50:29 by sel-huss          #+#    #+#             */
/*   Updated: 2024/12/30 22:11:03 by sel-huss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inexistant_file(char **args)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	error_is_directory(char **args)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": Is a directory\n", 2);
}

void	unfound_command(char **args)
{
	ft_putstr_fd(args[0], 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	permission_check(char **args, char *cmd_path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(args[0], 2);
	if (access(cmd_path, F_OK) == -1)
		ft_putstr_fd(": No such file or directory\n", 2);
	else
		ft_putstr_fd(": Permission denied\n", 2);
	free(cmd_path);
}

int	execute_external(char **args, char **env)
{
	char	*cmd_path;

	if (!args || !args[0])
		return (1);
	if (args[0][0] == '$')
		return (unfound_command(args), 127);
	if (args[0][0] == '/' || (args[0][0] == '.' && args[0][1] == '/'))
	{
		if (access(args[0], F_OK) == -1)
			return (inexistant_file(args), 127);
		if (is_directory(args[0]))
			return (error_is_directory(args), 126);
		cmd_path = ft_strdup(args[0]);
	}
	else
		cmd_path = find_command_path(args[0], env);
	if (!cmd_path)
		return (unfound_command(args), 127);
	if (access(cmd_path, X_OK) == -1)
		return (permission_check(args, cmd_path), 126);
	return (execute_cmd(args, env, cmd_path));
}
