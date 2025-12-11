/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:31:34 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/06 12:45:17 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

float	sqrf(float f)
{
	return (f * f);
}

float	dot(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_vector	x_prod(t_vector v1, t_vector v2)
{
	t_vector	cross_product;

	cross_product.x = (v1.y * v2.z) - (v1.z * v2.y);
	cross_product.y = (v1.z * v2.x) - (v1.x * v2.z);
	cross_product.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (cross_product);
}
