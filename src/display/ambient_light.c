/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 18:31:14 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:10:02 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "colours.h"

t_colour	get_ambient_shading(t_light ambient_light,
				t_object *obj, t_point point)
{
	t_colour	ambient_shading;
	t_colour	obj_c;

	obj_c = obj->get_colour(obj, point);
	ambient_shading.r = (ambient_light.colour.r / 255.0f)
		* ambient_light.brightness * obj_c.r;
	ambient_shading.g = (ambient_light.colour.g / 255.0f)
		* ambient_light.brightness * obj_c.g;
	ambient_shading.b = (ambient_light.colour.b / 255.0f)
		* ambient_light.brightness * obj_c.b;
	return (ambient_shading);
}
