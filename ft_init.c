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

static void	ft_init(t_env *e, char **av)
{
	e->name = av[1];
	e->max_it = 1024;
	e->zoom = 512;
	e->offset.x = WIN_WIDTH / 2;
	e->offset.y = WIN_HEIGHT / 2;
	e->mlx = mlx_init();
	if (e->mlx == NULL)
		ft_error("Failed to init mlx.");
	e->win = mlx_new_window(e->mlx, WIN_WIDTH, WIN_HEIGHT, "Fract'ol");
	if (ft_strequ("mandelbrot", av[1]))
		mlx_expose_hook(e->win, draw_mandelbrot, e);
	else if (ft_strequ("julia", av[1]))
		mlx_expose_hook(e->win, draw_julia, e);
	else if (ft_strequ("cosinus", av[1]))
		mlx_expose_hook(e->win, draw_mandelbrot, e);
	e->buffer.img = mlx_new_image(e->mlx, WIN_WIDTH, WIN_HEIGHT);
	e->buffer.data = mlx_get_data_addr(e->buffer.img, &e->buffer.bpp,
			&e->buffer.line_size, &e->buffer.endian);
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
	ft_init(&e, av);
	mlx_key_hook(e.win, keyboard_event, &e);
	mlx_mouse_hook(e.win, mouse_event, &e);
	mlx_loop(e.mlx);
	return (0);
}
