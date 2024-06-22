/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_input_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:32:34 by taekhkim          #+#    #+#             */
/*   Updated: 2024/06/22 17:46:33 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

static int		check_valid_line(char *line);
static void		input_node(t_node *start, char *line);
static t_node	*make_start_node(int fd);

void	input_map(int fd, t_map_info *map_info)
{
	t_node	*start;
	char	**map;

	start = make_start_node(fd);
	map = map_make_map(start);
	map_info->map = map;
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

