/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:17:10 by cbinet            #+#    #+#             */
/*   Updated: 2017/12/11 09:40:13 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int	modcolor(t_fract fract, size_t i)
{
	unsigned int color;

	if (i % 3 == 0)
		color = fract.color;
	else if (i % 3 == 1)
	{
		if (fract.color > 0x1)
			color = fract.color / 0x100;
		else
			color = 0x10000;
		color = 0x010101 - color;
	}
	else
	{
		if (fract.color < 0x10000)
			color = fract.color * 0x100;
		else
			color = 0x1;
		color = 0x010101 - color;
	}
	return (color);
}

unsigned int	ratiocolor(t_fract fract, size_t i)
{
	unsigned int color;

	if (i < fract.it_max / 3)
		color = fract.color;
	else if (i < 2 * fract.it_max / 3)
	{
		if (fract.color > 0x1)
			color = fract.color / 0x100;
		else
			color = 0x10000;
		color = 0x010101 - color;
	}
	else
	{
		if (fract.color < 0x10000)
			color = fract.color * 0x100;
		else
			color = 0x1;
		color = 0x010101 - color;
	}
	return (color);
}

unsigned int	get_color(t_fract fract, size_t i)
{
	unsigned int color;

	if (fract.colormode <= 1)
		return (fract.color);
	else if (fract.colormode <= 3)
		return (modcolor(fract, i));
	else
		return (ratiocolor(fract, i));
	return (color);
}

void			increasepixel(t_fractenv *env, t_pixel pixel,
		unsigned int color)
{
	size_t place;

	pixel.y *= env->fract[env->op].zoom;
	pixel.x *= env->fract[env->op].zoom;
	pixel.y -= env->fract[env->op].x;
	pixel.x -= env->fract[env->op].y;
	place = (size_t)pixel.y + (size_t)pixel.x * env->width;
	if (place < (size_t)env->width * env->height)
	{
		if ((size_t)env->imgstr[place] + (size_t)color < 0x1000000)
			env->imgstr[place] += (unsigned int)color;
	}
}

void			addpixel(t_fractenv *env, t_pixel pixel, int color)
{
	if (env->fract[env->op].colormode % 2 == 1)
	{
		color = 0xffffff ^ color;
		if (color % 0x100 > 0xd0 && color / 0x10000 > 0xd0 &&
				(color % 0x10000) / 0x100 > 0xd0)
			color = 0x111111;
	}
	env->imgstr[(int)pixel.x + (int)pixel.y * (int)env->width] =
		(unsigned int)color;
}
