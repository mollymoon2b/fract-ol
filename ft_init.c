/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 14:18:50 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/01/09 15:35:31 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	ft_init(t_env *e)
{
	e->max_it = 250;
	e->offset.x = WIN_WIDTH / 2;
	e->offset.y = WIN_HEIGHT / 2;
	e->mlx = mlx_init();
	if (e->mlx == NULL)
		ft_error("Failed to init mlx.");
	e->win = mlx_new_window(e->mlx, WIN_WIDTH, WIN_HEIGHT, "Fract'ol");
	if (ft_strequ("mandelbrot", e->name))
		e->function = draw_mandelbrot;
	else if (ft_strequ("julia", e->name))
		e->function = draw_julia;
	else if (ft_strequ("cosinus", e->name))
		e->function = draw_mandelbrot;
	e->buffer.img = mlx_new_image(e->mlx, WIN_WIDTH, WIN_HEIGHT);
	e->buffer.data = mlx_get_data_addr(e->buffer.img, &e->buffer.bpp,
			&e->buffer.line_size, &e->buffer.endian);
}

int 	expose_hook(t_env *e)
{
	e->function(e);
	return (0);
}

int			main(int ac, char **av)
{
	t_env	e;

	if (ac < 2)
		ft_error("Specify a fractal: mandelbrot, julia or cosinus.");
	else if (ac > 2)
		ft_error("Specify a valid fractal: mandelbrot, julia or cosinus.");
	if (!(ft_strequ("mandelbrot", av[1]) || ft_strequ("julia", av[1]) ||
			ft_strequ("cosinus", av[1])))
		ft_error("Specify a valid fractal: mandelbrot, julia or cosinus.");
	e.name = av[1];
	ft_init(&e);
	mlx_expose_hook(e.win, expose_hook, &e);
	mlx_key_hook(e.win, keyboard_event, &e);
	mlx_loop(e.mlx);
	return (0);
}
