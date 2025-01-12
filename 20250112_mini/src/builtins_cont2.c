/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cont2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-huss <sel-huss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 22:11:56 by rgedeon           #+#    #+#             */
/*   Updated: 2024/12/30 22:24:23 by sel-huss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_cd_dash(char **envp)
{
	char	*oldpwd;
	char	cwd[MAX_PATH];

	oldpwd = getenv("OLDPWD");
	if (!oldpwd)
	{
		fprintf(stderr, "minishell: cd: OLDPWD not set\n");
		return (1);
	}
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
	while (envp[i])
	{
		len = get_var_len(envp[i]);
		if (ft_strlen(name) == len && ft_strncmp(envp[i], name, len) == 0)
		{
			temp = ft_strjoin(name, "=");
			if (!temp)
				return (1);
			new_env = ft_strjoin(temp, value);
			free(temp);
			if (!new_env)
				return (1);
			free(envp[i]);
			envp[i] = new_env;
			return (0);
		}
		i++;
	}
	return (1);
}
