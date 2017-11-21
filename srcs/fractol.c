#include "fractol.h"


void	csquare(t_pixel *z)
{
	double	tmp;

	tmp = z->x;
	z->x = z->x * z->x - z->y * z->y;
	z->y = z->y * 2 * tmp;
}

void	mand(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	p.x = (((pixel.x - 2 + env->x )/ env->zoom )) ;// (env->size / 4) ;
	p.y =  (((pixel.y - 2  + env->y) / env->zoom)); // (env->size / 8) ;
	z.x = 0;
	z.y = 0;
	i = 0;
	while (i < env->it_max && z.x * z.x + z.y * z.y < env->max && (z.x * z.x + z.y * z.y > env->min || i == 0))
	{
		csquare(&z);
		z.x += p.x;
		z.y += p.y;
		i++;	
		mlx_pixel_put(env->mlx, env->win, pixel.x , pixel.y , i * 256);
	}
	if (i == env->it_max)
		mlx_pixel_put(env->mlx, env->win, pixel.x , pixel.y ,0x00ff00);
	else
		mlx_pixel_put(env->mlx, env->win, pixel.x , pixel.y , i * 256);
}
void	fract(t_fractenv *env, t_pixel	(op(t_fractenv, t_pixel)))
{
	t_pixel	z;
	z.x = 0;
	while (z.x != env->size)
	{
		z.y = 0;
		while (z.y != env->size / 2)
		{
			mand(env, z);
			z.y++;
		}
		z.x++;
	}
}


int	main()
{
	t_fractenv env;

	env.mlx = mlx_init();
env.zoom = 100;
env.x = -600;
env.y = -300;
env.min = -1000;
env.max = 9;
	env.win = mlx_new_window(env.mlx, 1200,600, "fract");
	env.size = 1200;
	env.it_max = 10;
	fract(&env, &mand);
	mlx_key_hook(env.win, &keypressed, &env);
	mlx_hook(env.win, MN, MM, &mousemove, &env);
	mlx_mouse_hook(env.win, &buttonpressed, &env);
	mlx_loop(env.mlx);
}
