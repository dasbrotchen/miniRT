/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:11:54 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/13 23:08:00 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

t_point	get_intersection_point(t_ray ray, float t)
{
	t_point	i1;

	i1.x = ray.origin.x + ray.direction.x * t;
	i1.y = ray.origin.y + ray.direction.y * t;
	i1.z = ray.origin.z + ray.direction.z * t;
	return (i1);
}

t_object	*get_closest_object(t_object **objs)
{
	t_object		*closest;
	unsigned int	k;
	float			min;

	k = 0;
	min = -1;
	closest = (void *)0;
	while (objs[k])
	{
		if ((objs[k]->distance < min && objs[k]->distance >= 0)
			|| (objs[k]->distance >= 0 && min < 0))
		{
			min = objs[k]->distance;
			closest = objs[k];
		}
		k++;
	}
	return (closest);
}
