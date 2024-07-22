/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_dir_change.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 20:43:04 by minyekim          #+#    #+#             */
/*   Updated: 2024/07/22 20:50:56 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

double	wall_dir_change(t_total *total, double x_dis, double y_dis, int flag)
{
	if ((x_dis < y_dis || y_dis == FAIL) && x_dis != FAIL)
	{
		if (flag == Q1 || flag == Q4)
			total->map_info->wall_dir = WALL_W;
		else
			total->map_info->wall_dir = WALL_E;
		return (x_dis);
	}
	if (flag == Q1 || flag == Q2)
		total->map_info->wall_dir = WALL_S;
	else
		total->map_info->wall_dir = WALL_N;
	return (y_dis);
}
