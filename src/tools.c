/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonya <sdonya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 02:07:16 by sdonya            #+#    #+#             */
/*   Updated: 2020/07/04 02:07:21 by sdonya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int		ft_close(void)
{
	exit(1);
	return (0);
}

void	put_pxl_to_img(t_fractol *fractal, int x, int y, int color)
{
	if (fractal->x < WIDTH && fractal->y < WIDTH)
	{
		color = mlx_get_color_value(fractal->mlx_ptr, color);
		ft_memcpy(fractal->img_ptr + 4 * WIDTH * y + x * 4,
				&color, sizeof(int));
	}
}

void	put_text2(t_fractol *fractal)
{
	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 10, 139, \
			W, "Green black - '2'");
	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 10, 156, \
			W, "Blue black - '3'");
	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 10, 173, \
			W, "Exit - 'esc'");
	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 475, 20, \
			W, "Zoom in and out - 'mouse wheel'");
	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 475, 37, \
			W, "increase - 'left mouse button'");
	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 475, 54, \
			W, "downsizing - 'right click'");
}

void	put_text(t_fractol *fractal)
{
	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 10, 3, \
			W, "KEYBOARD");
	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 10, 20, \
			W, "Top down left right - 'arrows'");
	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 10, 37, \
			W, "Decrease the number of iterations - '-'");
	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 10, 54, \
			W, "Increase the number of iterations - '+'");
	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 10, 71, \
			W, "Returns everything back - ' '");
	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 10, 88, \
			W, "Backlight - 'I'");
	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 10, 105, \
			W, "Mouse off in julia - 'P'");
	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 10, 122, \
			W, "Color gamut - '1'");
	put_text2(fractal);
}
