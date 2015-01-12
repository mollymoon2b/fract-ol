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
	e->mlx = mlx_init();
	if (e->mlx == NULL)
		ft_error("Failed to init mlx.");
	e->win = mlx_new_window(e->mlx, WIN_WIDTH, WIN_HEIGHT, "Fract'ol");
	if (ft_strequ("mandelbrot", e->name))
		ft_init_mandelbrot(e);
	else if (ft_strequ("julia", e->name))
		ft_init_julia(e);
	e->buffer.img = mlx_new_image(e->mlx, WIN_WIDTH, WIN_HEIGHT);
	e->buffer.data = mlx_get_data_addr(e->buffer.img, &e->buffer.bpp,
			&e->buffer.line_size, &e->buffer.endian);
}

int 	expose_hook(t_env *e)
{
	ft_screenloop(e, e->z);
	mlx_put_image_to_window(e->mlx, e->win, e->buffer.img, 0, 0);
	return (0);
}

void	ft_error(char *s)
{
	ft_putendl_fd(s, 2);
	exit(1);
}

int			main(int ac, char **av)
{
	t_env	*e;

	if (ac < 2)
		ft_error("Specify a fractal: mandelbrot, julia or cosinus.");
	else if (ac > 2)
		ft_error("Specify a valid fractal: mandelbrot, julia or cosinus.");
	if (!(ft_strequ("mandelbrot", av[1]) || ft_strequ("julia", av[1]) ||
			ft_strequ("cosinus", av[1])))
		ft_error("Specify a valid fractal: mandelbrot, julia or cosinus.");
	e = (t_env *)ft_memalloc(sizeof(t_env));
	e->name = av[1];
	ft_init(e);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_key_hook(e->win, keyboard_event, e);
	mlx_loop(e->mlx);
	return (0);
}
