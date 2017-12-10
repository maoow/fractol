/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:10:21 by cbinet            #+#    #+#             */
/*   Updated: 2017/12/10 15:10:36 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	csquare(t_pixel *z)
{
	double	tmp;

	tmp = z->x;
	z->x = z->x * z->x - z->y * z->y;
	z->y = z->y * 2 * tmp;
}

bool	is_bounded(t_fractenv *env, t_pixel a)
{
	double tmp;

	tmp = a.x * a.x + a.y * a.y;
	return ((tmp < env->fract[env->op].max && tmp > env->fract[env->op].min));
}
