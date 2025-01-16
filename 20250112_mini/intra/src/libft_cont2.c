/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_cont2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgedeon <rgedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 00:44:36 by rgedeon           #+#    #+#             */
/*   Updated: 2024/12/17 22:02:48 by rgedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strncpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while ((i < size - 1) && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (dst);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = 0;
	while (src[src_len] != '\0')
	{
		src_len++;
	}
	if (size == 0)
	{
		return (src_len);
	}
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	if (size > 0)
	{
		dst[i] = '\0';
	}
	return (src_len);
}

char	*ft_strcpy(char *dest, const char *src)
{
	char	*dest_ptr;

	if (dest == NULL || src == NULL)
		return (NULL);
	dest_ptr = dest;
	while (*src != '\0')
	{
		*dest_ptr = *src;
		dest_ptr++;
		src++;
	}
	*dest_ptr = '\0';
	return (dest);
}

int	int_length(int n)
{
	int	length;

	length = 0;
	if (n == 0)
		return (1);
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		length++;
		n = n * -1;
	}
	while (n > 0)
	{
		n = n / 10;
		length++;
	}
	return (length);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		length;

	length = int_length(n);
	result = (char *)malloc((length + 1) * sizeof(char));
	if (result == NULL)
		return (NULL);
	if (n == -2147483648)
		ft_strlcpy(result, "-2147483648", 12);
	if (n == 0)
		result[0] = '0';
	else if (n < 0)
	{
		result[0] = '-';
		n = n * -1;
	}
	result[length] = '\0';
	while (n > 0)
	{
		result[--length] = (n % 10) + '0';
		n = n / 10;
	}
	return (result);
}
