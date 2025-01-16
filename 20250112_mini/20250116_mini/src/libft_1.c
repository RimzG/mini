/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_cont.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 22:07:13 by rgedeon           #+#    #+#             */
/*   Updated: 2024/09/25 23:52:11 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s)
{
	char	*s1;
	char	*ptr;
	size_t	len;

	len = ft_strlen(s);
	s1 = (char *)malloc((len + 1) * sizeof(char));
	if (s1 == NULL)
		return (NULL);
	ptr = s1;
	while (*s != '\0')
	{
		*ptr = *s;
		ptr++;
		s++;
	}
	*ptr = '\0';
	return (s1);
}

char	*ft_strndup(const char *s, int n)
{
	char	*s1;
	char	*ptr;

	s1 = (char *)malloc((n + 1) * sizeof(char));
	if (s1 == NULL)
		return (NULL);
	ptr = s1;
	while (*s != '\0' && n >= 0)
	{
		*ptr = *s;
		ptr++;
		s++;
		n--;
	}
	*ptr = '\0';
	return (s1);
}

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;
	size_t	j;

	j = 0;
	i = 0;
	while (s[i] != '\0')
		i++;
	if (start >= i)
		return (ft_strdup(""));
	if (len > i - start)
		len = i - start;
	sub = (char *)malloc((len + 1) * (sizeof(char)));
	if (sub == NULL)
		return (NULL);
	while (len != 0 && s[start] != '\0')
	{
		sub[j] = s[start];
		start++;
		j++;
		len--;
	}
	sub[j] = '\0';
	return (sub);
}
