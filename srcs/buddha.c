#include "fractol.h"

void	buddhadraw(t_fractenv *env, size_t i)
{
	unsigned int color;

	if (env->colormode % 2 == 1)
		color = get_color(env, i);
	while (--i > 0)
	{
		if (env->colormode % 2 == 0)
			color = get_color(env, i);
		increasepixel(env, env->imap[i], color);
	}
}

void	buddha(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;

	p.x = (((pixel.x + env->x) / env->zoom));
	p.y = (((pixel.y + env->y) / env->zoom));
	i = 0;
	z = p;
	while (++i < env->it_max && (is_bounded(env, z) || i == 0))
		env->imap[i] = ju_op(&z, p);
	if (i != env->it_max)
		buddhadraw(env, i);
}
void	rbuddha(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;
	unsigned int color;

	p.x = (((pixel.x + env->x) / env->zoom));
	p.y = (((pixel.y + env->y) / env->zoom));
	i = 0;
	z = p;
	while (++i < env->it_max && (is_bounded(env, z) || i == 0))
		env->imap[i] = ju_op(&z, p);
 if (i == env->it_max)
		buddhadraw(env, i);
}
