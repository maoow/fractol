/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:40:01 by cbinet            #+#    #+#             */
/*   Updated: 2017/11/28 15:00:37 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		quit(t_fractenv *env)
{
	exit(0);
}

int			g_button[B_NB] =
{
	3,
	4,
	5,
	1,
	108
};

void		(*g_buttonf[B_NB])() =
{
	&zoom,
	&zoom,
	&dezoom,
	&dezoom,
	&right
};

int			g_key[K_NB] =
{
	K_Q,
	K_H,
	K_J,
	K_K,
	K_L,
	K_F,
	K_D,
	K_M,
	K_COMMA
};

void		(*g_keyf[K_NB])() =
{
	&quit,
	&left,
	&down,
	&up,
	&right,
	&higher,
	&lower,
	&zoom,
	&dezoom
};

int			mloop(t_fractenv *env)
{
	if (env->mod)
	{
		fract(env, env->opt[env->op]);
		env->mod =false;
	}
	return (0);
}

int			loop(int key, int x, int y, t_fractenv *env)
{
	return (0);
}

int			loopachieved(t_fractenv *env)
{
	return (0);
}

int			mousemove(int x, int y, t_fractenv *env)
{
	size_t		count;

	count = 0;
	ft_printf("%d,%d\n", env->x, env->y);
	env->mouse.x = x;
	env->mouse.y = y;
	if (env->op == 1)
			env->mod = true;
	return (0);
}

int			buttonpressed(int key, int x, int y, t_fractenv *env)
{
	size_t		count;

	count = 0;
	env->key = key;
	while (count < K_NB)
	{
		if (key == g_button[count])
		{
			g_buttonf[count](env);
			env->mod = true;
		}
		count++;
	}
	fract(env, env->opt[env->op]);
	return (0);
}

int			keypressed(int key, t_fractenv *env)
{
	size_t		count;

	count = 0;
	env->key = key;
	while (count < K_NB && key != g_key[count])
		count++;
	if (count < K_NB)
	{
		g_keyf[count](env);
		env->mod = true;
	}
	else
		ft_printf("%d\n", key);
	fract(env, env->opt[env->op]);
	return (0);
}
