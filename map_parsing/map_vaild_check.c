/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_vaild_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:40:19 by taekhkim          #+#    #+#             */
/*   Updated: 2024/06/23 16:08:08 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

static int	map_content_check(char **map, int width, int height);
static int	check_surround(char **map, int width, int height);
static int	check_outside_zero(char **map, int width, int height);

void	map_vaild_check(char **map)
{
	int	width;
	int	height;

	if (map[0] == NULL)
		exit(EXIT_FAILURE);
	width = ft_strlen(map[0]);
	height = 0;
	while (map[height] != NULL)
		height++;
	if (map_content_check(map, width, height) == FAIL)
		exit(EXIT_FAILURE);
	if (check_outside_zero(map, width, height) == FAIL)
		exit(EXIT_FAILURE);
	if (check_surround(map, width, height) == FAIL)
		exit(EXIT_FAILURE);
}

static int	map_content_check(char **map, int width, int height)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
					|| (map[i][j] == 'E') || map[i][j] == 'W')
				count++;
			if (count > 1)
				return (FAIL);
			j++;
		}
		i++;
	}
	if (count == 0)
		return (FAIL);
	return (SUCCESS);
}

static int	check_surround(char **map, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (map[i][j] == '0' || map[i][j] == 'N' || map[i][j] == 'S'
					|| (map[i][j] == 'E') || map[i][j] == 'W')
			{
				if ((j + 1 < width) && (map[i][j + 1] == ' '))
					return (FAIL);
				if ((j - 1 >= 0) && (map[i][j - 1] == ' '))
					return (FAIL);
				if ((i + 1 > height) && (map[i + 1][j] == ' '))
					return (FAIL);
				if ((i - 1 >= 0) && (map[i - 1][j] == ' '))
					return (FAIL);
			}
			j++;
		}
		i++;
	}
	return (SUCCESS);
}

static int	check_outside_zero(char **map, int width, int height)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < width)
	{
		if (map[i][j] == '0')
			return (FAIL);
		j++;
	}
	i = height - 1;
	j = 0;
	while (j < width)
	{
		if (map[i][j] == '0')
			return (FAIL);
		j++;
	}
	j = 0;
	i = 0;
	while (i < height)
	{
		if (map[i][j] == '0')
			return (FAIL);
		i++;
	}
	j = width - 1;
	i = 0;
	while (i < height)
	{
		if (map[i][j] == '0')
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}
