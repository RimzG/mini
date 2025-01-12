/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cont.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-huss <sel-huss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 23:11:52 by rgedeon           #+#    #+#             */
/*   Updated: 2024/12/27 19:30:58 by sel-huss         ###   ########.fr       */
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

int	ft_cd(char **args, char **envp)
{
	char	cwd[MAX_PATH];
	char	*path;

	if (args[1] && args[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (!args[1] || ft_strcmp(args[1], "~") == 0)
	{
		path = getenv("HOME");
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	}
	else if (ft_strcmp(args[1], "-") == 0)
		return (handle_cd_dash(envp));
	else
		path = args[1];
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return (perror("minishell: cd"), 1);
	if (chdir(path) != 0)
		return (dir_change(path), 1);
	update_pwd("OLDPWD", cwd, envp);
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		update_pwd("PWD", cwd, envp);
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

char	*remove_quotes(char *str)
{
	static char	buf[MAX_TOKEN_SIZE];
	int			i;
	int			j;
	char		quote;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				buf[j++] = str[i++];
			if (str[i])
				i++;
		}
		else
			buf[j++] = str[i++];
	}
	buf[j] = '\0';
	return (buf);
}

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
		exit(2);
	}
	exit_code = ft_atoi(arg);
	return (exit((unsigned char)exit_code), 0);
}
