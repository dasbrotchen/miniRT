/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_intersection_finder.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 20:57:47 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:07:54 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

static float	is_on_cone_cap(t_cone cone, t_ray ray)
{
	float	dist_to_bot;
	t_point	first_inter;
	float	radius;

	dist_to_bot = (cone.minz - ray.origin.z) / ray.direction.z;
	if (isnan(dist_to_bot) || dist_to_bot < 0)
		return (-1);
	first_inter = get_intersection_point(ray, dist_to_bot);
	radius = (cone.height / 2) * tanf(cone.theta);
	if (sqrtf(sqrf(first_inter.x) + sqrf(first_inter.y)) <= radius)
		return (dist_to_bot);
	return (-1);
}

static float	check_cone_point_height(t_ray ray, t_cone cone,
			float t1, float t2)
{
	t_point	i1;
	t_point	i2;
	float	dist_to_cap;
	int		valid_i1;
	int		valid_i2;

	i1 = get_intersection_point(ray, t1);
	i2 = get_intersection_point(ray, t2);
	valid_i1 = (i1.z >= cone.minz && i1.z <= 0 && t1 > 0);
	valid_i2 = (i2.z >= cone.minz && i2.z <= 0 && t2 > 0);
	dist_to_cap = is_on_cone_cap(cone, ray);
	if (dist_to_cap > 0 && (!valid_i1 || dist_to_cap < t1)
		&& (!valid_i2 || dist_to_cap < t2))
		return (dist_to_cap);
	if (valid_i1 && (!valid_i2 || t1 < t2))
		return (t1);
	else if (valid_i2)
		return (t2);
	return (-1);
}

static float	b_term_cone_quadratic(t_ray ray, t_cone cone)
{
	return (2 * (ray.origin.x * ray.direction.x
			+ ray.origin.y * ray.direction.y
			- ray.origin.z * ray.direction.z * sqrf(tanf(cone.theta))));
}

static float	c_term_cone_quadratic(t_ray ray, t_cone cone)
{
	return (sqrf(ray.origin.x)
		+ sqrf(ray.origin.y)
		- sqrf(ray.origin.z) * sqrf(tanf(cone.theta)));
}

/*
* Ray is in LOCAL coordinates. Note that 'discriminant'
* is reused to store the intersection distance; this is purely
* due to norm constraints, and its name is unrelated to its
* assignation to check_cone_point_height.
*/
float	get_cone_intersections(t_ray ray,
			void *object, t_point *point)
{
	t_cone		cone;
	float		discriminant;
	t_vector	terms;
	float		t_1;
	float		t_2;

	cone = *(t_cone *)object;
	terms.x = sqrf(ray.direction.x) + sqrf(ray.direction.y)
		- sqrf(ray.direction.z) * sqrf(tanf(cone.theta));
	terms.y = b_term_cone_quadratic(ray, cone);
	terms.z = c_term_cone_quadratic(ray, cone);
	discriminant = sqrf(terms.y) - 4 * terms.x * terms.z;
	if (discriminant < 0)
		return (-1);
	t_1 = (-terms.y - sqrt(discriminant)) / (2 * terms.x);
	t_2 = (-terms.y + sqrt(discriminant)) / (2 * terms.x);
	discriminant = check_cone_point_height(ray, cone, t_1, t_2);
	if (discriminant != -1)
		*point = get_intersection_point(ray, discriminant);
	return (discriminant);
}
