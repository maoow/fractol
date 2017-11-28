#include "mlx.h"
//#include <X11.h>
//#include "mlx_int.h"
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
	void		*img2;
	unsigned int	*imgstr2;
	t_pixel	mouse;
	size_t	i;
	int key;

	size_t	op;
	void	*opt[3];
	int end;
	int sl;
	int bpp;

	bool mod;
}		t_fractenv;
int			keypressed(int key, t_fractenv *env);
int			buttonpressed(int key,int x,int y, t_fractenv *env);
int			mousemove(int x,int y, t_fractenv *env);
int			mloop(t_fractenv *env);


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
void			julia(t_fractenv *env, t_pixel pixel);
void			buddha(t_fractenv *env, t_pixel pixel);
void	fract(t_fractenv *env, void	(op(t_fractenv *, t_pixel)));


#define K_Q			12
#define K_ESC		53
#define K_H			4
#define K_J			38
#define K_K			40
#define K_L			37
#define K_M			46
#define K_F			3
#define K_D			2
#define K_COMMA		43
#define K_Y			16
#define K_U			32
#define K_I			34
#define K_O			31
#define K_7			28
#define K_8			26
#define K_A			0
#define K_S			1
#define K_E			14
#define K_R			15
#define K_C			8
#define K_V			9
#define K_Z			6
#define K_X			7
#define K_POINT		44
#define K_SLASH		47
