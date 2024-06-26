/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:27:49 by taekhkim          #+#    #+#             */
/*   Updated: 2024/06/26 19:35:14 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	dir_init(t_map_info *map_info, t_ray_cast *ray_info);
static int	plane_init(t_map_info *map_info, t_ray_cast *ray_info);
static int	plane_init(t_map_info *map_info, t_ray_cast *ray_info);

int	ray_init(t_map_info *map_info, t_ray_cast *ray_info)
{
	ray_info->pos_x = (double)map_info->s_x;
	ray_info->pos_y = (double)map_info->s_y;
	if (dir_init(map_info, ray_info) == FAIL)
		exit(EXIT_FAILURE);
	if (plane_init(map_info, ray_info) == FAIL)
		exit(EXIT_FAILURE);
	return (SUCCESS);
}

static int	dir_init(t_map_info *map_info, t_ray_cast *ray_info)
{
	if (map_info->s_dir == 'N')
	{
		ray_info->dir_x = 0;
		ray_info->dir_y = 1 * DIR_DIS;
	}
	else if (map_info->s_dir == 'S')
	{
		ray_info->dir_x = 0;
		ray_info->dir_y = -1 * DIR_DIS;
	}
	else if (map_info->s_dir == 'E')
	{
		ray_info->dir_x = 1 * DIR_DIS;
		ray_info->dir_y = 0;
	}
	else if (map_info->s_dir == 'W')
	{
		ray_info->dir_x = -1 * DIR_DIS;
		ray_info->dir_y = 0;
	}
	else
		return (FAIL);
	return (SUCCESS);
}

static int	plane_init(t_map_info *map_info, t_ray_cast *ray_info)
{
	if (map_info->s_dir == 'N' || map_info->s_dir == 'S')
	{
		ray_info->plane_x = 1 * PLANE_DIS;
		ray_info->plane_y = 0;
	}
	else if (map_info->s_dir == 'E' || map_info->s_dir == 'W')
	{
		ray_info->plane_x = 0;
		ray_info->plane_y = 1 * PLANE_DIS;
	}
	else
		return (FAIL);
	return (SUCCESS);
}
