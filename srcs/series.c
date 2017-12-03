#include "fractol.h"

void	csquare(t_pixel *z)
{
	long double	tmp;

	tmp = z->x;
	z->x = z->x * z->x - z->y * z->y;
	z->y = z->y * 2 * tmp;
}

void	casquare(t_pixel *z)
{
	long double	tmp;
//(a - bi)
//a2 - 2abi + b2
//(a + bi)
//a2 + 2abi + b2

	tmp = z->x;
	z->x = z->x * z->x - z->y * z->y;
	z->y = z->y * 2 * tmp;
}

void	ccube(t_pixel *z)
{
	long double	tmp;

	tmp = z->x;
	z->x = z->x * z->x - z->y * z->y;
	z->y = z->y * 2 * tmp;
	tmp = z->x;
	z->x = z->x * z->x - z->y * z->y;
	z->y = z->y * 2 * tmp;
}

bool	is_rbounded(t_fractenv *env, t_pixel a)
{
	double tmp;
	tmp = a.x * a.y + a.x * a.y;
	return (
			(tmp < env->max && tmp > env->min )
	       );
}

bool	is_sbounded(t_fractenv *env, t_pixel a)
{
	double tmp;
	tmp = a.x * a.x + a.y * a.y;
	tmp = abs(a.x * a.x) + abs(a.y * a.y);
	return (
			(tmp < env->max && tmp > env->min )
	       );
}
bool	is_bounded(t_fractenv *env, t_pixel a)
{
	double tmp;
	tmp = a.x * a.x + a.y * a.y;
	return (
			(tmp < env->fract[env->op].max && tmp > env->fract[env->op].min)
	       );
}

t_pixel	tju_op(t_pixel *a, t_pixel b)
{
	csquare(a);
	csquare(a);
	csquare(a);
	a->x += b.x;
	a->y += b.y;
	a->x += b.x;
	a->y += b.y;
	a->x += b.x;
	a->y += b.y;
	return (*a);
}

t_pixel	dju_op(t_pixel *a, t_pixel b)
{
	csquare(a);
	csquare(a);
	a->x += b.x;
	a->y += b.y;
	a->x += b.x;
	a->y += b.y;
	return (*a);
}

t_pixel	ju_op(t_pixel *a, t_pixel b)
{
	csquare(a);
	a->x += (b.x);
	a->y += (b.y);
	return (*a);
}
t_pixel	mrju_op(t_pixel *a, t_pixel b, long double zoom)
{
a->x *= zoom;
a->y *= zoom;
	a->x = abs(a->x);
a->x /= zoom;
a->y /= zoom;
	csquare(a);
	a->x += (b.x);
	a->y += (b.y);
	return (*a);
}
t_pixel	rju_op(t_pixel *a, t_pixel b, long double zoom)
{
a->x *= zoom;
a->y *= zoom;
	a->x = abs(a->x);
	a->y = abs(a->y);
a->x /= zoom;
a->y /= zoom;
	csquare(a);
	a->x += (b.x);
	a->y += (b.y);
	return (*a);
}
