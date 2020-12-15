/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonya <sdonya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 02:06:41 by sdonya            #+#    #+#             */
/*   Updated: 2020/07/04 02:06:42 by sdonya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int		mouse_julia(int x, int y, t_fractol *fractal)
{
	if (fractal->fract == 1 && fractal->julia_mouse == 1)
	{
		fractal->c_r = x * 2;
		fractal->c_i = y * 2 - 800;
		fract_calc(fractal);
	}
	return (0);
}

void	julia_init(t_fractol *fractal)
{
	fractal->it_max = 50;
	fractal->zoom = 200;
	fractal->x1 = -2.0;
	fractal->y1 = -1.9;
	fractal->color = 265;
	fractal->c_r = 0.285;
	fractal->c_i = 0.01;
	fractal->julia_mouse = 1;
}

void	julia_calc(t_fractol *fractal)
{
	fractal->z_r = fractal->x / fractal->zoom + fractal->x1;
	fractal->z_i = fractal->y / fractal->zoom + fractal->y1;
	fractal->it = 0;
	while (fractal->z_r * fractal->z_r + fractal->z_i \
			* fractal->z_i < 4 && fractal->it < fractal->it_max)
	{
		fractal->tmp = fractal->z_r;
		fractal->z_r = fractal->z_r * fractal->z_r -
			fractal->z_i * fractal->z_i - 0.8 + (fractal->c_r / WIDTH);
		fractal->z_i = 2 * fractal->z_i * fractal->tmp + fractal->c_i / WIDTH;
		fractal->it++;
	}
	if (fractal->it == fractal->it_max)
		put_pxl_to_img(fractal, fractal->x, fractal->y, 0x000000);
	else
		put_pxl_to_img(fractal, fractal->x, fractal->y, \
				(fractal->color * fractal->it));
}

void	*julia(void *tab)
{
	int			tmp;
	t_fractol	*fractal;

	fractal = (t_fractol *)tab;
	fractal->x = 0;
	tmp = fractal->y;
	while (fractal->x < WIDTH)
	{
		fractal->y = tmp;
		while (fractal->y < fractal->y_max)
		{
			julia_calc(fractal);
			fractal->y++;
		}
		fractal->x++;
	}
	return (tab);
}

void	julia_pthread(t_fractol *fractal)
{
	t_fractol	tab[THREAD_NUMBER];
	pthread_t	t[THREAD_NUMBER];
	int			i;

	i = 0;
	while (i < THREAD_NUMBER)
	{
		ft_memcpy((void*)&tab[i], (void*)fractal, sizeof(t_fractol));
		tab[i].y = THREAD_WIDTH * i;
		tab[i].y_max = THREAD_WIDTH * (i + 1);
		pthread_create(&t[i], NULL, julia, &tab[i]);
		i++;
	}
	while (i--)
		pthread_join(t[i], NULL);
	mlx_put_image_to_window(fractal->mlx_ptr, \
			fractal->win_ptr, fractal->img, 0, 0);
}
