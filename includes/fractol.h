#include "mlx.h"
//#include <X11.h>
#include "mlx_int.h"
#include "ft_printf.h"
#include "libft.h"
#include "get_next_line.h"
#define K_NB 9
#define B_NB 5
#define MN 6
#define MM (1L<<6)

typedef struct	s_pixel
{
	double	x;
	double	y;
	int	color;
}		t_pixel;

typedef struct	s_fractenv
{
	double	min;
	double	max;
	double	size;
	double	zoom;
	double	x;
	double	y;
	int	width;
	int	height;
	size_t	it_max;
	void	*mlx;
	void	*win;
	void		*img;
	unsigned int	*imgstr;
	t_pixel	mouse;
	size_t	i;
int key;

int end;
int sl;
int bpp;
}		t_fractenv;
int			keypressed(int key, t_fractenv *env);
int			buttonpressed(int key,int x,int y, t_fractenv *env);
int			mousemove(int x,int y, t_fractenv *env);


void			mouserotate(t_fractenv *env);
void			center(t_fractenv *env);
void			left(t_fractenv *env);
void			up(t_fractenv *env);
void			down(t_fractenv *env);
void			right(t_fractenv *env);
void			higher(t_fractenv *env);
void			lower(t_fractenv *env);
void			zoom(t_fractenv *env);
void			dezoom(t_fractenv *env);
void			mand(t_fractenv *env, t_pixel pixel);
void	fract(t_fractenv *env, void	(op(t_fractenv *, t_pixel)));
