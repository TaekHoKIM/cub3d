/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_vaild_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:40:19 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/26 19:48:28 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	map_content_check(char **map, int width, int height);
static int	check_surround(char **map, int width, int height);
static int	check_outside_zero(char **map, int width, int height);

void	map_vaild_check(char **map)
{
	int	width;
	int	height;

	if (map[0] == NULL)
		map_exit_error("map vaild error\n");
	width = ft_strlen(map[0]);
	height = 0;
	while (map[height] != NULL)
		height++;
	if (map_content_check(map, width, height) == FAIL)
		map_exit_error("map vaild error\n");
	if (check_outside_zero(map, width, height) == FAIL)
		map_exit_error("map vaild error\n");
	if (check_surround(map, width, height) == FAIL)
		map_exit_error("map vaild error\n");
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
		j = -1;
		while (++j < width)
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
		}
		i++;
	}
	return (SUCCESS);
}

static int	check_zero(char **map, int cnt, int i, int flag)
{
	int	j;

	j = 0;
	if (flag == WIDTH)
	{
		while (j < cnt)
		{
			if (map[i][j] == '0')
				return (FAIL);
			j++;
		}
	}
	else if (flag == HEIGHT)
	{
		while (j < cnt)
		{
			if (map[j][i] == '0')
				return (FAIL);
			j++;
		}
	}
	return (SUCCESS);
}

static int	check_outside_zero(char **map, int width, int height)
{
	if (check_zero(map, width, 0, WIDTH) == FAIL)
		return (FAIL);
	if (check_zero(map, width, height - 1, WIDTH) == FAIL)
		return (FAIL);
	if (check_zero(map, height, 0, HEIGHT) == FAIL)
		return (FAIL);
	if (check_zero(map, height, width - 1, HEIGHT) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
