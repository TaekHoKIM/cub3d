/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_input_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:32:34 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/08 16:05:18 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int		check_valid_line(char *line);
static void		input_node(t_node *start, char *line);
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

static int	check_valid_line(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (!(line[i] == ' ' || line[i] == '0' || line[i] == '1'))
			if (!(line[i] == 'N' || line[i] == 'S'
					|| (line[i] == 'E') || line[i] == 'W'))
				return (FAIL);
		if (flag == 0 && (line[i] == '0' || line[i] == '1'))
			flag = 1;
		i++;
	}
	if (flag == 0)
		return (FAIL);
	return (SUCCESS);
}

static void	input_node(t_node *start, char *line)
{
	t_node	*tmp;
	t_node	*new_node;

	tmp = start;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->map_line = line;
	new_node->next = NULL;
	tmp->next = new_node;
	return ;
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
			if (check_valid_line(line) == FAIL)
			{
				free(line);
				break ;
			}
			if (start == NULL)
			{
				start = (t_node *)malloc(sizeof(t_node));
				start->map_line = line;
				start->next = NULL;
			}
			else
				input_node(start, line);
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
		exit(EXIT_FAILURE);
	map_info->map_size_x = ft_strlen(map[0]);
	i = 0;
	while (i < map_info->map_size_y)
	{
		j = 0;
		while (j < map_info->map_size_x)
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
					|| (map[i][j] == 'E') || map[i][j] == 'W')
			{
				map_info->s_x = j;
				map_info->s_y = i;
				map_info->s_dir = map[i][j];
			}
			j++;
		}
		i++;
	}
}
