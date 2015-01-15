/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keypress.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 13:41:32 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/01/14 11:55:02 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

void	ft_inputs(int keycode, t_env *e)
{
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
		e->steps.real *= 9 / 10.0;
		e->steps.imag *= 9 / 10.0;
	}
	if (keycode == LESS)
	{
		e->steps.real *= 10 / 9.0;
		e->steps.imag *= 10 / 9.0;
	}
}

int		keyboard_event(int keycode, t_env *e)
{
	(void)e;
	if (keycode == 65307)
		exit(0);
	if (keycode == UP || keycode == DOWN || keycode == LEFT ||
		keycode == RIGHT || keycode == LESS || keycode == MORE)
		e->update = 1;
	ft_inputs(keycode, e);
	return (0);
}

void ft_inputs_mouse(int button, t_env *e)
{
	if (button == 4)
		e->steps.real *= 9 / 10.0;
		e->steps.imag *= 9 / 10.0;
	if (button == 5)
		e->steps.real *= 10 / 9.0;
		e->steps.imag *= 10 / 9.0;				

}

int		mouse_event(int button, int x, int y, t_env *e)
{
	(void)e;
	if (button == 4 || button == 5)
		e->update = 1;
	ft_inputs_mouse(button, e);
	(void)x;
	(void)y;
	return (0);
}
