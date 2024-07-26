/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:54:09 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/25 18:11:43 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int	main(int argc, char **argv)
{
	t_map_info	*map_info;
	void		*mlx;
	void		*win;

	mlx = mlx_init();
	win = mlx_new_window (mlx, WIN_SIZE_X, WIN_SIZE_Y, "cub3d");
	if (argc != 2)
		exit(EXIT_FAILURE);
	map_info = map_parsing(argv[1]);
	ray_cast(map_info, mlx, win);
}
