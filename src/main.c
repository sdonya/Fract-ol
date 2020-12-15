/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdonya <sdonya@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 02:06:48 by sdonya            #+#    #+#             */
/*   Updated: 2020/07/04 02:06:53 by sdonya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	fract_calc(t_fractol *fractal)
{
	if (fractal->it_max < 0)
		fractal->it_max = 0;
	if (fractal->fract == 0)
		mandelbrot_pthread(fractal);
	else if (fractal->fract == 1)
		julia_pthread(fractal);
	else if (fractal->fract == 2)
		burningship_pthread(fractal);
	if (fractal->show_text)
		put_text(fractal);
}

void	fract_init(t_fractol *fractal)
{
	if (fractal->fract == 0)
		mandelbrot_init(fractal);
	else if (fractal->fract == 1)
		julia_init(fractal);
	else if (fractal->fract == 2)
		burningship_init(fractal);
	fract_calc(fractal);
}

void	mlx_win_init(t_fractol *fractal)
{
	fractal->mlx_ptr = mlx_init();
	fractal->win_ptr = mlx_new_window(fractal->mlx_ptr, \
			WIDTH, WIDTH, "Fractol");
	fractal->img = mlx_new_image(fractal->mlx_ptr, WIDTH, WIDTH);
	fractal->img_ptr = mlx_get_data_addr(fractal->img,
			&fractal->bpp, &fractal->sl, &fractal->endian);
	fractal->show_text = 1;
}

int		fract_comp(char **av, t_fractol *fractal)
{
	if (ft_strcmp(av[1], "mandelbrot") == 0)
		fractal->fract = 0;
	else if (ft_strcmp(av[1], "julia") == 0)
		fractal->fract = 1;
	else if (ft_strcmp(av[1], "burningship") == 0)
		fractal->fract = 2;
	else
	{
		ft_putendl("Usage /fractol \"mandelbrot\", \"julia\", \"burningship\"");
		return (0);
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_fractol	*fractal;

	if (!(fractal = (t_fractol *)malloc(sizeof(t_fractol))))
		return (-1);
	if (ac == 2)
	{
		mlx_win_init(fractal);
		if ((fract_comp(av, fractal)) == 0)
			return (0);
		fract_init(fractal);
		mlx_hook(fractal->win_ptr, 6, 1L < 6, mouse_julia, fractal);
		mlx_hook(fractal->win_ptr, 17, 0L, ft_close, fractal);
		mlx_hook(fractal->win_ptr, 2, 1L, key_hook, fractal);
		mlx_mouse_hook(fractal->win_ptr, mouse_hook, fractal);
		mlx_loop(fractal->mlx_ptr);
	}
	else
		ft_putendl("Usage /fractol \"mandelbrot\", \"julia\", \"burningship\"");
	return (0);
}
