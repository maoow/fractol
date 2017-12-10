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

static void	parse(t_fractenv *env, char *str)
{
	int			op;

	op = ft_atoi(str);
	if (op > 0 && op <= NB_FRACT && isonlydigit(str))
		env->op = op - 1;
	else
	{
		ft_printf("illegal option : %s\n", str);
		ft_printf("possible params :\n");
		op = 0;
		while (op < NB_FRACT)
		{
			ft_printf("[%d]: %s\n", op + 1, env->fract[op].name);
			op++;
		}
		exit(0);
	}
}

int			main(int ac, char **av)
{
	t_fractenv	env;

	initfract(&env);
	init(&env);
	env.op = 0;
	if (ac == 2)
		parse(&env, av[1]);
	mlx_key_hook(env.win, &keypressed, &env);
	mlx_hook(env.win, MN, MM, &mousemove, &env);
	mlx_loop_hook(env.mlx, &mloop, &env);
	mlx_mouse_hook(env.win, &buttonpressed, &env);
	mlx_loop(env.mlx);
	clean(&env);
}
