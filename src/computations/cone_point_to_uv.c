/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_point_to_uv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 17:46:48 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:07:49 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

/*
* We are only considering points with negative z coordinates
* (bottom half of the hourglass), so we divide by -height
* for the v coordinate to always be positive.
*/
static t_2dpoint	cone_uv_curved(t_point point, float height)
{
	float	azimuthal_angle;

	azimuthal_angle = atan2f(point.y, point.x);
	return ((t_2dpoint){.x = (azimuthal_angle / 2 * M_PI),
		.y = point.z / -height});
}

/*
* Custom uvpoint converter ONLY for checkers, we get
* better visuals on the cap. NOT TO BE USED WITH BUMP
* AND IMAGE MAPPING
*/
t_2dpoint	cone_point_to_uv_checkers(t_point point, t_cone cone)
{
	t_2dpoint	uvpoint;

	if (fabs(point.z + (cone.height * 0.5)) <= EPSILON)
	{
		uvpoint.x = 1 - (atan2f(point.y, point.x) / 2 * M_PI);
		uvpoint.y = fmod(point.z, 1.0f);
	}
	else
		uvpoint = cone_uv_curved(point, cone.height);
	return (uvpoint);
}

/*
* 'normal' uv mapping for cones, to be used with bumps
*/
t_2dpoint	cone_point_to_uv(t_point point, t_cone cone)
{
	t_2dpoint	uvpoint;
	t_vector	cap_center;
	float		radius;

	if (fabs(point.z + (cone.height * 0.5)) <= EPSILON)
	{
		cap_center = (t_point){cone.apex.x,
			cone.apex.y, cone.minz};
		radius = (cone.height / 2) * tanf(cone.theta);
		return (uv_cap(point, cap_center, radius));
	}
	uvpoint = cone_uv_curved(point, cone.height);
	return (uvpoint);
}
