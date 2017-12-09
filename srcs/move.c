/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:36:52 by cbinet            #+#    #+#             */
/*   Updated: 2017/12/04 11:04:58 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			reset(t_fractenv *env)
{
env->fract[env->op] = resetfract(env->fract[env->op]);
}
void			colorup(t_fractenv *env)
{
	if (env->fract[env->op].color < 0x10000)
		env->fract[env->op].color *= 0x100;
	else
		env->fract[env->op].color = 0x1;
}

void			verbose(t_fractenv *env)
{
	env->verbose = !env->verbose;
}

void			move(t_fractenv *env)
{
	env->move = !env->move;

printf("%s\n",env->fract[env->op].name);
printf("%F%F\n",env->fract[env->op].mouse.x * 300 + env->width / 2, env->fract[env->op].mouse.y * 300 + env->height / 2);
}

void			left(t_fractenv *env)
{
	env->fract[env->op].colormode++;
	if (env->fract[env->op].colormode > 5)
		env->fract[env->op].colormode = 0;
}

void			up(t_fractenv *env)
{
	env->op++;
	if (env->op >= NB_FRACT)
		env->op = 0;
	if (env->verbose)
		ft_printf("fractale : %s\n", env->fract[env->op].name);
	if (env->fract[env->op].img)
	{
		mlx_put_image_to_window(env->mlx, env->win, env->fract[env->op].img, 0, 0);
		if (env->verbose)
			printenv(env);
		env->mod = false;
	}
}

void			down(t_fractenv *env)
{
	if (env->op > 0)
		env->op--;
	else
		env->op = NB_FRACT - 1;
	if (env->verbose)
		ft_printf("fractale : %s\n", env->fract[env->op].name);
	if (env->fract[env->op].img)
	{
		mlx_put_image_to_window(env->mlx, env->win, env->fract[env->op].img, 0, 0);
		if (env->verbose)
			printenv(env);
		env->mod = false;
	}
}

void			right(t_fractenv *env)
{
	if (env->fract[env->op].color > 0x000001)
		env->fract[env->op].color /= 256;
	else
		env->fract[env->op].color = 0x010000;
	if (env->verbose)
		ft_printf("color mult: %d\n", env->fract[env->op].color);
}

void			higher(t_fractenv *env)
{

	if (env->fract[env->op].it_max > 15 && env->fract[env->op].it_max < 4096)
		env->fract[env->op].it_max += env->fract[env->op].it_max / 8;
	else
		env->fract[env->op].it_max++;
	if (env->verbose)
		ft_printf("it_max: %d\n", env->fract[env->op].it_max);
}

void			lower(t_fractenv *env)
{
	if (env->fract[env->op].it_max > 16)
		env->fract[env->op].it_max -= env->fract[env->op].it_max / 8;
	else if (env->fract[env->op].it_max > 1)
		env->fract[env->op].it_max--;
	if (env->verbose)
		ft_printf("it_max: %d\n", env->fract[env->op].it_max);
}

void			zoom(t_fractenv *env)
{
	int speed;

	speed = 1;
	if (env->mouse.x)
	{
		env->fract[env->op].x += (env->fract[env->op].x + env->width / 2) / 5;
		env->fract[env->op].y += (env->fract[env->op].y + env->height / 2) / 5;
		env->fract[env->op].zoom += (env->fract[env->op].zoom / 5) * speed;
		env->fract[env->op].x += ((env->mouse.x - env->width / 2) / 5);
		env->fract[env->op].y += ((env->mouse.y - env->height / 2) / 5);
		//		env->it_max += 1;
	}
	else
	{
		env->fract[env->op].zoom *= 2;
		env->fract[env->op].x += (env->fract[env->op].x + env->width / 2);
		env->fract[env->op].y += (env->fract[env->op].y + env->height / 2);
	}
	if (env->verbose)
		ft_printf("zoom: %d\n", env->fract[env->op].zoom);
}

void			dezoom(t_fractenv *env)
{
	int speed;

	speed = 1;
	if (env->mouse.x)
	{
		env->fract[env->op].zoom -= (env->fract[env->op].zoom / 5) * speed;
		env->fract[env->op].x -= (env->fract[env->op].x + env->width / 2) / 5;
		env->fract[env->op].y -= (env->fract[env->op].y + env->height / 2) / 5;
		env->fract[env->op].x -= ((env->mouse.x - env->width / 2) / 5);
		env->fract[env->op].y -= ((env->mouse.y - env->height / 2) / 5);
	}
	else
	{
		env->fract[env->op].x -= (env->fract[env->op].x + env->width / 2);
		env->fract[env->op].y -= (env->fract[env->op].y + env->height / 2);
		env->fract[env->op].zoom /= 2;
	}
	if (env->verbose)
		ft_printf("zoom: %d\n", env->fract[env->op].zoom);
}
