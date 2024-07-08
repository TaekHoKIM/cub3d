/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_input_win.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:52:51 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/08 16:38:51 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static double	ray_distance(t_map_info *map_info, t_ray_cast *ray_info,
					int idx);
static double	ray_distance_sub(t_map_info *map_info, t_ray_cast *ray_info,
					double a, double b);
static double	ray_distance_x(t_map_info *map_info, t_ray_cast *ray_info,
					double ratio, int flag);
static double	ray_distance_y(t_map_info *map_info, t_ray_cast *ray_info,
					double ratio, int flag);
static double	ray_distance_x_y_zero(t_map_info *map_info,
					t_ray_cast *ray_info, double a, double b);

void	ray_input_win(t_map_info *map_info, t_ray_cast *ray_info,
	void *mlx, void *win)
{
	int		i;
	double	dis;

	i = 0;
	while (i < WIN_SIZE_X)
	{
		dis = ray_distance(map_info, ray_info, i);
		put_pixel(map_info, mlx, win, dis, i);
		i++;
	}
}

static double	ray_distance(t_map_info *map_info, t_ray_cast *ray_info,
				int idx)
{
	double	a;
	double	b;
	int		point_x;
	int		point_y;
	double	tmp;

	tmp = (2 * (double)DIR_DIS / WIN_SIZE_X) * idx;
	a = ray_info->dir_x - (ray_info->plane_x * PLANE_DIS) + \
		(tmp * ray_info->plane_x * PLANE_DIS);
	b = ray_info->dir_y - (ray_info->plane_y * PLANE_DIS) + \
		(tmp * ray_info->plane_y * PLANE_DIS);
	converttounitvector(a, b, &a, &b);
	return (ray_distance_sub(map_info, ray_info, a, b));
}

static double	ray_distance_sub(t_map_info *map_info, t_ray_cast *ray_info,
	double a, double b)
{
	double	x_dis;
	double	y_dis;
	int		flag;

	if (a > 0 && b > 0)
	{
		x_dis = ray_distance_x(map_info, ray_info, b / a, Q1);
		y_dis = ray_distance_y(map_info, ray_info, a / b, Q1);
		flag = Q1;
	}
	else if (a < 0 && b > 0)
	{
		x_dis = ray_distance_x(map_info, ray_info, b / a, Q2);
		y_dis = ray_distance_y(map_info, ray_info, a / b, Q2);
		flag = Q2;
	}
	else if (a < 0 && b < 0)
	{
		x_dis = ray_distance_x(map_info, ray_info, b / a, Q3);
		y_dis = ray_distance_y(map_info, ray_info, a / b, Q3);
		flag = Q3;
	}
	else if (a > 0 && b < 0)
	{
		x_dis = ray_distance_x(map_info, ray_info, b / a, Q4);
		y_dis = ray_distance_y(map_info, ray_info, a / b, Q4);
		flag = Q4;
	}
	else
		return (ray_distance_x_y_zero(map_info, ray_info, a, b));
	if (x_dis == FAIL)
	{
		if (flag == Q1 || flag == Q2)
			map_info->wall_dir = WALL_S;
		else
			map_info->wall_dir = WALL_N;
		return (y_dis);
	}
	else if (y_dis == FAIL)
	{
		if (flag == Q1 || flag == Q4)
			map_info->wall_dir = WALL_W;
		else
			map_info->wall_dir = WALL_E;
		return (x_dis);
	}
	if (x_dis < y_dis)
	{
		if (flag == Q1 || flag == Q4)
			map_info->wall_dir = WALL_W;
		else
			map_info->wall_dir = WALL_E;
		return (x_dis);
	}
	if (flag == Q1 || flag == Q2)
		map_info->wall_dir = WALL_S;
	else
		map_info->wall_dir = WALL_N;
	return (y_dis);
}

static double	ray_distance_x(t_map_info *map_info, t_ray_cast *ray_info,
	double ratio, int flag)
{
	int		x;
	double	y;

	if (flag == Q1 || flag == Q4)
	{
		x = (int)ray_info->pos_x + 1;
		y = ray_info->pos_y - ratio * \
			((int)ray_info->pos_x + 1 - ray_info->pos_x);
		if (y < 0 || y >= (double)map_info->map_size_y
			|| map_info->map[(int)y][x] == ' ')
			return (FAIL);
		while (map_info->map[(int)y][x] != '1' && map_info->map[(int)y][x] != ' ')
		{
			x++;
			y -= ratio;
			if (y < 0 || y >= (double)map_info->map_size_y)
				return (FAIL);
		}
	}
	else
	{
		x = (int)ray_info->pos_x;
		y = ray_info->pos_y - ratio * ((int)ray_info->pos_x - ray_info->pos_x);
		if (y < 0 || y >= (double)map_info->map_size_y || map_info->map[(int)y][x - 1] == ' ')
			return (FAIL);
		while (map_info->map[(int)y][x - 1] != '1' && map_info->map[(int)y][x - 1] != ' ')
		{
			x--;
			y += ratio;
			if (y < 0 || y >= (double)map_info->map_size_y)
				return (FAIL);
		}
	}
	map_info->y_hit = y;
	return (distance_plane(ray_info, (double)x, y));
}

static double	ray_distance_y(t_map_info *map_info, t_ray_cast *ray_info,
	double ratio, int flag)
{
	double		x;
	int			y;

	if (flag == Q1 || flag == Q2)
	{
		y = (int)ray_info->pos_y;
		x = ray_info->pos_x - ratio * ((int)ray_info->pos_y - ray_info->pos_y);
		if (x < 0 || x >= (double)map_info->map_size_x || map_info->map[y - 1][(int)x] == ' ')
			return (FAIL);
		while (map_info->map[y - 1][(int)x] != '1' && map_info->map[y - 1][(int)x] != ' ')
		{
			x += ratio;
			y--;
			if (x < 0 || x >= (double)map_info->map_size_x)
				return (FAIL);
		}
	}
	else
	{
		y = (int)ray_info->pos_y + 1;
		x = ray_info->pos_x - ratio * ((int)ray_info->pos_y + 1 - ray_info->pos_y);
		if (x < 0 || x >= (double)map_info->map_size_x || map_info->map[y][(int)x] == ' ')
			return (FAIL);
		while (map_info->map[y][(int)x] != '1' && map_info->map[y][(int)x] != ' ')
		{
			x -= ratio;
			y++;
			if (x < 0 || x >= (double)map_info->map_size_x)
				return (FAIL);
		}
	}
	map_info->x_hit = x;
	return (distance_plane(ray_info, x, (double)y));
}

static double	ray_distance_x_y_zero(t_map_info *map_info,
	t_ray_cast *ray_info, double a, double b)
{
	double		x;
	double		y;

	x = ray_info->pos_x;
	y = ray_info->pos_y;
	if (a == 0)
	{
		y = (int)y;
		if (b < 0)
			y++;
		while (map_info->map[(int)y][(int)x] != '1')
		{
			y -= b;
		}
		if (b > 0)
			y++;
	}
	else if (b == 0)
	{
		x = (int)x;
		if (b > 0)
			x++;
		while (map_info->map[(int)y][(int)x] != '1')
		{
			x += a;
		}
		if (b < 0)
			x++;
	}
	return (distance_plane(ray_info, x, y));
}
