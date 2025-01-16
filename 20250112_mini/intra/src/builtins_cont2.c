/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cont2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:11:56 by rgedeon           #+#    #+#             */
/*   Updated: 2025/01/14 21:03:34 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_oldpwd(char **envp)
{
	int		i;
	char	*oldpwd;

	i = 0;
	oldpwd = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "OLDPWD=", 7) == 0)
		{
			oldpwd = envp[i] + 7;
			break ;
		}
		i++;
	}
	if (!oldpwd)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (NULL);
	}
	return (oldpwd);
}

int	handle_cd_dash(char **envp)
{
	char	*oldpwd;
	char	cwd[MAX_PATH];

	oldpwd = get_oldpwd(envp);
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
		update_pwd("PWD", cwd, envp);
	return (0);
}

int	ft_setenv(char *name, const char *value, char **envp)
{
	int		i;
	char	*new_env;
	char	*temp;
	size_t	len;

	i = 0;
	temp = ft_strjoin(name, "=");
	if (!temp)
		return (1);
	new_env = ft_strjoin(temp, value);
	free(temp);
	if (!new_env)
		return (1);
	while (envp[i])
	{
		len = get_var_len(envp[i]);
		if (ft_strlen(name) == len && ft_strncmp(envp[i], name, len) == 0)
		{
			free(envp[i]);
			envp[i] = new_env;
			return (0);
		}
		i++;
	}
	return (free(new_env), 1);
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

void	update_pwd(char *var, char *value, char **envp)
{
	if (ft_setenv(var, value, envp) == 1)
		perror("setenv");
}
