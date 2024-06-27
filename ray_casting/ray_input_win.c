/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_input_win.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:52:51 by taekhkim          #+#    #+#             */
/*   Updated: 2024/06/27 19:53:40 by taekhkim         ###   ########.fr       */
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

void	ray_input_win(t_map_info *map_info, t_ray_cast *ray_info,
	void *mlx, void *win)
{
	int		i;
	double	dis;
	char	wall_dir;

	i = 0;
	while (i < 1)
	{
		dis = ray_distance(map_info, ray_info, wall_dir, i);
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

	tmp = (2 * (double)DIR_DIS / WIN_SIZE_X) * idx;
	a = ray_info->dir_x - ray_info->plane_x + (tmp * ray_info->plane_x);
	b = ray_info->dir_y - ray_info->plane_y + (tmp * ray_info->plane_y);
	// converttounitvector(double a, double b, double *unitA, double *unitB)
	// a,b 단위벡터로 바꿔줘야 함
	ray_distance_sub(map_info, ray_info, a, b);
}

static double	ray_distance_sub(t_map_info *map_info, t_ray_cast *ray_info,
	double a, double b)
{
	// part_x = (int)(ray_info->pos_x + a) - ray_info->pos_x;
	// part_y = (int)(ray_info->pos_y + b) - ray_info->pos_y;
	// a 가 양수 (int)(1.3) + 1 - 1.3
	// a 가 음수 (int)(1.3) - 1.3
	// b 		위와 동일
	if (a > 0 && b > 0)		// 1사분면
	{
		
	}
	else if (a < 0 && b > 0)		// 2사분면
	{
		
	}
	else if (a < 0 && b < 0)		// 3사분면
	{
		
	}
	else if (a > 0 && b < 0)		// 4사분면
	{
		
	}
	else							// 수직 ray들
	{
		
	}
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
		y = ray_info->pos_y + ratio * ((int)ray_info->pos_x + 1 - ray_info->pos_x);		// 첫번째 y 검사위치
		while (map_info->map[x][(int)y] != 1)
		{
			x++;
			y += ratio;
		}
	}
	else
	{
		x = (int)ray_info->pos_x;			// 첫번째 x 검사위치
		y = ray_info->pos_y + ratio * ((int)ray_info->pos_x - ray_info->pos_x);		// 첫번째 y 검사위치
		while (map_info->map[x][(int)y] != 1)
		{
			x++;
			y += ratio;
		}
	}
	// 길이 반환 - 근데 이게 자신하고 부딪힌 부분이랑 이라서 좀 애매함
}

static double	ray_distance_y(t_map_info *map_info, t_ray_cast *ray_info,
	double ratio, int flag)
{
	// ratio는 a/b로 와야 됨
	double		x;			// check x값
	int			y;			// check y값

	if (flag == Q1 || flag == Q2)
	{
		y = (int)ray_info->pos_y + 1;				// 첫번째 y 검사위치
		x = ray_info->pos_x + ratio * ((int)ray_info->pos_y + 1 - ray_info->pos_y);		// 첫번째 x 검사위치
		while (map_info->map[(int)x][y] != 1)
		{
			x += ratio;
			y++;
		}
	}
	else
	{
		y = (int)ray_info->pos_y + 1;				// 첫번째 y 검사위치
		x = ray_info->pos_x + ratio * ((int)ray_info->pos_y - ray_info->pos_y);		// 첫번째 x 검사위치
		while (map_info->map[(int)x][y] != 1)
		{
			x += ratio;
			y++;
		}
	}
	// 길이 반환 - 근데 이게 자신하고 부딪힌 부분이랑 이라서 좀 애매함
}
