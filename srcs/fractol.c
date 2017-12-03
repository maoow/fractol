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

t_fract	initfractale(char *name, t_pixel (*serie)(), void (*ffract)(), t_pixel lim, bool mdep)
{
	t_fract fract;
	fract.name = ft_strdup(name);
	fract.serie = serie;
	fract.function = ffract;
	fract.min = lim.x;
	fract.max = lim.y;
	fract.mdep = mdep;
	fract.img = NULL;
	fract.lastit = 0;
	return (fract);
}

void	initfract(t_fractenv *env)
{
	t_pixel	reglim;
	t_pixel	bublim;
	reglim.x = 0;
	reglim.y = 4.5;
	bublim.x = 0.015;
	bublim.y = 4.5;
	env->zoom = env->width / 8;
	env->mouse.x = 0;
	env->mouse.y = 0;
	env->mouse2.x = env->width / 2;
	env->mouse2.y = env->width / 2;
	env->x = -env->width / 2;
	env->y = -(env->height) / 2;
	env->min = -env->height ;// 2;
	env->max = env->height ;// 2;
	env->it_max = 50;
	env->color = 0x000100;
	env->colormode = 0;
	env->fract[1] = initfractale("bship", &rju_op, &fract, reglim, false);
	env->fract[0] = initfractale("mand", &ju_op, &fract, reglim, false);
	env->fract[2] = initfractale("dmand", &dju_op, &fract, reglim, false);
	env->fract[3] = initfractale("tmand", &tju_op, &fract, reglim, false);
	env->fract[4] = initfractale("ju", &ju_op, &fract, reglim, true);
	env->fract[5] = initfractale("dju", &dju_op, &fract, reglim, true);
	env->fract[6] = initfractale("tju", &tju_op, &fract, reglim, true);
	env->fract[7] = initfractale("absju", &mrju_op, &fract, reglim, true);
	env->fract[8] = initfractale("buble", &ju_op, &fract, bublim, true);
	env->fract[9] = initfractale("dbuble", &dju_op, &fract, bublim, true);
	env->fract[10] = initfractale("tbuble", &tju_op, &fract, bublim, true);
	env->fract[11] = initfractale("absbuble", &mrju_op, &fract, bublim, true);
	env->fract[12] = initfractale("buddha", &ju_op, &bfract, reglim, false);
}

void	init(t_fractenv *env)
{

	env->mlx = mlx_init();
	env->move = false;
	env->width = 1350;
	env->height = 750;
	env->win = mlx_new_window(env->mlx, env->width, env->height, "fract");
	//initmand(env, &(env->fract[1]));
	//initdmand(env, &(env->fract[2]));
	env->op = 0;

	initfract(env);

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
