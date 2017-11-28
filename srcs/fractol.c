/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:43:11 by cbinet            #+#    #+#             */
/*   Updated: 2017/11/28 16:13:44 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	csquare(t_pixel *z)
{
	double	tmp;

	tmp = z->x;
	z->x = z->x * z->x - z->y * z->y;
	z->y = z->y * 2 * tmp;
}

void	init(t_fractenv *env)
{
	int fd;

	env->mlx = mlx_init();
	env->width = 2000;
	env->height = 1350;
	env->zoom = env->width / 2;
	env->mouse.x = 0;
	env->mouse.y = 0;
	env->x = -env->width / 2;
	env->y = -env->height / 2;
	env->min = -1000;
	env->max = 9;
	env->win = mlx_new_window(env->mlx, env->width, env->height, "fract");
	env->op = 0;
	env->opt[0] = &mand;
	env->opt[1] = &julia;
	env->opt[2] = &buddha;
	env->img2 = mlx_new_image(env->mlx, 2000, 1000);
	env->imgstr2 = (unsigned int *)mlx_get_data_addr(env->img2, &env->bpp,
			&env->sl, &env->end);
	fd = open("test.map", O_RDONLY);
	read(fd, env->imgstr2, 46080000);
	mlx_put_image_to_window(env->mlx, env->win, env->img2,
			(env->width - 2000) / 2, (env->height - 1000) / 4);
	close(fd);
	env->it_max = 10;
	env->i = 0x000100;
	env->mod = true;
}

int		main(void)
{
	t_fractenv env;

	init(&env);
	fract(&env, env.opt[env.op]);
	mlx_key_hook(env.win, &keypressed, &env);
	mlx_hook(env.win, MN, MM, &mousemove, &env);
	mlx_loop_hook(env.mlx, &mloop, &env);
	mlx_mouse_hook(env.win, &buttonpressed, &env);
	mlx_loop(env.mlx);
}
