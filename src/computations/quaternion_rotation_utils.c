/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_rotation_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 12:50:59 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:09:11 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

/*
* Three cases to consider: normal case, parallel case and anti parallel case.
* If not handled, x_prod(cylinder_axis, target_axis)
* can result in (0, 0, 0) -> NaN in subsequent operations.
*/
t_vector	find_rotation_axis(t_vector cylinder_axis)
{
	t_vector	target_axis;
	t_vector	rotation_axis;
	float		dot_product;

	target_axis = (t_vector){0, 0, 1};
	dot_product = dot(cylinder_axis, target_axis);
	if (fabsf(dot_product) > 1 - EPSILON)
	{
		if (dot_product > 0)
			return ((t_vector){0, 0, 0});
		else
		{
			if (fabsf(cylinder_axis.x) < fabsf(cylinder_axis.y))
				rotation_axis = x_prod((t_vector){1, 0, 0}, cylinder_axis);
			else
				rotation_axis = x_prod((t_vector){0, 1, 0}, cylinder_axis);
		}
	}
	else
		rotation_axis = x_prod(cylinder_axis, target_axis);
	return (normalise(rotation_axis));
}

/*
* A positive dot product (necessarily very close to 1) implies parallel axes.
* The same is true for a negative, close to -1 dot product,
* with anti-parallel axes.
* We consider these cases separately to, once again, avoid divisions by 0.
*/
t_quaternion	construct_quaternion_parallel_axes(t_vector cylinder_axis,
					t_vector rotation_axis)
{
	if (dot(cylinder_axis, (t_vector){0, 0, 1}) > 0)
		return ((t_quaternion){1.0f,
			0.0f,
			0.0f,
			0.0f});
	return ((t_quaternion){0.0f,
		rotation_axis.x,
		rotation_axis.y,
		rotation_axis.z});
}
