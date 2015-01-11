/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keypress.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 13:41:32 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/01/09 15:20:39 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_error(char *s)
{
	ft_putendl_fd(s, 2);
	exit(1);
}

int		ft_exposehook(t_env *e)
{
	mlx_put_image_to_window(e->mlx, e->win, e->buffer.img, 0, 0);
	return (0);
}

int		keyboard_event(int keycode, t_env *e)
{
	(void)e;
	if (keycode == 65307)
		exit(0);
	return (0);
}

int		mouse_event(int button, int x, int y, t_env *e)
{
	(void)e;
	(void)button;
	(void)x;
	(void)y;
	return (0);
}
