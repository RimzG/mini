/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 19:50:29 by sel-huss          #+#    #+#             */
/*   Updated: 2025/01/17 00:57:42 by rgedeon          ###   ########.fr       */
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

char	**get_path(char **env)
{
	int		i;
	char	**paths;
	char	*path_str;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path_str = env[i] + 5;
			paths = ft_split(path_str, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

char	*build_path(char *base_path, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(base_path, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	return (full_path);
}

char	*search_in_paths(char **paths, char *cmd)
{
	char	*full_path;
	int		i;

	i = 0;
	while (paths && paths[i])
	{
		full_path = build_path(paths[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

int	execute_external(char **args, t_env *envp_list)
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
		cmd_path = find_command_path(args[0], envp_list);
	if (!cmd_path)
		return (unfound_command(args), 127);
	if (access(cmd_path, X_OK) == -1)
		return (permission_check(args, cmd_path), 126);
	return (execute_cmd(args, envp_list, cmd_path));
}

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

