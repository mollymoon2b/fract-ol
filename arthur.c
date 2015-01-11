/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arthur.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/11 19:19:31 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/01/11 19:19:32 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>
#include <mlx.h>

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
	else
		ft_get_color(&color, 255, 255, 255);
	return (color.color);
}

int 	ft_formatcolor(int r, int g, int b)
{
	int color;

	color = r;
	color = (color << 16) + g;
	color = (color << 16) + b;
	return (color);
}

int 	ft_effect(int color)
{
	return (color * 16);
}

int 	ft_multicolor(t_env *e, int i)
{
	i %= 768;
//	i *= 768 / e->maxiter;
	// e->effect(i);
//	i *= 16;
	//i %= 768;
	if (i < 256)
		return (ft_formatcolor(255 - i, i , 0)); 
 	else if (i < 512)
 		return (ft_formatcolor(0, 255 - (i - 256), i- 256)); 
 	else
 		return (ft_formatcolor(i - 512, 0, 255 - (i - 512))); 

	// color %= 768;
	// color *= 768 / e->maxiter;
	// if (color < 256)
	// 	return ((255 - color) * 16 * 16 + color * 16);
	// if (color < 512)
	// 	return (255 * 16 + 512 - color + 512);
	// else
	// 	return ((color - 512) * 16 * 16 + 255 - (color - 512));
}

int 	ft_getcolor(t_env *e, int color)
{
	return (ft_multicolor(e, color));
	// int white;
	// int blue;
	// int returned;
	// double ratio;

	// white = 0xFFFFFF;
	// blue = 0x0000FF;
	// ratio = color / (double)e->maxiter;
	// returned = 0;
	// returned += ((white >> 16) & 0xFF) * ratio + ((blue >> 16) & 0xFF) * (1 - ratio);
	// returned += ((white >> 8) & 0xFF) * ratio + ((blue >> 16) & 0xFF) * (1 - ratio);
	// returned += (white & 0xFF) * ratio + ((blue >> 16) & 0xFF) * (1 - ratio);
	// returned = ((white >> 16) & 0xFF) * ratio + ((blue >> 16) & 0xFF) * (1 - ratio);
	// returned = (returned << 8) + ((white >> 8) & 0xFF) * ratio + ((blue >> 16) & 0xFF) * (1 - ratio);
	// returned = (returned << 8) + (white & 0xFF) * ratio + ((blue >> 16) & 0xFF) * (1 - ratio);
	// return (returned);
	// double	diff;
	// double 	
	// diff = 0x0000FF / e->maxiter * color * 1;
	// return (diff * 65536 + diff * 256 + 0x000077);
	// diff = 0x0000FF / e->maxiter;
	// return (0xFFFFFF);
	// return ((e->maxiter - color) * diff);
}

int 	ft_julia(t_env *e)
{
	t_complex	inter;
	t_complex	z;
	int  		color;
	
	color = 0;
	z.real = e->z.real;
	z.imag = e->z.imag;
	while (color < e->maxiter && z.real * z.real + z.imag * z.imag <= 4 && color < e->maxiter)
	{
		inter.real = (z.real * z.real) - (z.imag  * z.imag) + e->c.real;
		inter.imag = 2 * (z.real * z.imag) + e->c.imag;
		z.real = inter.real;
		z.imag = inter.imag;
		color++;
	}
	// if (color == 11)
	// 	return (0xFF0000);
	// return (0x0000FF);
	// if (color != 0)
		// printf("Color = %i\n", color);
	// printf("Width = %im color pos = %i\n", e->text.width, (((color == e->maxiter) ? 0 : color)) % e->text.width);
	// return (ft_getxpmcolor(e->text.ptr + color * 4));
	return ((color % (e->maxiter / 3)) << 16 + (color % (e->maxiter / 2)) << 8 + color % e->maxiter);
	return (color * 25);
	return (ft_getcolor(e, color));
}

void	ft_calcenv(t_env *e)
{
	e->xorigin = e->xcenter - (e->width / 2) * e->xdiff;
	e->yorigin = e->ycenter - (e->height / 2) * e->ydiff;
}

t_env 	*ft_initenv()
{
	t_env	*e;

	e = (t_env *)malloc(sizeof(t_env));
	// e->c.real = 0.1;
	// e->c.imag = 0.651;
	// e->c.real = -0.835;
	// e->c.imag = 0.2321;
	e->c.real = -0.75;
	e->c.imag = 0.11;
	e->width = 1500;
	e->height = 1500;
	e->xcenter = 0;
	e->ycenter = 0;
	e->xdiff = 0.01;
	e->ydiff = 0.01;
	e->maxiter = 5000;
	e->mlx = mlx_init();
	e->win = mlx_new_window(e->mlx, e->width, e->height, "42");
	return (e);
}

void	ft_showjulia(t_env *e)
{
	e->ypos = 0;
	e->z.imag = e->yorigin;
	while (e->ypos < e->height)
	{
		e->xpos = 0;
		e->z.real = e->xorigin;
		while (e->xpos < e->width)
		{
			ft_put_pixel_to_image(e, e->xpos, e->ypos, ft_julia(e));
			e->xpos++;
			e->z.real += e->xdiff;
		}
		e->ypos++;
		e->z.imag += e->ydiff;
	}
}

static int 	expose_hook(t_env *e)
{
	ft_update_img(e, ft_showjulia);
	return (0);
}

int			ft_updatekey(int key, t_env *e)
{
	if (key == 65307) // esc
	{
		//ft_putendl("We hope to see you once again very soon.\nPS : The cake is a lie");
		exit (0);
	}
	// if (key == A)
	// 	e->pos.z += 0.025;
	// if (key == D)
	// 	e->pos.z -= 0.025;
	if (key == W)
	{
		// e->xdiff += 0.01;
		// e->ydiff += 0.01;
		e->xdiff *= 9.0 / 10.0;
		e->ydiff *= 9.0 / 10.0;
	}
	if (key == S)
	{
		// e->xdiff -= 0.01;
		// e->ydiff -= 0.01;
		e->xdiff *= 10.0 / 9.0;
		e->ydiff *= 10.0 / 9.0;
	}
	if (key == RIGHT)
		e->xcenter += e->xdiff * 10;
	if (key == LEFT)
		e->xcenter -= e->xdiff * 10;
	if (key == DOWN)
		e->ycenter += e->ydiff * 10;
	if (key == UP)
		e->ycenter -= e->ydiff * 10;
	ft_calcenv(e);
	ft_update_img(e, ft_showjulia);
	return (0);
}

int 	main(void)
{
	t_env	*e;

	e = ft_initenv();
	ft_calcenv(e);
	e->text = ft_getimg(e, "text.xpm");
	e->maxiter = 10000;
	//ft_update_img(e, ft_showjulia);
	//sleep (2);
	mlx_expose_hook(e->win, expose_hook, e);
	mlx_hook(e->win, 2, 1, ft_updatekey, e);
	mlx_loop(e->mlx);
	// sleep(100);
}