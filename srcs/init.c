/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 16:18:58 by cbinet            #+#    #+#             */
/*   Updated: 2017/12/11 08:59:40 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_fract		resetfract(t_fract fract)
{
	fract.img = NULL;
	fract.lastit = 0;
	fract.it_max = 16;
	fract.color = 0x000100;
	fract.colormode = 4;
	fract.x = -WIDTH / 2;
	fract.y = -HEIGHT / 2;
	fract.zoom = 350;
	return (fract);
}

t_fract		initfractale(char *name, t_pixel (*serie)(),
		void (*ffract)(), bool mdep)
{
	t_fract fract;

	if (!(fract.name = ft_strdup(name)))
		exit(1);
	fract = resetfract(fract);
	fract.serie = serie;
	fract.function = ffract;
	fract.min = 0;
	fract.mdep = mdep;
	fract.max = 4.5;
	return (fract);
}

void		initfract(t_fractenv *env)
{
	env->width = WIDTH;
	env->height = HEIGHT;
	env->move = true;
	env->mouse.x = 0;
	env->mouse.y = 0;
	env->op = 0;
	env->mod = true;
	env->verbose = true;
	env->move = true;
}

void		init(t_fractenv *env)
{
	env->fract[env->op] = initfractale("mand", &ju_op, &fract, 0);
	env->fract[++env->op] = initfractale("bship", &rju_op, &fract, 0);
	env->fract[++env->op] = initfractale("dmand", &dju_op, &fract, 0);
	env->fract[++env->op] = initfractale("tmand", &tju_op, &fract, 0);
	env->fract[++env->op] = initfractale("ju", &ju_op, &fract, 1);
	mousemove(877, 648, env);
	env->fract[++env->op] = initfractale("dju", &dju_op, &fract, 1);
	mousemove(902, 690, env);
	env->fract[++env->op] = initfractale("tju", &tju_op, &fract, 1);
	mousemove(1213, 650, env);
	env->fract[++env->op] = initfractale("absju", &mrju_op, &fract, 1);
	mousemove(1215, 623, env);
	env->fract[++env->op] = initfractale("buble", &ju_op, &fract, 1);
	env->fract[env->op].min = 0.145;
	mousemove(877, 648, env);
	env->fract[++env->op] = initfractale("dbuble", &dju_op, &fract, 1);
	env->fract[env->op].min = 0.145;
	mousemove(902, 690, env);
	env->fract[++env->op] = initfractale("tbuble", &tju_op, &fract, 1);
	env->fract[env->op].min = 0.145;
	mousemove(1213, 650, env);
	env->fract[++env->op] = initfractale("absbub", &mrju_op, &fract, 1);
	env->fract[env->op].min = 0.145;
	mousemove(1215, 623, env);
	env->fract[++env->op] = initfractale("buddha", &ju_op, &bfract, 0);
}
