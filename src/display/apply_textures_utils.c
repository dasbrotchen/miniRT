/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_textures_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:44:00 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 12:10:11 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compute.h"

t_colour	int_to_rgb(int colour)
{
	return ((t_colour){.r = ((colour >> 16) & 0xFF),
		.g = ((colour >> 8) & 0xFF),
		.b = colour & 0xFF});
}

t_colour	colour_at_point(t_bumpmap *bm, int i1, int i2)
{
	return (int_to_rgb(bm->pixel_data[i1 * bm->width + i2]));
}
