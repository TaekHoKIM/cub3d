/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_to_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 21:19:00 by minyekim          #+#    #+#             */
/*   Updated: 2024/07/05 20:31:08 by taekhkim         ###   ########.fr       */
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

static void	xpm_file_square_check(char *file_name, t_img *img)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file_name, O_RDONLY);
	if (fd == FAIL)
		exit(EXIT_FAILURE);
	img->width = -1;
	img->height = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		i = 0;
		while (line[i] != '\0')
			i++;
		if (img->width == -1)
			img->width = i;
		if (img->width != i)
				exit(EXIT_FAILURE);
		img->height++;
	}
	if (img->width != img->height)
		exit(EXIT_FAILURE);
}

void	dir_xmp_file_to_image(void *mlx_ptr, t_map_info *info, t_img **img)
{
	*img = malloc(sizeof(t_img) * 4);
	if (*img == NULL)
		exit(EXIT_FAILURE);
	// xpm_file_square_check(info->no_filename, &((*img)[NO]));
	xpm_to_image(mlx_ptr, &((*img)[NO]), info->no_filename);
	(*img)[NO].type = NO;
	// xpm_file_square_check(info->no_filename, &((*img)[SO]));
	xpm_to_image(mlx_ptr, &((*img)[SO]), info->so_filename);
	(*img)[SO].type = SO;
	// xpm_file_square_check(info->no_filename, &((*img)[WE]));
	xpm_to_image(mlx_ptr, &((*img)[WE]), info->we_filename);
	(*img)[WE].type = WE;
	// xpm_file_square_check(info->no_filename, &((*img)[EA]));
	xpm_to_image(mlx_ptr, &((*img)[EA]), info->ea_filename);
	(*img)[EA].type = EA;
}