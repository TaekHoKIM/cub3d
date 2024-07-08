/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_in_wall.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:42:32 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/08 16:15:52 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	get_wall_pixel_rgb(t_map_info *map_info, t_img *wall_img, int wall_size, int py, int rgb)
{
	int		x;
	int		y;
	double	k;
	int		pixel;

	if (wall_size > WIN_SIZE_Y)
	{
		k = (wall_size - WIN_SIZE_Y) / 2;
		y = (int)((wall_img->height * k) / wall_size) + \
			((py * wall_img->height) / wall_size);
	}
	else
		y = (wall_img->height * (py - abs(WIN_SIZE_Y - wall_size) / 2))
			/ wall_size;
	if (wall_img->type == NO || wall_img->type == SO)
		x = (int)((map_info->x_hit - (int)map_info->x_hit) * \
			(double)wall_img->width);
	else
		x = (int)((map_info->y_hit - (int)map_info->y_hit) * \
			(double)wall_img->width);
	pixel = (y * wall_img->size_line) + (x * (wall_img->bits_per_pixel / 8));
	if (rgb == 0)
		return (wall_img->data[pixel]);
	if (rgb == 1)
		return (wall_img->data[pixel + 1]);
	if (rgb == 2)
		return (wall_img->data[pixel + 2]);
}
