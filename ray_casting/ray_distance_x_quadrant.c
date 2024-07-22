/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_distance_x_quadrant.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:00:47 by minyekim          #+#    #+#             */
/*   Updated: 2024/07/22 20:38:54 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static double	ray_distance_x_quadrant_1_4(t_total *total, double ratio)
{
	int		x;
	double	y;

	x = (int)total->ray_info->pos_x + 1;
	y = total->ray_info->pos_y - ratio * \
		((int)total->ray_info->pos_x + 1 - total->ray_info->pos_x);
	if (y < 0 || y >= (double)total->map_info->map_size_y
		|| total->map_info->map[(int)y][x] == ' ')
		return (FAIL);
	while (total->map_info->map[(int)y][x] != '1' &&
		total->map_info->map[(int)y][x] != ' ')
	{
		x++;
		y -= ratio;
		if (y < 0 || y >= (double)total->map_info->map_size_y)
			return (FAIL);
	}
	total->map_info->y_hit = y;
	return (distance_plane(total->ray_info, (double)x, y));
}

static double	ray_distance_x_quadrant_2_3(t_total *total, double ratio)
{
	int		x;
	double	y;

	x = (int)total->ray_info->pos_x;
	y = total->ray_info->pos_y - ratio * \
		((int)total->ray_info->pos_x - total->ray_info->pos_x);
	if (y < 0 || y >= (double)total->map_info->map_size_y
		|| total->map_info->map[(int)y][x - 1] == ' ')
		return (FAIL);
	while (total->map_info->map[(int)y][x - 1] != '1' &&
		total->map_info->map[(int)y][x - 1] != ' ')
	{
		x--;
		y += ratio;
		if (y < 0 || y >= (double)total->map_info->map_size_y)
			return (FAIL);
	}
	total->map_info->y_hit = y;
	return (distance_plane(total->ray_info, (double)x, y));
}

double	ray_distance_x(t_total *total, double a, double b)
{
	if ((a > 0 && b > 0) || (a > 0 && b < 0))
		return (ray_distance_x_quadrant_1_4(total, b / a));
	else if ((a < 0 && b > 0) || (a < 0 && b < 0))
		return (ray_distance_x_quadrant_2_3(total, b / a));
	return (FAIL);
}
