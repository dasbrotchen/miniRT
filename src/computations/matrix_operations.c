/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_operations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 23:49:09 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/11/14 12:08:41 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

t_vector	mat_vec_product(t_matrix matrix, t_vector vec)
{
	t_vector	product;

	product.x = matrix.r1[0] * vec.x
		+ matrix.r1[1] * vec.y + matrix.r1[2] * vec.z;
	product.y = matrix.r2[0] * vec.x
		+ matrix.r2[1] * vec.y + matrix.r2[2] * vec.z;
	product.z = matrix.r3[0] * vec.x
		+ matrix.r3[1] * vec.y + matrix.r3[2] * vec.z;
	return (product);
}

t_matrix	transpose(t_matrix matrix)
{
	t_matrix	transpose;

	transpose.r1[0] = matrix.r1[0];
	transpose.r2[0] = matrix.r1[1];
	transpose.r3[0] = matrix.r1[2];
	transpose.r1[1] = matrix.r2[0];
	transpose.r2[1] = matrix.r2[1];
	transpose.r3[1] = matrix.r2[2];
	transpose.r1[2] = matrix.r3[0];
	transpose.r2[2] = matrix.r3[1];
	transpose.r3[2] = matrix.r3[2];
	return (transpose);
}
