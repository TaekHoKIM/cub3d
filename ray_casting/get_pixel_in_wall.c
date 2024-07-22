/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_in_wall.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:42:32 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/22 19:10:50 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	get_wall_pixel_rgb(t_total *total, t_img *wall_img, int py, int rgb)
{
	int		x;
	int		y;
	double	k;
	int		pixel;

	if (wall_img->wall_size > WIN_SIZE_Y)
	{
		k = (wall_img->wall_size - WIN_SIZE_Y) / 2;
		y = (int)((wall_img->height * k) / wall_img->wall_size) + \
			((py * wall_img->height) / wall_img->wall_size);
	}
	else
		y = (wall_img->height * \
			(py - abs(WIN_SIZE_Y - wall_img->wall_size) / 2))
			/ wall_img->wall_size;
	if (wall_img->type == NO || wall_img->type == SO)
		x = (int)((total->map_info->x_hit - (int)total->map_info->x_hit) * \
			(double)wall_img->width);
	else
		x = (int)((total->map_info->y_hit - (int)total->map_info->y_hit) * \
			(double)wall_img->width);
	pixel = (y * wall_img->size_line) + (x * (wall_img->bits_per_pixel / 8));
	return (wall_img->data[pixel + rgb]);
}
