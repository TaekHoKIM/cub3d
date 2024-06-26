/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:54:09 by taekhkim          #+#    #+#             */
/*   Updated: 2024/06/26 16:59:23 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv)
{
	t_map_info	*map_info;
	void		*mlx;
	void		*win;

	mlx = mlx_init();
	win = mlx_new_window (mlx, WIN_SIZE_X, WIN_SIZE_Y, "테스트");
	if (argc != 2)
		exit(EXIT_FAILURE);
	map_info = map_parsing(argv[1]);
	ray_cast(map_info, mlx, win);
	mlx_loop(mlx);
}
