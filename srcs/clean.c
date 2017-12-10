/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:16:18 by cbinet            #+#    #+#             */
/*   Updated: 2017/12/10 15:16:26 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		fractclean(t_fractenv *env)
{
	size_t	op;

	op = 0;
	while (op < NB_FRACT)
	{
		free(env->fract[op].name);
		if (env->fract[op].img)
			mlx_destroy_image(env->mlx, env->fract[op].img);
		op++;
	}
}
