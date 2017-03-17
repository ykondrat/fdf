/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykondrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 15:25:54 by ykondrat          #+#    #+#             */
/*   Updated: 2017/02/16 18:07:19 by ykondrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			fdf_put_str(t_win *win)
{
	char	**array;
	char	*str;

	str = ft_strdup("Map: ");
	array = ft_strsplit(win->title, '/');
	array = ft_strsplit(array[2], '.');
	str = ft_strjoin(str, array[0]);
	mlx_string_put(win->mlx, win->win, 5, 3, 0x00FF00, "Zoom in: NUM +");
	mlx_string_put(win->mlx, win->win, 5, 20, 0x00FF00, "Zoom out: NUM -");
	mlx_string_put(win->mlx, win->win, win->width - 170, 3, 0x00FF00,
			"Move: use arrows");
	mlx_string_put(win->mlx, win->win, (win->width / 2) - 50, 3, 0xFFF800, str);
	mlx_string_put(win->mlx, win->win, win->width - 170, 20, 0x00FF00,
			"To exit: esc");
	mlx_string_put(win->mlx, win->win, 5, win->height - 30, 0x00FF00,
			"Z index increment: +");
	mlx_string_put(win->mlx, win->win, 5, win->height - 47, 0x00FF00,
			"Z index decrement: -");
}

static t_point	*fdf_start_fdf(int ac, char **av)
{
	t_point		*point;
	int			fd;

	fdf_error(ac);
	fd = open(av[1], O_RDONLY);
	fdf_open_error(fd, av[1]);
	point = fdf_create_struct(fd, av[1]);
	return (point);
}

int				main(int ac, char **av)
{
	t_point	*point;
	t_win	*win;

	point = fdf_start_fdf(ac, av);
	win = fdf_create_win(point, av);
	fdf_put_str(win);
	fdf_start_draw_map(point, win);
	mlx_hook(win->win, 2, 3, &key_hook, &win);
	mlx_loop(win->mlx);
	return (0);
}
