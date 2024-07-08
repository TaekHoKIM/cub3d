/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:02 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/08 16:26:36 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

double	calculatedistance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

void	converttounitvector(double a, double b, double *unitA, double *unitB)
{
	double	magnitude;

	magnitude = sqrt(a * a + b * b);
	if (magnitude == 0)
	{
		printf("Zero vector cannot be converted to a unit vector.\n");
		*unitA = 0;
		*unitB = 0;
	}
	else
	{
		*unitA = a / magnitude;
		*unitB = b / magnitude;
	}
}

static double	distance_point_to_line(t_ray_cast *ray_info, double x, double y)
{
	double	a;
	double	b;
	double	c;
	double	distance;

	a = (ray_info->pos_y + ray_info->plane_y) - ray_info->pos_y;
	b = ray_info->pos_x - (ray_info->pos_x - ray_info->plane_x);
	c = (ray_info->pos_x - ray_info->plane_x) * ray_info->pos_y - \
		(ray_info->pos_y + ray_info->plane_y) * ray_info->pos_x;
	distance = fabs(a * x + b * y + c) / sqrt(a * a + b * b);
	return (distance);
}

double	distance_plane(t_ray_cast *ray_info, double x_hit, double y_hit)
{
	return (distance_point_to_line(ray_info, x_hit, y_hit));
}

void	rotateclockwise(double a, double b, double theta, double *newX, double *newY)
{
	double	cos_theta;
	double	sin_theta;

	cos_theta = cos(theta);
	sin_theta = sin(theta);
	*newX = cos_theta * a - sin_theta * b;
	*newY = cos_theta * b + sin_theta * a;
}

// 반시계 방향으로 각도 theta 만큼 회전한 벡터를 계산하는 함수
void	rotatecounterclockwise(double a, double b, double theta, double *newX, double *newY)
{
	double	cos_theta;
	double	sin_theta;

	cos_theta = cos(theta);
	sin_theta = sin(theta);
	*newX = cos_theta * a + sin_theta * b;
	*newY = -sin_theta * a + cos_theta * b;
}
