/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_distance_y_quadrant.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:16:06 by minyekim          #+#    #+#             */
/*   Updated: 2024/07/22 20:40:10 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static double	ray_distance_y_quadrant_1_2(t_total *total, double ratio)
{
	double		x;
	int			y;

	y = (int)total->ray_info->pos_y;
	x = total->ray_info->pos_x - ratio * \
		((int)total->ray_info->pos_y - total->ray_info->pos_y);
	if (x < 0 || x >= (double)total->map_info->map_size_x
		|| total->map_info->map[y - 1][(int)x] == ' ')
		return (FAIL);
	while (total->map_info->map[y - 1][(int)x] != '1' &&
		total->map_info->map[y - 1][(int)x] != ' ')
	{
		x += ratio;
		y--;
		if (x < 0 || x >= (double)total->map_info->map_size_x)
			return (FAIL);
	}
	total->map_info->x_hit = x;
	return (distance_plane(total->ray_info, x, (double)y));
}

static double	ray_distance_y_quadrant_3_4(t_total *total, double ratio)
{
	double		x;
	int			y;

	y = (int)total->ray_info->pos_y + 1;
	x = total->ray_info->pos_x - ratio * \
		((int)total->ray_info->pos_y + 1 - total->ray_info->pos_y);
	if (x < 0 || x >= (double)total->map_info->map_size_x
		|| total->map_info->map[y][(int)x] == ' ')
		return (FAIL);
	while (total->map_info->map[y][(int)x] != '1' &&
		total->map_info->map[y][(int)x] != ' ')
	{
		x -= ratio;
		y++;
		if (x < 0 || x >= (double)total->map_info->map_size_x)
			return (FAIL);
	}
	total->map_info->x_hit = x;
	return (distance_plane(total->ray_info, x, (double)y));
}

double	ray_distance_y(t_total *total, double a, double b, int *flag)
{
	if (a > 0 && b > 0)
	{
		*flag = Q1;
		return (ray_distance_y_quadrant_1_2(total, a / b));
	}
	else if (a < 0 && b > 0)
	{
		*flag = Q2;
		return (ray_distance_y_quadrant_1_2(total, a / b));
	}
	else if (a < 0 && b < 0)
	{
		*flag = Q3;
		return (ray_distance_y_quadrant_3_4(total, a / b));
	}
	else if (a > 0 && b < 0)
	{
		*flag = Q4;
		return (ray_distance_y_quadrant_3_4(total, a / b));
	}
	return (FAIL);
}
