/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_getters.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 19:03:09 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:09:16 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

t_ray	get_cylinder_ray(t_ray ray, void *obj)
{
	t_cylinder	cylinder;
	t_ray		to_shoot;

	cylinder = *(t_cylinder *)obj;
	to_shoot.origin = rotate_vec(cylinder.rot_quaternion,
			vector_operation(ray.origin, cylinder.centre, substract));
	to_shoot.direction = rotate_vec(cylinder.rot_quaternion, ray.direction);
	return (to_shoot);
}

t_ray	get_cone_ray(t_ray ray, void *obj)
{
	t_cone	cone;
	t_ray	to_shoot;

	cone = *(t_cone *)obj;
	to_shoot.origin = rotate_vec(cone.rot_quaternion,
			vector_operation(ray.origin, cone.apex, substract));
	to_shoot.direction = rotate_vec(cone.rot_quaternion, ray.direction);
	return (to_shoot);
}

t_ray	get_normal_ray(t_ray ray, void *obj)
{
	(void)obj;
	return (ray);
}
