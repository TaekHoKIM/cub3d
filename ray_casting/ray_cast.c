/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:51:10 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/03 16:15:05 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	get_wall_size(t_map_info *map_info, double distance);
static void	rendering_loop(void *param);
static void	handle_keyhook(int keycode, void *param);

int	ray_cast(t_map_info *map_info, void	*mlx, void *win)
{
	t_ray_cast		*ray_info;
	t_total			*total;

	total = (t_total *)malloc(sizeof(t_total));
	ray_info = (t_ray_cast *)malloc(sizeof(t_ray_cast));
	map_info->image = mlx_new_image(mlx, WIN_SIZE_X, WIN_SIZE_Y);
	ray_init(map_info, ray_info);
	ray_input_win(map_info, ray_info, mlx, win);
	total->map_info = map_info;
	total->ray_info = ray_info;
	total->mlx = mlx;
	total->win = win;
	mlx_loop_hook(mlx, rendering_loop, (void *)total);
	mlx_hook(win, 2, 1L<<0, handle_keyhook, (void *)total);
}
// 이미지 
// 렌더링 함수 -> 이미지를 계속 그리기만 하고 <- 이미지를 그릴 때 사용되는 조건들
// 키입력 함수 -> 

void	put_pixel(t_map_info *map_info, void *mlx, void *win, double distance, int idx)
{
	int		wall_size;
	char	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;
	int 	pixel;
	int		x;
	int		y;
	int		tmp;

 	data_addr = mlx_get_data_addr(map_info->image, &bpp, &size_line, &endian);
	wall_size = get_wall_size(map_info, distance);
	x = idx;
	if (map_info->wall_dir == WALL_E)
		tmp = 0;
	else if (map_info->wall_dir == WALL_W)
		tmp = 50;
	else if (map_info->wall_dir == WALL_S)
		tmp = 100;
	else if (map_info->wall_dir == WALL_N)
		tmp = 150;
	for (y = 0; y < WIN_SIZE_Y; y++)
	{
		pixel = (y * size_line) + (x * (bpp / 8));
		if (y < abs(WIN_SIZE_Y - wall_size) / 2)
		{
			data_addr[pixel] = map_info->ceiling_b;       // 블루 채널
			data_addr[pixel + 1] = map_info->ceiling_g;   // 그린 채널
			data_addr[pixel + 2] = map_info->ceiling_r; // 레드 채널
			// data_addr[pixel + 3] = 0; // 알파 채널 (필요한 경우)
		}
		else if (y < abs(WIN_SIZE_Y - wall_size) / 2 + wall_size)
		{
			data_addr[pixel] = tmp;       // 블루 채널
			data_addr[pixel + 1] = 0;   // 그린 채널
			data_addr[pixel + 2] = 0; // 레드 채널
			// data_addr[pixel + 3] = 0; // 알파 채널 (필요한 경우)
		}
		else
		{
			data_addr[pixel] = map_info->floor_b;       // 블루 채널
			data_addr[pixel + 1] = map_info->floor_g;   // 그린 채널
			data_addr[pixel + 2] = map_info->floor_r; // 레드 채널
			// data_addr[pixel + 3] = 0; // 알파 채널 (필요한 경우)
		}
	}
}

static int	get_wall_size(t_map_info *map_info, double distance)
{
	double	wall_size;

	if (distance < R_SIZE)
		return (WIN_SIZE_Y);
	wall_size = ((WIN_SIZE_Y / distance) * R_SIZE);
	return((int)wall_size);
}

static void	rendering_loop(void *param)
{
	t_total			*total_info;
	int				i;

	total_info = (t_total *)param;
	mlx_put_image_to_window(total_info->mlx, total_info->win, total_info->map_info->image, 0, 0);
}

static void	handle_keyhook(int keycode, void *param)
{
	t_total			*total_info;
	t_ray_cast		*ray_info;
	double			theta;

	total_info = (t_total *)param;
	ray_info = total_info->ray_info;
	theta = 1.0 * M_PI / 180.0 * R_ANGLE;
	// key 이동 이상함 - 위치 이동 문제
	if (keycode == ESC)
	{
		printf("ESC key pressed. Exiting...\n");
		exit(0);
	}
	else if (keycode == W_KEY)
	{
		ray_info->pos_x += ray_info->dir_x * R_STEP;
		ray_info->pos_y -= ray_info->dir_y * R_STEP;
		if (total_info->map_info->map[(int)ray_info->pos_y][(int)ray_info->pos_x] == '1')
		{
			ray_info->pos_x -= ray_info->dir_x * R_STEP;
			ray_info->pos_y += ray_info->dir_y * R_STEP;
		}
	}
	else if (keycode == A_KEY)
	{
		ray_info->pos_x -= ray_info->dir_y * R_STEP;
		ray_info->pos_y -= ray_info->dir_x * R_STEP;
		if (total_info->map_info->map[(int)ray_info->pos_y][(int)ray_info->pos_x] == '1')
		{
			ray_info->pos_x += ray_info->dir_y * R_STEP;
			ray_info->pos_y += ray_info->dir_x * R_STEP;
		}
	}
	else if (keycode == S_KEY)
	{
		ray_info->pos_x -= ray_info->dir_x * R_STEP;
		ray_info->pos_y += ray_info->dir_y * R_STEP;
		if (total_info->map_info->map[(int)ray_info->pos_y][(int)ray_info->pos_x] == '1')
		{
			ray_info->pos_x += ray_info->dir_x * R_STEP;
			ray_info->pos_y -= ray_info->dir_y * R_STEP;
		}
	}
	else if (keycode == D_KEY)
	{
		ray_info->pos_x += ray_info->dir_y * R_STEP;
		ray_info->pos_y += ray_info->dir_x * R_STEP;
		if (total_info->map_info->map[(int)ray_info->pos_y][(int)ray_info->pos_x] == '1')
		{
			ray_info->pos_x -= ray_info->dir_y * R_STEP;
			ray_info->pos_y -= ray_info->dir_x * R_STEP;
		}
	}
	else if (keycode == RIGHT_ARROW_KEY)
	{
		rotatecounterclockwise(ray_info->dir_x, ray_info->dir_y,theta, &ray_info->dir_x, &ray_info->dir_y);
		converttounitvector(ray_info->dir_x, ray_info->dir_y, &ray_info->dir_x, &ray_info->dir_y);
		plane_angle(ray_info);
	}
	else if (keycode == LEFT_ARROW_KEY)
	{
		rotateclockwise(ray_info->dir_x, ray_info->dir_y,theta, &ray_info->dir_x, &ray_info->dir_y);
		converttounitvector(ray_info->dir_x, ray_info->dir_y, &ray_info->dir_x, &ray_info->dir_y);
		plane_angle(ray_info);
	}
	printf("dir_x:%lf / dir_y:%lf\n",ray_info->dir_x, ray_info->dir_y);
	printf("pos_x:%lf / pos_y:%lf\n",ray_info->pos_x, ray_info->pos_y);
	printf("plane_x:%lf / plane_y:%lf\n",ray_info->plane_x, ray_info->plane_y);
	ray_input_win(total_info->map_info, total_info->ray_info, total_info->mlx, total_info->win);
	// 움직일때 벽 통과 해결해야됨, 각도 제대로 변하는 지 확인해야함
}


// bool [TRUE down left right]
//1
//1
//1
//1 뗌

// key_hook <- 통해서 입력이 감지된 순간에는 
// mlx_loop_hook <- 이미지를 다시 그린다.
