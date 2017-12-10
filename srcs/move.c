/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:36:52 by cbinet            #+#    #+#             */
/*   Updated: 2017/12/10 16:12:47 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	if (env->fract[env->op].img)
	{
		mlx_put_image_to_window(env->mlx, env->win, env->fract[env->op].img,
				0, 0);
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
	if (env->fract[env->op].img)
	{
		mlx_put_image_to_window(env->mlx, env->win, env->fract[env->op].img,
				0, 0);
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
}
