/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:39:43 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/25 18:12:09 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	max;
	char	*return_ptr;

	if (s == NULL)
		return (NULL);
	max = 0;
	if (ft_strlen(s) <= (size_t)start)
		max = 0;
	else
	{
		while (s[(size_t)start + max] != '\0' && max < len)
			max++;
	}
	return_ptr = ft_malloc(sizeof(char), (max + 1));
	i = 0;
	while (i < max)
	{
		return_ptr[i] = s[(size_t)start + i];
		i++;
	}
	return_ptr[i] = '\0';
	return (return_ptr);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			minus;
	long long	return_value;

	i = 0;
	minus = 1;
	return_value = 0;
	while ((9 <= str[i] && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			minus = -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		return_value *= 10;
		return_value += str[i] - '0';
		i++;
	}
	return ((int)(return_value * (long long)minus));
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (0);
}

void	map_exit_error(char *s)
{
	write(2, "Error\n", 6);
	write(2, s, ft_strlen(s));
	exit(EXIT_FAILURE);
}
