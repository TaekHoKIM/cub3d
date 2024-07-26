/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_to_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:19:00 by minyekim          #+#    #+#             */
/*   Updated: 2024/07/26 18:42:32 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	xpm_to_image(void *mlx_ptr, t_img *img, char *file_name)
{
	img->img_ptr = mlx_xpm_file_to_image(mlx_ptr, file_name,
			&(img->width), &(img->height));
	if (img->img_ptr == NULL)
		exit(EXIT_FAILURE);
	img->data = mlx_get_data_addr(img->img_ptr,
			&(img->bits_per_pixel), &(img->size_line),
			&(img->endian));
	if (img->data == NULL)
		exit(EXIT_FAILURE);
}

static void	file_check(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd == FAIL)
		map_exit_error("map texture error");
	if (close(fd) == FAIL)
		exit(EXIT_FAILURE);
}

void	dir_xmp_file_to_image(void *mlx_ptr, t_map_info *info, t_img **img)
{
	*img = ft_malloc(sizeof(t_img), 4);
	file_check(info->no_filename);
	xpm_to_image(mlx_ptr, &((*img)[NO]), info->no_filename);
	(*img)[NO].type = NO;
	file_check(info->so_filename);
	xpm_to_image(mlx_ptr, &((*img)[SO]), info->so_filename);
	(*img)[SO].type = SO;
	file_check(info->we_filename);
	xpm_to_image(mlx_ptr, &((*img)[WE]), info->we_filename);
	(*img)[WE].type = WE;
	file_check(info->ea_filename);
	xpm_to_image(mlx_ptr, &((*img)[EA]), info->ea_filename);
	(*img)[EA].type = EA;
}
