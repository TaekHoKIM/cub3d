/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keyhook.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 19:18:52 by minyekim          #+#    #+#             */
/*   Updated: 2024/07/22 19:32:14 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	move_side(t_total *total, int keycode)
{
	if (keycode == A_KEY)
	{
		total->ray_info->pos_x -= total->ray_info->dir_y * R_STEP;
		total->ray_info->pos_y -= total->ray_info->dir_x * R_STEP;
		if (total->map_info->map[(int)total->ray_info->pos_y] \
			[(int)total->ray_info->pos_x] == '1')
		{
			total->ray_info->pos_x += total->ray_info->dir_y * R_STEP;
			total->ray_info->pos_y += total->ray_info->dir_x * R_STEP;
		}
	}
	else if (keycode == D_KEY)
	{
		total->ray_info->pos_x += total->ray_info->dir_y * R_STEP;
		total->ray_info->pos_y += total->ray_info->dir_x * R_STEP;
		if (total->map_info->map[(int)total->ray_info->pos_y] \
			[(int)total->ray_info->pos_x] == '1')
		{
			total->ray_info->pos_x -= total->ray_info->dir_y * R_STEP;
			total->ray_info->pos_y -= total->ray_info->dir_x * R_STEP;
		}
	}
}

static void	move_up_and_down(t_total *total, int keycode)
{
	if (keycode == W_KEY)
	{
		total->ray_info->pos_x += total->ray_info->dir_x * R_STEP;
		total->ray_info->pos_y -= total->ray_info->dir_y * R_STEP;
		if (total->map_info->map[(int)total->ray_info->pos_y] \
			[(int)total->ray_info->pos_x] == '1')
		{
			total->ray_info->pos_x -= total->ray_info->dir_x * R_STEP;
			total->ray_info->pos_y += total->ray_info->dir_y * R_STEP;
		}
	}
	else if (keycode == S_KEY)
	{
		total->ray_info->pos_x -= total->ray_info->dir_x * R_STEP;
		total->ray_info->pos_y += total->ray_info->dir_y * R_STEP;
		if (total->map_info->map[(int)total->ray_info->pos_y] \
			[(int)total->ray_info->pos_x] == '1')
		{
			total->ray_info->pos_x += total->ray_info->dir_x * R_STEP;
			total->ray_info->pos_y -= total->ray_info->dir_y * R_STEP;
		}
	}
}

void	arrow_key(t_total *total, int keycode)
{
	t_ray_cast		*ray_info;
	double			theta;

	ray_info = total->ray_info;
	theta = 1.0 * M_PI / 180.0 * R_ANGLE;
	if (keycode == RIGHT_ARROW_KEY)
	{
		rotatecounterclockwise((double []){ray_info->dir_x, ray_info->dir_y},
			theta, &ray_info->dir_x, &ray_info->dir_y);
		converttounitvector(ray_info->dir_x, ray_info->dir_y,
			&ray_info->dir_x, &ray_info->dir_y);
		plane_angle(ray_info);
	}
	else if (keycode == LEFT_ARROW_KEY)
	{
		rotateclockwise((double []){ray_info->dir_x, ray_info->dir_y}, theta,
			&ray_info->dir_x, &ray_info->dir_y);
		converttounitvector(ray_info->dir_x, ray_info->dir_y,
			&ray_info->dir_x, &ray_info->dir_y);
		plane_angle(ray_info);
	}
}

int	handle_keyhook(int keycode, void *param)
{
	t_total			*total;

	total = (t_total *)param;
	if (keycode == ESC)
	{
		printf("ESC key pressed. Exiting...\n");
		exit(0);
	}
	else if (keycode == W_KEY || keycode == S_KEY)
		move_up_and_down(total, keycode);
	else if (keycode == A_KEY || keycode == D_KEY)
		move_side(total, keycode);
	else if (keycode == RIGHT_ARROW_KEY || keycode == LEFT_ARROW_KEY)
		arrow_key(total, keycode);
	ray_input_win(total);
	return (0);
}
