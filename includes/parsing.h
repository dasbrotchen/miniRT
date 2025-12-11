/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgrangeo <rgrangeo@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:15:02 by rgrangeo          #+#    #+#             */
/*   Updated: 2024/11/07 19:45:20 by rgrangeo         ###   ########.fr       */
/*   Updated: 2024/11/06 12:35:41 by pantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# ifndef COORD_MAX
#  define COORD_MAX 999999.0f
# endif
# ifndef ERR_CTRL
#  define ERROR -1
#  define NONE 0
#  define OBJECT 1
#  define LIGHT 2
# endif
# define SP_MIN_ARGS 4
# define PL_MIN_ARGS 4
# define CY_MIN_ARGS 6
# define CO_MIN_ARGS 6

# include "shapes.h"
# include "camera.h"
# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>

typedef enum e_objecttype
{
	NORMAL,
	CHECKERED,
	TEXTURED,
}	t_objecttype;

typedef struct s_nbr_element
{
	unsigned int	ambient_lightning;
	unsigned int	camera;
	unsigned int	light;
	unsigned int	object;
	int				error;
}	t_nbr_element;

typedef struct s_memory_scene
{
	t_object	**object_m;
	t_light		*light_m;
}	t_memory_scene;

t_nbr_element		element_counter(int fd);
float				str_float(const char *string, int *error);
int					str_fov(const char *nptr, int *error);
int					str_colour(const char *nptr, int *error);
void				*putstr_malloc_error(void);
t_nbr_element		split_malloc_error(char *line, int fd,
						t_nbr_element nbr_element);
int					split_scene_malloc_error(char *line, int fd,
						t_memory_scene mscene, t_scene *scene);
void				origin_scene(t_memory_scene m_scene, t_scene *scene);
t_nbr_element		unrecognised_object(int fd, t_nbr_element nbr_element);
void				free_split(char **split);
int					open_file(const char *path);
int					parsing(const char *path, t_scene *scene);
int					putstr_error(char *msg);
int					nbr_parameters(char **split);
int					type_object(char *type);
int					object_valid_n_params(unsigned int type,
						unsigned int n_param, unsigned int min_params);
int					create_sphere(char **line, t_scene *scene);
int					create_cylinder(char **line, t_scene *scene);
int					create_plane(char **line, t_scene *scene);
int					create_cone(char **line, t_scene *scene);
void				*object_filler_error(void *obj, void *texture, char *msg);
int					assign_function_ptrs(int type, t_scene *scene,
						char **line, int shape);
void				init_function_ptrs(t_scene *scene);
int					parse_element(int fd, t_scene *scene);
int					free_gnl(int fd);
void				free_scene(t_scene *scene);
int					parse_vector(t_vector *vector, char *line, int *error);
int					parse_colour(t_colour *colour, char *line, int *error);
void				set_lighting_intensities_dfl(t_object *object);
int					parse_textured_lighting_intensities(char **line,
						int *error, t_scene *scene, int type);
int					parse_lighting_intensities(t_object *object,
						char **line, int *error);
int					parse_normalise_vectors(t_vector *vector, char *line,
						int *error);
int					load_textures(int type, t_scene *scene, char **line,
						char *filename);
int					malloc_texture(int type, void *obj, void **texture);
int					create_camera(char **line, t_camera *camera);
int					create_ambient_lightning(char **line, t_light *ambiant);
int					create_light(char **line, t_light *light);

#endif
