/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfractales.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:11:35 by cbinet            #+#    #+#             */
/*   Updated: 2017/12/11 09:07:26 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			bdraw(t_fractenv *env, size_t i)
{
	unsigned int color;

	if (env->fract[env->op].colormode % 2 == 1)
		color = get_color(env->fract[env->op], i);
	while (--i > 0)
	{
		if (env->fract[env->op].colormode % 2 == 0)
			color = get_color(env->fract[env->op], i);
		if (env->fract[env->op].it_max < 255)
			color *= ((255) / env->fract[env->op].it_max);
		increasepixel(env, env->imap[i], color);
	}
}

void			bpfract(t_fractenv *env, t_pixel pixel)
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
		p.x = (env->fract[env->op].mouse.x - env->width / 2) / 1000;
		p.y = (env->fract[env->op].mouse.y - env->height / 2) / 1000;
	}
	i = 0;
	while (++i != env->fract[env->op].it_max && (is_bounded(env, z) || i == 0))
		env->imap[i] =
			env->fract[env->op].serie(&z, p, env->fract[env->op].zoom);
	if (i != env->fract[env->op].it_max)
		bdraw(env, i);
}

static void		bbrowse(t_fractenv *env)
{
	t_pixel	z;

	z.x = 0;
	while (z.x != env->width)
	{
		z.y = 0;
		while (z.y != env->height)
		{
			bpfract(env, z);
			z.y++;
		}
		z.x++;
	}
}

void			bfract(t_fractenv *env)
{
	clock_t	t;
	char	*tmp;

	if (!(env->imap = (t_pixel *)malloc(env->fract[env->op].it_max *
					sizeof(t_pixel))))
		exit(1);
	if (!(env->img = mlx_new_image(env->mlx, env->width, env->height)))
		exit(1);
	env->imgstr = (unsigned int *)mlx_get_data_addr(env->img,
			&env->bpp, &env->sl, &env->end);
	t = clock();
	bbrowse(env);
	t = clock() - t;
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	if (env->verbose)
	{
		printenv(env);
		tmp = ft_itoa((t * 1000) / CLOCKS_PER_SEC);
		mlx_string_put(env->mlx, env->win, 80, 35, 0x00FF00, tmp);
		free(tmp);
	}
	if (env->fract[env->op].img)
		mlx_destroy_image(env->mlx, env->fract[env->op].img);
	env->fract[env->op].img = env->img;
	free(env->imap);
}
