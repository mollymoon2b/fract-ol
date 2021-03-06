/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 13:40:37 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/01/13 09:45:18 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_color	ft_get_color(char r, char g, char b)
{
	t_color c;

	c.rgb[3] = 0;
	c.rgb[2] = r;
	c.rgb[1] = g;
	c.rgb[0] = b;
	return (c);
}

void	ft_put_pixel(t_buffer *buffer, int x, int y, t_color color)
{
	int		octet;
	char	*position;

	octet = buffer->line_size / WIN_WIDTH;
	if (y > 0)
		y -= 1;
	position = buffer->data + (buffer->line_size * y) + (x * octet);
	*(position) = color.rgb[0];
	*(position + 1) = color.rgb[1];
	*(position + 2) = color.rgb[2];
}

void	ft_setinit(t_env *e)
{
	e->init.real = e->center.real - WIN_HEIGHT / 2 * e->steps.real;
	e->init.imag = e->center.imag - WIN_WIDTH / 2 * e->steps.imag;
}

t_color	ft_tohex(int h, float s, float l)
{
	t_color	color;
	float	c;
	float	x;
	float	m;

	c = (1.0 - fabs(2 * l - 1.0)) * s;
	x = c * (1.0 - fabs(fmod((h / 60.0), 2) - 1.0));
	m = l - 0.5 * c;
	if (h >= 0 && h < 360)
		return (ft_get_color((c + m) * 255, (x + m) * 255, (0 + m) * 255));
	color.rgb[0] = 0;
	color.rgb[1] = 0;
	color.rgb[2] = 0;
	color.rgb[3] = 0;
	return (color);
}

void	ft_error(char *s)
{
	ft_putendl_fd(s, 2);
	exit(1);
}
