/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:02 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/03 17:41:15 by taekhkim         ###   ########.fr       */
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

static double distance_point_to_line(double x, double y, double x1, double y1, double x2, double y2) {
    // 선의 방향 벡터 (x2 - x1, y2 - y1)
    double A = y2 - y1;
    double B = x1 - x2;
    double C = x2 * y1 - y2 * x1;

    // 거리 공식
    double distance = fabs(A * x + B * y + C) / sqrt(A * A + B * B);

    return distance;
}

double	distance_plane(t_ray_cast *ray_info, double x_hit, double y_hit)
{

      // 선의 방향 벡터 (x2 - x1, y2 - y1)
   
	return (distance_point_to_line(x_hit,y_hit, ray_info->pos_x, ray_info->pos_y, ray_info->pos_x - ray_info->plane_x, ray_info->pos_y + ray_info->plane_y));

}

void rotateclockwise(double a, double b, double theta, double *newX, double *newY)
{
	double	cos_theta;
	double	sin_theta;

	cos_theta = cos(theta);
	sin_theta = sin(theta);
	*newX = cos_theta * a - sin_theta * b;
	*newY = cos_theta * b + sin_theta * a;
}

// 반시계 방향으로 각도 theta 만큼 회전한 벡터를 계산하는 함수
void rotatecounterclockwise(double a, double b, double theta, double *newX, double *newY)
{
	double	cos_theta;
	double	sin_theta;

	cos_theta = cos(theta);
	sin_theta = sin(theta);
	*newX = cos_theta * a + sin_theta * b;
	*newY = -sin_theta * a + cos_theta * b;
}
