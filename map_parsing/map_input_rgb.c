/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_input_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:38:51 by taekhkim          #+#    #+#             */
/*   Updated: 2024/06/22 19:09:50 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

static void	input_rgb_sub1(char *line, t_map_info *map_info);
static void	input_rgb_sub2(char *line, t_map_info *map_info, int flag);
static void	input_rgb_sub3(t_map_info *map_info, int flag, int rgb, int val);
static int	check_full_rgb(t_map_info *map_info);
static void	check_num(char **split_set);

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

static void	input_rgb_sub1(char *line, t_map_info *map_info)
{
	int	len;

	len = ft_strlen(line);
	if (len > 2)
	{
		if (line[0] == 'F' && line[1] == ' ')
			input_rgb_sub2(line, map_info, 0);
		else if (line[0] == 'C' && line[1] == ' ')
			input_rgb_sub2(line, map_info, 1);
	}
}

static void	input_rgb_sub2(char *line, t_map_info *map_info, int flag)
{
	int		l;
	char	*tmp;
	char	*sub_str;
	char	**split_set;
	int		idx;

	l = ft_strlen(line);
	sub_str = ft_substr(line, 2, l - 3);
	tmp = ft_strtrim(sub_str, " ");
	free(sub_str);
	split_set = ft_split(tmp, ',');
	free(tmp);
	check_num(split_set);
	idx = 0;
	while (idx < 3)
	{
		l = ft_atoi(split_set[idx]);
		if (!(0 <= l && l <= 255))
			exit(EXIT_FAILURE);
		input_rgb_sub3(map_info, flag, idx, l);
		idx++;
	}
	idx = 0;
	while (idx < 3)
	{
		free(split_set[idx]);
		idx++;
	}
	free(split_set);
	return ;
}

static void	input_rgb_sub3(t_map_info *map_info, int flag, int rgb, int val)
{
	if (flag == 0)
	{
		if (rgb == 0)
			map_info->floor_r = val;
		else if (rgb == 1)
			map_info->floor_g = val;
		else if (rgb == 2)
			map_info->floor_b = val;
	}
	else if (flag == 1)
	{
		if (rgb == 0)
			map_info->ceiling_r = val;
		else if (rgb == 1)
			map_info->ceiling_g = val;
		else if (rgb == 2)
			map_info->ceiling_b = val;
	}
	return ;
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

static void	check_num(char **split_set)
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
