/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_input_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:38:51 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/10 18:44:22 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	check_full_rgb(t_map_info *map_info);

void	map_input_rgb(int fd, t_map_info *map_info)
{
	char	*line;
	int		flag;

	flag = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (!(ft_strlen(line) == 1 && line[0] == '\n'))
		{
			input_rgb_sub1(line, map_info);
			flag = 1;
		}
		else if (flag == 1)
		{
			free(line);
			break ;
		}
		free(line);
	}
	if (check_full_rgb(map_info) == SUCCESS)
		return ;
	exit(EXIT_FAILURE);
}

static int	check_full_rgb(t_map_info *map_info)
{
	if (map_info->floor_r == -1)
		return (FAIL);
	if (map_info->floor_g == -1)
		return (FAIL);
	if (map_info->floor_b == -1)
		return (FAIL);
	if (map_info->ceiling_r == -1)
		return (FAIL);
	if (map_info->ceiling_g == -1)
		return (FAIL);
	if (map_info->ceiling_b == -1)
		return (FAIL);
	return (SUCCESS);
}

void	check_num(char **split_set)
{
	int	count;
	int	i;

	count = 0;
	while (split_set[count] != NULL)
		count++;
	if (count != 3)
		exit(EXIT_FAILURE);
	count = 0;
	while (count < 3)
	{
		i = 0;
		while (split_set[count][i] != '\0')
		{
			if (!('0' <= split_set[count][i] && split_set[count][i] <= '9'))
				exit(EXIT_FAILURE);
			i++;
		}
		count++;
	}
	return ;
}

void	check_comma(char *line)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
		exit(EXIT_FAILURE);
	return ;
}
