/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractales.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:11:57 by cbinet            #+#    #+#             */
/*   Updated: 2017/12/04 11:04:30 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	bdraw(t_fractenv *env, size_t i)
{
	unsigned int color;

	if (env->colormode % 2 == 1)
		color = get_color(env, i);
	while (--i > 0)
	{
		if (env->colormode % 2 == 0)
			color = get_color(env, i);
		increasepixel(env, env->imap[i], color);
	}
}

void	bpfract(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	z.x = (pixel.x + env->x) / env->zoom;
	z.y = (pixel.y + env->y) / env->zoom;
	if (!env->fract[env->op].mdep)
		p = z;
	else
	{
		p.x = (env->mouse2.x - env->width / 2)/ 1000;
		p.y = (env->mouse2.y - env->height / 2)/ 1000;
	}
	i = 0;
	while (++i < env->it_max && (is_bounded(env, z) || i == 0))
		env->imap[i] = env->fract[env->op].serie(&z, p, env->zoom);
	if (i != env->it_max)
		bdraw(env, i);
}

void	pfract(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	z.x = (pixel.x + env->x) / env->zoom;
	z.y = (pixel.y + env->y) / env->zoom;
	if (!env->fract[env->op].mdep)
		p = z;
	else
	{
		p.x = (env->mouse2.x - env->width / 2)/ (env->width / 4);
		p.y = (env->mouse2.y - env->height / 2)/ (env->height / 4);	}
	i = 0;
	while (++i < env->it_max && (is_bounded(env, z) || i == 0))
		env->fract[env->op].serie(&z, p, env->zoom);
	i *= get_color(env,i);
	addpixel(env, pixel, i);
}

static void	bbrowse(t_fractenv *env)// void (op(t_fractenv *, t_pixel)))
{
	t_pixel	z;

	z.x = 0;
	while (z.x < env->width)
	{
		z.y = 0;
		while (z.y < env->height)
		{
			bpfract(env, z);
			z.y++;
		}
		if (env->verbose && (int)z.x % 12 == 0)
			put_loading_logo(env, (int)z.x);
		z.x++;
	}
}

static void	browse(t_fractenv *env)// void (op(t_fractenv *, t_pixel)))
{
	t_pixel	z;

	z.x = 0;
	while (z.x < env->width)
	{
		z.y = 0;
		while (z.y < env->height)
		{
			pfract(env, z);
			z.y++;
		}
		if (env->verbose && (int)z.x % 12 == 0)
			put_loading_logo(env, (int)z.x);
		z.x++;
	}
}

void	bfract(t_fractenv *env)
{
	clock_t t;	
	clock_t t2;	

	env->imap = (t_pixel *)malloc(env->it_max * sizeof(t_pixel));
	env->img = mlx_new_image(env->mlx, env->width, env->height);
	env->imgstr = (unsigned int *)mlx_get_data_addr(env->img, &env->bpp, &env->sl, &env->end);
	t = clock();
	bbrowse(env);// op);
	t2 = clock();
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	if (env->verbose)
	{
		printenv(env);
		printf("time: %5.5f\n",(double)((t2 - t)) / CLOCKS_PER_SEC);
		mlx_string_put(env->mlx, env->win, 50, 35,0x00FF00, ft_itoa(((t2 - t) * 1000) / CLOCKS_PER_SEC)); 
	}
	if (env->fract[env->op].img)
		mlx_destroy_image(env->mlx, env->fract[env->op].img);
	env->fract[env->op].img = env->img;
	free(env->imap);
}

void	fract(t_fractenv *env)
{
	clock_t t;	
	clock_t t2;	

	env->img = mlx_new_image(env->mlx, env->width, env->height);
	env->imgstr = (unsigned int *)mlx_get_data_addr(env->img, &env->bpp, &env->sl, &env->end);
	t = clock();
	browse(env);// op);
	t2 = clock();
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	if (env->verbose)
	{
		printenv(env);
		printf("time: %5.5f\n",(double)((t2 - t)) / CLOCKS_PER_SEC);
		mlx_string_put(env->mlx, env->win, 50, 35,0x00FF00, ft_itoa(((t2 - t) * 1000) / CLOCKS_PER_SEC)); 
	}
	if (env->fract[env->op].img)
		mlx_destroy_image(env->mlx, env->fract[env->op].img);
	env->fract[env->op].img = env->img;
}
