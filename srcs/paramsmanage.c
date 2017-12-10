/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paramsmanage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:20:40 by cbinet            #+#    #+#             */
/*   Updated: 2017/12/10 15:20:55 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			reset(t_fractenv *env)
{
	if (env->fract[env->op].img)
		mlx_destroy_image(env->mlx, env->fract[env->op].img);
	env->fract[env->op] = resetfract(env->fract[env->op]);
}

void			colorup(t_fractenv *env)
{
	if (env->fract[env->op].color < 0x10000)
		env->fract[env->op].color *= 0x100;
	else
		env->fract[env->op].color = 0x1;
}

void			move(t_fractenv *env)
{
	env->move = !env->move;
}
