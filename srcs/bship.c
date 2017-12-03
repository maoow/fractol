#include "fractol.h"

void	bship(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	p.x = (pixel.x + env->x) / env->zoom;
	p.y = (pixel.y + env->y) / env->zoom;
	//z = p;
	//z.x = abs(z.x);
	//z.y = abs(z.y);
	z.x = abs(pixel.x + env->x) / env->zoom;
	z.y = abs(pixel.y + env->y) / env->zoom;
	i = 0;
	while (++i < env->it_max && (is_bounded(env, z) || i == 0))
		rju_op(&z, p, env->zoom);
	i *= get_color(env,i);
	addpixel(env, pixel, i);
}

