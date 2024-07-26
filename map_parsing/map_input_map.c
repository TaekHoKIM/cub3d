/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_input_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:32:34 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/25 17:51:29 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static t_node	*make_start_node(int fd);
static void		input_start_info(t_map_info *map_info);

void	input_map(int fd, t_map_info *map_info)
{
	t_node	*start;
	char	**map;

	start = make_start_node(fd);
	map = map_make_map(start);
	map_info->map = map;
	input_start_info(map_info);
}

static t_node	*make_start_node(int fd)
{
	char	*line;
	t_node	*start;

	start = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (!(ft_strlen(line) == 1 && line[0] == '\n'))
		{
			if (check_valid_and_input(&start, line) == FAIL)
				break ;
		}
		else if (start != NULL)
		{
			free(line);
			break ;
		}
		else
			free(line);
	}
	return (start);
}

static void	dir_check(t_map_info *map_info, char **map, int i, int j)
{
	if (map[i][j] == 'N' || map[i][j] == 'S'
		|| (map[i][j] == 'E') || map[i][j] == 'W')
	{
		map_info->s_x = j;
		map_info->s_y = i;
		map_info->s_dir = map[i][j];
	}
}

static void	input_start_info(t_map_info *map_info)
{
	int		i;
	int		j;
	char	**map;

	map = map_info->map;
	i = 0;
	while (map[i] != NULL)
		i++;
	map_info->map_size_y = i;
	if (i == 0)
		map_exit_error("map contents error\n");
	map_info->map_size_x = ft_strlen(map[0]);
	i = 0;
	while (i < map_info->map_size_y)
	{
		j = 0;
		while (j < map_info->map_size_x)
		{
			dir_check(map_info, map, i, j);
			j++;
		}
		i++;
	}
}
