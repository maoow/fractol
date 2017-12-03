#include "fractol.h"

void	sbuddhadraw(t_fractenv *env, size_t i)
{
	unsigned int color;

	if (env->colormode % 2 == 1)
		color = get_color(env, i);
	while (--i > env->it_max - (env->it_max / 50))
	{
		if (env->colormode % 2 == 0)
			color = get_color(env, i);
		increasepixel(env, env->imap[i], color);
	}
}
void	dbuddhadraw(t_fractenv *env, size_t i)
{
	unsigned int color;

	if (env->colormode % 2 == 1)
		color = get_color(env, i);
	while (--i > 0)
	{
		if (env->colormode % 2 == 0)
			color = get_color(env, i);
//color *= 2;
		increasepixel(env, env->imap[i], color);
	}
}

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

void	dbuddha(t_fractenv *env, t_pixel pixel)
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
		dbuddhadraw(env, i);
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

void	bbuddha(t_fractenv *env, t_pixel pixel)
{
	size_t	i;
	t_pixel	z;
	t_pixel	p;
	unsigned int color;

	p.x = (((env->mouse2.x + env->x) / env->zoom));
	p.y = (((env->mouse2.y + env->y) / env->zoom));
	p.x = (env->mouse2.x - env->width / 2)/ 1000;
	p.y = (env->mouse2.y - env->height / 2)/ 1000;
	z.x = (((pixel.x - 2 + env->x) / env->zoom));
	z.y = (((pixel.y - 2 + env->y) / env->zoom));
	i = 0;
	//z = p;
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
		sbuddhadraw(env, i);
}
