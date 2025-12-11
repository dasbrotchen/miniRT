/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_point_to_uv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 23:00:39 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:09:24 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

/*
* This must be used in the context of showing checkers on
* a sphere. We directly use the intersection point.
*/
t_2dpoint	sphere_point_to_uv_point(t_point point, t_sphere sphere, float zoom)
{
	float		azimuthal_angle;
	float		polar_angle;
	float		normalised_y;

	azimuthal_angle = atan2f(point.z, point.x);
	normalised_y = fminf(fmaxf(point.y / sphere.radius, -1.0f), 1.0f);
	polar_angle = acosf(normalised_y);
	return ((t_2dpoint){((azimuthal_angle / (2 * M_PI)) + 0.5f) * zoom,
		(polar_angle / M_PI) * zoom});
}

/*
* Unlike checkers, for bumps on a sphere the uvpoint 
* must be constructed with a transformed point, i.e. 
* the vector from the sphere centre to the point on the surface.
*/
t_2dpoint	sphere_point_to_uv_direction(t_point point,
				t_sphere sphere, float zoom)
{
	float		azimuthal_angle;
	float		polar_angle;
	float		normalised_y;
	t_vector	direction;

	direction = normalise(vector_operation(point, sphere.centre, substract));
	azimuthal_angle = atan2f(direction.z, direction.x);
	normalised_y = fminf(fmaxf(direction.y, -1.0f), 1.0f);
	polar_angle = acosf(normalised_y);
	return ((t_2dpoint){((azimuthal_angle / (2 * M_PI)) + 0.5f) * zoom,
		(polar_angle / M_PI) * zoom});
}
