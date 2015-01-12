/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 16:01:49 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/01/11 16:01:49 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

	z = z;
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

void		ft_screenloop(t_env *e, t_complex z)
{
	int			i;
	int			x;
	int			y;
	t_complex	c;

	y = 0;
	c.real = e->init.real;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		c.imag = e->init.imag;
		while (x < WIN_WIDTH)
		{
			// c.real = (x - e->offset.x) * (1 / (e->zoom * 5));
			// c.imag = (y - e->offset.y) * (1 / (e->zoom * 5));
			c.imag += e->steps.imag;
			i = e->fractal(e->max_it, c, z);
			ft_put_pixel_to_img(&e->buffer, x, y,
				ft_tohex(i % 360, 1, 0.5 * (i < e->max_it)));
			x++;
		}
		y++;
		c.real += e->steps.real;
	}
}

int				ft_init_mandelbrot(t_env *e)
{
	e->steps.real = 0.01;
	e->steps.imag = 0.01;
	e->center.real = 0;
	e->center.imag = 0;
	ft_setinit(e);
	e->fractal = ft_mandelbrot;
	return (0);
}

int				ft_init_julia(t_env *e)
{
	e->z.real = -0.8;
	e->z.imag = 0.156;
	e->steps.real = 0.01;
	e->steps.imag = 0.01;
	e->center.real = 0;
	e->center.imag = 0;
	ft_setinit(e);
	e->fractal = ft_julia;
	return (0);
}
