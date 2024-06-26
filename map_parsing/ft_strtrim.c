/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:58:13 by taekhkim          #+#    #+#             */
/*   Updated: 2024/06/26 16:56:29 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static char	*null_check(char const *s1);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	count;
	size_t	start;
	size_t	i;

	count = 0;
	start = 0;
	if (s1 == NULL || set == NULL)
		return (null_check(s1));
	while (ft_strchr(set, s1[start]) != NULL && s1[start] != '\0')
	{
		count++;
		start++;
	}
	i = ft_strlen(s1);
	if (i != 0 && i != start)
	{
		i--;
		while (ft_strchr(set, s1[i]) != NULL && i > start)
		{
			count++;
			i--;
		}
	}
	return (ft_substr(s1, start, ft_strlen(s1) - count));
}

static char	*null_check(char const *s1)
{
	if (s1 == NULL)
		return (NULL);
	return (ft_substr(s1, 0, ft_strlen(s1)));
}
