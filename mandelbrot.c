/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 14:50:55 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/01/09 15:18:52 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		ft_iterate(int max_it, t_complex c)
{
	int			i;
	t_complex	tmp;
	float		x;

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

static void		ft_buff_image(t_env *e)
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
			c.x = (x - e->offset.x) * (1 / (e->zoom ));
			c.y = (y - e->offset.y) * (1 / (e->zoom ));
			i = ft_iterate(e->max_it, c);
			ft_put_pixel_to_img(&e->buffer, x, y,
				ft_tohex(i % 360, 1, 0.5 * (i < e->max_it)));
			x++;
		}
		y++;
	}
}

int				draw_mandelbrot(t_env *e)
{
	ft_buff_image(e);
	mlx_put_image_to_window(e->mlx, e->win, e->buffer.img, 0, 0);
	return (0);
}
