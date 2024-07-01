/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:51:10 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/01 21:16:51 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	get_wall_size(t_map_info *map_info, double distance);
static void	handle_keypress(int keycode, void *param);
static void	handle_keyhook(int keycode, void *param);

int is_unit_vector(double x, double y) {
    double length = sqrt(x * x + y * y);
    return fabs(length - 1.0) < 0.000001;
}

int	ray_cast(t_map_info *map_info, void	*mlx, void *win)
{
	t_ray_cast		ray_info;
	t_total			total;

	map_info->image = mlx_new_image(mlx, WIN_SIZE_X, WIN_SIZE_Y);
	ray_init(map_info, &ray_info);
	ray_input_win(map_info, &ray_info, mlx, win);
	total.map_info = map_info;
	total.ray_info = &ray_info;
	total.mlx = mlx;
	total.win = win;
	mlx_key_hook(win, handle_keyhook, (void *)&total);
	mlx_hook(win, 2, 1L<<0, handle_keypress, (void *)&total);
	mlx_loop(mlx);
	return (SUCCESS);
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

 	data_addr = mlx_get_data_addr(map_info->image, &bpp, &size_line, &endian);
	wall_size = get_wall_size(map_info, distance);
	x = idx;
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
			data_addr[pixel] = 255;       // 블루 채널
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
	mlx_put_image_to_window(mlx, win, map_info->image, 0, 0);
}

static int	get_wall_size(t_map_info *map_info, double distance)
{
	double	wall_size;

	if (distance < 1)
		return (WIN_SIZE_Y);
	wall_size = (WIN_SIZE_Y / distance) * R_SIZE;
	return((int)wall_size);
}

static void	handle_keypress(int keycode, void *param)
{
	t_total			*total_info;

	total_info = (t_total *)param;
	ray_input_win(total_info->map_info, total_info->ray_info, total_info->mlx, total_info->win);
}

static void	handle_keyhook(int keycode, void *param)
{
	t_total			*total_info;
	t_ray_cast		*ray_info;
	double			theta;

	total_info = (t_total *)param;
	ray_info = total_info->ray_info;
	theta = 1.0 * M_PI / 180.0 * R_ANGLE;
	if (keycode == ESC)
	{
		printf("ESC key pressed. Exiting...\n");
		exit(0);
	}
	else if (keycode == W_KEY)
	{
		ray_info->pos_x += ray_info->dir_x * R_STEP;
		ray_info->pos_y -= ray_info->dir_y * R_STEP;
	}
	else if (keycode == A_KEY)
	{
		ray_info->pos_x -= ray_info->dir_y * R_STEP;
		ray_info->pos_y += ray_info->dir_x * R_STEP;
	}
	else if (keycode == S_KEY)
	{
		ray_info->pos_x -= ray_info->dir_x * R_STEP;
		ray_info->pos_y += ray_info->dir_y * R_STEP;
	}
	else if (keycode == D_KEY)
	{
		ray_info->pos_x += ray_info->dir_y * R_STEP;
		ray_info->pos_y -= ray_info->dir_x * R_STEP;
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
	printf("is_unit:%d\n",is_unit_vector(ray_info->dir_x, ray_info->dir_y));
	printf("is_unit:%d\n",is_unit_vector(ray_info->plane_x,ray_info->plane_y));
	printf("dir_x:%lf / dir_y:%lf\n",ray_info->dir_x, ray_info->dir_y);
	printf("pos_x:%lf / pos_y:%lf\n",ray_info->pos_x, ray_info->pos_y);
	printf("plane_x:%lf / plane_y:%lf\n",ray_info->plane_x, ray_info->plane_y);
	// 움직일때 벽 통과 해결해야됨, 각도 제대로 변하는 지 확인해야함
}


// bool [TRUE down left right]
//1
//1
//1
//1 뗌

// key_hook <- 통해서 입력이 감지된 순간에는 
// mlx_loop_hook <- 이미지를 다시 그린다.
