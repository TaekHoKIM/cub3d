/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 17:20:02 by taekhkim          #+#    #+#             */
/*   Updated: 2024/06/27 19:52:55 by taekhkim         ###   ########.fr       */
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
