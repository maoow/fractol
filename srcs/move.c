#include "fractol.h"
void			mouserotate(t_fractenv *env)
{
}
void			center(t_fractenv *env)
{
}
void			left(t_fractenv *env)
{
env->x-= env->width / 4;
}
void			up(t_fractenv *env)
{
env->y-= env->height / 4;
}
void			down(t_fractenv *env)
{
env->y+= env->height / 4;
}
void			right(t_fractenv *env)
{
env->x+= env->width / 4;
}
void			higher(t_fractenv *env)
{
env->it_max += 10;
}
void			lower(t_fractenv *env)
{
env->it_max -= 10;
}
void			zoom(t_fractenv *env)
{
	int speed = 1;
if (env->mouse.x)
{
env->x += (env->x + env->width / 2)/ 10;
env->y += (env->y + env->height / 2) / 10;
env->zoom += (env->zoom / 10) * speed;
env->x += ((env->mouse.x - env->width / 2) / 10);// * sqrt(env->zoom);
env->y += ((env->mouse.y - env->height / 2) /  10); //* sqrt(env->zoom);
	fract(env, &mand);
}
//env->zoom *= 2;
//env->x += (env->x + env->width / 2);
//env->y += (env->y + env->height / 2);
}
void			dezoom(t_fractenv *env)
{
if (env->zoom >= 2)
{
env->x -= (env->x + env->width / 2);
env->y -= (env->y + env->height / 2);
env->zoom /= 2;
}
}
