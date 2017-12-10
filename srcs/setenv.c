/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:19:09 by cbinet            #+#    #+#             */
/*   Updated: 2017/12/10 16:07:07 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			higher(t_fractenv *env)
{
	if (env->fract[env->op].it_max > 15 && env->fract[env->op].it_max < 4096)
		env->fract[env->op].it_max += env->fract[env->op].it_max / 8;
	else
		env->fract[env->op].it_max++;
}

void			lower(t_fractenv *env)
{
	if (env->fract[env->op].it_max > 16)
		env->fract[env->op].it_max -= env->fract[env->op].it_max / 8;
	else if (env->fract[env->op].it_max > 1)
		env->fract[env->op].it_max--;
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
	}
	else
	{
		env->fract[env->op].zoom *= 2;
		env->fract[env->op].x += (env->fract[env->op].x + env->width / 2);
		env->fract[env->op].y += (env->fract[env->op].y + env->height / 2);
	}
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
}

void			verbose(t_fractenv *env)
{
	env->verbose = !env->verbose;
}
