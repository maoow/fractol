/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:43:11 by cbinet            #+#    #+#             */
/*   Updated: 2017/12/04 11:04:40 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_fract resetfract(t_fract fract)
{
	fract.img = NULL;
	fract.lastit = 0;
	fract.it_max = 4;
	fract.color = 0x000100;
	fract.colormode = 2;
	fract.x = -650;
	fract.y = -450;
	//fract.zoom = env->width / 8;
	fract.zoom = 200;
	return (fract);
}
t_fract	initfractale(char *name, t_pixel (*serie)(), void (*ffract)(), t_pixel lim, bool mdep)
{
	t_fract fract;
	fract = resetfract(fract);
	fract.name = ft_strdup(name);
	fract.serie = serie;
	fract.function = ffract;
	fract.min = lim.x;
	fract.max = lim.y;
	fract.mdep = mdep;
	return (fract);
}

void	initfract(t_fractenv *env)
{
	env->move = false;
	env->mouse.x = 0;
	env->mouse.y = 0;
	env->op = 0;
	env->mod = true;
	env->verbose = true;
}

void	init(t_fractenv *env)
{

	t_pixel	reglim;
	t_pixel	bublim;
	reglim.x = 0;
	reglim.y = 4.5;
	bublim.x = 0.145;
	bublim.y = 4.5;
	env->mlx = mlx_init();
	env->width = 1350;
	env->height = 760;
env->move = true;
env->op = 0;
	env->fract[env->op] = initfractale("mand", &ju_op, &fract, reglim, false);
	env->fract[++env->op] = initfractale("bship", &rju_op, &fract, reglim, false);
	env->fract[++env->op] = initfractale("dmand", &dju_op, &fract, reglim, false);
	env->fract[++env->op] = initfractale("tmand", &tju_op, &fract, reglim, false);
	env->fract[++env->op] = initfractale("ju", &ju_op, &fract, reglim, true);
mousemove(317, 318, env);
	env->fract[++env->op] = initfractale("dju", &dju_op, &fract, reglim, true);
mousemove(452, 317, env);
	env->fract[++env->op] = initfractale("tju", &tju_op, &fract, reglim, true);
mousemove(577, 389, env);
	env->fract[++env->op] = initfractale("absju", &mrju_op, &fract, reglim, true);
mousemove(589, 328, env);
	env->fract[++env->op] = initfractale("buble", &ju_op, &fract, bublim, true);
mousemove(788, 491, env);
	env->fract[++env->op] = initfractale("dbuble", &dju_op, &fract, bublim, true);
mousemove(581, 517, env);
	env->fract[++env->op] = initfractale("tbuble", &tju_op, &fract, bublim, true);
mousemove(615, 442, env);
	env->fract[++env->op] = initfractale("absbuble", &mrju_op, &fract, bublim, true);
mousemove(551, 437, env);
	env->fract[++env->op] = initfractale("buddha", &ju_op, &bfract, reglim, false);
mousemove(317, 318, env);
	initfract(env);
	env->win = NULL;
env->op = 0;
	//while (env->op < NB_FRACT)
	//{
		//env->fract[env->op].colormode = env->op % 6;
		//if (env->op % 3 == 1)
			//env->fract[env->op].color = 0x100;
		//else if (env->op % 3 == 2)
			//env->fract[env->op].color = 0x10000;
		//env->fract[env->op].function(env);
		//env->op++;
	//}
	env->move = false;
//	env->fract[12].it_max = 2000;
	env->op = 12;
	env->win = mlx_new_window(env->mlx, env->width, env->height, "fract");
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
