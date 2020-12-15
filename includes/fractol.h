/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonya <sdonya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 02:04:14 by sdonya            #+#    #+#             */
/*   Updated: 2020/07/04 02:04:19 by sdonya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <OpenGL/OpenGL.h>
# include "../libft/includes/libft.h"
# include "../minilibx_macos/mlx.h"
# include "math.h"
# include "pthread.h"
# define WIDTH 800
# define THREAD_WIDTH 5
# define THREAD_NUMBER 160
# define W 0xffffff

typedef struct	s_fractol
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img;
	void		*img_ptr;
	int			endian;
	int			sl;
	int			bpp;
	int			fract;
	int			color;
	int			julia_mouse;
	int			x;
	int			y;
	int			y_max;
	int			it;
	int			it_max;
	int			show_text;
	double		zoom;
	double		x1;
	double		y1;
	double		c_r;
	double		c_i;
	double		z_r;
	double		z_i;
	double		tmp;
}				t_fractol;

int				key_hook(int keycode, t_fractol *fractal);
int				key_hook2(int keycode, t_fractol *fractal);
void			ft_zoom(int x, int y, t_fractol *fractal);
void			ft_dezoom(int x, int y, t_fractol *fractal);
int				mouse_hook(int mousecode, int x, int y, t_fractol *fractal);

void			mandelbrot_init(t_fractol *fractal);
void			mandelbrot_calc(t_fractol *fractal);
void			*mandelbrot(void *tab);
void			mandelbrot_pthread(t_fractol *fractal);

int				mouse_julia(int x, int y, t_fractol *fractal);
void			julia_init(t_fractol *fractal);
void			julia_calc(t_fractol *fractal);
void			*julia(void *tab);
void			julia_pthread(t_fractol *fractal);

void			burningship_init(t_fractol *fractal);
void			burningship_calc(t_fractol *fractal);
void			*burningship(void *tab);
void			burningship_pthread(t_fractol *fractal);

int				ft_close(void);
void			put_pxl_to_img(t_fractol *fractal, int x, int y, int color);
void			put_text(t_fractol *fractal);

void			fract_calc(t_fractol *fractal);
void			fract_init(t_fractol *fractal);
void			mlx_win_init(t_fractol *fractal);
int				fract_comp(char **av, t_fractol *fractal);
#endif
