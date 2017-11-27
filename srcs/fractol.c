#include "fractol.h"


void	csquare(t_pixel *z)
{
	double	tmp;

	tmp = z->x;
	z->x = z->x * z->x - z->y * z->y;
	z->y = z->y * 2 * tmp;
}

void	increasepixel(t_fractenv *env, t_pixel pixel, int color)
{
	pixel.y *= env->zoom;
	pixel.y += env->height / 2;
	pixel.x *= env->zoom;
	pixel.x += env->width / 2;
	if (pixel.y  < env->width && pixel.x < env->height && pixel.y >=0 && pixel.x >= 0)
		if (env->imgstr[(int)pixel.y + (int)pixel.x * env->width] < 0x1000000)
			env->imgstr[(int)pixel.y + (int)pixel.x * env->width] += (unsigned int)color;
}
void	addpixel(t_fractenv *env, t_pixel pixel, int color)
{
	//>	mlx_pixel_put(env->mlx, env->win, pixel.x , pixel.y , color);
	env->imgstr[(int)pixel.x + (int)pixel.y * env->width] = (unsigned int)color;
}

void	julia(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	p.x = env->mouse.x - env->width / 2;
	p.y = env->mouse.y - env->height / 2;
	p.x /= 1000;
	p.y /= 1000;
	z.x = (((pixel.x - 2 + env->x )/ env->zoom ));
	z.y =  (((pixel.y - 2  + env->y) / env->zoom));
	i = 0;
	while (i < env->it_max && z.x * z.x + z.y * z.y < env->max && (z.x * z.x + z.y * z.y > env->min || i == 0))
	{
		csquare(&z);
		z.x += p.x;
		z.y += p.y;
		i++;	
		//addpixel(env, pixel.x , pixel.y , i * 256);
	}
	if (i != env->it_max)
		addpixel(env, pixel, i * env->i);
}
void	mand(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	p.x = (((pixel.x - 2 + env->x )/ env->zoom ));
	p.y =  (((pixel.y - 2  + env->y) / env->zoom));
	z.x = 0;
	z.y = 0;
	i = 0;
	while (i < env->it_max && z.x * z.x + z.y * z.y < env->max && (z.x * z.x + z.y * z.y > env->min || i == 0))
	{
		csquare(&z);
		z.x += p.x;
		z.y += p.y;
		i++;	
	}
	if (i == env->it_max)
		addpixel(env, pixel, 0xff * env->i);
	else
		addpixel(env, pixel, i * env->i);
}

void	buddha(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	p.x = ((pixel.x -env->width / 2) / env->zoom ) ;
	p.y =  ((pixel.y  -env->height / 2) / env->zoom);
	z.x = 0;
	z.y = 0;
	i = 0;
	while (i < env->it_max && z.x * z.x + z.y * z.y < env->max && (z.x * z.x + z.y * z.y > env->min || i == 0))
	{
		csquare(&z);
		z.x += p.x;
		z.y += p.y;

		i++;	
	}
	if (i != env->it_max)
	{
		z.x = 0;
		z.y = 0;
		i = 0;
		while (i < env->it_max && z.x * z.x + z.y * z.y < env->max && (z.x * z.x + z.y * z.y > env->min || i == 0))
		{
			increasepixel(env, z, env->i);
			csquare(&z);
			z.x += p.x;
			z.y += p.y;
			i++;	
		}
	}
}
void	fract(t_fractenv *env, void	(op(t_fractenv *, t_pixel)))
{
	t_pixel	z;

	env->img = mlx_new_image(env->mlx, env->width, env->height);
	env->imgstr = (unsigned int *)mlx_get_data_addr(env->img, &env->bpp, &env->sl, &env->end);
	z.x = 0;
	while (z.x < env->width)
	{
		z.y = 0;
		while (z.y < env->height)
		{
			op(env, z);
			z.y++;
		}
		z.x++;
	}

	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	/*
	   int fd;
	   ft_printf("%d\n", env->it_max);
	   fd = open("test.map", O_WRONLY);
	   write(fd, env->imgstr, env->width * env->height * sizeof(unsigned int) / sizeof(char));
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

}

void	init(t_fractenv *env)
{
	env->mlx = mlx_init();
	env->width = 1350;
	env->height = 750;
	env->zoom = env->width / 2;
	env->mouse.x = 0;
	env->mouse.y = 0;
	env->x = -env->width / 2;
	env->y = -env->height / 2;
	env->min = -1000;
	env->max = 9;
	env->win = mlx_new_window(env->mlx, env->width, env->height, "fract");
	env->op = 1;
	env->opt[0] = &mand;
	env->opt[1] = &julia;
	env->opt[2] = &buddha;
	env->img2 = mlx_new_image(env->mlx, 2000, 1000);
	env->imgstr2 = (unsigned int *)mlx_get_data_addr(env->img2, &env->bpp, &env->sl, &env->end);
	int fd;
	fd = open("test.map", O_RDONLY);
	read(fd, env->imgstr2,46080000);
	mlx_put_image_to_window(env->mlx, env->win, env->img2, (env->width - 2000) / 2, (env->height - 1000) / 4);
	close(fd);


	env->it_max = 200;
	env->i = 0x000300;
}
int	mloop(t_fractenv *env)
{
	fract(env, env->opt[env->op]);
printf("%d %d %e\n",env->x, env->y, env->zoom);
}

int	main()
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
