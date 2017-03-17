/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykondrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/28 15:16:08 by ykondrat          #+#    #+#             */
/*   Updated: 2017/02/16 18:07:43 by ykondrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# include "mlx.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>

typedef struct		s_point
{
	int				x;
	int				x1;
	int				y;
	int				y1;
	int				z;
	int				color;
	struct s_point	*next;
}					t_point;

typedef struct		s_win
{
	void			*mlx;
	void			*win;
	int				width;
	int				height;
	double			step;
	int				space_x;
	int				space_y;
	char			*title;
	t_point			*point;
}					t_win;

typedef struct		s_pix
{
	int				x0;
	int				x1;
	int				y0;
	int				y1;
	int				color;
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				e0;
	int				e1;
}					t_pix;

void				fdf_error(int ac);
void				fdf_open_error(int fd, char *file_name);
void				fdf_file_error(void);
void				fdf_close_error(char *file_name);
t_point				*fdf_create_struct(int fd, char *file_name);
t_win				*fdf_create_win(t_point *point, char **av);
int					fdf_valid_struct_count_y(t_point *point);
int					fdf_count_x(t_point *point);
void				fdf_valid_line(char *line);
void				fdf_valid_struct(t_point *point);
int					ft_atoi_base(char *str, int str_base, int i, int res);
int					key_hook(int keycode, t_win **win);
void				fdf_start_draw_map(t_point *point, t_win *win);
void				fdf_draw_line(t_point *tmp, t_point *buf, t_win *win);
void				fdf_clear_win(t_win *win);
void				fdf_put_str(t_win *win);

#endif
