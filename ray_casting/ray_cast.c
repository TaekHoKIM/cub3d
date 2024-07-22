/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:51:10 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/22 19:27:51 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	rendering_loop(void *param);

int	ray_cast(t_map_info *map_info, void	*mlx, void *win)
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
	mlx_loop_hook(mlx, rendering_loop, (void *)total);
	mlx_hook(win, 2, 1L << 0, &handle_keyhook, (void *)total);
	return (SUCCESS);
}

static int	rendering_loop(void *param)
{
	t_total			*total_info;
	int				i;

	total_info = (t_total *)param;
	mlx_put_image_to_window(total_info->mlx, total_info->win,
		total_info->map_info->image, 0, 0);
	return (SUCCESS);
}
