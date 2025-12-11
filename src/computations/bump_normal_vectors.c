/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump_normal_vectors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:06:42 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:08:06 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

t_vector	sphere_bump_normal_vector(t_point point, t_object *obj)
{
	t_bumpmap	*bm;
	t_sphere	sphere;
	t_vector	normal;
	t_vector	bumped_normal;
	t_2dpoint	uvpoint;

	sphere = *(t_sphere *)obj->object;
	bm = (t_bumpmap *)obj->texture;
	normal = sphere_unit_normal_vector(point, obj);
	uvpoint = sphere_point_to_uv_direction(point, sphere, bm->zoom);
	bumped_normal = bump_normal(bm, uvpoint, normal, bm->depth);
	return (bumped_normal);
}

/*
* Third argument to plane_point_to_uv_textures is the scale factor.
* 1:1 is a scale factor of 1, smaller values will zoom on the pattern.
*/
t_vector	plane_bump_normal_vector(t_point point, t_object *obj)
{
	t_bumpmap	*bm;
	t_plane		plane;
	t_vector	bumped_normal;
	t_2dpoint	uvpoint;

	plane = *(t_plane *)obj->object;
	bm = (t_bumpmap *)obj->texture;
	uvpoint = plane_point_to_uv_textures(point, plane, bm->zoom);
	bumped_normal = bump_normal(bm, uvpoint, plane.normal, bm->depth);
	return (bumped_normal);
}

/*
* Point is in world coordinates. Due to the way cylinder_unit_normal_vector
* is implemented, we have to send the world point, get the normal,
* then convert the point and find the corresponding uvpoint
*/
t_vector	cylinder_bump_normal_vector(t_point point, t_object *obj)
{
	t_bumpmap	*bm;
	t_cylinder	cylinder;
	t_vector	bumped_normal;
	t_vector	normal;
	t_2dpoint	uvpoint;

	cylinder = *(t_cylinder *)obj->object;
	bm = (t_bumpmap *)obj->texture;
	normal = cylinder_unit_normal_vector(point, obj);
	point = rotate_vec(cylinder.rot_quaternion,
			vector_operation(point, cylinder.centre, substract));
	uvpoint = cylinder_point_to_uv(point, cylinder);
	uvpoint.x *= bm->zoom;
	uvpoint.y *= bm->zoom;
	bumped_normal = bump_normal(bm, uvpoint, normal, bm->depth);
	return (bumped_normal);
}

t_vector	cone_bump_normal_vector(t_point point, t_object *obj)
{
	t_bumpmap	*bm;
	t_cone		cone;
	t_vector	bumped_normal;
	t_vector	normal;
	t_2dpoint	uvpoint;

	cone = *(t_cone *)obj->object;
	bm = (t_bumpmap *)obj->texture;
	normal = cone_unit_normal_vector(point, obj);
	point = rotate_vec(cone.rot_quaternion,
			vector_operation(point, cone.apex, substract));
	uvpoint = cone_point_to_uv(point, cone);
	uvpoint.x *= bm->zoom;
	uvpoint.y *= bm->zoom;
	bumped_normal = bump_normal(bm, uvpoint, normal, bm->depth);
	return (bumped_normal);
}
