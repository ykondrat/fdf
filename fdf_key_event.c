/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_key_event.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykondrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/09 16:49:38 by ykondrat          #+#    #+#             */
/*   Updated: 2017/02/17 10:48:58 by ykondrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_new_step(t_win *win, int keycode)
{
	if (keycode == 69)
	{
		win->step = win->step * 1.1;
		win->space_x = win->space_x * 0.9 + 10;
		win->space_y = win->space_y * 0.9 - 10;
	}
	if (keycode == 78)
	{
		win->step = win->step * 0.9;
		win->space_x = win->space_x * 1.1 - 10;
		win->space_y = win->space_y * 1.1 + 10;
	}
}

void	fdf_clear_win(t_win *win)
{
	int		x;
	int		y;

	x = 0;
	while (x < win->width)
	{
		y = 0;
		while (y < win->height)
		{
			mlx_pixel_put(win->mlx, win->win, x, y, 0x000000);
			y++;
		}
		x++;
	}
	fdf_put_str(win);
}

void	key_move(int keycode, t_win *win)
{
	if (keycode == 123)
	{
		win->space_x = win->space_x * 0.9;
		fdf_start_draw_map(win->point, win);
	}
	if (keycode == 124)
	{
		win->space_x = win->space_x * 1.1;
		fdf_start_draw_map(win->point, win);
	}
	if (keycode == 125)
	{
		win->space_y = win->space_y * 1.1 + 10;
		fdf_start_draw_map(win->point, win);
	}
	if (keycode == 126)
	{
		win->space_y = win->space_y * 0.9 - 10;
		fdf_start_draw_map(win->point, win);
	}
}

void	key_z_index(int keycode, t_win *win)
{
	t_point *tmp;

	tmp = win->point;
	if (keycode == 27)
	{
		while (tmp)
		{
			if (tmp->z != 0)
				tmp->z -= 3;
			tmp = tmp->next;
		}
		fdf_start_draw_map(win->point, win);
	}
	if (keycode == 24)
	{
		while (tmp)
		{
			if (tmp->z != 0)
				tmp->z += 3;
			tmp = tmp->next;
		}
		fdf_start_draw_map(win->point, win);
	}
}

int		key_hook(int keycode, t_win **win)
{
	if (keycode == 53)
		exit(0);
	if (keycode == 69)
	{
		fdf_clear_win(*win);
		fdf_new_step(*win, keycode);
		fdf_start_draw_map((*win)->point, *win);
	}
	if (keycode == 78)
	{
		fdf_clear_win(*win);
		fdf_new_step(*win, keycode);
		fdf_start_draw_map((*win)->point, *win);
	}
	if (keycode == 123 || keycode == 124 || keycode == 125 || keycode == 126)
	{
		fdf_clear_win(*win);
		key_move(keycode, *win);
	}
	if (keycode == 27 || keycode == 24)
	{
		fdf_clear_win(*win);
		key_z_index(keycode, *win);
	}
	return (0);
}
