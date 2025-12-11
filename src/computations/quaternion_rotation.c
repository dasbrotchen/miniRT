/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_rotation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:38:18 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/11/14 12:09:06 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

inline t_quaternion	quaternion_conjugate(t_quaternion quaternion)
{
	quaternion.ix = -quaternion.ix;
	quaternion.iy = -quaternion.iy;
	quaternion.iz = -quaternion.iz;
	return (quaternion);
}

/*
* theta is the angle between the target axis (0, 0, 1)
* and the cylinder_axis. The rest follows from the
* definition of the rotation quaternion.
*/
t_quaternion	construct_quaternion(t_vector cylinder_axis)
{
	float			dot_product;
	t_vector		rotation_axis;
	float			theta;

	rotation_axis = find_rotation_axis(cylinder_axis);
	dot_product = dot(cylinder_axis, (t_vector){0, 0, 1});
	if (fabsf(dot_product) > 1 - EPSILON)
		return (construct_quaternion_parallel_axes(cylinder_axis,
				rotation_axis));
	theta = acosf(dot_product);
	return ((t_quaternion){cosf(theta * 0.5f),
		sinf(theta * 0.5f) * rotation_axis.x,
		sinf(theta * 0.5f) * rotation_axis.y,
		sinf(theta * 0.5f) * rotation_axis.z});
}

/*
* These somewhat scary operations are actually just the application
* of the hamiltonian product, following the famous rules:
*
*		i^2 = j^2 = k^2 = -1;
*		ij = -ji = k;
*		jk = -kj = i;
*		ki = -ik = j;
*/
static inline t_quaternion	hamiltonian_product(t_quaternion q1,
								t_quaternion q2)
{
	return ((t_quaternion){q1.r * q2.r - q1.ix * q2.ix
		- q1.iy * q2.iy - q1.iz * q2.iz,
		q1.r * q2.ix + q1.ix * q2.r
		+ q1.iy * q2.iz - q1.iz * q2.iy,
		q1.r * q2.iy - q1.ix * q2.iz
		+ q1.iy * q2.r + q1.iz * q2.ix,
		q1.r * q2.iz + q1.ix * q2.iy
		- q1.iy * q2.ix + q1.iz * q2.r});
}

/*
* To limit the number of operations, we do not normalise the quaternion.
* This works based on the assumption that:
* 1) The cylinder axis is normalised
* 2) The rotation axis is normalised
*
* Note that the second argument in the first h. product
* is simply the vector/point to be rotated, but in its quaternion
* form, i.e. only with imaginary parts.
* Furthermore, q_1 in qvq_1 means the inversion of q, which happens to be
* its conjugate.
*/
t_vector	rotate_vec(t_quaternion q, t_vector v)
{
	t_quaternion	qv;
	t_quaternion	qvq_1;

	qv = hamiltonian_product(q, (t_quaternion){0, v.x, v.y, v.z});
	qvq_1 = hamiltonian_product(qv, quaternion_conjugate(q));
	return ((t_vector){qvq_1.ix, qvq_1.iy, qvq_1.iz});
}
