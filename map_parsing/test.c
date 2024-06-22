/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 15:00:06 by taekhkim          #+#    #+#             */
/*   Updated: 2024/06/22 20:09:40 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map_parse.h"

void leak()
{
	system("leaks a.out");
}

int main()
{
	t_map_info	*map_info;
	int			i;
	t_node		*test;

	// atexit(leak);
	map_info = map_parsing("test.cub");
	printf("success\n");
	printf("no_filenam:%s\n",map_info->no_filename);
	printf("so_filenam:%s\n",map_info->so_filename);
	printf("we_filenam:%s\n",map_info->we_filename);
	printf("ea_filenam:%s\n",map_info->ea_filename);
	printf("floor_r:%d\n",map_info->floor_r);
	printf("floor_g:%d\n",map_info->floor_g);
	printf("floor_b:%d\n",map_info->floor_b);
	printf("ceiling_r:%d\n",map_info->ceiling_r);
	printf("ceiling_g:%d\n",map_info->ceiling_g);
	printf("ceiling_b:%d\n",map_info->ceiling_b);
	i = 0;
	printf("------------------------\n");
	while (map_info->map[i] != NULL)
	{
		printf("%s$\n", map_info->map[i]);
		i++;
	}
}
