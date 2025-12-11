/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pantoine <pantoine@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:03:49 by pantoine          #+#    #+#             */
/*   Updated: 2024/11/12 22:14:00 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H
# include "ray.h"
# include "colours.h"
# include "camera.h"

typedef struct s_colour
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}	t_colour;

typedef struct s_colourblend
{
	t_colour	s;
	t_colour	d;
	t_colour	a;
	t_colour	r;
}	t_colourblend;

/*
 * width is the number of horizontal tiles
 * height is the number of vertical tiles
 * a is the first colour of the pattern (r, g, b)
 * b is the second colour of the pattern (r, g, b)
 * img_ptr will always be set to NULL.
*/
typedef struct s_checkerboard
{
	unsigned int		width;
	unsigned int		height;
	struct s_colour		a;
	struct s_colour		b;
}	t_checkerboard;

/*
* mlx_xpm_file_to_image must be assigned to img_ptr
* mlx_get_data_addr must be assigned to pixel_data
* width and height are automatically filled by
* mlx_xpm_file_to_image
*/
typedef struct s_bumpmap
{
	float			depth;
	float			zoom;
	int				width;
	int				height;
	int				*pixel_data;
	void			*img_ptr;
}	t_bumpmap;

typedef struct s_light
{
	t_point			origin;
	float			brightness;
	t_colour		colour;
	unsigned char	is_blocked;
}	t_light;

/*
* Unlike objects, the lights array is not
* NULL-terminated. No particular reason why.
*/
typedef struct s_sources
{
	t_light			*source;
	unsigned int	nb_lights;
}	t_sources;

typedef struct s_plane
{
	t_point		position;
	t_vector	normal;
}	t_plane;

typedef struct s_sphere
{
	t_point		centre;
	float		radius;
}	t_sphere;

typedef struct s_cylinder
{
	t_point			centre;
	t_vector		axis;
	float			radius;
	float			height;
	float			minz;
	float			maxz;
	t_quaternion	rot_quaternion;
}	t_cylinder;

typedef struct s_cone
{
	t_point			apex;
	t_vector		axis;
	float			height;
	float			theta;
	float			minz;
	float			maxz;
	t_quaternion	rot_quaternion;
}	t_cone;

struct					s_object;
typedef float			(*t_intersect_func)(t_ray ray,
							void *obj, t_point * point);
typedef t_vector		(*t_normal_vec_get)(t_point point,
							struct s_object * obj);
typedef t_ray			(*t_ray_get)(t_ray ray, void * obj);
typedef t_point			(*t_point_get)(t_point point, void *obj);
typedef struct s_colour	(*t_colour_get)(struct s_object *obj, t_point point);

typedef struct s_object
{
	t_ray				ray;
	void				*object;
	float				shininess;
	float				distance;
	float				specular_coef;
	float				diffuse_coef;
	float				reflection_coef;
	t_colour			colour;
	void				*texture;
	unsigned char		has_img;
	t_intersect_func	intersect;
	t_normal_vec_get	get_normal_vec;
	t_ray_get			get_ray;
	t_point_get			get_point;
	t_colour_get		get_colour;
}	t_object;

typedef enum e_shapetype
{
	SPHERE = 0,
	PLANE = 1,
	CYLINDER = 2,
	CONE = 3
}	t_shapetype;

typedef enum e_funcptroffsets
{
	NORMAL_OFFSET = 0,
	BUMP_OFFSET = 1,
	CHECKERED_OFFSET = 1,
	IMG_TEXTURE_OFFSET = 2,
}	t_funcptroffsets;

typedef struct s_funcptrs
{
	t_intersect_func	intersect_ptr[4];
	t_ray_get			ray_get_ptr[4];
	t_point_get			point_get_ptr[4];
	t_colour_get		colour_get_ptr[4][3];
	t_normal_vec_get	normal_get_ptr[4][2];
}	t_funcptrs;

typedef struct s_scene
{
	t_object			**objs;
	t_sources			light_sources;
	t_light				ambient;
	t_camera			camera;
	t_img				img;
	void				*inst;
	void				*window;
	t_funcptrs			funcptrs;
}	t_scene;

t_point					get_cylinder_point(t_point point, void *obj);
t_point					get_cone_point(t_point point, void *obj);
t_point					get_normal_point(t_point point, void *obj);
t_ray					get_cylinder_ray(t_ray ray, void *obj);
t_ray					get_cone_ray(t_ray ray, void *obj);
t_ray					get_normal_ray(t_ray ray, void *obj);
t_object				*get_closest_object(t_object **objs);
t_object				*create_cylinder_object(void *inst);
t_object				*create_cone_object(void *inst);
t_object				*create_sphere_object(void *inst);
t_object				*create_plane_object(void *inst);
t_object				**create_all_objects(void *inst);

#endif
