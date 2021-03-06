/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractales.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:11:57 by cbinet            #+#    #+#             */
/*   Updated: 2017/12/11 09:07:35 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			pfract(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	z.x = (pixel.x + env->fract[env->op].x) / env->fract[env->op].zoom;
	z.y = (pixel.y + env->fract[env->op].y) / env->fract[env->op].zoom;
	if (!env->fract[env->op].mdep)
		p = z;
	else
	{
		p.x = (env->fract[env->op].mouse.x);
		p.y = (env->fract[env->op].mouse.y);
	}
	i = 0;
	while (++i != env->fract[env->op].it_max && (is_bounded(env, z) || i == 0))
		env->fract[env->op].serie(&z, p, env->fract[env->op].zoom);
	i = (get_color(env->fract[env->op], i)) *
		(i * 0xfe / env->fract[env->op].it_max);
	addpixel(env, pixel, i);
}

static void		browse(t_fractenv *env)
{
	t_pixel	z;

	z.x = 0;
	while (z.x != env->width)
	{
		z.y = 0;
		while (z.y != env->height)
		{
			pfract(env, z);
			z.y++;
		}
		z.x++;
	}
}

void			fract(t_fractenv *env)
{
	clock_t	t;
	clock_t	t2;
	char	*tmp;

	if (!(env->img = mlx_new_image(env->mlx, env->width, env->height)))
		exit(1);
	env->imgstr = (unsigned int *)mlx_get_data_addr(env->img,
			&env->bpp, &env->sl, &env->end);
	t = clock();
	browse(env);
	t2 = clock();
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	if (env->verbose)
	{
		printenv(env);
		tmp = ft_itoa(((t2 - t) * 1000) / CLOCKS_PER_SEC);
		mlx_string_put(env->mlx, env->win, 80, 35, 0x00FF00, tmp);
		free(tmp);
	}
	if (env->fract[env->op].img)
		mlx_destroy_image(env->mlx, env->fract[env->op].img);
	env->fract[env->op].img = env->img;
}
