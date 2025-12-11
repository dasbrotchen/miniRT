/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_point_to_uv.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:59:07 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:07:42 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

/*
* Returns the uvpoint if the intersection is on one
* of the caps of the cylinder.
*/
t_2dpoint	uv_cap(t_point point, t_point cap_center, float radius)
{
	return ((t_2dpoint){0.5f + ((point.x - cap_center.x) / (2.0f * radius)),
		0.5f + ((point.y - cap_center.y) / (2.0f * radius))});
}

/*
 * The point is in world coordinates. Returns the 'normal'
 * uvpoint of the cylinder, i.e. not on a cap.
*/
static t_2dpoint	cylinder_uv_curved(t_point point)
{
	float		azimuthal_angle;

	azimuthal_angle = atan2f(point.y, point.x);
	return ((t_2dpoint){1 - ((azimuthal_angle / (2 * M_PI)) + 0.5f),
		fmod(point.z, 1.0f)});
}

/*
* Recall that point is in local cylinder coordinates.
* We can directly check the height, and compute the
* a different uv point if the point is exactly on the cap.
*/
t_2dpoint	cylinder_point_to_uv(t_point point, t_cylinder cylinder)
{
	t_point		cap_center;

	if (fabs(point.z + (cylinder.height * 0.5)) <= EPSILON
		|| fabs(point.z - (cylinder.height * 0.5)) <= EPSILON)
	{
		if (fabs(point.z + (cylinder.height * 0.5)) <= EPSILON)
			cap_center = (t_point){cylinder.centre.x,
				cylinder.centre.y, cylinder.minz};
		else
			cap_center = (t_point){cylinder.centre.x,
				cylinder.centre.y, cylinder.maxz};
		return (uv_cap(point, cap_center, cylinder.radius));
	}
	return (cylinder_uv_curved(point));
}
