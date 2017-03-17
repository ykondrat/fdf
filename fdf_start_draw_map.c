/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_start_draw_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykondrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 15:22:58 by ykondrat          #+#    #+#             */
/*   Updated: 2017/03/16 18:57:41 by ykondrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	fdf_transfer_list(t_point **point, t_win *win)
{
	t_point	*tmp;
	int		x;
	int		y;
	int		width;
	int		hight;

	width = 0;
	hight = 0;
	tmp = *point;
	while (tmp)
	{
		x = tmp->x + width;
		y = tmp->y + hight;
		width = width + win->step;
		if (tmp->next && (tmp->next->x < tmp->x))
		{
			hight = hight + win->step;
			width = 0;
		}
		tmp->x1 = (x - y) + win->space_x;
		tmp->y1 = ((x + y) / 2) - tmp->z + win->step + win->space_y;
		tmp = tmp->next;
	}
}

static void	fdf_put_horizontal_line(t_point *point, t_win *win)
{
	t_point *tmp;

	tmp = point;
	while (tmp->next)
	{
		if (tmp->x1 > tmp->next->x1)
			tmp = tmp->next;
		fdf_draw_line(tmp, tmp->next, win);
		tmp = tmp->next;
	}
}

static void	fdf_put_vertical_line(t_point *point, t_win *win)
{
	t_point	*tmp;
	t_point	*buf;

	tmp = point;
	buf = tmp->next;
	while (buf->next)
	{
		while ((tmp->x1 < buf->x1) && buf->next)
			buf = buf->next;
		while (buf->next && (buf->next->x1 < tmp->x1)
				&& (buf->next->x1 > buf->x1))
			buf = buf->next;
		fdf_draw_line(tmp, buf, win);
		if (buf->next)
		{
			tmp = tmp->next;
			buf = tmp->next;
		}
	}
}

void		fdf_start_draw_map(t_point *point, t_win *win)
{
	fdf_transfer_list(&point, win);
	fdf_put_horizontal_line(point, win);
	fdf_put_vertical_line(point, win);
}
