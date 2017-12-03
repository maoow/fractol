#include "fractol.h"

void	mand(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	p.x = (pixel.x + env->x) / env->zoom;
	p.y = (pixel.y + env->y) / env->zoom;
	z = p;
	i = 0;
	while (++i < env->it_max && (is_bounded(env, z) || i == 0))
		ju_op(&z, p);
	if (i != env->it_max)
	{
		i *= get_color(env,i);
		addpixel(env, pixel, i);
	}
}

void	dmand(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	z.x = (((pixel.x + env->x) / env->zoom));
	z.y = (((pixel.y + env->y) / env->zoom));
	p = z;
	i = 0;
	while (++i < env->it_max && (is_bounded(env, z) || i == 0))
		dju_op(&z, p);
	i *= get_color(env,i);
	addpixel(env, pixel, i);
}

void	tmand(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	z.x = (((pixel.x + env->x) / env->zoom));
	z.y = (((pixel.y + env->y) / env->zoom));
	p.x = sin(z.y);
	p.y = sin(z.x);
	p = z;
	i = 0;
	while (++i < env->it_max && (is_bounded(env, z) || i == 0))
		tju_op(&z, p);
	i *= get_color(env,i);
	addpixel(env, pixel, i);
}
