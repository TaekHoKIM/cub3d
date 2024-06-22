/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taekhkim <xorgh456@naver.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 18:56:43 by taekhkim          #+#    #+#             */
/*   Updated: 2024/06/22 16:46:15 by taekhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_PARSE_H
# define MAP_PARSE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

# define SUCCESS 0
# define FAIL -1

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
	char	**map;
}	t_map_info;

typedef struct single_node
{
	char				*map_line;
	struct single_node	*next;
}	t_node;

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

#endif