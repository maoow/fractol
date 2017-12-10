/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 14:43:11 by cbinet            #+#    #+#             */
/*   Updated: 2017/12/10 16:31:34 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static bool	isonlydigit(const char *str)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] && !ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}
static void	usage(t_fractenv *env)
{
	int			op;

	ft_printf("fractol [fractale_id] [iterations_nb] :\n");
	ft_printf("fractales :\n");
	op = 0;
	while (op < NB_FRACT)
	{
		ft_printf("[%d]: %s\n", op + 1, env->fract[op].name);
		op++;
	}
	exit(0);
}

static void	parse(t_fractenv *env, int ac, char **av)
{
	int			n;

	if (ac >= 2)
	{
		n = ft_atoi(av[1]);
		if (n > 0 && n <= NB_FRACT && isonlydigit(av[1]))
			env->op = n - 1;
		else
		{
			ft_printf("illegal option : %s\n", av[1]);
			usage(env);
		}
		if (ac >= 3)
		{
			n = ft_atoi(av[2]);
			if (n > 0 && isonlydigit(av[2]))
				env->fract[env->op].it_max = n;
			else
			{
				ft_printf("illegal option : %s\n", av[2]);
				usage(env);
			}
		}
	}
}

int			main(int ac, char **av)
{
	t_fractenv	env;

	initfract(&env);
	init(&env);
	env.op = 0;
	parse(&env, ac, av);
	mlx_key_hook(env.win, &keypressed, &env);
	mlx_hook(env.win, MN, MM, &mousemove, &env);
	mlx_loop_hook(env.mlx, &mloop, &env);
	mlx_mouse_hook(env.win, &buttonpressed, &env);
	mlx_loop(env.mlx);
}
