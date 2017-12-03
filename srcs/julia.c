#include "fractol.h"

void	tjulia(t_fractenv *env, t_pixel pixel)
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
		dju_op(&z, p);
	addpixel(env, pixel, i );
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
		addpixel(env, pixel, i);
}
