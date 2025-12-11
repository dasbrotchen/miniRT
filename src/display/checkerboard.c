/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkerboard.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 16:12:32 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:11:08 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

t_colour	checkered_colour_from_uv(t_2dpoint uvpoint,
					t_checkerboard checkers)
{
	if (((int)floorf(uvpoint.x * checkers.width)
			+ (int)floorf(uvpoint.y * checkers.height)) % 2 == 0)
		return (checkers.b);
	return (checkers.a);
}

/*
* point to uvpoint mapper must use the intersection point
* and NOT the direction from the point to the sphere's origin,
* unlike get_sphere_img_colour()
*/
t_colour	get_checkered_sphere_colour(t_object *obj, t_point point)
{
	t_checkerboard	checkers;
	t_sphere		sphere;
	t_2dpoint		uvpoint;

	checkers = *(t_checkerboard *)obj->texture;
	sphere = *(t_sphere *)obj->object;
	point = vector_operation(point, sphere.centre, substract);
	uvpoint = sphere_point_to_uv_point(point, sphere, 1.0f);
	return (checkered_colour_from_uv(uvpoint, checkers));
}

t_colour	get_checkered_plane_colour(t_object *obj, t_point point)
{
	t_checkerboard	checkers;
	t_2dpoint		uvpoint;

	checkers = *(t_checkerboard *)obj->texture;
	uvpoint = plane_point_to_uv(point, 1.0f);
	return (checkered_colour_from_uv(uvpoint, checkers));
}

/*
* The point is received in world coordinates and transformed inside the
* function.
*/
t_colour	get_checkered_cylinder_colour(t_object *obj, t_point point)
{
	t_checkerboard	checkers;
	t_2dpoint		uvpoint;
	t_cylinder		cylinder;

	checkers = *(t_checkerboard *)obj->texture;
	cylinder = *(t_cylinder *)obj->object;
	point = vector_operation(point, cylinder.centre, substract);
	point = rotate_vec(cylinder.rot_quaternion, point);
	uvpoint = cylinder_point_to_uv(point, cylinder);
	return (checkered_colour_from_uv(uvpoint, checkers));
}

t_colour	get_checkered_cone_colour(t_object *obj, t_point point)
{
	t_checkerboard	checkers;
	t_2dpoint		uvpoint;
	t_cone			cone;

	checkers = *(t_checkerboard *)obj->texture;
	cone = *(t_cone *)obj->object;
	point = rotate_vec(cone.rot_quaternion,
			vector_operation(point, cone.apex, substract));
	uvpoint = cone_point_to_uv_checkers(point, cone);
	return (checkered_colour_from_uv(uvpoint, checkers));
}
