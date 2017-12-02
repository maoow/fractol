/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractales.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:11:57 by cbinet            #+#    #+#             */
/*   Updated: 2017/11/30 13:41:20 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
bool	is_rbounded(t_fractenv *env, t_pixel a)
{
	double tmp;
	tmp = a.x * a.y + a.x * a.y;
	return (
			(tmp < env->max && tmp > env->min )
	       );
}
bool	is_bounded(t_fractenv *env, t_pixel a)
{
	double tmp;
	tmp = a.x * a.x + a.y * a.y;
	return (
			(tmp < env->max && tmp > env->min )
	       );
}

t_pixel	tju_op(t_pixel *a, t_pixel b)
{
	csquare(a);
	csquare(a);
	csquare(a);
	a->x += b.x;
	a->y += b.y;
	a->x += b.x;
	a->y += b.y;
	a->x += b.x;
	a->y += b.y;
	return (*a);
}

t_pixel	dju_op(t_pixel *a, t_pixel b)
{
	csquare(a);
	csquare(a);
	a->x += b.x;
	a->y += b.y;
	a->x += b.x;
	a->y += b.y;
	return (*a);
}

t_pixel	ju_op(t_pixel *a, t_pixel b)
{
	csquare(a);
	a->x += b.x;
	a->y += b.y;
	return (*a);
}


void	rdjulia(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	p.x = (env->mouse2.x - env->width / 2)/ 1000;
	p.y = (env->mouse2.y - env->height / 2)/ 1000;
	z.x = (((pixel.x - 2 + env->x) / env->zoom));
	z.y = (((pixel.y - 2 + env->y) / env->zoom));
	i = 0;
	while (++i < env->it_max && (is_bounded(env, z) || i == 0))
		dju_op(&z, p);
	if (i == env->it_max)
		addpixel(env, pixel, i);
}

void	djulia(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	p.x = (env->mouse2.x - env->width / 2)/ 1000;
	p.y = (env->mouse2.y - env->height / 2)/ 1000;
	z.x = (((pixel.x - 2 + env->x) / env->zoom));
	z.y = (((pixel.y - 2 + env->y) / env->zoom));
	i = 0;
	while (++i < env->it_max && (is_bounded(env, z) || i == 0))
		tju_op(&z, p);
	if (i != env->it_max)
		addpixel(env, pixel, i * env->i);
}

void	julia(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	p.x = (env->mouse2.x - env->width / 2)/ 1000;
	p.y = (env->mouse2.y - env->height / 2)/ 1000;
	z.x = (((pixel.x - 2 + env->x) / env->zoom));
	z.y = (((pixel.y - 2 + env->y) / env->zoom));
	i = 0;
	while (++i < env->it_max && (is_bounded(env, z) || i == 0))
		ju_op(&z, p);
	if (i != env->it_max)
		addpixel(env, pixel, i * env->i);
}

void	mand(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	p.x = (((pixel.x + env->x) / env->zoom));
	p.y = (((pixel.y + env->y) / env->zoom));
	z = p;
	i = 0;
	while (++i < env->it_max && (is_bounded(env, z) || i == 0))
		ju_op(&z, p);
	if (i == env->it_max)
		addpixel(env, pixel, env->it_max);
	else
		addpixel(env, pixel, i * env->i);
}

unsigned int get_color(t_fractenv *env, size_t i)
{
	unsigned int color;

	if (i < env->it_max /100)
		color= 0x010000;
	else if (i < 3 * env->it_max /10)
		color= 0x000100;
	else
		color= 0x000001;
	return (color);
}

void	buddha(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;
	unsigned int color;

	p.x = (((pixel.x + env->x) / env->zoom));
	p.y = (((pixel.y + env->y) / env->zoom));
	i = 0;
	z = p;
	while (++i < env->it_max && (is_bounded(env, z) || i == 0))
		env->imap[i] = ju_op(&z, p);
	if (i != env->it_max)
	{
		if (env->move)
			color = get_color(env, i);
		while (--i > 0)
		{
			if (!env->move)
				color = get_color(env, i);
			increasepixel(env, env->imap[i], color);
		}
	}
}
void	rbuddha(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;
	unsigned int color;

	p.x = (((pixel.x + env->x) / env->zoom));
	p.y = (((pixel.y + env->y) / env->zoom));
	i = 0;
	z = p;
	while (++i < env->it_max && (is_bounded(env, z) || i == 0))
		env->imap[i] = ju_op(&z, p);
			color = 0x01;
	if (i == env->it_max)
	{
		while (--i > 0)
		{
			increasepixel(env, env->imap[i], color);
		}
	}
}

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
	img = mlx_new_image(env->mlx, 90 , 60 );
	imgstr = (unsigned int *)mlx_get_data_addr(img, &env->bpp, &env->sl, &env->end);
	while (i < (5400 ) )
	{
		if (i % 90 == 0 || i % 90 == 89 || (i / 90) % 60 == 0 || (i / 90) % 60== 59)
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
	//mlx_string_put(env->mlx, env->win, 10, 80,0x00FF00, " \x01 \x02 \x03 \x10 \x11 \x1b");
	mlx_string_put(env->mlx, env->win, 10, 35,0x00FF00, "time :");
}

void	fract(t_fractenv *env, void (op(t_fractenv *, t_pixel)))
{
	t_pixel	z;
	clock_t t;	
	clock_t t2;	

	env->imap = (t_pixel *)malloc(env->it_max * sizeof(t_pixel));
	env->img = mlx_new_image(env->mlx, env->width, env->height);
	env->imgstr = (unsigned int *)mlx_get_data_addr(env->img, &env->bpp, &env->sl, &env->end);
	if (env->verbose)
	{
		//		printenv(env);
		//		mlx_string_put(env->mlx, env->win, 50, 35,0x00FF00, "-"); 
		t = clock();
	}
	z.x = 0;
	while (z.x < env->width)
	{
		z.y = 0;
		while (z.y < env->height)
		{
			op(env, z);
			z.y++;
		}
		if (env->verbose && (int)z.x % 12 == 0)
		{
			put_loading_logo(env, z.x);

		}
		z.x++;
	}
	t2 = clock();
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	if (env->verbose)
	{
		printenv(env);
		printf("time: %5.5f\n",(double)((t2 - t)) / CLOCKS_PER_SEC);
		mlx_string_put(env->mlx, env->win, 50, 35,0x00FF00, ft_itoa(((t2 - t) * 1000) / CLOCKS_PER_SEC)); 
	}
	mlx_destroy_image(env->mlx, env->img);
	free(env->imap);
}
/*
   int fd;
   ft_printf("%d\n", env->it_max);
   fd = open("test.map", O_WRONLY);
   write(fd, env->imgstr,
   env->width * env->height * sizeof(unsigned int) / sizeof(char));
   close(fd);
   ft_printf("%d\n", env->it_max);
   env->it_max += env->it_max;
   if (env->it_max > 100000)
   exit(0);
   ft_printf("%d\n", env->it_max);

   env->i *= 256;
   env->i %= 0xffffff;
   exit(0);
   */
