/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printenv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:13:38 by cbinet            #+#    #+#             */
/*   Updated: 2017/12/10 15:13:51 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			printenv(t_fractenv *env)
{
	char *tmp;

	mlx_string_put(env->mlx, env->win, 10, 55, 0x00FF00, "imax :");
	tmp = ft_itoa(env->fract[env->op].it_max);
	mlx_string_put(env->mlx, env->win, 80, 55, 0x00FF00, tmp);
	free(tmp);
	mlx_string_put(env->mlx, env->win, 10, 75, 0x00FF00, "frac :");
	mlx_string_put(env->mlx, env->win, 80, 75, 0x00FF00,
			env->fract[env->op].name);
	mlx_string_put(env->mlx, env->win, 10, 95, 0x00FF00, "col  :");
	tmp = ft_itoa(env->fract[env->op].colormode);
	mlx_string_put(env->mlx, env->win, 80, 95,
			0x00FF * env->fract[env->op].color, tmp);
	free(tmp);
	mlx_string_put(env->mlx, env->win, 10, 35, 0x00FF00, "time :");
}
