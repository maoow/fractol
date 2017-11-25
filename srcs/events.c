#include "fractol.h"


void			quit(t_fractenv *env)
{
	exit(0);
}

int		g_button[B_NB] =
{
	3,
	4,
	5,
	1,
	108
};
void		(*g_buttonf[B_NB])() =
{
	&zoom,
	&zoom,
	&dezoom,
	&center,
	&right
};

int		g_key[K_NB] =
{
	113,
	104,
	106,
	107,
	108,
	102,
	100,
	110,
	109,
	117,
	121,
	111,
	55,
	56,
	105,
	101,
	114
};
void		(*g_keyf[K_NB])() =
{
	&quit,
	&left,
	&down,
	&up,
	&right,
	&higher,
	&lower,
	&zoom,
	&dezoom
};

int			loop(int key,int x,int y, t_fractenv *env)
{
	//printf("x: %f y: %f z: %f\nzoom: %d\n\n", env->rotate.x, env->rotate.y, env->rotate.z,env->zoom);
return (0);
}
int			loopachieved(t_fractenv *env)
{
	//if (env->key == 0)
	//{
		//env->rotate.z += 0.02 / env->zoom;
		//drawpoint(env);
	//}
//	printf("x: %f y: %f z: %f\nzoom: %d\n\n", env->rotate.x, env->rotate.y, env->rotate.z,env->zoom);
}
int			mousemove(int x,int y, t_fractenv *env)
{
	size_t		count;
//static int test = 0;

//if (test % 100 == 0)
//{
	count = 0;
ft_printf( "%d,%d\n" , env->x, env->y);
env->mouse.x = x;
env->mouse.y = y;
//}
//test++;
}

int			buttonpressed(int key,int x,int y, t_fractenv *env)
{
	size_t		count;

	count = 0;
	env->key = key;
	while(count < K_NB)
	{
		if (key == g_button[count])
			g_buttonf[count](env);
		count++;
	}
	fract(env, env->opt[env->op]);
}

int			keypressed(int key, t_fractenv *env)
{
	size_t		count;

	count = 0;
	env->key = key;
	while(count < K_NB && key != g_key[count])
		count++;
	if (count < K_NB)
		g_keyf[count](env);
	else
		ft_printf("%d\n", key);
	fract(env, env->opt[env->op]);
}
