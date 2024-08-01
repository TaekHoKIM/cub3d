/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:51:10 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/25 18:11:38 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

t_total	*ray_cast(t_map_info *map_info, void *mlx, void *win)
{
	t_ray_cast		*ray_info;
	t_img			*wall_image_set;
	t_total			*total;

	total = ft_malloc(sizeof(t_total), 1);
	ray_info = ft_malloc(sizeof(t_ray_cast), 1);
	map_info->image = mlx_new_image(mlx, WIN_SIZE_X, WIN_SIZE_Y);
	dir_xmp_file_to_image(mlx, map_info, &wall_image_set);
	map_info->wall_image_set = wall_image_set;
	total->map_info = map_info;
	total->ray_info = ray_info;
	total->mlx = mlx;
	total->win = win;
	ray_init(total);
	ray_input_win(total);
	mlx_put_image_to_window(total->mlx, total->win,
		total->map_info->image, 0, 0);
	return (total);
}
