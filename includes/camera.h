/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:38:45 by pantoine          #+#    #+#             */
/*   Updated: 2025/12/11 15:39:05 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "ray.h"
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define WIDTH 900
# define HEIGHT 500

typedef struct s_camera
{
	t_point		viewpoint;
	t_vector	direction;
	t_vector	right;
	t_vector	up;
	int			fov;
	float		radian_fov;
	float		screen_width;
	float		screen_height;
	t_matrix	inverse_camera;
}	t_camera;

typedef struct s_img
{
	void	*img_ptr;
	char	*img_pixels;
	int		bpp;
	int		size_line;
	int		endian;
}	t_img;

t_camera	setup_camera(t_camera camera);

#endif
