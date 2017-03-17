/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykondrat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 13:50:14 by ykondrat          #+#    #+#             */
/*   Updated: 2017/02/16 18:07:03 by ykondrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_error(int ac)
{
	if (ac != 2)
	{
		ft_putendl("\x1b[31m\tusage: ./fdf [file name]");
		exit(0);
	}
}

void	fdf_open_error(int fd, char *file_name)
{
	if (fd < 0)
	{
		ft_putstr("\x1b[31m\topen() error with file: ");
		ft_putendl(file_name);
		exit(0);
	}
}

void	fdf_file_error(void)
{
	ft_putendl("\x1b[31m\terror: file not valid");
	exit(0);
}

void	fdf_close_error(char *file_name)
{
	ft_putstr("\x1b[31m\tclose() error with file: ");
	ft_putendl(file_name);
	exit(0);
}
