/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:40:01 by cbinet            #+#    #+#             */
/*   Updated: 2017/11/30 13:38:14 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		quit()
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
	K_V,
	K_H,
	K_K,
	K_J,
	K_L,
	K_F,
	K_D,
	K_U,
	K_M,
	K_COMMA
};

void		(*g_keyf[K_NB])() =
{
	&quit,
	&verbose,
	&left,
	&down,
	&up,
	&move,
	&higher,
	&lower,
	&colorup,
	&zoom,
	&dezoom
};

int			mloop(t_fractenv *env)
{
	if (env->mod)
	{
		env->mod =false;
		env->fract[env->op].function(env);
		env->fract[env->op].lastit = env->it_max;
	}
	return (0);
}


int			mousemove(int x, int y, t_fractenv *env)
{

if (env->move && env->fract[env->op].mdep && x >= 0 && y >= 0 && x <= env->width && y <= env->height)
{
	env->mouse2.x = x;
	env->mouse2.y = y;
			env->mod = true;
}
	env->mouse.x = x;
	env->mouse.y = y;
	return (0);
}

int			buttonpressed(int key, int x, int y, t_fractenv *env)
{
	size_t		count;

	env->mouse.x = x;
	env->mouse.y = y;
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
	return (0);
}

int			keypressed(int key, t_fractenv *env)
{
	size_t		count;

		if (!env->mod)
{
	count = 0;
	env->key = key;
	while (count < K_NB && key != g_key[count])
		count++;
	if (count < K_NB)
	{
		env->mod = true;
		g_keyf[count](env);
	}
	else
		ft_printf("%d\n", key);
}
	return (0);
}
