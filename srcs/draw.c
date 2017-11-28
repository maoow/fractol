/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:17:10 by cbinet            #+#    #+#             */
/*   Updated: 2017/11/28 14:38:13 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	increasepixel(t_fractenv *env, t_pixel pixel, int color)
{
	pixel.y *= env->zoom;
	pixel.y += env->height / 2;
	pixel.x *= env->zoom;
	pixel.x += env->width / 2;
	if (pixel.y < env->width && pixel.x < env->height && pixel.y >= 0 &&
			pixel.x >= 0)
		if (env->imgstr[(int)pixel.y + (int)pixel.x * env->width] < 0x1000000)
			env->imgstr[(int)pixel.y + (int)pixel.x * env->width] +=
				(unsigned int)color;
}

void	addpixel(t_fractenv *env, t_pixel pixel, int color)
{
	env->imgstr[(int)pixel.x + (int)pixel.y * env->width] = (unsigned int)color;
}
