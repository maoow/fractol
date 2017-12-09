/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:17:10 by cbinet            #+#    #+#             */
/*   Updated: 2017/12/04 13:24:45 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_loading_logo(t_fractenv *env, int x)
{
	void	*img;
	unsigned int *imgstr;
	size_t		i;
	char		*tmp;

	i = 0;
	img = mlx_new_image(env->mlx, env->width , 1 );
	imgstr = (unsigned int *)mlx_get_data_addr(img, &env->bpp, &env->sl, &env->end);
	while (i < (size_t)env->width)
	{
		imgstr[i ] = 0x00ff00;
		i++;
	}
	mlx_put_image_to_window(env->mlx, env->win, img, 0, 16);
	mlx_put_image_to_window(env->mlx, env->win, img, 0, 2);
	mlx_string_put(env->mlx, env->win,x / 2 + env->width / 2 , 14,0x008833, "#");
	mlx_string_put(env->mlx, env->win,(-x / 2) + env->width / 2 , 14,0x008833, "#");
	mlx_string_put(env->mlx, env->win, env->width / 2 - 2, 14,0xff, "\x2");
	mlx_string_put(env->mlx, env->win, env->width / 2 - 1, 14,0xff, "\x2");
	mlx_string_put(env->mlx, env->win, env->width / 2 + 1, 14,0xff, "\x2");
	mlx_string_put(env->mlx, env->win, env->width / 2 + 2, 14,0xff, "\x2");
	mlx_string_put(env->mlx, env->win, env->width / 2 + 3, 14,0xff, "\x2");
	mlx_string_put(env->mlx, env->win, env->width / 2 + 4, 14,0xff, "\x2");
	mlx_string_put(env->mlx, env->win, env->width / 2 + 5, 14,0xff, "\x2");
	mlx_string_put(env->mlx, env->win, env->width / 2 + 6, 14,0xff, "\x2");
	mlx_string_put(env->mlx, env->win, env->width / 2 + 7, 14,0xff, "\x2");
	mlx_string_put(env->mlx, env->win, env->width / 2 + 8, 14,0xff, "\x2");
	mlx_string_put(env->mlx, env->win, env->width / 2 + 9, 14,0xff, "\x2");
	mlx_string_put(env->mlx, env->win, env->width / 2 + 10, 14,0xff, "\x2");
	mlx_string_put(env->mlx, env->win, env->width / 2 + 11, 14,0xff, "\x2");
	mlx_string_put(env->mlx, env->win, env->width / 2 + 12, 14,0xff, "\x2");
	tmp = ft_itoa((x * 100) / env->width);
	mlx_string_put(env->mlx, env->win, env->width / 2 , 14,0xffff00, tmp);
	free(tmp);
	mlx_string_put(env->mlx, env->win, env->width / 2 + 12, 14,0xffff00, 
			"%");
	mlx_do_sync(env->mlx);
	mlx_destroy_image(env->mlx, img);

}
void	printenv(t_fractenv *env)
{
	void	*img;
	unsigned int *imgstr;
	size_t		i;
	char *tmp;

	i = 0;
	img = mlx_new_image(env->mlx, 90 , 80 );
	imgstr = (unsigned int *)mlx_get_data_addr(img, &env->bpp, &env->sl, &env->end);
	while (i < (7200 ))
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
	tmp = ft_itoa(env->fract[env->op].it_max);
	mlx_string_put(env->mlx, env->win, 50, 55,0x00FF00, tmp );
	free(tmp);
	mlx_string_put(env->mlx, env->win, 10, 75,0x00FF00, "frac :");
	mlx_string_put(env->mlx, env->win, 50, 75,0x00FF00, env->fract[env->op].name);
	mlx_string_put(env->mlx, env->win, 10, 95,0x00FF00, "col  :");
	tmp = ft_itoa(env->fract[env->op].colormode);
	mlx_string_put(env->mlx, env->win, 50, 95,0x00FF * env->fract[env->op].color,
			tmp);
	free(tmp);
	mlx_string_put(env->mlx, env->win, 10, 35,0x00FF00, "time :");
}

unsigned int	modcolor(t_fract fract, size_t i)
{
	unsigned int color;

	if (i % 3 == 0)
		color= fract.color;
	else if (i % 3 == 1)
	{
		if (fract.color > 0x1)
			color = fract.color / 0x100;
		else
			color =0x10000;
		color= 0x010101 - color;
	}
	else
	{
		if (fract.color < 0x10000)
			color = fract.color * 0x100;
		else
			color =0x1;
		color= 0x010101 - color;
	}
	return (color);
}

unsigned int	ratiocolor(t_fract fract, size_t i)
{
	unsigned int color;

	if (i < fract.it_max / 3)
		color= fract.color;
	else if (i < 2 * fract.it_max / 3)
	{
		if (fract.color > 0x1)
			color = fract.color / 0x100;
		else
			color =0x10000;
		color= 0x010101 - color;
	}
	else
	{
		if (fract.color < 0x10000)
			color = fract.color * 0x100;
		else
			color =0x1;
		color= 0x010101 - color;
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
		return(ratiocolor(fract, i));
	return (color);
}

void	increasepixel(t_fractenv *env, t_pixel pixel, unsigned int color)
{
	size_t place;
	pixel.y *= env->fract[env->op].zoom;
	pixel.x *= env->fract[env->op].zoom;
	pixel.y -= env->fract[env->op].x;
	pixel.x -= env->fract[env->op].y;
	place = (size_t)pixel.y + (size_t)pixel.x * env->width;
	if (place <= (size_t)env->width * env->height)
	{
		if ((size_t)env->imgstr[place] + (size_t)color < 0x1000000)
			env->imgstr[place] += (unsigned int)color;
	}
}

void	addpixel(t_fractenv *env, t_pixel pixel, int color)
{
	if (env->fract[env->op].colormode % 2 == 1)
	{
		color = 0xffffff ^ color;
		color = 0x0f0f0f & color;
		color *= 0x10 ;
	}
	env->imgstr[(int)pixel.x + (int)pixel.y * (int)env->width] = (unsigned int)color;
}
