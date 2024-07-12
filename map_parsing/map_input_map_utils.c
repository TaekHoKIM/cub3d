/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_input_map_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minyekim <minyekim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:14:36 by minyekim          #+#    #+#             */
/*   Updated: 2024/07/10 18:24:54 by minyekim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static void	input_node(t_node *start, char *line)
{
	t_node	*tmp;
	t_node	*new_node;

	tmp = start;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	new_node = (t_node *)malloc(sizeof(t_node));
	new_node->map_line = line;
	new_node->next = NULL;
	tmp->next = new_node;
	return ;
}

static int	check_valid_line(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (!(line[i] == ' ' || line[i] == '0' || line[i] == '1'))
			if (!(line[i] == 'N' || line[i] == 'S'
					|| (line[i] == 'E') || line[i] == 'W'))
				return (FAIL);
		if (flag == 0 && (line[i] == '0' || line[i] == '1'))
			flag = 1;
		i++;
	}
	if (flag == 0)
		return (FAIL);
	return (SUCCESS);
}

int	check_valid_and_input(t_node **start, char *line)
{
	if (check_valid_line(line) == FAIL)
	{
		free(line);
		return (FAIL);
	}
	if ((*start) == NULL)
	{
		(*start) = (t_node *)malloc(sizeof(t_node));
		(*start)->map_line = line;
		(*start)->next = NULL;
	}
	else
		input_node((*start), line);
	return (SUCCESS);
}
