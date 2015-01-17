/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-bonn <ade-bonn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/09 13:40:54 by ade-bonn          #+#    #+#             */
/*   Updated: 2015/01/14 11:16:59 by ade-bonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIN_WIDTH 780
# define WIN_HEIGHT 540
# include <mlx.h>
# include <math.h>
# include "libft/libft.h"
# include "X11/Xlib.h"

# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define LESS 45
# define MORE 61

typedef struct	s_color
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
	double		real;
	double		imag;
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
	t_complex	init;
	t_complex	center;
	t_complex	steps;
	t_complex	pastpos;
	t_complex	mouse;
	int			update;
}				t_env;

int				main(int ac, char **av);
void			ft_error(char *s);
int				ft_exposehook(t_env *e);
int				keyboard_event(int keycode, t_env *e);
int				mouse_event(int button, int x, int y, t_env *e);
void			ft_put_pixel(t_buffer *buffer, int x, int y, t_color color);
t_color			ft_tohex(int h, float s, float l);
t_color			ft_get_color(char r, char g, char b);
void			ft_screenloop(t_env *e, t_complex z);
int				ft_init_mandelbrot(t_env *e);
int				ft_init_julia(t_env *e);
int				ft_init_fractoil(t_env *e);
int				ft_init_dragon(t_env *e);
int				ft_fractoil(int max_it, t_complex z, t_complex c);
int				ft_julia(int max_it, t_complex z, t_complex c);
int				ft_mandelbrot(int max_it, t_complex z, t_complex c);
int				ft_dragon(int max_it, t_complex z, t_complex c);
void			ft_setinit(t_env *e);

#endif
