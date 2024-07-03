/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:55:51 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/03 14:19:10 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_map_info	*map_parsing(char *map_name)
{
	t_map_info	*map_info;
	int			fd;

	map_info = (t_map_info *)malloc(sizeof(t_map_info));
	if (map_info == NULL)
		exit(EXIT_FAILURE);
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
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
