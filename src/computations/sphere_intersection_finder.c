/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_intersection_finder.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 22:35:55 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:09:20 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

static float	b_term_sphere_quadratic(t_ray ray, t_sphere sphere)
{
	return (2 * dot(ray.direction, ray.origin)
		- 2 * dot(ray.direction, sphere.centre));
}

static float	c_term_sphere_quadratic(t_ray ray, t_sphere sphere)
{
	return (sqrf(ray.origin.x)
		+ sqrf(ray.origin.y)
		+ sqrf(ray.origin.z)
		+ sqrf(sphere.centre.x)
		+ sqrf(sphere.centre.y)
		+ sqrf(sphere.centre.z)
		- 2 * dot(ray.origin, sphere.centre)
		- sqrf(sphere.radius));
}

/*
* Returns the closest positive distance associated with an
* intersection for the sphere.
*/
static float	closest_positive_sphere_inter(float t_1,
					float t_2)
{
	if (t_1 > 0 && t_2 > 0)
		return (t_1 * (t_1 < t_2) + t_2 * (t_2 < t_1));
	if (t_1 > 0)
		return (t_1);
	if (t_2 > 0)
		return (t_2);
	return (-1);
}

float	get_sphere_intersections(t_ray ray, void *object,
			t_point *to_pixelise)
{
	t_sphere	sphere;
	float		discriminant;
	t_vector	terms;
	float		t_1;
	float		t_2;

	sphere = *(t_sphere *)object;
	terms.x = sqrf(ray.direction.x) + sqrf(ray.direction.y)
		+ sqrf(ray.direction.z);
	terms.y = b_term_sphere_quadratic(ray, sphere);
	terms.z = c_term_sphere_quadratic(ray, sphere);
	discriminant = sqrf(terms.y) - (4 * terms.x * terms.z);
	if (discriminant < 0)
		return (-1);
	t_1 = (-terms.y - sqrt(discriminant)) / (2 * terms.x);
	t_2 = (-terms.y + sqrt(discriminant)) / (2 * terms.x);
	if (t_1 <= t_2 && t_1 > 0)
		*to_pixelise = get_intersection_point(ray, t_1);
	else if (t_2 <= t_1 && t_2 > 0)
		*to_pixelise = get_intersection_point(ray, t_2);
	return (closest_positive_sphere_inter(t_1, t_2));
}
