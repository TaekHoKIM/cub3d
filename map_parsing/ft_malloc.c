/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 18:25:31 by minyekim          #+#    #+#             */
/*   Updated: 2024/07/22 18:26:31 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	*ft_malloc(size_t size, size_t cnt)
{
	void	*tmp;

	tmp = malloc(size * cnt);
	if (tmp == NULL)
		exit(EXIT_FAILURE);
	return (tmp);
}
