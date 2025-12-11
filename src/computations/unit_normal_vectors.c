/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unit_normal_vectors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:58:02 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:09:28 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

t_vector	cylinder_unit_normal_vector(t_point point, t_object *obj)
{
	t_cylinder	cylinder;
	t_vector	normal;

	cylinder = *(t_cylinder *)obj->object;
	point = rotate_vec(cylinder.rot_quaternion,
			vector_operation(point, cylinder.centre, substract));
	normal.x = (point.x) / cylinder.radius;
	normal.y = (point.y) / cylinder.radius;
	normal.z = 0;
	normal = rotate_vec(quaternion_conjugate(cylinder.rot_quaternion), normal);
	return (normalise(normal));
}

/*
* Point is in world coordinates, transform back into local coordinates.
* The normal is just the gradient of the implicit function for the 
* cone, i.e. grad(f(x, y, z, theta)) = grad(x^2 + y^2 - z^2tan^2(theta))
* The normal vector is in local coordinates, so we also transform it 
* back into world coordinates.
*/
t_vector	cone_unit_normal_vector(t_point point, t_object *obj)
{
	t_cone		cone;
	t_vector	normal;

	cone = *(t_cone *)obj->object;
	point = rotate_vec(cone.rot_quaternion,
			vector_operation(point, cone.apex, substract));
	normal = (t_vector){2 * point.x,
		2 * point.y,
		-2 * point.z * sqrf(tanf(cone.theta))};
	return (normalise(rotate_vec(quaternion_conjugate \
				(cone.rot_quaternion), normal)));
}

t_vector	sphere_unit_normal_vector(t_point point, t_object *obj)
{
	t_sphere	sphere;
	t_vector	normalised;

	sphere = *(t_sphere *)obj->object;
	normalised.x = 2 * point.x - 2 * sphere.centre.x;
	normalised.y = 2 * point.y - 2 * sphere.centre.y;
	normalised.z = 2 * point.z - 2 * sphere.centre.z;
	return (normalise(normalised));
}

t_vector	plane_unit_normal_vector(t_point point, t_object *obj)
{
	t_plane	plane;

	(void)point;
	plane = *(t_plane *)obj->object;
	return (plane.normal);
}
