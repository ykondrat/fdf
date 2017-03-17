/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_create_win.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykondrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 10:31:22 by ykondrat          #+#    #+#             */
/*   Updated: 2017/02/16 20:19:32 by ykondrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	fdf_max_z(t_point *point)
{
	t_point		*tmp;
	int			z;
	int			max;

	max = 0;
	tmp = point;
	while (tmp)
	{
		if (tmp->z < 0)
			z = tmp->z * -1;
		else
			z = tmp->z;
		if (z > max)
			max = z;
		tmp = tmp->next;
	}
	return (max);
}

static int	fdf_max_x(t_point *point)
{
	t_point		*tmp;
	int			x;

	x = 0;
	tmp = point;
	while (tmp->next)
		tmp = tmp->next;
	x = tmp->x;
	return (x);
}

static void	fdf_search_step_and_space(t_point *point, t_win **win, int y)
{
	int		x;

	x = fdf_count_x(point);
	(*win)->step = ((*win)->height) / (x + y);
	if ((*win)->height < 800)
		(*win)->step = ((*win)->height) / (x);
	(*win)->space_x = ((*win)->width / (x + y)) * y + y;
	(*win)->space_y = (*win)->height / (x + y) + 10;
	if (y < 300)
		(*win)->space_y = (*win)->height / (x + y) + y + x / 2;
}

t_win		*fdf_create_win(t_point *point, char **av)
{
	int			x;
	int			y;
	int			z;
	t_win		*win;

	if (!(win = (t_win*)malloc(sizeof(t_win))))
		return (NULL);
	if (!(win->title = ft_strjoin("fdf/", av[1])))
		return (NULL);
	y = fdf_valid_struct_count_y(point);
	x = fdf_max_x(point);
	z = fdf_max_z(point);
	win->mlx = mlx_init();
	win->width = ((x > y) ? x : y) * 10;
	(win->width < 800) ? win->width = 800 : 0;
	(win->width > 1900) ? win->width = 1900 : 0;
	win->height = (win->width * 9) / 16;
	fdf_search_step_and_space(point, &win, y);
	win->win = mlx_new_window(win->mlx, win->width, win->height, win->title);
	win->point = point;
	return (win);
}
