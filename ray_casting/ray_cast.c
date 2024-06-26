/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:51:10 by taekhkim          #+#    #+#             */
/*   Updated: 2024/06/26 17:39:52 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

int	ray_cast(t_map_info *map_info, void	*mlx, void *win)
{
	t_ray_cast	ray_info;

	ray_init(map_info, &ray_info);
	ray_input_win(map_info, &ray_info, mlx, win);
	return (SUCCESS);
}



