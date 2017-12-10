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

	ft_printf("fractol [-h] [fractale_id] [iterations_nb] [colormode 0-6] :\n");
	ft_printf("-h : display this help and exit\n\n");
	ft_printf("fractales :\n");
	op = 0;
	while (op < NB_FRACT)
	{
		ft_printf("[%d]: %s\n", op + 1, env->fract[op].name);
		op++;
	}
	exit(0);
}

static void	wrongoption(t_fractenv *env, char *str)
{
if (ft_strcmp("-h", str))
	ft_printf("illegal option : %s\n", str);
	usage(env);
}

static void	parse(t_fractenv *env, int ac, char **av)
{
	int			n;

	if (ac >= 2)
	{
		n = ft_atoi(av[1]);
		if (n == 0 || n > NB_FRACT || !isonlydigit(av[1]))
			wrongoption(env, av[1]);
		env->op = n - 1;
		if (ac >= 3)
		{
			n = ft_atoi(av[2]);
			if (n == 0 || !isonlydigit(av[2]))
				wrongoption(env, av[2]);
			env->fract[env->op].it_max = n;
			if (ac >= 4)
			{
				n = ft_atoi(av[3]);
				if (n == 0 || n > 5 || !isonlydigit(av[3]))
					wrongoption(env, av[3]);
				env->fract[env->op].colormode = n;
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
