/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykondrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 15:54:18 by ykondrat          #+#    #+#             */
/*   Updated: 2017/02/16 18:05:59 by ykondrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		fdf_draw_line_loop(t_pix *pix, t_win *win)
{
	while (pix->x0 != pix->x1 || pix->y0 != pix->y1)
	{
		mlx_pixel_put(win->mlx, win->win, pix->x0, pix->y0, pix->color);
		pix->e1 = pix->e0 * 2;
		if (pix->e1 > -(pix->dy))
		{
			pix->e0 -= pix->dy;
			pix->x0 += pix->sx;
		}
		if (pix->e1 < pix->dx)
		{
			pix->e0 += pix->dx;
			pix->y0 += pix->sy;
		}
	}
}

void			fdf_draw_line(t_point *tmp, t_point *buf, t_win *win)
{
	t_pix *pix;

	if (!(pix = (t_pix*)malloc(sizeof(t_pix))))
		return ;
	pix->x0 = tmp->x1;
	pix->x1 = buf->x1;
	pix->y0 = tmp->y1;
	pix->y1 = buf->y1;
	pix->dx = abs(pix->x1 - pix->x0);
	pix->dy = abs(pix->y1 - pix->y0);
	pix->color = (buf->y1 <= tmp->y1 + 1) ? buf->color : tmp->color;
	pix->sx = (pix->x0 < pix->x1) ? 1 : -1;
	pix->sy = (pix->y0 < pix->y1) ? 1 : -1;
	pix->e0 = pix->dx - pix->dy;
	mlx_pixel_put(win->mlx, win->win, pix->x1, pix->y1, pix->color);
	fdf_draw_line_loop(pix, win);
}
