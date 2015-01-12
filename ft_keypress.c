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
#include <stdio.h>

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

void	ft_setinit(t_env *e)
{
	e->init.real = e->center.real - WIN_HEIGHT / 2 * e->steps.real;
	e->init.imag = e->center.imag - WIN_WIDTH / 2 * e->steps.imag;
}

int		keyboard_event(int keycode, t_env *e)
{
	int update;
	update = 0;
	(void)e;
	if (keycode == 65307)
		exit(0);
	if (keycode == UP || keycode == DOWN || keycode == LEFT || keycode == RIGHT ||
		keycode == LESS || keycode == MORE)
		update = 1;
	if (keycode == UP)
		e->center.real -= e->steps.real * (WIN_WIDTH / 10);
	if (keycode == DOWN)
		e->center.real += e->steps.real * (WIN_WIDTH / 10);
	if (keycode == LEFT)
		e->center.imag -= e->steps.imag * (WIN_HEIGHT / 10);
	if (keycode == RIGHT)
		e->center.imag += e->steps.imag * (WIN_HEIGHT / 10);
	if (keycode == MORE)
	{
		printf("More\n");
		e->steps.real *= 9 / 10.0;
		e->steps.imag *= 9 / 10.0;
	}
	if (keycode == LESS)
	{
		printf("Less\n");
		e->steps.real *= 10 / 9.0;
		e->steps.imag *= 10 / 9.0;
	}
	if (update)
	{
		ft_setinit(e);
		ft_screenloop(e, e->z);
		// printf("Center x = %f, center y = %f\n", e->init.imag, e->init.real);
		// printf("Steps x = %f, steps y = %f\n", e->steps.imag, e->steps.real);
		mlx_put_image_to_window(e->mlx, e->win, e->buffer.img, 0, 0);
	}
	return (0);

	// int update;

	// update = 0;
	// (void)e;
	// if (keycode == 65307)
	// 	exit(0);
	// if (keycode == 65362)
	// {
	// 	e->offset.y += e->zoom / 8;
	// 	update = 1;
	// }
	// if (keycode == 65364)
	// {
	// 	e->offset.y -= e->zoom / 8;
	// 	update = 1;
	// }
	// if (keycode == 65361)
	// {
	// 	e->offset.x += e->zoom / 8;
	// 	update = 1;
	// }
	// if (keycode == 65363)
	// {
	// 	e->offset.x -= e->zoom / 8;
	// 	update = 1;
	// }
	// if (keycode == 45)
	// {
	// 	e->zoom *= 9 / 10.0;
	// 	update = 1;
	// }
	// if (keycode == 61)
	// {
	// 	e->zoom *= 10 / 9.0;
	// 	update = 1;
	// }
	// if (update)
	// {
	// 	printf("Updating\n");
	// 	ft_screenloop(e, e->z);
	// 	mlx_put_image_to_window(e->mlx, e->win, e->buffer.img, 0, 0);
	// }
	// return (0);
}

int		mouse_event(int button, int x, int y, t_env *e)
{
	(void)e;
	(void)button;
	(void)x;
	(void)y;
	return (0);
}
