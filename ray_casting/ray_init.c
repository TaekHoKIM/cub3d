/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:27:49 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/22 18:38:51 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	dir_init(t_total *total);
static int	plane_init(t_total *total);

int	ray_init(t_total *total)
{
	total->ray_info->pos_x = (double)total->map_info->s_x + 0.5;
	total->ray_info->pos_y = (double)total->map_info->s_y + 0.5;
	if (dir_init(total) == FAIL)
		exit(EXIT_FAILURE);
	if (plane_init(total) == FAIL)
		exit(EXIT_FAILURE);
	return (SUCCESS);
}

static int	dir_init(t_total *total)
{
	if (total->map_info->s_dir == 'N')
	{
		total->ray_info->dir_x = 0;
		total->ray_info->dir_y = 1 * DIR_DIS;
	}
	else if (total->map_info->s_dir == 'S')
	{
		total->ray_info->dir_x = 0;
		total->ray_info->dir_y = -1 * DIR_DIS;
	}
	else if (total->map_info->s_dir == 'E')
	{
		total->ray_info->dir_x = 1 * DIR_DIS;
		total->ray_info->dir_y = 0;
	}
	else if (total->map_info->s_dir == 'W')
	{
		total->ray_info->dir_x = -1 * DIR_DIS;
		total->ray_info->dir_y = 0;
	}
	else
		return (FAIL);
	return (SUCCESS);
}

static int	plane_init(t_total *total)
{
	if (total->map_info->s_dir == 'N' || total->map_info->s_dir == 'S')
	{
		total->ray_info->plane_x = 1;
		total->ray_info->plane_y = 0;
		if (total->map_info->s_dir == 'S')
			total->ray_info->plane_x *= -1;
	}
	else if (total->map_info->s_dir == 'E' || total->map_info->s_dir == 'W')
	{
		total->ray_info->plane_x = 0;
		total->ray_info->plane_y = 1;
		if (total->map_info->s_dir == 'W')
			total->ray_info->plane_y *= -1;
	}
	else
		return (FAIL);
	return (SUCCESS);
}

void	plane_angle(t_ray_cast *ray_info)
{
	ray_info->plane_x = ray_info->dir_y;
	ray_info->plane_y = -1 * ray_info->dir_x;
	converttounitvector(ray_info->plane_x, ray_info->plane_y,
		&ray_info->plane_x, &ray_info->plane_y);
	return ;
}
