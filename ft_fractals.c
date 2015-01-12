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
	// if (i)
		// printf("Color = %i\n", i);
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

	// e->init.real = 0;
	// e->init.imag = 0;
	// e->steps.real = 0.002497;
	// e->steps.imag = 0.002497;

	c.real = e->init.real;
	c.imag = e->init.imag;

	// x = 0;
	// y = 0;
	// c.imag = (x - e->offset.x) * (1 / (e->zoom * 5));
	// c.real = (y - e->offset.y) * (1 / (e->zoom * 5));
	printf("Init x = %f, init y = %f\n", c.imag, c.real);
	// printf("Steps x = %f, steps y = %f\n", e->steps.imag, e->steps.real);
	y = 0;
	c.real = e->init.real;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		c.imag = e->init.imag;
		while (x < WIN_WIDTH)
		{
			// c.imag = (x - e->offset.x) * (1 / (e->zoom * 5));
			// c.real = (y - e->offset.y) * (1 / (e->zoom * 5));
			i = e->fractal(e->max_it, c, z);
			ft_put_pixel_to_img(&e->buffer, x, y,
				ft_tohex(i % 360, 1, 0.5 * (i < e->max_it)));
			x++;
			c.imag += e->steps.imag;
		}
		y++;
		c.real += e->steps.real;
	}
	printf("Max x = %f, max y = %f\n", c.imag / 2, c.real / 2);
	printf("Steps x = %f, steps y = %f\n", c.imag / WIN_HEIGHT, c.real / WIN_HEIGHT);
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
	e->max_it = 10000;
	e->z.imag = -0.70176;
	e->z.real = -0.3842;
	e->steps.real = 0.002497;
	e->steps.imag = 0.002497;
	e->center.real = 1.872750;
	e->center.imag = 1.248500;
	ft_setinit(e);
	e->fractal = ft_julia;
	return (0);

	e->z.imag = -0.70176;
	e->z.real = -0.3842;
	e->max_it = 10000;
	e->zoom = 80;
	e->fractal = ft_julia;
	return (0);
}
