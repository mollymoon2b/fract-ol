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
	tmp.x = z.x;
	tmp.y = z.y;
	while (i < max_it && (tmp.x * tmp.x + tmp.y * tmp.y) < 4)
	{
		i++;
		x = tmp.x;
		tmp.x = tmp.x * tmp.x - tmp.y * tmp.y + c.x;
		tmp.y = (2 * x * tmp.y) + c.y;
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
	tmp.x = 0;
	tmp.y = 0;
	while (i < max_it && (tmp.x * tmp.x + tmp.y * tmp.y) < 4)
	{
		i++;
		x = tmp.x;
		tmp.x = tmp.x * tmp.x - tmp.y * tmp.y + c.x;
		tmp.y = (2 * x * tmp.y) + c.y;
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
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			c.x = (x - e->offset.x) * (1 / (e->zoom * 5));
			c.y = (y - e->offset.y) * (1 / (e->zoom * 5));
			i = e->fractal(e->max_it, c, z);
			ft_put_pixel_to_img(&e->buffer, x, y,
				ft_tohex(i % 360, 1, 0.5 * (i < e->max_it)));
			x++;
		}
		y++;
	}
}

int				ft_init_mandelbrot(t_env *e)
{
	e->zoom = 50;
	e->fractal = ft_mandelbrot;
	return (0);
}

int				ft_init_julia(t_env *e)
{
	e->z.x = -0.8;
	e->z.y = 0.156;
	e->zoom = 80;
	e->fractal = ft_julia;
	return (0);
}
