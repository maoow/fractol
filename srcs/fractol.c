/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:43:11 by cbinet            #+#    #+#             */
/*   Updated: 2017/11/30 18:42:14 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init(t_fractenv *env)
{
	int fd;

	env->mlx = mlx_init();
	env->move = false;
	env->width = 1350;
	env->height = 750;
	env->zoom = env->width / 8;
	env->mouse.x = 0;
	env->mouse.y = 0;
	env->mouse2.x = env->width / 2;
	env->mouse2.y = env->width / 2;
	env->x = -env->width / 2;
	env->y = -(env->height) / 2;
	env->min = -env->height ;// 2;
	env->max = env->height ;// 2;
	env->min = 0;
	env->max = 4.5;
	env->win = mlx_new_window(env->mlx, env->width, env->height, "fract");
	env->op = 3;
	env->opt[0] = &mand;
	env->opc[0] = ft_strdup("mand");
	env->opt[1] = &dmand;
	env->opc[1] = ft_strdup("dmand");
	env->opt[2] = &tmand;
	env->opc[2] = ft_strdup("tmand");
	env->opt[3] = &buddha;
	env->opc[3] = ft_strdup("buddha");
	env->opt[4] = &rbuddha;
	env->opc[4] = ft_strdup("rbuddha");
	env->opt[5] = &julia;
	env->opc[5] = ft_strdup("julia");
	env->opt[6] = &djulia;
	env->opc[6] = ft_strdup("djulia");
	env->opt[7] = &tjulia;
	env->opc[7] = ft_strdup("tjulia");
	env->opt[8] = &julia;
	env->opc[8] = ft_strdup("bubble");
	env->opt[9] = &djulia;
	env->opc[9] = ft_strdup("dbubble");
	env->opt[10] = &tjulia;
	env->opc[10] = ft_strdup("tbubble");
	env->opt[11] = &bship;
	env->opc[11] = ft_strdup("bship");
	env->it_max = 50;
	env->color = 0x000100;
	env->colormode = 5;
	env->mod = true;
	env->verbose = true;
}

int		main(void)
{
	t_fractenv env;

	init(&env);
	mlx_key_hook(env.win, &keypressed, &env);
	mlx_hook(env.win, MN, MM, &mousemove, &env);
	mlx_loop_hook(env.mlx, &mloop, &env);
	mlx_mouse_hook(env.win, &buttonpressed, &env);
	mlx_loop(env.mlx);
}
