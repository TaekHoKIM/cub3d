/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_distance_x_y_zero.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:55:37 by minyekim          #+#    #+#             */
/*   Updated: 2024/07/22 21:14:38 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

double	ray_distance_x_zero(t_total *total, double a, double b)
{
	double		x;
	double		y;

	x = total->ray_info->pos_x;
	y = total->ray_info->pos_y;
	y = (int)y;
	if (b < 0)
		y++;
	while (total->map_info->map[(int)y][(int)x] != '1')
	{
		y -= b;
	}
	if (b > 0)
		y++;
	return (distance_plane(total->ray_info, x, y));
}

double	ray_distance_y_zero(t_total *total, double a, double b)
{
	double		x;
	double		y;

	x = total->ray_info->pos_x;
	y = total->ray_info->pos_y;
	x = (int)x;
	if (b > 0)
		x++;
	while (total->map_info->map[(int)y][(int)x] != '1')
	{
		x += a;
	}
	if (b < 0)
		x++;
	return (distance_plane(total->ray_info, x, y));
}

double	ray_distance_x_y_zero(t_total *total, double a, double b)
{
	if (a == 0)
		return (ray_distance_x_zero(total, a, b));
	else if (b == 0)
		return (ray_distance_y_zero(total, a, b));
	return (FAIL);
}
