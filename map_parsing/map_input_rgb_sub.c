/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_input_rgb_sub.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:27:09 by minyekim          #+#    #+#             */
/*   Updated: 2024/07/10 18:43:50 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

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

static void	free_2d_char_arr(char **split_set)
{
	int	idx;

	idx = 0;
	while (idx < 3)
	{
		free(split_set[idx]);
		idx++;
	}
	free(split_set);
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
	check_comma(tmp);
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
	free_2d_char_arr(split_set);
	return ;
}

void	input_rgb_sub1(char *line, t_map_info *map_info)
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
