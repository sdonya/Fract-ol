/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonya <sdonya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 02:06:25 by sdonya            #+#    #+#             */
/*   Updated: 2020/07/04 02:06:27 by sdonya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	burningship_init(t_fractol *fractal)
{
	fractal->it_max = 50;
	fractal->zoom = 220;
	fractal->x1 = -2.2;
	fractal->y1 = -2.5;
	fractal->color = 265;
}

void	burningship_calc(t_fractol *fractal)
{
	fractal->c_r = fractal->x / fractal->zoom + fractal->x1;
	fractal->c_i = fractal->y / fractal->zoom + fractal->y1;
	fractal->z_r = 0;
	fractal->z_i = 0;
	fractal->it = 0;
	while (fractal->z_r * fractal->z_r + fractal->z_i * fractal->z_i < 4
			&& fractal->it < fractal->it_max)
	{
		fractal->tmp = fractal->z_r * fractal->z_r - fractal->z_i \
					* fractal->z_i + fractal->c_r;
		fractal->z_i = fabs(2 * fractal->z_r * fractal->z_i) + fractal->c_i;
		fractal->z_r = fractal->tmp;
		fractal->it++;
	}
	if (fractal->it == fractal->it_max)
		put_pxl_to_img(fractal, fractal->x, fractal->y, 0x000000);
	else
		put_pxl_to_img(fractal, fractal->x, fractal->y, \
				(fractal->color * fractal->it));
}

void	*burningship(void *tab)
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
			burningship_calc(fractal);
			fractal->y++;
		}
		fractal->x++;
	}
	return (tab);
}

void	burningship_pthread(t_fractol *fractal)
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
		pthread_create(&t[i], NULL, burningship, &tab[i]);
		i++;
	}
	while (i--)
		pthread_join(t[i], NULL);
	mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr, \
			fractal->img, 0, 0);
}
