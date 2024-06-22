/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_make_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 16:23:55 by taekhkim          #+#    #+#             */
/*   Updated: 2024/06/22 19:15:26 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

static int	map_count(t_node *start);
static void	map_input_line(t_node *start, char **map);
static void	map_fitting(char **map);
static void	copy_line(char *line, char *new_line, int max_len);

char	**map_make_map(t_node *start)
{
	int		count;
	int		i;
	char	**map;

	count = map_count(start);
	map = (char **)malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (i < count + 1)
	{
		map[i] = NULL;
		i++;
	}
	map_input_line(start, map);
	map_fitting(map);
	map_vaild_check(map);
	return (map);
}

static int	map_count(t_node *start)
{
	t_node	*tmp;
	int		count;

	tmp = start;
	count = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

static void	map_input_line(t_node *start, char **map)
{
	t_node	*tmp;
	t_node	*rm_node;
	int		count;

	tmp = start;
	count = 0;
	while (tmp != NULL)
	{
		rm_node = tmp;
		map[count] = tmp->map_line;
		tmp = tmp->next;
		free(rm_node);
		count++;
	}
}

static void	map_fitting(char **map)
{
	int		i;
	size_t	max_len;
	char	*new_line;

	max_len = 0;
	i = 0;
	while (map[i] != NULL)
	{
		if (ft_strlen(map[i]) > max_len)
			max_len = ft_strlen(map[i]);
		i++;
	}
	i = 0;
	while (map[i] != NULL)
	{
		new_line = (char *)malloc(sizeof(char) * (max_len + 1));
		new_line[max_len] = '\0';
		copy_line(map[i], new_line, max_len);
		free(map[i]);
		map[i] = new_line;
		i++;
	}
}

static void	copy_line(char *line, char *new_line, int max_len)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		new_line[i] = line[i];
		i++;
	}
	if (new_line[i - 1] == '\n')
		new_line[i - 1] = ' ';
	while (i < max_len)
	{
		new_line[i] = ' ';
		i++;
	}
}

