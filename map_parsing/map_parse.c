/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:55:51 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/25 17:50:04 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_map_info	*map_parsing(char *map_name)
{
	t_map_info	*map_info;
	int			fd;

	map_info = ft_malloc(sizeof(t_map_info), 1);
	fd = open(map_name, O_RDONLY);
	if (fd == FAIL)
		map_exit_error("map open error\n");
	map_init(map_info);
	map_input_texture(fd, map_info);
	map_input_rgb(fd, map_info);
	input_map(fd, map_info);
	return (map_info);
}

void	map_init(t_map_info *map_info)
{
	map_info->no_filename = NULL;
	map_info->so_filename = NULL;
	map_info->we_filename = NULL;
	map_info->ea_filename = NULL;
	map_info->floor_r = -1;
	map_info->floor_g = -1;
	map_info->floor_b = -1;
	map_info->ceiling_r = -1;
	map_info->ceiling_g = -1;
	map_info->ceiling_b = -1;
	map_info->s_x = 0;
	map_info->s_y = 0;
	map_info->s_dir = ' ';
	map_info->map = NULL;
	return ;
}
