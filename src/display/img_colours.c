/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_colours.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:00:20 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:11:28 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

t_colour	get_sphere_img_colour(t_object *obj, t_point point)
{
	t_sphere	sphere;
	t_2dpoint	uvpoint;
	t_bumpmap	*bm;

	sphere = *(t_sphere *)obj->object;
	bm = (t_bumpmap *)obj->texture;
	point = vector_operation(point, sphere.centre, substract);
	uvpoint = sphere_point_to_uv_point(point, sphere, bm->zoom);
	return (get_filtered_colour(bm, uvpoint.x, uvpoint.y));
}

/*
* Third argument to plane_point_to_uv_textures is the scale factor.
* 1:1 is a scale factor of 1, smaller values will zoom on the pattern.
*/
t_colour	get_plane_img_colour(t_object *obj, t_point point)
{
	t_plane		plane;
	t_2dpoint	uvpoint;
	t_bumpmap	*bm;

	plane = *(t_plane *)obj->object;
	bm = (t_bumpmap *)obj->texture;
	uvpoint = plane_point_to_uv_textures(point, plane, bm->zoom);
	return (get_filtered_colour(bm, uvpoint.x, uvpoint.y));
}

t_colour	get_cylinder_img_colour(t_object *obj, t_point point)
{
	t_cylinder	cylinder;
	t_2dpoint	uvpoint;
	t_bumpmap	*bm;

	cylinder = *(t_cylinder *)obj->object;
	bm = (t_bumpmap *)obj->texture;
	point = rotate_vec(cylinder.rot_quaternion,
			vector_operation(point, cylinder.centre, substract));
	uvpoint = cylinder_point_to_uv(point, cylinder);
	uvpoint.x *= bm->zoom;
	uvpoint.y *= bm->zoom;
	return (get_filtered_colour(bm, uvpoint.x, uvpoint.y));
}

t_colour	get_cone_img_colour(t_object *obj, t_point point)
{
	t_cone		cone;
	t_2dpoint	uvpoint;
	t_bumpmap	*bm;

	cone = *(t_cone *)obj->object;
	bm = (t_bumpmap *)obj->texture;
	point = rotate_vec(cone.rot_quaternion,
			vector_operation(point, cone.apex, substract));
	uvpoint = cone_point_to_uv(point, cone);
	uvpoint.x *= bm->zoom;
	uvpoint.y *= bm->zoom;
	return (get_filtered_colour(bm, uvpoint.x, uvpoint.y));
}
