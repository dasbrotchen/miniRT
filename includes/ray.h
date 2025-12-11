/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 22:20:09 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/05 23:49:41 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

typedef struct s_quaternion
{
	float	r;
	float	ix;
	float	iy;
	float	iz;
}	t_quaternion;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_2dpoint
{
	float	x;
	float	y;
}	t_2dpoint;

typedef struct s_vector	t_point;

typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}	t_ray;

typedef struct s_matrix
{
	float	r1[3];
	float	r2[3];
	float	r3[3];
}	t_matrix;

#endif
