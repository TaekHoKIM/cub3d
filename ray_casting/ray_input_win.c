/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_input_win.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:52:51 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/02 19:44:30 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static double	ray_distance(t_map_info *map_info, t_ray_cast *ray_info,
					char *wall_dir, int idx);
static double	ray_distance_sub(t_map_info *map_info, t_ray_cast *ray_info,
					double a, double b);
static double	ray_distance_x(t_map_info *map_info, t_ray_cast *ray_info,
					double ratio, int flag);
static double	ray_distance_y(t_map_info *map_info, t_ray_cast *ray_info,
					double ratio, int flag);
static double	ray_distance_x_y_zero(t_map_info *map_info, t_ray_cast *ray_info,
					double a, double b);

void	ray_input_win(t_map_info *map_info, t_ray_cast *ray_info,
	void *mlx, void *win)
{
	int		i;
	double	dis;
	char	wall_dir;

	i = 0;
	while (i < WIN_SIZE_X)
	{
		dis = ray_distance(map_info, ray_info, wall_dir, i);
		printf("dis:%lf\n",dis);
		put_pixel(map_info, mlx, win, dis, i);
		i++;
	}
}

static double	ray_distance(t_map_info *map_info, t_ray_cast *ray_info,
	char *wall_dir, int idx)
{
	double	a;
	double	b;
	int		point_x;
	int		point_y;
	double	tmp;

	wall_dir = 'T';
	tmp = (2 * (double)DIR_DIS / WIN_SIZE_X) * idx;
	a = ray_info->dir_x - (ray_info->plane_x * PLANE_DIS) + (tmp * ray_info->plane_x * PLANE_DIS);
	b = ray_info->dir_y - (ray_info->plane_y * PLANE_DIS) + (tmp * ray_info->plane_y * PLANE_DIS);
	converttounitvector(a, b, &a, &b);				// a,b 단위벡터로 변경
	return (ray_distance_sub(map_info, ray_info, a, b));
}

static double	ray_distance_sub(t_map_info *map_info, t_ray_cast *ray_info,
	double a, double b)
{
	double	x_dis;			// x 정수 일때 hit 거리
	double	y_dis;			// y 정수 일때 hit 거리

	if (a > 0 && b > 0)		// 1사분면
	{
		x_dis = ray_distance_x(map_info, ray_info, b/a, Q1);
		y_dis = ray_distance_y(map_info, ray_info, a/b, Q1);
	}
	else if (a < 0 && b > 0)		// 2사분면
	{
		x_dis = ray_distance_x(map_info, ray_info, b/a, Q2);
		y_dis = ray_distance_y(map_info, ray_info, a/b, Q2);
	}
	else if (a < 0 && b < 0)		// 3사분면
	{
		x_dis = ray_distance_x(map_info, ray_info, b/a, Q3);
		y_dis = ray_distance_y(map_info, ray_info, a/b, Q3);
	}
	else if (a > 0 && b < 0)		// 4사분면
	{
		x_dis = ray_distance_x(map_info, ray_info, b/a, Q4);
		y_dis = ray_distance_y(map_info, ray_info, a/b, Q4);
	}
	else							// 수직 ray들
	{
		return (ray_distance_x_y_zero(map_info, ray_info, a, b));
	}
	if (x_dis == FAIL)
		return (y_dis);
	else if (y_dis == FAIL)
		return (x_dis);
	if (x_dis < y_dis)
		return (x_dis);
	return (y_dis);
}

static double	ray_distance_x(t_map_info *map_info, t_ray_cast *ray_info,
	double ratio, int flag)
{
	// ratio는 b/a로 와야 됨
	int		x;			// check x값
	double	y;			// check y값

	if (flag == Q1 || flag == Q4)
	{
		x = (int)ray_info->pos_x + 1;			// 첫번째 x 검사위치
		y = ray_info->pos_y - ratio * ((int)ray_info->pos_x + 1 - ray_info->pos_x);		// 첫번째 y 검사위치
		if (y < 0 || y >= (double)map_info->map_size_y || map_info->map[(int)y][x] == ' ')
				return (FAIL);
		while (map_info->map[(int)y][x] != '1')
		{
			x++;
			y -= ratio;
			if (y < 0 || y >= (double)map_info->map_size_y || map_info->map[(int)y][x] == ' ')
				return (FAIL);
		}
	}
	else
	{
		x = (int)ray_info->pos_x;			// 첫번째 x 검사위치
		y = ray_info->pos_y - ratio * ((int)ray_info->pos_x - ray_info->pos_x);		// 첫번째 y 검사위치
		if (y < 0 || y >= (double)map_info->map_size_y || map_info->map[(int)y][x - 1] == ' ')
				return (FAIL);
		// x가 0 이하일때는 surround라서 없음
		while (map_info->map[(int)y][x - 1] != '1')
		{
			x--;
			y += ratio;
			if (y < 0 || y >= (double)map_info->map_size_y || map_info->map[(int)y][x - 1] == ' ')
				return (FAIL);
		}
	}
	// 여기에서 x,y는 hit된 지점의 x,y 임
	return (distance_plane(ray_info, (double)x, y));
}

static double	ray_distance_y(t_map_info *map_info, t_ray_cast *ray_info,
	double ratio, int flag)
{
	// ratio는 a/b로 와야 됨
	double		x;			// check x값
	int			y;			// check y값

	if (flag == Q1 || flag == Q2)
	{
		y = (int)ray_info->pos_y;				// 첫번째 y 검사위치
		x = ray_info->pos_x - ratio * ((int)ray_info->pos_y - ray_info->pos_y);		// 첫번째 x 검사위치
		if (x < 0 || x >= (double)map_info->map_size_x || map_info->map[y - 1][(int)x] == ' ')
				return (FAIL);
		while (map_info->map[y - 1][(int)x] != '1')
		{
			x += ratio;
			y--;
			if (x < 0 || x >= (double)map_info->map_size_x || map_info->map[y - 1][(int)x] == ' ')
				return (FAIL);
		}
	}
	else
	{
		y = (int)ray_info->pos_y + 1;				// 첫번째 y 검사위치
		x = ray_info->pos_x - ratio * ((int)ray_info->pos_y + 1 - ray_info->pos_y);		// 첫번째 x 검사위치
		if (x < 0 || x >= (double)map_info->map_size_x || map_info->map[y][(int)x] == ' ')
				return (FAIL);
		while (map_info->map[y][(int)x] != '1')
		{
			x -= ratio;
			y++;
			if (x < 0 || x >= (double)map_info->map_size_x || map_info->map[y][(int)x] == ' ')
				return (FAIL);
		}
	}
	return (distance_plane(ray_info, x, (double)y));
}

static double	ray_distance_x_y_zero(t_map_info *map_info, t_ray_cast *ray_info,
	double a, double b)
{
	double		x;			// check x값
	double		y;			// check y값

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
