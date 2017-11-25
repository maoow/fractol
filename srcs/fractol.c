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
	pixel.y += 6;
	pixel.y *= env->zoom;
	pixel.x += 3;
	pixel.x *= env->zoom;
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
{ size_t	i;
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
	if (i == env->it_max)
		addpixel(env, pixel, 0x00ff00);
	else
		addpixel(env, pixel, i * env->i);
}
void	frmod(t_fractenv *env, t_pixel pixel)
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
		addpixel(env, pixel, 0x00ff00);
	else
		addpixel(env, pixel, i * env->i);
}
void	mand(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	p.x = (((pixel.x + env->x )/ env->zoom ));
	p.y =  (((pixel.y + env->y) / env->zoom));
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
	while (z.x != env->width)
	{
		z.y = 0;
		while (z.y != env->height)
		{
			op(env, z);
			z.y++;
		}
		z.x++;
	}
int fd;
fd = open("test.map", O_WRONLY);
write(fd, env->imgstr, env->width * env->height * sizeof(unsigned int) / sizeof(char));
exit(0);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

void	init(t_fractenv *env)
{
	env->mlx = mlx_init();
	env->zoom = 100;
	env->width = 1200;
	env->height = 600;
	env->mouse.x = 0;
	env->mouse.y = 0;
	env->x = -600;
	env->y = -300;
	env->min = -1000;
	env->max = 9;
	env->win = mlx_new_window(env->mlx, env->width, env->height, "fract");
	env->it_max = 200000;
	env->i = 257;
}
void	mloop(t_fractenv *env)
{
	int speed = 100;
	//if (env->mouse.x)
	//{
	//env->x += (env->mouse.x - env->width / 2) /  speed * 2;
	//env->y += (env->mouse.y - env->height / 2) /  speed * 2;
	//env->zoom += env->zoom / speed;
	//fract(env, &mand);
	//}
}

int	main()
{
	t_fractenv env;

	init(&env);
	fract(&env, &mand);
	mlx_key_hook(env.win, &keypressed, &env);
	mlx_hook(env.win, MN, MM, &mousemove, &env);
	//	mlx_loop_hook(env.mlx, &mloop, &env);
	mlx_mouse_hook(env.win, &buttonpressed, &env);
	mlx_loop(env.mlx);
}
