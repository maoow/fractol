/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:17:10 by cbinet            #+#    #+#             */
/*   Updated: 2017/11/30 18:46:09 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	increasepixel(t_fractenv *env, t_pixel pixel, unsigned int color)
{
	pixel.y *= env->zoom;
	pixel.y -= env->x;// / 2;
	pixel.x *= env->zoom;
	pixel.x -= env->y;// / 2;
	color *= (0xf0 / sqrt(env->it_max)) + 1;
	if (color == 0)
		color++;
	if (pixel.y < env->width && pixel.x < env->height && pixel.y >= 0 &&
			pixel.x >= 0)
	{
		if (env->imgstr[(int)pixel.y + (int)pixel.x * env->width] + color < 0x1000000)
			env->imgstr[(int)pixel.y + (int)pixel.x * env->width] +=
				(unsigned int)color;
		//else
			//env->imgstr[(int)pixel.y + (int)pixel.x * env->width] =
				//(env->imgstr[(int)pixel.y + (int)pixel.x * env->width] + color) / 0x1000000;
	}
}

void	addpixel(t_fractenv *env, t_pixel pixel, int color)
{
	//if (color >= env->i * 0x100)
	//color = env->i * 0xff;
color *= 0xff + env->zoom / 0xff;
color /= env->it_max;// / env->zoom );
	env->imgstr[(int)pixel.x + (int)pixel.y * env->width] = (unsigned int)color;
}
