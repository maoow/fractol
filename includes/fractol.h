/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 15:30:04 by cbinet            #+#    #+#             */
/*   Updated: 2017/12/11 09:28:22 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "mlx.h"
# include "ft_printf.h"
# include "libft.h"
# include "get_next_line.h"
# include <time.h>
# include <stdio.h>
# include <math.h>
# define K_NB 13
# define B_NB 2
# define MN 6
# define MM (1L<<6)
# define NB_FRACT 13
# define HEIGHT 1380
# define WIDTH 2560

typedef struct		s_pixel
{
	double			x;
	double			y;
	int				color;
}					t_pixel;

typedef struct		s_fract
{
	char			*name;
	t_pixel			(*serie)();
	void			(*function)();
	void			*img;
	bool			mdep;
	double			min;
	double			max;
	size_t			it_max;
	size_t			lastit;
	double			zoom;
	size_t			color;
	unsigned char	colormode;
	double			x;
	double			y;
	t_pixel			mouse;
}					t_fract;

typedef struct		s_fractenv
{
	double			size;
	double			x;
	double			y;
	double			width;
	double			height;
	void			*mlx;
	void			*win;
	void			*img;
	unsigned int	*imgstr;
	void			*img2;
	unsigned int	*imgstr2;
	t_pixel			mouse;
	int				key;
	size_t			op;
	t_fract			fract[NB_FRACT];
	int				end;
	int				sl;
	int				bpp;
	bool			mod;
	bool			move;
	bool			verbose;
	t_pixel			*imap;
}					t_fractenv;

void				init(t_fractenv *env);
void				initfract(t_fractenv *env);
t_fract				initfractale(char *name, t_pixel (*serie)(),
		void (*ffract)(), bool mdep);
int					keypressed(int key, t_fractenv *env);
int					buttonpressed(int key, int x, int y, t_fractenv *env);
int					mousemove(int x, int y, t_fractenv *env);
int					mloop(t_fractenv *env);
bool				is_bounded(t_fractenv *env, t_pixel a);
void				mouserotate(t_fractenv *env);
void				center(t_fractenv *env);
void				csquare(t_pixel *z);
void				ccube(t_pixel *z);
void				move(t_fractenv *env);
void				left(t_fractenv *env);
void				up(t_fractenv *env);
void				down(t_fractenv *env);
void				right(t_fractenv *env);
void				verbose(t_fractenv *env);
void				higher(t_fractenv *env);
void				lower(t_fractenv *env);
void				colorup(t_fractenv *env);
void				zoom(t_fractenv *env);
void				dezoom(t_fractenv *env);
void				mand(t_fractenv *env, t_pixel pixel);
void				julia(t_fractenv *env, t_pixel pixel);
void				buddha(t_fractenv *env, t_pixel pixel);
void				fract(t_fractenv *env);
void				bfract(t_fractenv *env);
void				increasepixel(t_fractenv *env, t_pixel pixel,
		unsigned int color);
void				addpixel(t_fractenv *env, t_pixel pixel, int color);
void				rbuddha(t_fractenv *env, t_pixel pixel);
void				bbuddha(t_fractenv *env, t_pixel pixel);
void				tjulia(t_fractenv *env, t_pixel pixel);
void				tmand(t_fractenv *env, t_pixel pixel);
void				dmand(t_fractenv *env, t_pixel pixel);
void				tbship(t_fractenv *env, t_pixel pixel);
void				bship(t_fractenv *env, t_pixel pixel);
void				djulia(t_fractenv *env, t_pixel pixel);
void				rjulia(t_fractenv *env, t_pixel pixel);
void				initbship(t_fractenv *env, t_fract *fract);
void				printenv(t_fractenv *env);
void				put_loading_logo(t_fractenv *env, int x);
void				initfract(t_fractenv *env);
void				reset(t_fractenv *env);
void				fractclean(t_fractenv *env);
t_pixel				ju_op(t_pixel *a, t_pixel b);
t_pixel				tju_op(t_pixel *a, t_pixel b);
t_pixel				dju_op(t_pixel *a, t_pixel b);
t_pixel				rju_op(t_pixel *a, t_pixel b, double zoom);
t_pixel				mrju_op(t_pixel *a, t_pixel b, double zoom);
t_fract				resetfract(t_fract fract);
unsigned int		get_color(t_fract fract, size_t i);

# ifdef linux

#  define K_Q			113
#  define K_ESC			65307
#  define K_H			104
#  define K_J			106
#  define K_K			107
#  define K_L			108
#  define K_M			109
#  define K_F			102
#  define K_D			100
#  define K_COMMA		44
#  define K_Y			121
#  define K_U			117
#  define K_I			105
#  define K_O			111
#  define K_7			55
#  define K_8			56
#  define K_A			97
#  define K_S			115
#  define K_E			101
#  define K_R			114
#  define K_C			99
#  define K_V			118
#  define K_Z			122
#  define K_X			120
#  define K_POINT		46
#  define K_SLASH		47
#  define K_SPACE		32

# else

#  define K_Q			12
#  define K_ESC			53
#  define K_H			4
#  define K_J			38
#  define K_K			40
#  define K_L			37
#  define K_M			46
#  define K_F			3
#  define K_D			2
#  define K_COMMA		43
#  define K_Y			16
#  define K_U			32
#  define K_I			34
#  define K_O			31
#  define K_7			28
#  define K_8			26
#  define K_A			0
#  define K_S			1
#  define K_E			14
#  define K_R			15
#  define K_C			8
#  define K_V			9
#  define K_Z			6
#  define K_X			7
#  define K_POINT		44
#  define K_SLASH		47

# endif
#endif
