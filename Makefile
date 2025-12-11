NAME = miniRT

CC = cc

CFLAGS = -Wall -Werror -Wextra -g -I includes -I libft -I mlx -flto -funroll-loops -o3 -march=native -D REFLECTION_RECURSIONS=5

SRCS = main.c \
	   computations/operations.c \
	   computations/sphere_intersection_finder.c \
	   computations/cylinder_intersection_finder.c \
	   computations/cone_intersection_finder.c \
	   computations/plane_intersection_finder.c \
	   camera/world_to_camera_coords.c \
	   computations/matrix_operations.c \
	   camera/pixel_to_world.c \
	   computations/quaternion_rotation.c \
	   computations/quaternion_rotation_utils.c \
	   computations/vector_scalar_operations.c \
	   computations/vector_operations.c \
	   computations/unit_normal_vectors.c \
	   computations/bump_normal_vectors.c \
	   display/colour_light_utils.c \
	   display/diffuse_shading.c \
	   display/phong_reflections.c \
	   display/progress_bar.c \
	   parsing/translator.c \
	   parsing/open.c \
	   parsing/parsing.c \
	   parsing/get_next_line.c \
	   parsing/get_next_line_utils.c \
	   parsing/file_processor_utils.c \
	   parsing/element_counter.c \
	   parsing/base.c \
	   parsing/filling.c\
	   parsing/parsing_tools.c \
	   parsing/parsing_tools_bonus.c \
	   parsing/create_sphere.c \
	   parsing/parsing_assign_funcs.c \
	   parsing/create_cylinder.c \
	   parsing/create_plane.c \
	   parsing/create_camera.c \
	   parsing/create_light.c \
	   parsing/create_cone.c \
	   parsing/assign_shape_functions.c \
	   computations/object_utils.c \
	   computations/ray_getters.c \
	   computations/point_getters.c \
	   display/ambient_light.c \
	   computations/colour_operations.c \
	   computations/light_operations.c \
	   display/reflected_colours.c \
	   display/checkerboard.c \
	   display/renderer.c \
	   computations/plane_point_to_uv.c \
	   computations/cylinder_point_to_uv.c \
	   computations/cone_point_to_uv.c \
	   computations/sphere_point_to_uv.c \
	   display/bump_maps.c \
	   display/bump_maps_utils.c \
	   display/apply_textures.c \
	   display/apply_textures_utils.c \
	   display/img_colours.c

INC = includes/ray.h \
	  includes/shapes.h \
	  includes/compute.h \
	  includes/camera.h \
	  includes/colours.h \
	  includes/parsing.h \
	  includes/get_next_line.h \

ifeq ($(shell uname), Darwin)
	LIB = -Lmlx -lmlx -Llibft -lft -Imlx -L/usr/X11/lib -L/usr/lib -lXext -lX11 -lm -lz -framework OpenGL -framework AppKit
else
	LIB = -Lmlx -lmlx_Linux -Llibft -lft -Imlx -L/usr/lib -lXext -lX11 -lm -lz
endif

OBJS = $(SRCS:%.c=$(OBJ_D)%.o)

SRC_D = src/
OBJ_D = objects/

all: libft mlx
	@make --no-print-directory $(NAME)

$(OBJ_D)%.o: $(SRC_D)%.c $(INC)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I/usr/include -Imlx -c $< -o $@

$(NAME):	$(OBJ_D) $(OBJS) Makefile libft/libft.a  $(INC)
	$(MAKE) -C mlx
	$(CC) -g $(CFLAGS) $(OBJS) $(LIB) -o $@

libft:
	@make --no-print-directory -C libft

mlx:
	@make -C mlx

$(OBJ_D):
	@mkdir -p $(OBJ_D)

clean:
	@make clean -C mlx
	@make clean -C libft
	rm -rf $(OBJ_D)

fclean:
	@make clean -C mlx
	@make fclean -C libft
	rm -rf $(OBJ_D)
	rm -f $(NAME)

re: fclean all

normi:
	norminette $(SRC_D)$(SRCS)

.PHONY: all clean fclean re normi libft
