/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:00:39 by minyekim          #+#    #+#             */
/*   Updated: 2024/07/12 21:04:27 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	rotatecounterclockwise(double *ab, double theta,
				double *newX, double *newY)
{
	double	cos_theta;
	double	sin_theta;

	cos_theta = cos(theta);
	sin_theta = sin(theta);
	*newX = cos_theta * ab[0] + sin_theta * ab[1];
	*newY = -sin_theta * ab[0] + cos_theta * ab[1];
}

void	rotateclockwise(double *ab, double theta, double *newX, double *newY)
{
	double	cos_theta;
	double	sin_theta;

	cos_theta = cos(theta);
	sin_theta = sin(theta);
	*newX = cos_theta * ab[0] - sin_theta * ab[1];
	*newY = cos_theta * ab[1] + sin_theta * ab[0];
}
