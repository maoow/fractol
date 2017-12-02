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
	size_t place;
	pixel.y *= env->zoom;
	pixel.x *= env->zoom;
	pixel.y -= env->x;
	pixel.x -= env->y;
	place = (size_t)pixel.y + (size_t)pixel.x * env->width;
	if (place <= env->width * env->height)
		env->imgstr[place] += (unsigned int)color;
}

void	addpixel(t_fractenv *env, t_pixel pixel, int color)
{
	color *= 0xff;
	color /= env->it_max;
	env->imgstr[(int)pixel.x + (int)pixel.y * env->width] = (unsigned int)color;
}
