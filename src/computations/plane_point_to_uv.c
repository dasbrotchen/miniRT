/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_point_to_uv.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:28:12 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:08:57 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

static t_vector	get_right_vector(t_vector normal)
{
	t_vector	right;

	right = normalise(x_prod(normal, (t_vector){1, 0, 0}));
	if ((!right.x && !right.y && !right.z)
		|| (isnan(right.x) && isnan(right.y) && isnan(right.z)))
		right = normalise(x_prod(normal, (t_vector){0, 0, 1}));
	if ((!right.x && !right.y && !right.z)
		|| (isnan(right.x) && isnan(right.y) && isnan(right.z)))
		right = normalise(x_prod(normal, (t_vector){0, 1, 0}));
	return (right);
}

/*
* We need to create a basis of two vectors of the plane.
* I define the 'right' vector as a vector perpendicular to
* the normal, and not_parallel any other random vector resulting
* from the cross product of the right and normal vectors.
* Negative u, v values are wrapped by adding 1.
*/
t_2dpoint	plane_point_to_uv_textures(t_point point,
				t_plane plane, float scale)
{
	t_vector	right;
	t_vector	not_parallel;
	float		u;
	float		v;

	right = get_right_vector(plane.normal);
	not_parallel = normalise(x_prod(plane.normal, right));
	u = dot(right, point) * scale;
	u = fmod(u, 1.0f);
	v = dot(not_parallel, point) * scale;
	v = fmod(v, 1.0f);
	if (u < 0)
		u += 1.0f;
	if (v < 0)
		v += 1.0f;
	return ((t_2dpoint){.x = u,
		.y = v});
}

t_2dpoint	plane_point_to_uv(t_point point, float scale_factor)
{
	return ((t_2dpoint){fmod(point.x, 1.0f) * scale_factor,
		fmod(point.z, 1.0f) * scale_factor});
}
