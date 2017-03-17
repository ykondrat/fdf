/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykondrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 12:53:01 by ykondrat          #+#    #+#             */
/*   Updated: 2017/02/16 18:05:38 by ykondrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		fdf_set_z_and_color(t_point **point, char **str, int i)
{
	if (i == 1)
	{
		(*point)->z = ft_atoi(str[0]);
		(*point)->color = ft_atoi_base(str[1] + 2, 16, 0, 0);
	}
	else
	{
		(*point)->z = ft_atoi(str[0]);
		(*point)->color = ft_atoi_base("FFFFFF", 16, 0, 0);
	}
}

static void		free_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

static void		free_last_struct(t_point **point)
{
	t_point *tmp;
	t_point	*last;

	tmp = *point;
	while (tmp->next)
	{
		last = tmp;
		tmp = tmp->next;
	}
	free(tmp);
	last->next = NULL;
}

static t_point	*fdf_setcord_color(char *line, t_point *point, int y)
{
	char		**str_x;
	char		**str_color;
	int			i;

	i = 0;
	str_x = ft_strsplit(line, ' ');
	while (str_x[i])
	{
		point->y = y;
		point->x = i;
		str_color = ft_strsplit(str_x[i], ',');
		if (str_color[1])
			fdf_set_z_and_color(&point, str_color, 1);
		else
			fdf_set_z_and_color(&point, str_color, 0);
		if (!(point->next = (t_point*)malloc(sizeof(t_point))))
			return (NULL);
		point = point->next;
		free_array(str_color);
		i++;
	}
	free_array(str_x);
	return (point);
}

t_point			*fdf_create_struct(int fd, char *file_name)
{
	t_point		*point;
	t_point		*tmp;
	int			y;
	char		*line;

	if (!(point = (t_point*)malloc(sizeof(t_point))))
		return (NULL);
	tmp = point;
	y = 0;
	while (get_next_line(fd, &line) == 1)
	{
		fdf_valid_line(line);
		tmp = fdf_setcord_color(line, tmp, y);
		if (!(tmp->next = (t_point*)malloc(sizeof(t_point))))
			return (NULL);
		free(line);
		y++;
	}
	tmp->next = NULL;
	free_last_struct(&point);
	fdf_valid_struct(point);
	if (close(fd) == -1)
		fdf_close_error(file_name);
	return (point);
}
