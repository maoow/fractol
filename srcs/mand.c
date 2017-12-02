#include "fractol.h"

void	mand(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	p.x = (((pixel.x + env->x) / env->zoom));
	p.y = (((pixel.y + env->y) / env->zoom));
	z = p;
	i = 0;
	while (++i < env->it_max && (is_bounded(env, z) || i == 0))
		ju_op(&z, p);
	if (i == env->it_max)
		addpixel(env, pixel, env->it_max);
	else
		addpixel(env, pixel, i * env->i);
}
