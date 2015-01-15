/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/13 10:12:49 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/01/14 12:11:15 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_fractoil(int max_it, t_complex z, t_complex c)
{
	int			i;
	t_complex	tmp;
	double		x;

	i = 0;
	tmp.real = z.real;
	tmp.imag = z.imag;
	while (i < max_it && (pow(tmp.real, 2) + tmp.imag * tmp.imag) < 4)
	{
		i++;
		x = tmp.real;
		tmp.real = (tmp.real + c.real - tmp.imag + c.imag) / 2;
		tmp.imag = x * 2 * (tmp.imag + tmp.imag + c.real - tmp.real) / 2;
	}
	return (i);
}

int		ft_dragon(int max_it, t_complex z, t_complex c)
{
	int			i;
	t_complex	a;
	float		x;

	(void)z;
	i = 0;
	a.real = z.real;
	a.imag = z.imag;
	while (i < max_it && (a.real * a.real + a.imag * a.imag) < 4)
	{
		i++;
		x = a.real;
		a.real = a.real * a.real * a.real -
			(3 * a.real * a.imag * a.imag) + c.real;
		a.imag = (3 * x * x * a.imag) + c.imag;
	}
	return (i);
}

int		ft_julia(int max_it, t_complex z, t_complex c)
{
	int			i;
	t_complex	tmp;
	double		x;

	i = 0;
	tmp.real = z.real;
	tmp.imag = z.imag;
	while (i < max_it && (tmp.real * tmp.real + tmp.imag * tmp.imag) < 4)
	{
		i++;
		x = tmp.real;
		tmp.real = tmp.real * tmp.real - tmp.imag * tmp.imag + c.real;
		tmp.imag = (2 * x * tmp.imag) + c.imag;
	}
	return (i);
}

int		ft_mandelbrot(int max_it, t_complex c, t_complex z)
{
	int			i;
	t_complex	tmp;
	float		x;

	(void)z;
	i = 0;
	tmp.real = 0;
	tmp.imag = 0;
	while (i < max_it && (tmp.real * tmp.real + tmp.imag * tmp.imag) < 4)
	{
		i++;
		x = tmp.real;
		tmp.real = tmp.real * tmp.real - tmp.imag * tmp.imag + c.real;
		tmp.imag = (2 * x * tmp.imag) + c.imag;
	}
	return (i);
}

void	ft_screenloop(t_env *e, t_complex z)
{
	int			i;
	int			x;
	int			y;
	t_complex	c;

	c.real = e->init.real;
	c.imag = e->init.imag;
	y = 0;
	c.real = e->init.real;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		c.imag = e->init.imag;
		while (x < WIN_WIDTH)
		{
			i = e->fractal(e->max_it, c, z);
			ft_put_pixel(&e->buffer, x, y,
				ft_tohex(i % 360, 1, 0.5 * (i < e->max_it)));
			x++;
			c.imag += e->steps.imag;
		}
		y++;
		c.real += e->steps.real;
	}
}
