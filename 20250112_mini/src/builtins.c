/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-huss <sel-huss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:42:59 by sel-huss          #+#    #+#             */
/*   Updated: 2024/11/06 18:02:22 by sel-huss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_check(const char *input, char qtype)
{
	int	i;
	int	quote;

	i = 0;
	quote = 1;
	while (input[i] != '\0')
	{
		if (input[i] == qtype)
			quote = -quote;
		i++;
	}
	if (quote == 1)
		return (1);
	else
		return (0);
}

char	*remove_quotess(const char *str, char quote_type)
{
	static char	buf[MAX_TOKEN_SIZE];
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != quote_type || quote_check(str, quote_type) == 0)
			buf[j++] = str[i];
		i++;
	}
	buf[j] = '\0';
	return (buf);
}

char	*prepare_env_string(const char *name, const char *value)
{
	size_t	name_len;
	size_t	value_len;
	char	*env_str;

	if (name == NULL || value == NULL)
		return (NULL);
	name_len = ft_strlen(name);
	if (ft_strchr(name, '=') != NULL)
		return (NULL);
	value_len = ft_strlen(value);
	env_str = malloc(name_len + value_len + 2);
	if (env_str == NULL)
		return (NULL);
	ft_strcpy(env_str, name);
	env_str[name_len] = '=';
	ft_strcpy(env_str + name_len + 1, value);
	return (env_str);
}

void	update_pwd(char *var, char *value, char **envp)
{
	if (ft_setenv(var, value, envp) == 1)
		perror("setenv");
}

int	check_n(char *arg)
{
	int	i;

	i = 2;
	if (!arg || arg[0] != '-')
		return (0);
	if (arg[1] != 'n')
		return (0);
	while (arg[i] == 'n')
		i++;
	return (arg[i] == '\0');
}

void	ft_echo(char **args, char **envp)
{
	int		i;
	int		newline;
	char	*arg;

	(void)envp;
	i = 1;
	newline = 1;
	while (args[1] && check_n(args[i]))
	{
		newline = 0;
		i++;
	}
	while (args[i])
	{
		arg = args[i];
		ft_putstr_fd(arg, STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
