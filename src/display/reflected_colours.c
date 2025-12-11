/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflected_colours.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:04:27 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 18:22:40 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

static t_colour	get_colour_on_point(t_scene scene, t_object *object,
				t_point inter_point, t_ray reflection_ray)
{
	static int	max_recursions = 0;
	t_colour	specular;
	t_colour	diffuse;
	t_colour	ambient;
	t_colour	reflected;

	specular = get_specular_shading(scene, object, reflection_ray, inter_point);
	diffuse = get_diffuse_shading(scene, object, inter_point);
	ambient = get_ambient_shading(scene.ambient, object, inter_point);
	reflected = (t_colour){0, 0, 0};
	if (max_recursions++ < REFLECTION_RECURSIONS)
		reflected = get_reflected_light(scene,
				reflection_ray, object, inter_point);
	else
		max_recursions = 0;
	return (combine_all_lights(&(t_colourblend){specular,
			diffuse, ambient, reflected}, object));
}

/*
* We have decided to store the ray inside the object,
* otherwise two almost consecutive calls to get_ray are
* made; these can be computationally intensive in the case
* of the cone and the cylinder since we apply the rotation
* to the ray. Basic tests did not actually show improvements
* (the compiler probably already optimised it ?), but
* in scenes with many cones/cylinders this might prove
* useful.
*/
static void	get_intersection_distance(t_object **objs,
				t_ray raw_ray, t_point *inter_point)
{
	unsigned int	k;

	k = 0;
	while (objs[k])
	{
		objs[k]->ray = objs[k]->get_ray(raw_ray, objs[k]->object);
		objs[k]->distance = objs[k]->intersect(objs[k]->ray,
				objs[k]->object, inter_point);
		k++;
	}
}

/*
* Compute the distance of the intersection (-1 if none),
* find the closest object (the one to display), find the
* corresponding point and translate/rotate it to world 
* world coordinates.
*/
t_object	*first_hit_object(t_object **objs, t_ray raw_ray,
				t_point *inter_point)
{
	t_object		*closest;
	t_point			point;

	get_intersection_distance(objs, raw_ray, inter_point);
	closest = get_closest_object(objs);
	if (closest)
	{
		point = get_intersection_point(closest->ray, closest->distance);
		*inter_point = closest->get_point(point, closest->object);
	}
	return (closest);
}

/*
	* point is the intersection between my primary ray and the closest object. 
	* normal is the computed normal at that point.
	* incoming is the ray from the camera towards the object.
	* we move the point just a little bit to avoid self intersections.
*/
static t_ray	get_reflection_ray(t_point point, t_vector normal,
					t_ray incoming)
{
	t_ray	bouncing_ray;

	bouncing_ray.direction.x = incoming.direction.x - 2
		* dot(incoming.direction, normal) * normal.x;
	bouncing_ray.direction.y = incoming.direction.y - 2
		* dot(incoming.direction, normal) * normal.y;
	bouncing_ray.direction.z = incoming.direction.z - 2
		* dot(incoming.direction, normal) * normal.z;
	bouncing_ray.origin.x = point.x + bouncing_ray.direction.x * EPSILON;
	bouncing_ray.origin.y = point.y + bouncing_ray.direction.y * EPSILON;
	bouncing_ray.origin.z = point.z + bouncing_ray.direction.z * EPSILON;
	return (bouncing_ray);
}

t_colour	get_reflected_light(t_scene scene, t_ray ray,
				t_object *obj, t_point point)
{
	t_vector	normal;
	t_ray		reflection_ray;
	t_point		second_inter;
	t_object	*second_obj;

	if (!obj->reflection_coef)
		return ((t_colour){0, 0, 0});
	normal = obj->get_normal_vec(point, obj);
	reflection_ray = get_reflection_ray(point, normal, ray);
	second_obj = first_hit_object(scene.objs,
			reflection_ray, &second_inter);
	if (!second_obj)
		return ((t_colour){0, 0, 0});
	return (get_colour_on_point(scene, second_obj,
			second_inter, reflection_ray));
}
