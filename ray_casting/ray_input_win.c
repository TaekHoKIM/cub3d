/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_input_win.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 16:52:51 by taekhkim          #+#    #+#             */
/*   Updated: 2024/06/26 19:00:41 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static double	ray_distance(t_map_info *map_info, t_ray_cast *ray_info, char *wall_dir, int idx);

void	ray_input_win(t_map_info *map_info, t_ray_cast *ray_info, void *mlx, void *win)
{
	int		i;
	int		dis;
	char	wall_dir;

	i = 0;
	while (i < 10)
	{
		ray_distance(map_info, ray_info, wall_dir, i);
		i++;
	}
}


static double	ray_distance(t_map_info *map_info, t_ray_cast *ray_info, char *wall_dir, int idx)
{
	double	ray_x;
	double	ray_y;
	int		point_x;
	int		point_y;
	double	tmp;

	tmp = (2 * (double)DIR_DIS / WIN_SIZE_X) * idx;
	ray_x = ray_info->dir_x - ray_info->plane_x + (tmp * ray_info->plane_x);
	ray_y = ray_info->dir_y - ray_info->plane_y + (tmp * ray_info->plane_y);
	
}

static double	ray_distance_sub(t_map_info *map_info, t_ray_cast *ray_info, double ray_x, double ray_y)
{

	// part_x = (int)(ray_info->pos_x + ray_x) - ray_info->pos_x;
	// part_y = (int)(ray_info->pos_y + ray_y) - ray_info->pos_y;
	if (ray_x >= 0 && ray_y >= 0)
	{
		
	}
}

static double	ray_distance_x(t_map_info *map_info, t_ray_cast *ray_info, double ray_x, double ray_y)
{
	double	ratio_y;	// part_x에 맞게 y가 움직이는 위치
	double	one_step_y; // x가 1 움직일때 y가 움직이는 위치
	int	x;
	double	y;

	ratio_y = (ray_y * ((int)(ray_info->pos_x + ray_x) - ray_info->pos_x)) / ray_x;
	one_step_y = ray_y / ray_x;
	x = (int)(ray_info->pos_x + ray_x);
	y = ray_info->pos_y + ratio_y;
	while (map_info->map[x][(int)y] != 1)
	{
		x++;
		y += one_step_y;
	}
	// 길이 반환 - 근데 이게 자신하고 부딪힌 부분이랑 이라서 좀 애매함
}

static double	ray_distance_y(t_map_info *map_info, t_ray_cast *ray_info, double ray_x, double ray_y)
{
	double	ratio_x;	// part_y에 맞게 x가 움직이는 위치
	double	one_step_x; // y가 1 움직일때 x가 움직이는 위치
	double	x;
	int		y;

	ratio_x = (ray_x * ((int)(ray_info->pos_y + ray_y) - ray_info->pos_y)) / ray_y;
	one_step_x = ray_x / ray_y;
	x = ray_info->pos_x + ratio_x;
	y = (int)(ray_info->pos_y + ray_y) - ray_info->pos_y;
	while (map_info->map[(int)x][y] != 1)
	{
		x += one_step_x;
		y++;
	}
	// 길이 반환 - 근데 이게 자신하고 부딪힌 부분이랑 이라서 좀 애매함
}
