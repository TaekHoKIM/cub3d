/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:42:22 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/22 18:28:27 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static size_t	array_count(char const *s, char c);
static char		**copy_str(char **ptr, const char *s, char c);
static size_t	str_len(const char *start, char c);
static void		mem_free(char **ptr, size_t idx);

char	**ft_split(char const *s, char c)
{
	char	**return_ptr;
	size_t	count;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	count = array_count(s, c);
	return_ptr = ft_malloc(sizeof(char *), (count + 1));
	return_ptr[count] = NULL;
	return_ptr = copy_str(return_ptr, s, c);
	return (return_ptr);
}

static size_t	array_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (s[i] != c && s[i] != '\0')
		count++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static char	**copy_str(char **ptr, const char *s, char c)
{
	size_t	i;
	size_t	ptr_i;

	i = 0;
	ptr_i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			ptr[ptr_i] = ft_substr(s, i, str_len(&s[i], c));
			if (ptr[ptr_i] == NULL)
			{
				mem_free(ptr, ptr_i);
				return (NULL);
			}
			ptr_i++;
			i += str_len(&s[i], c);
		}
		else
			i++;
	}
	return (ptr);
}

static size_t	str_len(const char *start, char c)
{
	size_t	i;

	i = 0;
	while (start[i] != '\0')
	{
		if (start[i] == c)
			break ;
		i++;
	}
	return (i);
}

static void	mem_free(char **ptr, size_t idx)
{
	size_t	i;

	i = 0;
	while (i < idx)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}
