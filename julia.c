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

static int		ft_iterate_julia(int max_it, t_complex z, t_complex c)
{
	int			i;
	t_complex	tmp;
	float		x;

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

static void		ft_buff_image_julia(t_env *e, t_complex z)
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
			i = ft_iterate_julia(e->max_it, c, z);
			ft_put_pixel_to_img(&e->buffer, x, y,
				ft_tohex(i % 360, 1, 0.5 * (i < e->max_it)));
			x++;
		}
		y++;
	}
}

int				draw_julia(t_env *e)
{
	t_complex	z;
	static int init = 0;

	if (init == 0)
	{
		e->zoom = 512;
		init = 1;
	}
	z.x = 0.32;
	z.y = 0.043;
	e->zoom = 80;
	ft_buff_image_julia(e, z);
	mlx_put_image_to_window(e->mlx, e->win, e->buffer.img, 0, 0);
	return (0);
}
