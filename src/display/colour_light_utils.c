/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_light_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 17:51:09 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/11 18:58:36 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colours.h"
#include "compute.h"

t_colour	get_object_colour(t_object *obj, t_point point)
{
	(void)point;
	return (obj->colour);
}

float	get_light_intensity(t_vector normal, t_light source, t_point point)
{
	t_vector	light_direction;

	light_direction = normalise(vector_operation(source.origin,
				point, substract));
	return (fmaxf(dot(normal, light_direction), 0));
}
