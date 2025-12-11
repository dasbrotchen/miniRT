/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_intersection_finder.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 13:19:45 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:07:46 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

static float	is_on_cap(t_cylinder cylinder, t_ray ray)
{
	float	dist_to_bot;
	float	dist_to_top;
	t_point	first_inter;
	float	cap_dist;

	dist_to_bot = (cylinder.minz - ray.origin.z) / ray.direction.z;
	dist_to_top = (cylinder.maxz - ray.origin.z) / ray.direction.z;
	first_inter = (t_point){0, 0, 0};
	cap_dist = -1;
	if (isnan(dist_to_bot) || isnan(dist_to_top))
		return (-1);
	if (dist_to_bot < dist_to_top && dist_to_bot > 0)
		cap_dist = dist_to_bot;
	else if (dist_to_top > 0)
		cap_dist = dist_to_top;
	if (cap_dist > 0)
	{
		first_inter = get_intersection_point(ray, cap_dist);
		if (sqrtf(sqrf(first_inter.x) + sqrf(first_inter.y)) <= cylinder.radius)
			return (cap_dist);
	}
	return (-1);
}

static float	check_point_height(t_ray ray, t_cylinder cylinder,
			float t1, float t2)
{
	t_point	i1;
	t_point	i2;
	float	dist_to_cap;
	int		valid_i1;
	int		valid_i2;

	i1 = get_intersection_point(ray, t1);
	i2 = get_intersection_point(ray, t2);
	valid_i1 = (i1.z >= cylinder.minz && i1.z <= cylinder.maxz && t1 > 0);
	valid_i2 = (i2.z >= cylinder.minz && i2.z <= cylinder.maxz && t2 > 0);
	dist_to_cap = is_on_cap(cylinder, ray);
	if (dist_to_cap > 0 && (!valid_i1 || dist_to_cap < t1)
		&& (!valid_i2 || dist_to_cap < t2))
		return (dist_to_cap);
	else if (valid_i1 && (!valid_i2 || t1 < t2))
		return (t1);
	else if (valid_i2)
		return (t2);
	return (-1);
}

static float	b_term_cylinder_quadratic(t_ray ray)
{
	return (2 * (ray.origin.x * ray.direction.x
			+ ray.origin.y * ray.direction.y));
}

static float	c_term_cylinder_quadratic(t_ray ray, t_cylinder cylinder)
{
	return (sqrf(ray.origin.x)
		+ sqrf(ray.origin.y)
		- sqrf(cylinder.radius));
}

/*
* The line ray.origin.z += cylinder->centre.z is kind of a hack. but it works.
* The float variable discriminant is used twice, the second time to
* find the distance to the intersection. The is due to norm constraints,
* ignore the name in its second use case.
*/
float	get_cylinder_intersections(t_ray ray,
			void *object, t_point *point)
{
	t_cylinder	*cylinder;
	float		discriminant;
	t_vector	terms;
	float		t_1;
	float		t_2;

	cylinder = (t_cylinder *)object;
	ray.origin.z += cylinder->centre.z;
	terms.x = sqrf(ray.direction.x) + sqrf(ray.direction.y);
	terms.y = b_term_cylinder_quadratic(ray);
	terms.z = c_term_cylinder_quadratic(ray, *cylinder);
	discriminant = sqrf(terms.y) - 4 * terms.x * terms.z;
	if (discriminant < 0)
		return (-1);
	t_1 = (-terms.y - sqrt(discriminant)) / (2 * terms.x);
	t_2 = (-terms.y + sqrt(discriminant)) / (2 * terms.x);
	discriminant = check_point_height(ray, *cylinder, t_1, t_2);
	if (discriminant != -1)
		*point = get_intersection_point(ray, discriminant);
	return (discriminant);
}
