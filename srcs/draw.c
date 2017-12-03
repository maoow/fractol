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

void	put_loading_logo(t_fractenv *env, int x)
{
	void	*img;
	unsigned int *imgstr;
	size_t		i;

	i = 0;
	img = mlx_new_image(env->mlx, env->width , 1 );
	imgstr = (unsigned int *)mlx_get_data_addr(img, &env->bpp, &env->sl, &env->end);
	while (i < (env->width ) )
	{
		imgstr[i ] = 0x00ff00;
		i++;
	}
	mlx_put_image_to_window(env->mlx, env->win, img, 0, 16);
	mlx_put_image_to_window(env->mlx, env->win, img, 0, 2);
	mlx_string_put(env->mlx, env->win,x / 2 + env->width / 2 , 14,0x008833, "\x2");
	mlx_string_put(env->mlx, env->win,(-x / 2) + env->width / 2 , 14,0x008833, "\x2");
	mlx_string_put(env->mlx, env->win, env->width / 2 - 5, 14,0xff, "\x2\x2\x2\x2");
	mlx_string_put(env->mlx, env->win, env->width / 2 - 6, 14,0xff, "\x2\x2\x2\x2");
	mlx_string_put(env->mlx, env->win, env->width / 2 , 14,0x00, ft_itoa((x * 100) / env->width));
	mlx_string_put(env->mlx, env->win, env->width / 2 + 12, 14,0x00, 
			"%");
	mlx_do_sync(env->mlx);
	mlx_destroy_image(env->mlx, img);

}
void	printenv(t_fractenv *env)
{
	void	*img;
	unsigned int *imgstr;
	size_t		i;

	i = 0;
	img = mlx_new_image(env->mlx, 90 , 80 );
	imgstr = (unsigned int *)mlx_get_data_addr(img, &env->bpp, &env->sl, &env->end);
	while (i < (7200 ) )
	{
		if (i % 90 == 0 || i % 90 == 89 || (i / 90) % 80 == 0 || (i / 90) % 80== 79)
			imgstr[i] = 0x008888;
		else
			imgstr[i ] = 0x001111;
		i++;
	}
	mlx_put_image_to_window(env->mlx, env->win, img, 3, 22);
	mlx_destroy_image(env->mlx, img);

	mlx_string_put(env->mlx, env->win, 10, 55,0x00FF00, "imax :");
	mlx_string_put(env->mlx, env->win, 50, 55,0x00FF00, ft_itoa(env->it_max));
	mlx_string_put(env->mlx, env->win, 10, 75,0x00FF00, "frac :");
	mlx_string_put(env->mlx, env->win, 50, 75,0x00FF00, env->opc[env->op]);
	mlx_string_put(env->mlx, env->win, 10, 95,0x00FF00, "col  :");
	mlx_string_put(env->mlx, env->win, 50, 95,0x00FF * env->color, ft_itoa(env->colormode));
	//mlx_string_put(env->mlx, env->win, 10, 80,0x00FF00, " \x01 \x02 \x03 \x10 \x11 \x1b");
	mlx_string_put(env->mlx, env->win, 10, 35,0x00FF00, "time :");
}

unsigned int get_color(t_fractenv *env, size_t i)
{
	unsigned int color;

	if (env->colormode == 0)
	{
		return (env->color);
	}
	else if (env->colormode <= 2)
	{
		if (i % 3 == 0)
			color= env->color;
		else if (i % 3 == 1)
		{
			if (env->color > 0x1)
				color = env->color / 0x100;
			else
				color =0x10000;
			color= 0x010101 - color;
		}
		else
		{
			if (env->color < 0x10000)
				color = env->color * 0x100;
			else
				color =0x1;
			color= 0x010101 - color;
		}
	}
	else
	{
		if (i < 3 * env->it_max / 100)
			color= env->color;
		else if (i < 3 * env->it_max / 10)
		{
			if (env->color > 0x1)
				color = env->color / 0x100;
			else
				color =0x10000;
			color= 0x010101 - color;
		}
		else
		{
			if (env->color < 0x10000)
				color = env->color * 0x100;
			else
				color =0x1;
			color= 0x010101 - color;
		}
	}
	return (color);
}

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
	if (env->colormode == 0)
		color = (color * 0xffffff) / env->it_max;
	else if (env->colormode <= 2)
		color = (color);
	else if (env->colormode <= 4)
		color = (env->color * color);
	else if (color != env->it_max)
	{
		color *= 0xff;
		color /= (int)env->it_max;
		color %= 0xff;
		color *= env->color;
	}
	else
		color = env->color * 0xff;
	env->imgstr[(int)pixel.x + (int)pixel.y * env->width] = (unsigned int)color;
}
