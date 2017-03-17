/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykondrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 17:19:39 by ykondrat          #+#    #+#             */
/*   Updated: 2017/02/16 18:04:47 by ykondrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fdf_valid_struct_count_x(t_point *point)
{
	t_point		*tmp;
	int			x;

	x = 0;
	tmp = point;
	while (tmp->y == 0)
	{
		x = x + tmp->x;
		tmp = tmp->next;
	}
	return (x);
}

int			fdf_count_x(t_point *point)
{
	t_point		*tmp;
	int			x;

	x = 0;
	tmp = point;
	while (tmp->y == 0)
	{
		x++;
		tmp = tmp->next;
	}
	return (x);
}

int			fdf_valid_struct_count_y(t_point *point)
{
	t_point		*tmp;
	int			y;

	y = 0;
	tmp = point;
	while (tmp->next)
		tmp = tmp->next;
	y = tmp->y;
	return (y);
}

void		fdf_valid_struct(t_point *point)
{
	t_point	*tmp;
	int		res;
	int		x;
	int		i;
	int		y;

	i = 0;
	x = fdf_valid_struct_count_x(point);
	y = fdf_valid_struct_count_y(point);
	tmp = point;
	while (y > i)
	{
		res = 0;
		while (tmp->y == i)
		{
			res = res + tmp->x;
			tmp = tmp->next;
		}
		if (res != x)
			fdf_file_error();
		i++;
	}
}

void		fdf_valid_line(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if ((line[i] >= 48 && line[i] <= 57) || line[i] == 32 || line[i] == 44
				|| line[i] == 120 || (line[i] >= 65 && line[i] <= 70)
				|| (line[i] >= 97 && line[i] <= 102) || line[i] == 45)
			i++;
		else
			fdf_file_error();
	}
	i = 0;
	while (line[i])
	{
		if (line[i] == 44)
			if (line[i + 1] != 48 && line[i + 2] != 120 &&
					(line[i - 1] < 48 && line[i - 1] > 57))
				fdf_file_error();
		i++;
	}
}
