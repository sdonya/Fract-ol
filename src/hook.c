/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonya <sdonya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 02:06:33 by sdonya            #+#    #+#             */
/*   Updated: 2020/07/04 02:06:36 by sdonya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int		key_hook2(int keycode, t_fractol *fractal)
{
	if (keycode == 19)
		fractal->color = 2050;
	else if (keycode == 20)
		fractal->color = 265;
	else if (keycode == 35)
		fractal->julia_mouse = !fractal->julia_mouse;
	else if (keycode == 34)
		fractal->show_text = !fractal->show_text;
	return (0);
}

int		key_hook(int keycode, t_fractol *fractal)
{
	if (keycode == 53)
		exit(1);
	else if (keycode == 69)
		fractal->it_max += 50;
	else if (keycode == 78)
		fractal->it_max -= 50;
	else if (keycode == 123)
		fractal->x1 -= 30 / fractal->zoom;
	else if (keycode == 124)
		fractal->x1 += 30 / fractal->zoom;
	else if (keycode == 125)
		fractal->y1 += 30 / fractal->zoom;
	else if (keycode == 126)
		fractal->y1 -= 30 / fractal->zoom;
	else if (keycode == 49)
		fract_init(fractal);
	else if (keycode == 18)
		fractal->color = 1677216;
	key_hook2(keycode, fractal);
	fract_calc(fractal);
	return (0);
}

void	ft_zoom(int x, int y, t_fractol *fractal)
{
	fractal->x1 = (x / fractal->zoom + fractal->x1) \
				- (x / (fractal->zoom * 1.3));
	fractal->y1 = (y / fractal->zoom + fractal->y1) \
				- (y / (fractal->zoom * 1.3));
	fractal->zoom *= 1.3;
	fractal->it_max++;
}

void	ft_dezoom(int x, int y, t_fractol *fractal)
{
	fractal->x1 = (x / fractal->zoom + fractal->x1) \
				- (x / (fractal->zoom / 1.3));
	fractal->y1 = (y / fractal->zoom + fractal->y1) \
				- (y / (fractal->zoom / 1.3));
	fractal->zoom /= 1.3;
	fractal->it_max--;
}

int		mouse_hook(int mousecode, int x, int y, t_fractol *fractal)
{
	if (mousecode == 4 || mousecode == 1)
		ft_zoom(x, y, fractal);
	else if (mousecode == 5 || mousecode == 2)
		ft_dezoom(x, y, fractal);
	fract_calc(fractal);
	return (0);
}
