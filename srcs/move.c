/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:36:52 by cbinet            #+#    #+#             */
/*   Updated: 2017/11/30 13:42:09 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static bool isbub(size_t op)
{
return (op > 9 && op < 14);
}
void			colorup(t_fractenv *env)
{
if (env->color < 0x10000)
	env->color *= 0x100;
else
	env->color = 0x1;
}

void			verbose(t_fractenv *env)
{
	env->verbose = !env->verbose;
}

void			move(t_fractenv *env)
{
	env->move = !env->move;
}

void			left(t_fractenv *env)
{
	//env->min += .002;
//printf("%f\n",(double)env->min);
env->colormode++;
if (env->colormode > 5)
env->colormode = 0;
}

void			up(t_fractenv *env)
{
	if (env->op < 13)
		env->op++;
	else
		env->op = 0;
if (isbub(env->op))
		env->min = 0.12;
	else
	env->min = 0;
	if (env->verbose)
		ft_printf("fractale : %s\n", env->opc[env->op]);
}

void			down(t_fractenv *env)
{
	if (env->op > 0)
		env->op--;
	else
		env->op = 13;
if (isbub(env->op))
		env->min = 0.12;
	else
	env->min = 0;
	if (env->verbose)
		ft_printf("fractale : %s\n", env->opc[env->op]);
}

void			right(t_fractenv *env)
{
	if (env->color > 0x000001)
		env->color /= 256;
	else
		env->color = 0x010000;
	if (env->verbose)
		ft_printf("color mult: %d\n", env->color);
}

void			higher(t_fractenv *env)
{
	if (env->it_max > 15)
		env->it_max += env->it_max / 5;
	else
		env->it_max++;
	if (env->verbose)
		ft_printf("it_max: %d\n", env->it_max);
}

void			lower(t_fractenv *env)
{
	if (env->it_max > 10)
		env->it_max-= env->it_max / 5;
	else if (env->it_max > 1)
		env->it_max--;
	if (env->verbose)
		ft_printf("it_max: %d\n", env->it_max);
}

void			zoom(t_fractenv *env)
{
	int speed;

	speed = 1;
	if (env->mouse.x)
	{
		env->x += (env->x + env->width / 2) / 5;
		env->y += (env->y + env->height / 2) / 5;
		env->zoom += (env->zoom / 5) * speed;
		env->x += ((env->mouse.x - env->width / 2) / 5);
		env->y += ((env->mouse.y - env->height / 2) / 5);
//		env->it_max += 1;
	}
	else
	{
		env->zoom *= 2;
		env->x += (env->x + env->width / 2);
		env->y += (env->y + env->height / 2);
	}
	if (env->verbose)
		ft_printf("zoom: %d\n", env->zoom);
}

void			dezoom(t_fractenv *env)
{
	int speed;

	speed = 1;
	if (env->mouse.x)
	{
		env->zoom -= (env->zoom / 5) * speed;
		env->x -= (env->x + env->width / 2) / 5;
		env->y -= (env->y + env->height / 2) / 5;
		env->x -= ((env->mouse.x - env->width / 2) / 5);
		env->y -= ((env->mouse.y - env->height / 2) / 5);
	}
	else
	{
		env->x -= (env->x + env->width / 2);
		env->y -= (env->y + env->height / 2);
		env->zoom /= 2;
	}
	if (env->verbose)
		ft_printf("zoom: %d\n", env->zoom);
}
