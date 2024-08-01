/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:54:09 by taekhkim          #+#    #+#             */
/*   Updated: 2024/08/01 12:49:13 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int	exit_cross(void)
{
	exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	t_map_info	*map_info;
	t_total		*total;
	void		*mlx;
	void		*win;

	if (argc != 2)
		exit(EXIT_FAILURE);
	map_info = map_parsing(argv[1]);
	mlx = mlx_init();
	win = mlx_new_window (mlx, WIN_SIZE_X, WIN_SIZE_Y, "cub3D");
	total = ray_cast(map_info, mlx, win);
	mlx_hook(win, CLICK_CROSS, 0, exit_cross, NULL);
	mlx_hook(win, 2, 1L << 0, &handle_keyhook, (void *)total);
	mlx_loop(mlx);
}
