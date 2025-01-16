/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 01:56:28 by sel-huss          #+#    #+#             */
/*   Updated: 2024/09/21 01:02:25 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{	
	size_t				i;
	unsigned char		*a;
	unsigned const char	*b;

	i = 0;
	a = (unsigned char *)dest;
	b = (unsigned const char *)src;
	while (i < n)
	{
		a[i] = b[i];
		i++;
	}
	return (dest);
}

int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i] != '\0')
			{
				i++;
			}
		}
		else
			i++;
	}
	return (count);
}

char	**create_arr(const char *s, char c, char **result, int *w)
{
	int	i;
	int	start;
	int	length;

	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			start = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			length = i - start;
			result[*w] = (char *)malloc((length + 1) * sizeof(char));
			if (result[*w] == NULL)
				return (NULL);
			ft_memcpy(result[*w], &s[start], length);
			result[*w][length] = '\0';
			(*w)++;
		}
	}
	return (result);
}

char	**ft_split(char const *s, char c)
{
	int		w;
	int		word_count;
	char	**result;

	w = 0;
	word_count = count_words(s, c);
	result = (char **)malloc((word_count + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	result = create_arr(s, c, result, &w);
	result[word_count] = NULL;
	return (result);
}
