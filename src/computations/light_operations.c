/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 22:06:10 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:07:38 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

/*
 * Euclidean distance in a cartesian coordinates system.
*/
static float	point_distance(t_point p1, t_point p2)
{
	float	dx;
	float	dy;
	float	dz;

	dx = p2.x - p1.x;
	dy = p2.y - p1.y;
	dz = p2.z - p1.z;
	return (sqrt(sqrf(dx) + sqrf(dy) + sqrf(dz)));
}

static int	object_blocking_light(float dist,
				t_vector light_origin, t_ray ray)
{
	float	light_source_dist;

	light_source_dist = point_distance(ray.origin, light_origin);
	if (dist > EPSILON && dist < light_source_dist)
		return (1);
	return (0);
}

/*
* We start slightly towards the light ray to avoid self intersections. 
* This function is now called once per pixel, and we store the result for
* each light, instead of calling it for both specular and diffuse lightings.
*/
int	path_to_light(t_object **objs, t_light *source, t_point point)
{
	t_point		inter;
	t_ray		to_shoot;
	t_ray		og_ray;
	float		distance;
	int			i;

	i = -1;
	to_shoot.direction = normalise(vector_operation(source->origin,
				point, substract));
	to_shoot.origin.x = point.x + (to_shoot.direction.x * EPSILON);
	to_shoot.origin.y = point.y + (to_shoot.direction.y * EPSILON);
	to_shoot.origin.z = point.z + (to_shoot.direction.z * EPSILON);
	og_ray = to_shoot;
	while (objs[++i])
	{
		to_shoot = objs[i]->get_ray(og_ray, objs[i]->object);
		distance = objs[i]->intersect(to_shoot, objs[i]->object, &inter);
		if (object_blocking_light(distance, source->origin, to_shoot))
		{
			source->is_blocked = 1;
			return (0);
		}
	}
	source->is_blocked = 0;
	return (1);
}
