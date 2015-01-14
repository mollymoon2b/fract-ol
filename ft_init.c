/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 14:18:50 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/01/14 12:12:00 by ade-bonn         ###   ########.fr       */
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
	else if (ft_strequ("fractoil", e->name))
		ft_init_fractoil(e);
	e->buffer.img = mlx_new_image(e->mlx, WIN_WIDTH, WIN_HEIGHT);
	e->buffer.data = mlx_get_data_addr(e->buffer.img, &e->buffer.bpp,
			&e->buffer.line_size, &e->buffer.endian);
	e->pastpos.imag = 0;
	e->pastpos.real = 0;
}

int			expose_hook(t_env *e)
{
	ft_screenloop(e, e->z);
	mlx_put_image_to_window(e->mlx, e->win, e->buffer.img, 0, 0);
	return (0);
}

void		ft_error(char *s)
{
	ft_putendl_fd(s, 2);
	exit(1);
}

int			mousemotion(int x, int y, t_env *e)
{
//	printf("X = %i, Y = %i\n", x, y);
//	printf("Past : Imag = %f, Real = %f\n", e->z.imag, e->z.real);
	e->z.imag += (x - e->pastpos.imag) / WIN_WIDTH;
	e->z.real += (y - e->pastpos.real) / WIN_HEIGHT;
	e->pastpos.imag = x;
	e->pastpos.real = y;
	e->update = 1;
//	printf("Trying to update\n");
//	printf("New  : Imag = %f, Real = %f\n", e->z.imag, e->z.real);
	return (0);
	// mlx_hook(e.win, MotionNotify, PointerMotionMask, &edit, &e);
	e++;
	x++;
	y++;
//	button++;
}

int		ft_refresh(t_env *e)
{
	if (e->update)
    {
        printf("Updating\n");
		ft_setinit(e);
        ft_screenloop(e, e->z);
        mlx_put_image_to_window(e->mlx, e->win, e->buffer.img, 0, 0);
		e->update = 0;
	}
	return (0);
}

int			main(int ac, char **av)
{
	t_env	*e;

	if (ac < 2)
		ft_error("Specify a fractal: mandelbrot, julia or fractoil.");
	else if (ac > 2)
		ft_error("Specify a valid fractal: mandelbrot, julia or fractoil.");
	if (!(ft_strequ("mandelbrot", av[1]) || ft_strequ("julia", av[1]) ||
			ft_strequ("fractoil", av[1])))
		ft_error("Specify a valid fractal: mandelbrot, julia or fractoil.");
	e = (t_env *)ft_memalloc(sizeof(t_env));
	e->name = av[1];
	ft_init(e);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_key_hook(e->win, keyboard_event, e);
	mlx_hook(e->win, MotionNotify, PointerMotionMask, &mousemotion, e);
	mlx_loop_hook(e->mlx, &ft_refresh, e);
	mlx_loop(e->mlx);
	return (0);
}
