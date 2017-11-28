/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractales.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:11:57 by cbinet            #+#    #+#             */
/*   Updated: 2017/11/28 16:12:17 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	julia(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	p.x = env->mouse.x - env->width / 2;
	p.y = env->mouse.y - env->height / 2;
	p.x /= 1000;
	p.y /= 1000;
	z.x = (((pixel.x - 2 + env->x) / env->zoom));
	z.y = (((pixel.y - 2 + env->y) / env->zoom));
	i = 0;
	while (i < env->it_max && z.x * z.x + z.y * z.y < env->max &&
			(z.x * z.x + z.y * z.y > env->min || i == 0))
	{
		csquare(&z);
		z.x += p.x;
		z.y += p.y;
		i++;
	}
	if (i != env->it_max)
		addpixel(env, pixel, i * env->i);
}

void	mand(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	p.x = (((pixel.x - 2 + env->x) / env->zoom));
	p.y = (((pixel.y - 2 + env->y) / env->zoom));
	z.x = 0;
	z.y = 0;
	i = 0;
	while (i < env->it_max && z.x * z.x + z.y * z.y < env->max &&
			(z.x * z.x + z.y * z.y > env->min || i == 0))
	{
		csquare(&z);
		z.x += p.x;
		z.y += p.y;
		i++;
	}
	if (i == env->it_max)
		addpixel(env, pixel, 0xff * env->i);
	else
		addpixel(env, pixel, i * env->i);
}

void	buddha(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	p.x = ((pixel.x - env->width / 2) / env->zoom);
	p.y = ((pixel.y - env->height / 2) / env->zoom);
	z.x = 0;
	z.y = 0;
	i = 0;
	while (i < env->it_max && z.x * z.x + z.y * z.y < env->max &&
			(z.x * z.x + z.y * z.y > env->min || i == 0))
	{
		csquare(&z);
		z.x += p.x;
		z.y += p.y;
		i++;
	}
	if (i != env->it_max)
	{
		z.x = 0;
		z.y = 0;
		while (i >= 0)
		{
			increasepixel(env, z, env->i);
			csquare(&z);
			z.x += p.x;
			z.y += p.y;
			i--;
		}
	}
}

void	fract(t_fractenv *env, void (op(t_fractenv *, t_pixel)))
{
	t_pixel	z;

	env->img = mlx_new_image(env->mlx, env->width, env->height);
	env->imgstr = (unsigned int *)mlx_get_data_addr(env->img, &env->bpp,
			&env->sl, &env->end);
	z.x = 0;
	while (z.x < env->width)
	{
		z.y = 0;
		while (z.y < env->height)
		{
			op(env, z);
			z.y++;
		}
		z.x++;
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
/*
   int fd;
   ft_printf("%d\n", env->it_max);
   fd = open("test.map", O_WRONLY);
   write(fd, env->imgstr,
   env->width * env->height * sizeof(unsigned int) / sizeof(char));
   close(fd);
   ft_printf("%d\n", env->it_max);
   env->it_max += env->it_max;
   if (env->it_max > 100000)
   exit(0);
   ft_printf("%d\n", env->it_max);

   env->i *= 256;
   env->i %= 0xffffff;
   exit(0);
   */
