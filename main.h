/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:56:43 by taekhkim          #+#    #+#             */
/*   Updated: 2024/06/26 19:32:50 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include "./mlx/mlx.h"
# include <math.h>

# define SUCCESS 0
# define FAIL -1
# define DIR_DIS 1
# define PLANE_DIS 1
# define WIN_SIZE_X 1000
# define WIN_SIZE_Y 500

typedef struct s_node
{
	int				fd;
	char			*content;
	ssize_t			len;
	ssize_t			idx;
	struct s_node	*next;
}	t_temp;

typedef struct map_info
{
	char	*no_filename;
	char	*so_filename;
	char	*we_filename;
	char	*ea_filename;
	int		floor_r;
	int		floor_g;
	int		floor_b;
	int		ceiling_r;
	int		ceiling_g;
	int		ceiling_b;
	int		s_x;
	int		s_y;
	char	s_dir;
	int		map_size_x;
	int		map_size_y;
	char	**map;
}	t_map_info;

typedef struct single_node
{
	char				*map_line;
	struct single_node	*next;
}	t_node;

typedef struct ray_cast
{
	double	pos_x;			// 내 위치
	double	pos_y;
	double	dir_x;			// 바라보는 방향
	double	dir_y;
	double	plane_x;		// 시야 평면 방향
	double	plane_y;

}	t_ray_cast;

// map_parsing.dir -------------------------------------
// get_next_line_bonus.c
char		*get_next_line(int fd);
char		*result(t_temp *c_node, t_temp **start, char *restr);
size_t		check_next(char *s, ssize_t idx, ssize_t len);
char		*ft_strcat(char *s1, char *s2);
char		*substr(char *s, ssize_t start, ssize_t len);

// get_next_line_utils_bonus.c
t_temp		*new_node(int fd);
int			content_change(t_temp *node);
void		*remove_target(t_temp **start, t_temp *target, char *restr);
t_temp		*current_temp(t_temp *start, int fd);
int			check(t_temp **start, t_temp *c_node, char *restr);

// map_parse.c
t_map_info	*map_parsing(char *map_name);
void		map_init(t_map_info *map_info);

// ft_sub.c
size_t		ft_strlen(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_atoi(const char *str);
char		*ft_strchr(const char *s, int c);

// ft_split.c
char		**ft_split(char const *s, char c);

// ft_strtrim.c
char		*ft_strtrim(char const *s1, char const *set);

// map_input_texutre.c
void		map_input_texture(int fd, t_map_info *map_info);

// map_input_rgb.c
void		map_input_rgb(int fd, t_map_info *map_info);

// map_input_map.c
void		input_map(int fd, t_map_info *map_info);

// map_make_map.c
char		**map_make_map(t_node	*start);

// map_vaild_check.c
void		map_vaild_check(char **map);

// map_parsing.dir -------------------------------------


// rat_cast
int			ray_cast(t_map_info *map_info, void	*mlx, void *win);

// ray_init.c
int			ray_init(t_map_info *map_info, t_ray_cast *ray_info);

// ray_input_win.c
void		ray_input_win(t_map_info *map_info, t_ray_cast *ray_info, void *mlx, void *win);

// math_utils.c
double		calculatedistance(double x1, double y1, double x2, double y2);
#endif