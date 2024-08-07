/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_input_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 19:29:39 by taekhkim          #+#    #+#             */
/*   Updated: 2024/07/25 17:49:32 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	input_texture_sub1(char *line, t_map_info *map_info);
static void	input_texture_sub2(char *line, t_map_info *map_info, int i);
static int	check_full_texture(t_map_info *map_info);

void	map_input_texture(int fd, t_map_info *map_info)
{
	char	*line;
	int		flag;

	flag = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (!(ft_strlen(line) == 1 && line[0] == '\n'))
		{
			input_texture_sub1(line, map_info);
			flag = 1;
		}
		else if (flag == 1)
		{
			free(line);
			break ;
		}
		free(line);
	}
	if (check_full_texture(map_info) == SUCCESS)
		return ;
	map_exit_error("map texture error\n");
}

static void	input_texture_sub1(char *line, t_map_info *map_info)
{
	int		len;

	len = ft_strlen(line);
	if (len > 3)
	{
		if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
			input_texture_sub2(line, map_info, 0);
		else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
			input_texture_sub2(line, map_info, 1);
		else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
			input_texture_sub2(line, map_info, 2);
		else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
			input_texture_sub2(line, map_info, 3);
	}
}

static void	input_texture_dir(t_map_info *map_info, char *tmp, int i)
{
	if (i == 0)
	{
		if (map_info->no_filename != NULL)
			map_exit_error("map texture error\n");
		map_info->no_filename = tmp;
	}
	else if (i == 1)
	{
		if (map_info->so_filename != NULL)
			map_exit_error("map texture error\n");
		map_info->so_filename = tmp;
	}
	else if (i == 2)
	{
		if (map_info->we_filename != NULL)
			map_exit_error("map texture error\n");
		map_info->we_filename = tmp;
	}
	else if (i == 3)
	{
		if (map_info->ea_filename != NULL)
			map_exit_error("map texture error\n");
		map_info->ea_filename = tmp;
	}
}

static void	input_texture_sub2(char *line, t_map_info *map_info, int i)
{
	char	*sub_str;
	char	*tmp;
	int		len;

	len = ft_strlen(line);
	sub_str = ft_substr(line, 3, len - 4);
	tmp = ft_strtrim(sub_str, " ");
	free(sub_str);
	input_texture_dir(map_info, tmp, i);
}

static int	check_full_texture(t_map_info *map_info)
{
	if (map_info->no_filename == NULL)
		return (FAIL);
	if (map_info->so_filename == NULL)
		return (FAIL);
	if (map_info->we_filename == NULL)
		return (FAIL);
	if (map_info->ea_filename == NULL)
		return (FAIL);
	return (SUCCESS);
}
