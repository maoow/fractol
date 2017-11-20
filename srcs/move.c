#include "fractol.h"

void			mouserotate(t_fractenv *env)
{
}
void			center(t_fractenv *env)
{
}
void			left(t_fractenv *env)
{
env->x-= 100;
}
void			up(t_fractenv *env)
{
env->y-= 100;
}
void			down(t_fractenv *env)
{
env->y+= 100;
}
void			right(t_fractenv *env)
{
env->x+= 100;
}
void			higher(t_fractenv *env)
{
env->it_max *=2;
}
void			lower(t_fractenv *env)
{
env->it_max /=2;
}
void			zoom(t_fractenv *env)
{
env->zoom *= 2;
}
void			dezoom(t_fractenv *env)
{
if (env->zoom >= 2)
env->zoom /= 2;
}
void			harder(t_fractenv *env)
{
}
void			smoother(t_fractenv *env)
{
}
