/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   series.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbinet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 13:59:19 by cbinet            #+#    #+#             */
/*   Updated: 2017/12/10 15:10:40 by cbinet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	return (*a);
}

t_pixel	ju_op(t_pixel *a, t_pixel b)
{
	csquare(a);
	a->x += (b.x);
	a->y += (b.y);
	return (*a);
}

t_pixel	mrju_op(t_pixel *a, t_pixel b, double zoom)
{
	a->x *= zoom;
	a->x = fabsl(a->x);
	a->x /= zoom;
	csquare(a);
	a->x += (b.x);
	a->y += (b.y);
	return (*a);
}

t_pixel	rju_op(t_pixel *a, t_pixel b, double zoom)
{
	a->x *= zoom;
	a->y *= zoom;
	a->x = fabsl(a->x);
	a->y = fabsl(a->y);
	a->x /= zoom;
	a->y /= zoom;
	csquare(a);
	a->x += (b.x);
	a->y += (b.y);
	return (*a);
}
