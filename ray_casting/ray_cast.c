/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 15:51:10 by taekhkim          #+#    #+#             */
/*   Updated: 2024/06/26 19:35:08 by minyekim         ###   ########.fr       */
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
