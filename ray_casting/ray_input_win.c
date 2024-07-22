/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_input_win.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:52:51 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/22 20:58:17 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static double	ray_distance(t_total *total, int idx);
static double	ray_distance_sub(t_total *total, double a, double b);

void	ray_input_win(t_total *total)
{
	int		i;
	double	dis;

	i = 0;
	while (i < WIN_SIZE_X)
	{
		dis = ray_distance(total, i);
		put_pixel(total, dis, i);
		i++;
	}
}

static double	ray_distance(t_total *total, int idx)
{
	double	a;
	double	b;
	int		point_x;
	int		point_y;
	double	tmp;

	tmp = (2 * (double)DIR_DIS / WIN_SIZE_X) * idx;
	a = total->ray_info->dir_x - (total->ray_info->plane_x * PLANE_DIS) + \
		(tmp * total->ray_info->plane_x * PLANE_DIS);
	b = total->ray_info->dir_y - (total->ray_info->plane_y * PLANE_DIS) + \
		(tmp * total->ray_info->plane_y * PLANE_DIS);
	converttounitvector(a, b, &a, &b);
	return (ray_distance_sub(total, a, b));
}

static double	ray_distance_sub(t_total *total, double a, double b)
{
	double	x_dis;
	double	y_dis;
	int		flag;

	if (a == 0 || b == 0)
		return (ray_distance_x_y_zero(total, a, b));
	x_dis = ray_distance_x(total, a, b);
	y_dis = ray_distance_y(total, a, b, &flag);
	return (wall_dir_change(total, x_dis, y_dis, flag));
}
