/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 13:40:37 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/01/09 15:19:17 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_get_color(t_color *c, char r, char g, char b)
{
	c->rgb[0] = b;
	c->rgb[1] = g;
	c->rgb[2] = r;
	c->rgb[3] = 0;
}

void	ft_put_pixel_to_img(t_buffer *buffer, int x, int y, int color)
{
	int	octet;
	int	position;

	octet = buffer->line_size / WIN_WIDTH;
	if (y > 0)
		y -= 1;
	position = (buffer->line_size * y) + (x * octet);
	if (ft_memcmp(buffer->data + position, &color, octet) != 0)
		ft_memcpy(buffer->data + position, &color, octet);
}

int		ft_tohex(int h, float s, float l)
{
	t_color	color;
	float	c;
	float	x;
	float	m;

	c = (1.0 - fabs(2 * l - 1.0)) * s;
	x = c * (1.0 - fabs(fmod((h / 60.0), 2) - 1.0));
	m = l - 0.5 * c;
	if (h >= 0 && h < 360)
		ft_get_color(&color, (c + m) * 255, (x + m) * 255, (0 + m) * 255);
	return (color.color);
}
