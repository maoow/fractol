/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:43:11 by cbinet            #+#    #+#             */
/*   Updated: 2017/11/30 18:42:14 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	csquare(t_pixel *z)
{
	long double	tmp;

	tmp = z->x;
	z->x = z->x * z->x - z->y * z->y;
	z->y = z->y * 2 * tmp;
}

void	init(t_fractenv *env)
{
	int fd;

	env->mlx = mlx_init();
	env->move = false;
	env->width = 1350;
	env->height = 750;
	env->zoom = env->width / 8;
	env->mouse.x = 0;
	env->mouse.y = 0;
	env->x = -env->width / 2;
	env->y = -(2 * env->height) / 3;
/*
	env->x = -156680112740850656;
	env->y = 136003;
	env->zoom = 83121335602583760;
*/
	env->min = -env->height ;// 2;
	env->max = env->height ;// 2;
	env->min = 0;
	env->max = 4.5;
	env->win = mlx_new_window(env->mlx, env->width, env->height, "fract");
	env->op = 1;
	env->opt[0] = &mand;
	env->opt[1] = &julia;
	env->opt[4] = &djulia;
	env->opt[5] = &rdjulia;
	env->opt[2] = &buddha;
	env->opt[3] = &rbuddha;
	env->opc[0] = ft_strdup("mand");
	env->opc[1] = ft_strdup("julia");
	env->opc[4] = ft_strdup("djulia");
	env->opc[5] = ft_strdup("rdjulia");
	env->opc[2] = ft_strdup("buddha");
	env->opc[3] = ft_strdup("buddhar");
	env->it_max = 50;

	env->i = 0x000001;
	env->mod = true;
	env->verbose = true;
	env->verbose = true;
/*
	env->img2 = mlx_new_image(env->mlx, 2000, 1000);
	env->imgstr2 = (unsigned int *)mlx_get_data_addr(env->img2, &env->bpp,
			&env->sl, &env->end);
	fd = open("test.map", O_RDONLY);
	read(fd, env->imgstr2, 46080000);
	mlx_put_image_to_window(env->mlx, env->win, env->img2,
			(env->width - 2000) / 2, (env->height - 1000) / 4);
			close(fd);
			*/
}

int		main(void)
{
	t_fractenv env;

	init(&env);
ft_printf("max%d\n",env.it_max);
	//fract(&env, env.opt[env.op]);
	mlx_key_hook(env.win, &keypressed, &env);
	mlx_hook(env.win, MN, MM, &mousemove, &env);
	mlx_loop_hook(env.mlx, &mloop, &env);
	mlx_mouse_hook(env.win, &buttonpressed, &env);
	mlx_loop(env.mlx);
}
