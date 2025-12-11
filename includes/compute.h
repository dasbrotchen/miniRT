/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:35:10 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/14 16:33:02 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPUTE_H
# define COMPUTE_H
# include "shapes.h"
# include "camera.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"
# define EPSILON 0.001f
# define SHADOW_INTENSITY 0.75
# ifndef REFLECTION_RECURSIONS
#  define REFLECTION_RECURSIONS 2
# endif
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

//main rendering function
void			render_scene(t_scene scene);
void			progress_bar(int start, int max);

//quaternions
t_quaternion	quaternion_conjugate(t_quaternion quaternion);
t_vector		find_rotation_axis(t_vector cylinder_axis);
t_quaternion	construct_quaternion(t_vector cylinder_axis);
t_quaternion	construct_quaternion_parallel_axes(t_vector cylinder_axis,
					t_vector rotation_axis);
t_vector		rotate_vec(t_quaternion q, t_vector v);

//intersections, object operations
t_object		*first_hit_object(t_object **objs, t_ray reflection_ray,
					t_point *inter_point);
t_point			plane_intersection_point(t_ray ray, float distance);
float			get_sphere_intersections(t_ray ray, void *object,
					t_point *to_pixelise);
float			get_cylinder_intersections(t_ray ray, void *object,
					t_point *point);
float			get_cone_intersections(t_ray ray,
					void *object, t_point *point);
float			get_plane_intersection(t_ray ray, void *obj,
					t_point *point);
t_vector		cylinder_unit_normal_vector(t_point point,
					t_object *obj);
t_vector		cone_unit_normal_vector(t_point point,
					t_object *obj);
t_vector		sphere_unit_normal_vector(t_point point,
					t_object *obj);
t_vector		plane_unit_normal_vector(t_point point,
					t_object *obj);
t_vector		sphere_bump_normal_vector(t_point point,
					t_object *obj);
t_vector		plane_bump_normal_vector(t_point point,
					t_object *obj);
t_vector		cylinder_bump_normal_vector(t_point point,
					t_object *obj);
t_vector		cone_bump_normal_vector(t_point point,
					t_object *obj);

//coordinates translation
t_ray			pixel_to_ray(t_camera camera, t_2dpoint pixel);
t_point			get_intersection_point(t_ray ray, float t);

//float operations
float			sqrf(float f);
float			dot(t_vector v1, t_vector v2);
float			add(float n1, float n2);
float			substract(float n1, float n2);
float			multiply(float n1, float n2);
float			divide(float n1, float n2);

//matrix/vector operations
t_vector		mat_vec_product(t_matrix matrix, t_vector vec);
t_vector		vector_scalar_operation(t_vector v1,
					float scalar, float (*f)(float n1, float n2));
t_vector		vector_operation(t_vector v1, t_vector v2,
					float (*f)(float n1, float n2));
t_vector		x_prod(t_vector v1, t_vector v2);
t_vector		normalise(t_vector vec);
t_matrix		transpose(t_matrix matrix);

#endif
