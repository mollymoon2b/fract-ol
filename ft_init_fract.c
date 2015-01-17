/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_fract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 12:22:36 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/01/17 14:41:33 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_init_mandelbrot(t_env *e)
{
	e->max_it = 100;
	e->steps.real = 0.007;
	e->steps.imag = 0.007;
	e->center.real = -0.8;
	e->center.imag = 0;
	ft_setinit(e);
	e->fractal = ft_mandelbrot;
	return (0);
}

int		ft_init_julia(t_env *e)
{
	e->max_it = 50;
	e->z.imag = -0.65186;
	e->z.real = -0.0986;
	e->steps.real = 0.001;
	e->steps.imag = 0.001;
	e->center.real = 0;
	e->center.imag = 0;
	ft_setinit(e);
	e->fractal = ft_julia;
	return (0);
}

int		ft_init_fractoil(t_env *e)
{
	e->max_it = 100;
	e->z.imag = -0.75;
	e->z.real = -0.00;
	e->steps.real = 0.01;
	e->steps.imag = 0.01;
	e->center.real = 0;
	e->center.imag = 0;
	ft_setinit(e);
	e->fractal = ft_fractoil;
	return (0);
}

int		ft_init_dragon(t_env *e)
{
	e->max_it = 100;
	e->z.imag = -0.45186;
	e->z.real = -0.0984651;
	e->steps.real = 0.01;
	e->steps.imag = 0.01;
	e->center.real = 0;
	e->center.imag = 0;
	ft_setinit(e);
	e->fractal = ft_dragon;
	return (0);
}
