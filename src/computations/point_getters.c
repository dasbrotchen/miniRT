/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_getters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:32:55 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:09:02 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

t_point	get_cylinder_point(t_point point, void *obj)
{
	t_cylinder	cylinder;
	t_point		translated_point;

	cylinder = *(t_cylinder *)obj;
	translated_point = rotate_vec(quaternion_conjugate(cylinder.rot_quaternion),
			point);
	translated_point = vector_operation(cylinder.centre, translated_point, add);
	return (translated_point);
}

t_point	get_cone_point(t_point point, void *obj)
{
	t_cone	cone;
	t_point	translated_point;

	cone = *(t_cone *)obj;
	translated_point = rotate_vec(quaternion_conjugate(cone.rot_quaternion),
			point);
	translated_point = vector_operation(cone.apex, translated_point, add);
	return (translated_point);
}

t_point	get_normal_point(t_point point, void *obj)
{
	(void)obj;
	return (point);
}
