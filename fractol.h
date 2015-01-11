/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 13:40:54 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/01/09 15:19:34 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIN_WIDTH 1500
# define WIN_HEIGHT 1000
# include <mlx.h>
# include <math.h>
# include "libft/libft.h"

#include <stdio.h>

typedef struct	u_color
{
	char		rgb[4];
}				t_color;

typedef struct	s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct	s_complex
{
	double		x;
	double		y;
}				t_complex;

typedef struct	s_buffer
{
	void		*img;
	char		*data;
	int			bpp;
	int			line_size;
	int			endian;
}				t_buffer;

typedef struct	s_env
{
	int			(*function)(struct s_env *e);
	int			(*fractal)(int max_it, t_complex c, t_complex z);
	void		*mlx;
	void		*win;
	char		*name;
	float		zoom;
	t_point		offset;
	int			max_it;
	t_buffer	buffer;
	t_complex	z;
	t_complex	c;
}				t_env;

int				main(int ac, char **av);
void			ft_error(char *s);
int				ft_exposehook(t_env *e);
int				keyboard_event(int keycode, t_env *e);
int				mouse_event(int button, int x, int y, t_env *e);
int				draw_mandelbrot(t_env *e);
int				draw_julia(t_env *e);

void			ft_put_pixel_to_img(t_buffer *buffer, int x, int y, t_color color);
t_color			ft_tohex(int h, float s, float l);
t_color			ft_get_color(char r, char g, char b);
void		ft_screenloop(t_env *e, t_complex z);
#endif
