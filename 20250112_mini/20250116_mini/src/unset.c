/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 00:11:37 by rgedeon           #+#    #+#             */
/*   Updated: 2024/09/25 00:06:58 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;
	size_t		i;

	d = (char *)dest;
	s = (const char *)src;
	if (s > d)
	{
		i = 0;
		while (i < n)
		{
			d[i] = s[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			d[i - 1] = s[i - 1];
			i--;
		}
	}
	return (dest);
}

char	**env_shift(char **envp, int i)
{
	int	len;
	int	j;

	len = 0;
	if (!envp || i < 0)
		return (NULL);
	while (envp[len])
		len++;
	if (i >= len)
		return (envp);
	free(envp[i]);
	j = i;
	while (j < len - 1)
	{
		envp[j] = envp[j + 1];
		j++;
	}
	envp[len - 1] = NULL;
	return (envp);
}

int	var_search(const char *var, char **envp, int var_len)
{
	int		i;
	char	*equal_sign;
	int		curr_len;

	i = 0;
	if (!var || !envp || var_len <= 0)
		return (-1);
	while (envp[i])
	{
		equal_sign = ft_strchr(envp[i], '=');
		curr_len = (int)ft_strlen(envp[i]);
		if (equal_sign || curr_len == var_len)
		{
			if (ft_strncmp(envp[i], var, var_len) == 0
				&& (envp[i][var_len] == '=' || envp[i][var_len] == '\0'))
				return (i);
		}
		i++;
	}
	return (-1);
}

int	remove_env(const char *var, char **envp)
{
	int		i;
	int		var_len;

	if (!var || !envp)
		return (1);
	var_len = (int)ft_strlen(var);
	i = var_search(var, envp, var_len);
	if (i == -1)
		return (0);
	env_shift(envp, i);
	return (0);
}
