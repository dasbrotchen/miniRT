/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_shape_functions.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 18:37:08 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:11:56 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

static void	assign_normal_vec_functions(t_scene *scene)
{
	scene->funcptrs.normal_get_ptr[SPHERE][NORMAL_OFFSET] = \
		&sphere_unit_normal_vector;
	scene->funcptrs.normal_get_ptr[SPHERE][BUMP_OFFSET] = \
		&sphere_bump_normal_vector;
	scene->funcptrs.normal_get_ptr[PLANE][NORMAL_OFFSET] = \
		&plane_unit_normal_vector;
	scene->funcptrs.normal_get_ptr[PLANE][BUMP_OFFSET] = \
		&plane_bump_normal_vector;
	scene->funcptrs.normal_get_ptr[CYLINDER][NORMAL_OFFSET] = \
		&cylinder_unit_normal_vector;
	scene->funcptrs.normal_get_ptr[CYLINDER][BUMP_OFFSET] = \
		&cylinder_bump_normal_vector;
	scene->funcptrs.normal_get_ptr[CONE][NORMAL_OFFSET] = \
		&cone_unit_normal_vector;
	scene->funcptrs.normal_get_ptr[CONE][BUMP_OFFSET] = \
		&cone_bump_normal_vector;
}

static void	assign_colour_functions(t_scene *scene)
{
	scene->funcptrs.colour_get_ptr[SPHERE][NORMAL_OFFSET] = \
		&get_object_colour;
	scene->funcptrs.colour_get_ptr[SPHERE][CHECKERED_OFFSET] = \
		&get_checkered_sphere_colour;
	scene->funcptrs.colour_get_ptr[SPHERE][IMG_TEXTURE_OFFSET] = \
		&get_sphere_img_colour;
	scene->funcptrs.colour_get_ptr[PLANE][NORMAL_OFFSET] = \
		&get_object_colour;
	scene->funcptrs.colour_get_ptr[PLANE][CHECKERED_OFFSET] = \
		&get_checkered_plane_colour;
	scene->funcptrs.colour_get_ptr[PLANE][IMG_TEXTURE_OFFSET] = \
		&get_plane_img_colour;
	scene->funcptrs.colour_get_ptr[CYLINDER][NORMAL_OFFSET] = \
		&get_object_colour;
	scene->funcptrs.colour_get_ptr[CYLINDER][CHECKERED_OFFSET] = \
		&get_checkered_cylinder_colour;
	scene->funcptrs.colour_get_ptr[CYLINDER][IMG_TEXTURE_OFFSET] = \
		&get_cylinder_img_colour;
	scene->funcptrs.colour_get_ptr[CONE][NORMAL_OFFSET] = \
		&get_object_colour;
	scene->funcptrs.colour_get_ptr[CONE][CHECKERED_OFFSET] = \
		&get_checkered_cone_colour;
	scene->funcptrs.colour_get_ptr[CONE][IMG_TEXTURE_OFFSET] = \
		&get_cone_img_colour;
}

static void	assign_intersection_functions(t_scene *scene)
{
	scene->funcptrs.intersect_ptr[SPHERE] = &get_sphere_intersections;
	scene->funcptrs.intersect_ptr[PLANE] = &get_plane_intersection;
	scene->funcptrs.intersect_ptr[CYLINDER] = &get_cylinder_intersections;
	scene->funcptrs.intersect_ptr[CONE] = &get_cone_intersections;
	scene->funcptrs.ray_get_ptr[SPHERE] = &get_normal_ray;
	scene->funcptrs.ray_get_ptr[PLANE] = &get_normal_ray;
	scene->funcptrs.ray_get_ptr[CYLINDER] = &get_cylinder_ray;
	scene->funcptrs.ray_get_ptr[CONE] = &get_cone_ray;
	scene->funcptrs.point_get_ptr[SPHERE] = &get_normal_point;
	scene->funcptrs.point_get_ptr[PLANE] = &get_normal_point;
	scene->funcptrs.point_get_ptr[CYLINDER] = &get_cylinder_point;
	scene->funcptrs.point_get_ptr[CONE] = &get_cone_point;
}

void	init_function_ptrs(t_scene *scene)
{
	assign_intersection_functions(scene);
	assign_colour_functions(scene);
	assign_normal_vec_functions(scene);
}
