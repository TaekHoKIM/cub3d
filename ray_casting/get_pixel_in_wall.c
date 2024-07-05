/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixel_in_wall.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 18:42:32 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/05 20:21:07 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	get_wall_pixel_rgb(t_map_info *map_info, t_img *wall_img, int wall_size, int py, int rgb)
{
	int		x;
	int		y;
	double	k;
	int		pixel;
	// y는 wall_size에 비례해서 만들어야 함
	// x가 hit 위치에 따라 만들어야 됨
	if (wall_size > WIN_SIZE_Y)				// wall_size가 화면 넘어갈때 -> 위 아래 짤라야 함
	{
		k = (wall_size - WIN_SIZE_Y) / 2;
		y = (int)((wall_img->height * k) / wall_size) + ((py * wall_img->height)/ wall_size);
	}
	else									// wall_size가 화면 안넘어갈때 -> image의 모든 y가 출려되어야 함
	{
		y = (wall_img->height * (py - abs(WIN_SIZE_Y - wall_size) / 2)) / wall_size;
	}
	if (wall_img->type == NO || wall_img->type == SO)		// 맞은 벽인 north or south -> map_info->x_hit 사용
	{
		x = (int)((map_info->x_hit - (int)map_info->x_hit) * (double)wall_img->width);
	}
	else													// 맞은 벽인 east or west -> map_info->y_hit 사용
	{
		x = (int)((map_info->y_hit - (int)map_info->y_hit) * (double)wall_img->width);
	}
	pixel = (y * wall_img->size_line) + (x * (wall_img->bits_per_pixel / 8));	// 해당하는 image pixel
	if (rgb == 0)
		return (wall_img->data[pixel]);
	if (rgb == 1)
		return (wall_img->data[pixel + 1]);
	if (rgb == 2)
		return (wall_img->data[pixel + 2]);
}