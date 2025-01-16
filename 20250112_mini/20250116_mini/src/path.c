/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:11:52 by rgedeon           #+#    #+#             */
/*   Updated: 2025/01/17 00:49:31 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dir_change(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

static char	*get_oldpwd(t_env *env_list)
{
	int		i;
	char	*oldpwd;

	i = 0;
	oldpwd = NULL;
	while (env_list)
	{
		if (ft_strncmp(env_list, "OLDPWD=", 7) == 0)
		{
			oldpwd = env_list + 7;
			break ;
		}
		env_list = env_list->next;
	}
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (NULL);
	}
	return (oldpwd);
}

void	update_pwd(char *var, char *value, t_env *env_list)
{
	if (ft_setenv(var, value, env_list) == 1)
		perror("setenv");
}

int	handle_cd_dash(t_env *env_list)
{
	char	*oldpwd;
	char	cwd[MAX_PATH];

	oldpwd = get_oldpwd(env_list);
	if (!oldpwd)
		return (1);
	if (chdir(oldpwd) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	printf("%s\n", oldpwd);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd");
	else
		update_pwd("PWD", cwd, env_list);
	return (0);
}

char	*get_env_value(char *var_name, t_env *env_list)
{
	t_env	*current;
	size_t	len;

	if (!var_name || !env_list)
		return (NULL);
	current = env_list;
	len = ft_strlen(var_name);
	while (current)
	{
		if (ft_strncmp(current->env_value, var_name, len) == 0 && 
			current->env_value[len] == '=')
			return (current->env_value + len + 1);
		current = current->next;
	}
	return (NULL);
}

int	ft_cd(char **args, t_env *env_list)
{
	char	cwd[MAX_PATH];
	char	*path;

	if (args[1] && args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		path = get_env_value("HOME", env_list);
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	}
	else if (ft_strcmp(args[1], "-") == 0)
		return (handle_cd_dash(env_list));
	else
		path = args[1];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror("minishell: cd"), 1);
	if (chdir(path) != 0)
		return (dir_change(path), 1);
	update_pwd("OLDPWD", cwd, env_list);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		update_pwd("PWD", cwd, env_list);
	return (0);
}

int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		perror("minishell: pwd");
		return (1);
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

// char	*s(char *str)
// {
// 	static char	buf[MAX_TOKEN_SIZE];
// 	int			i;
// 	int			j;
// 	char		quote;

// 	i = 0;
// 	j = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' || str[i] == '"')
// 		{
// 			quote = str[i++];
// 			while (str[i] && str[i] != quote)
// 				buf[j++] = str[i++];
// 			if (str[i])
// 				i++;
// 		}
// 		else
// 			buf[j++] = str[i++];
// 	}
// 	buf[j] = '\0';
// 	return (buf);
// }

int	ft_exit(char **args)
{
	char		*arg;
	long long	exit_code;
	int			i;

	if (!args[1])
		exit(0);
	arg = args[1];
	if (args[2])
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2), 1);
	i = 0;
	while (arg[i])
	{
		if ((i == 0 && (arg[i] == '+' || arg[i] == '-'))
			|| (arg[i] >= '0' && arg[i] <= '9'))
		{
			i++;
			continue ;
		}
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit (2);
	}
	exit_code = ft_atoi(arg);
	return (printf("exit\n"), exit((unsigned char)exit_code), 0);
}



void	execute_path(char **env, char **cmd_args)
{
	char	*cmd_path;

	cmd_path = find_command_path(cmd_args[0], env);
	if (!cmd_path)
	{
		free_args(cmd_args);
		exit(127);
	}
	execve(cmd_path, cmd_args, env);
	free(cmd_path);
	exit(127);
}
