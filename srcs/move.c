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

void			move(t_fractenv *env)
{
	env->move = !env->move;
}
void			left(t_fractenv *env)
{
	env->min += .002;
}

void			up(t_fractenv *env)
{
	if (env->op < 5)
		env->op++;
	else
		env->op = 0;
	if (env->verbose)
		ft_printf("fractale : %s\n", env->opc[env->op]);
}

void			down(t_fractenv *env)
{
	if (env->op > 0)
		env->op--;
	else
		env->op = 5;
	if (env->verbose)
		ft_printf("fractale : %s\n", env->opc[env->op]);
}

void			right(t_fractenv *env)
{
	if (env->i > 0x000001)
		env->i /= 256;
	else
		env->i = 0x010000;
	if (env->verbose)
		ft_printf("color mult: %d\n", env->i);
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
		env->it_max += 1;
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
