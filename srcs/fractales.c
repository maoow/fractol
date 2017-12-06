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

	if (env->fract[env->op].colormode % 2 == 1)
	{
		color = get_color(env->fract[env->op], i);

	}
	while (--i > 0)
	{
		if (env->fract[env->op].colormode % 2 == 0)
			color = get_color(env->fract[env->op], i);
		if (env->fract[env->op].it_max < 255)
			color *= ((255) / env->fract[env->op].it_max);
		increasepixel(env, env->imap[i], color);
	}
}

void	bpfract(t_fractenv *env, t_pixel pixel)
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
		p.x = (env->fract[env->op].mouse.x - env->width / 2)/ 1000;
		p.y = (env->fract[env->op].mouse.y - env->height / 2)/ 1000;
	}
	i = 0;
	while (++i != env->fract[env->op].it_max && (is_bounded(env, z) || i == 0))
		env->imap[i] = env->fract[env->op].serie(&z, p, env->fract[env->op].zoom);
	if (i != env->fract[env->op].it_max)
		bdraw(env, i);
}

void	pfract(t_fractenv *env, t_pixel pixel)
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
	i = (get_color(env->fract[env->op],i)
	    ) * (i * 0xfe / env->fract[env->op].it_max);
	addpixel(env, pixel, i);
}

static void	bbrowse(t_fractenv *env)// void (op(t_fractenv *, t_pixel)))
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
		//if (env->verbose && (int)z.x % 12 == 0)
		//put_loading_logo(env, (int)z.x);
		z.x++;
	}
}

static void	browse(t_fractenv *env)// void (op(t_fractenv *, t_pixel)))
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
		//if (env->verbose && (int)z.x % 12 == 0)
		//put_loading_logo(env, (int)z.x);
		z.x++;
	}
}

void	bfract(t_fractenv *env)
{
	clock_t t;	
	clock_t t2;	

	env->imap = (t_pixel *)malloc(env->fract[env->op].it_max * sizeof(t_pixel));
	env->img = mlx_new_image(env->mlx, env->width, env->height);
	env->imgstr = (unsigned int *)mlx_get_data_addr(env->img, &env->bpp, &env->sl, &env->end);
	t = clock();
	bbrowse(env);// op);
	t2 = clock();
	if (env->win)
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	if (env->win)
		if (env->verbose)
		{
			printenv(env);
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
	if (env->win)
		mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	if (env->win)
		if (env->verbose)
		{
			printenv(env);
			mlx_string_put(env->mlx, env->win, 50, 35,0x00FF00, ft_itoa(((t2 - t) * 1000) / CLOCKS_PER_SEC)); 
		}
	if (env->fract[env->op].img)
		mlx_destroy_image(env->mlx, env->fract[env->op].img);
	env->fract[env->op].img = env->img;
}
