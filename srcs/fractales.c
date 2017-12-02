/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractales.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:11:57 by cbinet            #+#    #+#             */
/*   Updated: 2017/11/30 13:41:20 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
static void	browse(t_fractenv *env, void (op(t_fractenv *, t_pixel)))
{
	t_pixel	z;

	z.x = 0;
	while (z.x < env->width)
	{
		z.y = 0;
		while (z.y < env->height)
		{
			op(env, z);
			z.y++;
		}
		if (env->verbose && (int)z.x % 12 == 0)
			put_loading_logo(env, (int)z.x);
		z.x++;
	}
}

void	fract(t_fractenv *env, void (op(t_fractenv *, t_pixel)))
{
	clock_t t;	
	clock_t t2;	

	env->imap = (t_pixel *)malloc(env->it_max * sizeof(t_pixel));
	env->img = mlx_new_image(env->mlx, env->width, env->height);
	env->imgstr = (unsigned int *)mlx_get_data_addr(env->img, &env->bpp, &env->sl, &env->end);
	t = clock();
browse(env, op);
	t2 = clock();
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	if (env->verbose)
	{
		printenv(env);
		printf("time: %5.5f\n",(double)((t2 - t)) / CLOCKS_PER_SEC);
		mlx_string_put(env->mlx, env->win, 50, 35,0x00FF00, ft_itoa(((t2 - t) * 1000) / CLOCKS_PER_SEC)); 
	}
	mlx_destroy_image(env->mlx, env->img);
	free(env->imap);
}
