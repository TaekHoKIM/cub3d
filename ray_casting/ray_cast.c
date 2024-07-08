/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:51:10 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/08 16:31:46 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	get_wall_size(t_map_info *map_info, double distance);
static void	rendering_loop(void *param);
static void	handle_keyhook(int keycode, void *param);

int	ray_cast(t_map_info *map_info, void	*mlx, void *win)
{
	t_ray_cast		*ray_info;
	t_img			*wall_image_set;
	t_total			*total;

	total = (t_total *)malloc(sizeof(t_total));
	ray_info = (t_ray_cast *)malloc(sizeof(t_ray_cast));
	map_info->image = mlx_new_image(mlx, WIN_SIZE_X, WIN_SIZE_Y);
	dir_xmp_file_to_image(mlx, map_info, &wall_image_set);
	map_info->wall_image_set = wall_image_set;
	ray_init(map_info, ray_info);
	ray_input_win(map_info, ray_info, mlx, win);
	total->map_info = map_info;
	total->ray_info = ray_info;
	total->mlx = mlx;
	total->win = win;
	mlx_loop_hook(mlx, rendering_loop, (void *)total);
	mlx_hook(win, 2, 1L<<0, handle_keyhook, (void *)total);
}

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
	t_img	*wall_image;

	x = idx;
 	data_addr = mlx_get_data_addr(map_info->image, &bpp, &size_line, &endian);
	wall_size = get_wall_size(map_info, distance);
	if (map_info->wall_dir == WALL_E)
		wall_image = &(map_info->wall_image_set[EA]);
	else if (map_info->wall_dir == WALL_W)
		wall_image = &(map_info->wall_image_set[WE]);
	else if (map_info->wall_dir == WALL_S)
		wall_image = &(map_info->wall_image_set[SO]);
	else if (map_info->wall_dir == WALL_N)
		wall_image = &(map_info->wall_image_set[NO]);
	if (wall_size < WIN_SIZE_Y)
	{
		for (y = 0; y < WIN_SIZE_Y; y++)
		{
			pixel = (y * size_line) + (x * (bpp / 8));
			if (y < abs(WIN_SIZE_Y - wall_size) / 2)
			{
				data_addr[pixel] = map_info->ceiling_b;
				data_addr[pixel + 1] = map_info->ceiling_g;
				data_addr[pixel + 2] = map_info->ceiling_r;
			}
			else if (y < abs(WIN_SIZE_Y - wall_size) / 2 + wall_size)
			{
				data_addr[pixel] = get_wall_pixel_rgb(map_info, wall_image, wall_size, y, 0);
				data_addr[pixel + 1] = get_wall_pixel_rgb(map_info, wall_image, wall_size, y, 1);
				data_addr[pixel + 2] = get_wall_pixel_rgb(map_info, wall_image, wall_size, y, 2);
			}
			else
			{
				data_addr[pixel] = map_info->floor_b;
				data_addr[pixel + 1] = map_info->floor_g;
				data_addr[pixel + 2] = map_info->floor_r;
			}
		}
	}
	else
	{
		for (y = 0; y < WIN_SIZE_Y; y++)
		{
			pixel = (y * size_line) + (x * (bpp / 8));
			data_addr[pixel] = get_wall_pixel_rgb(map_info, wall_image, wall_size, y, 0);
			data_addr[pixel + 1] = get_wall_pixel_rgb(map_info, wall_image, wall_size, y, 1);
			data_addr[pixel + 2] = get_wall_pixel_rgb(map_info, wall_image, wall_size, y, 2);
		}
	}
}

static int	get_wall_size(t_map_info *map_info, double distance)
{
	double	wall_size;

	wall_size = ((WIN_SIZE_Y / distance) * R_SIZE);
	return ((int)wall_size);
}

static void	rendering_loop(void *param)
{
	t_total			*total_info;
	int				i;

	total_info = (t_total *)param;
	mlx_put_image_to_window(total_info->mlx, total_info->win,
		total_info->map_info->image, 0, 0);
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
		rotatecounterclockwise(ray_info->dir_x, ray_info->dir_y, theta,
			&ray_info->dir_x, &ray_info->dir_y);
		converttounitvector(ray_info->dir_x, ray_info->dir_y,
			&ray_info->dir_x, &ray_info->dir_y);
		plane_angle(ray_info);
	}
	else if (keycode == LEFT_ARROW_KEY)
	{
		rotateclockwise(ray_info->dir_x, ray_info->dir_y, theta,
			&ray_info->dir_x, &ray_info->dir_y);
		converttounitvector(ray_info->dir_x, ray_info->dir_y,
			&ray_info->dir_x, &ray_info->dir_y);
		plane_angle(ray_info);
	}
	ray_input_win(total_info->map_info, total_info->ray_info,
		total_info->mlx, total_info->win);
}
