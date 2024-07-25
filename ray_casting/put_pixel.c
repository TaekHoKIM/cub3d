/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:50:35 by minyekim          #+#    #+#             */
/*   Updated: 2024/07/25 17:36:51 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	get_wall_size(t_map_info *map_info, double distance)
{
	double	wall_size;

	wall_size = ((WIN_SIZE_Y / distance) * R_SIZE);
	return ((int)wall_size);
}

static t_img	*wall_dir_image(t_total *total)
{
	if (total->map_info->wall_dir == WALL_E)
		return (&(total->map_info->wall_image_set[EA]));
	else if (total->map_info->wall_dir == WALL_W)
		return (&(total->map_info->wall_image_set[WE]));
	else if (total->map_info->wall_dir == WALL_S)
		return (&(total->map_info->wall_image_set[SO]));
	else if (total->map_info->wall_dir == WALL_N)
		return (&(total->map_info->wall_image_set[NO]));
	return (NULL);
}

static void	pixel_rgb(t_total *total, t_img *img, t_data *data, int y)
{
	if (y < abs(WIN_SIZE_Y - img->wall_size) / 2)
	{
		data->addr[data->pixel] = total->map_info->ceiling_b;
		data->addr[data->pixel + 1] = total->map_info->ceiling_g;
		data->addr[data->pixel + 2] = total->map_info->ceiling_r;
	}
	else if (y < abs(WIN_SIZE_Y - img->wall_size) \
		/ 2 + img->wall_size)
	{
		data->addr[data->pixel] = get_wall_pixel_rgb(total, img, y, 0);
		data->addr[data->pixel + 1] = get_wall_pixel_rgb(total, img, y, 1);
		data->addr[data->pixel + 2] = get_wall_pixel_rgb(total, img, y, 2);
	}
	else
	{
		data->addr[data->pixel] = total->map_info->floor_b;
		data->addr[data->pixel + 1] = total->map_info->floor_g;
		data->addr[data->pixel + 2] = total->map_info->floor_r;
	}
}

static void	wall_pixel_rgb(t_total *total, t_img *img, t_data *data, int idx)
{
	int	x;
	int	y;

	x = idx;
	if (img->wall_size < WIN_SIZE_Y)
	{
		y = -1;
		while (++y < WIN_SIZE_Y)
		{
			data->pixel = (y * data->size_line) + (x * (data->bpp / 8));
			pixel_rgb(total, img, data, y);
		}
	}
	else
	{
		y = -1;
		while (++y < WIN_SIZE_Y)
		{
			data->pixel = (y * data->size_line) + (x * (data->bpp / 8));
			data->addr[data->pixel] = get_wall_pixel_rgb(total, img, y, 0);
			data->addr[data->pixel + 1] = get_wall_pixel_rgb(total, img, y, 1);
			data->addr[data->pixel + 2] = get_wall_pixel_rgb(total, img, y, 2);
		}
	}
}

void	put_pixel(t_total *total, double distance, int idx)
{
	t_data	data;
	t_img	*img;

	data.addr = mlx_get_data_addr(total->map_info->image,
			&data.bpp, &data.size_line, &data.endian);
	img = wall_dir_image(total);
	img->wall_size = get_wall_size(total->map_info, distance);
	wall_pixel_rgb(total, img, &data, idx);
}
