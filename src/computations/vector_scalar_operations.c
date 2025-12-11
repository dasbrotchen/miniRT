/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_scalar_operations.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 18:31:42 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/06 12:49:06 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"

t_vector	vector_scalar_operation(t_vector v1, float scalar,
				float (*f)(float n1, float n2))
{
	t_vector	result;

	result.x = f(v1.x, scalar);
	result.y = f(v1.y, scalar);
	result.z = f(v1.z, scalar);
	return (result);
}

float	add(float n1, float n2)
{
	return (n1 + n2);
}

float	substract(float n1, float n2)
{
	return (n1 - n2);
}

float	multiply(float n1, float n2)
{
	return (n1 * n2);
}

float	divide(float n1, float n2)
{
	return (n1 / n2);
}
