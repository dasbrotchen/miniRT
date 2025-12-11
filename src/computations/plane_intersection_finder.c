/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_intersection_finder.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:37:06 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:08:51 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

float	get_plane_intersection(t_ray ray, void *object, t_point *point)
{
	t_plane	plane;
	float	t;
	float	numerator;
	float	denominator;

	plane = *(t_plane *)object;
	numerator = -dot(plane.normal, vector_operation(ray.origin,
				plane.position, substract));
	denominator = dot(plane.normal, ray.direction);
	if (!denominator)
		return (-1);
	t = numerator / denominator;
	if (t < 0 || !t)
		return (-1);
	*point = get_intersection_point(ray, t);
	return (t);
}
