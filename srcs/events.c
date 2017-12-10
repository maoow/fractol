/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:40:01 by cbinet            #+#    #+#             */
/*   Updated: 2017/12/10 16:13:21 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		quit(void)
{
	exit(0);
}

int			mloop(t_fractenv *env)
{
	if (env->mod)
	{
		env->mod = false;
		env->fract[env->op].function(env);
	}
	return (0);
}

int			mousemove(int x, int y, t_fractenv *env)
{
	if (env->move && env->fract[env->op].mdep
			&& x >= 0 && y >= 0 && x <= env->width && y <= env->height)
	{
		env->fract[env->op].mouse.x = (double)(x - env->width / 2) / 300;
		env->fract[env->op].mouse.y = (double)(y - env->height / 2) / 300;
		env->mod = true;
	}
	env->mouse.x = x;
	env->mouse.y = y;
	return (0);
}

int			buttonpressed(int key, int x, int y, t_fractenv *env)
{
	size_t		count;
	const int	buttont[B_NB] =
	{ 4, 5};
	void		(*const buttonf[B_NB])() =
	{ &zoom, &dezoom};

	env->mouse.x = x;
	env->mouse.y = y;
	count = 0;
	env->key = key;
	while (count < B_NB)
	{
		if (key == buttont[count])
		{
			buttonf[count](env);
			env->mod = true;
		}
		count++;
	}
	return (0);
}

int			keypressed(int key, t_fractenv *env)
{
	size_t			count;
	void			(*const keyf[K_NB])() =
	{ &quit, &verbose, &left, &down, &up, &move, &higher,
		&lower, &colorup, &zoom, &dezoom, &reset};
	const int		keyt[K_NB] =
	{ K_Q, K_V, K_H, K_K, K_J, K_L, K_F, K_D, K_U, K_M, K_COMMA, K_I};

	count = 0;
	while (count < K_NB && key != keyt[count])
		count++;
	if (env->mod || count >= K_NB)
		return (0);
	env->key = key;
	env->mod = true;
	keyf[count](env);
	return (0);
}
