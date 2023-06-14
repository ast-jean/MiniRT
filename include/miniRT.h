/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 10:06:21 by ast-jean          #+#    #+#             */
/*   Updated: 2023/06/14 16:31:44 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdarg.h>
# include <limits.h>
# include <math.h>
# include <fcntl.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include "libft_dlist/dlist.h"

# define BLACK	0x000000FF
# define WHITE	0xFFFFFFFF
# define GRAY	0x888888FF
# define RED	0xFF0000FF
# define GREEN	0x00FF00FF
# define BLUE	0x0000FFFF
# define FP_SCALE	256
# define WIDTH		500
# define HEIGHT		500

typedef struct s_fixed{
	int	value;
}	t_fixed;

typedef struct s_2dPoint{
	t_fixed	x;
	t_fixed	y;
}	t_2dPoint;

typedef struct s_3dPoint{
	t_fixed	x;
	t_fixed	y;
	t_fixed	z;
}	t_3dPoint;

typedef struct s_rgba{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
}	t_rgba;

typedef struct s_rgba_unit{
	double	r;
	double	g;
	double	b;
}	t_rgba_unit;

typedef struct s_vector2d{
	double	x;
	double	y;
}	t_vector2d;

typedef struct s_vector3d{
	double	x;
	double	y;
	double	z;
}	t_vector3d;

typedef struct s_ray{
	t_vector3d	o;
	t_vector3d	d;
}	t_ray;

typedef struct s_shape
{
	char		*id;
	int			index;
	t_fixed		light_ratio;
	uint32_t	color;
	t_3dPoint	orientation;
	int16_t		fov;
	t_3dPoint	coord;
	t_fixed		radius;
	t_fixed		height;
	t_vector2d	ts;
}	t_shape;

typedef struct s_ray_hit{
	double		distance;
	uint32_t	color;
	t_shape		*shape;
	t_vector3d	coord;
	t_vector3d	normal;
	bool		hit;
	bool		bounced;
}	t_ray_hit;

typedef struct s_vars
{
	mlx_t		*mlx;
	t_dlist		*objs;
	t_shape		*camera;
	t_shape		*ambient_light;
	t_shape		*light;
	mlx_image_t	*img;
	bool		orientation_trigger;
	bool		x_trigger;
	bool		y_trigger;
	bool		z_trigger;
	bool		camera_trigger;
	bool		radius_trigger;
	bool		height_trigger;
	bool		fov_trigger;
	bool		light_trigger;
	bool		ambient_trigger;
	bool		interface_trigger;
	double		distance_to_screen;
	int			mouse_x;
	int			mouse_y;
	t_shape		*selected;
	char		*error_message;
	int			i;
	int			nbr_obj;
}	t_vars;

/*-------------------------Initialisation-------------------------*/
//miniRT.c
void		free_vars(t_vars *vars);
void		light_x(t_vars *vars);
/*----------------------------parsing----------------------------*/
//colors.c
int			str_is_digit(char *color);
uint8_t		valid_uint8(char *elem);
uint32_t	rgb_to_hex(char *elem);
//converter.c
t_fixed		str_to_fixed(char *elem);
t_3dPoint	str_to_3d(char *elem);
double		atod(char *str);
//debug.c
void		error_exit(int code, char *str);
int			info_count(char **elem);
//objects.c
t_shape		*object_sp(char **elem, t_vars *vars);
t_shape		*object_pl(char **elem, t_vars *vars);
t_shape		*object_cy(char **elem, t_vars *vars);
t_fixed		parse_size(char *elem);
t_fixed		parse_radius(char *elem);
//parsing.c
void		parse(int argc, char **argv);
void		valid_file(char *file);
void		split(char *file);
void		valid_element(char **elem);
//scene.c
void		object_a(char **elem, t_vars *vars);
void		object_c(char **elem, t_vars *vars);
void		object_l(char **elem, t_vars *vars);
t_fixed		parse_light_ratio(char *elem);
t_3dPoint	parse_coordinates(char *elem);
t_3dPoint	parse_orientation(char *elem);
uint8_t		parse_fov(char *elem);
//utils.c
void		free_split(char **args);
int			range(double elem, int low, int high);
int			char_isdigit(char c);
int			is_number(char *str);
void		valid_scene(void);
//split_whitespace.c
char		**split_on_space(char const *str);
/*-------------------------ray_tracing-------------------------*/
// ray_tracing.c
void		ray_to_screen(void);
uint32_t	ray_tracing(const t_ray ray);
t_ray_hit	ray_trace(t_ray ray, double dist, t_shape *shape);
// check.c
void		ray_checkhit(const t_ray ray, t_ray_hit *rh,
				double *distance, t_shape *shape_o);
bool		check_cy(t_shape *s, const t_ray ray,
				t_ray_hit *rh, double *dist);
bool		check_pl(const t_shape *s, const t_ray ray,
				t_ray_hit *rh, double *dist);
bool		check_sp(const t_shape *s, const t_ray ray,
				t_ray_hit *rh, double *dist);
//check_cy.c
void		calculate_vectors(const t_ray r, const t_shape *c,
				t_vector3d *d, t_vector3d *e);
bool		check_and_update_intersection(t_shape *c, const t_ray r,
				t_ray_hit *rh, double dist);
void		calculate_intersection_points(const t_ray r, t_vector2d,
				t_vector3d *P0, t_vector3d *P1);
void		calculate_heights(const t_shape *c, t_vector3d P0,
				t_vector3d P1, t_vector2d *h);
//normal.c
t_vector3d	light_normal(t_vector3d coords, t_vector3d obj_coord);
t_vector3d	cylinder_normal(t_vector3d intersection, \
t_vector3d C, t_vector3d V, double radius);
t_vector3d	plane_normal(t_vector3d hit_coords, t_vector3d orientation);
t_vector3d	find_normal(t_vector3d coords, t_vector3d obj_coord, \
t_shape shape, t_vector3d light_ray);
double		find_angle_normals(t_vector3d Norm1, t_vector3d Norm2);
//shading.c
t_rgba		shading(t_ray_hit *hit);
//colors.c
t_rgba		brightness(t_rgba color, double scale);
t_rgba		mix_colors(t_rgba colorA, t_rgba colorB, double mix_factor);
t_rgba		mix_colors_light(t_ray_hit hit, t_shape shape, double coeff);
//colors_utils.c
int32_t		rgba_to_int32_t(t_rgba rgba);
t_rgba		rgba_init(int r, int g, int b);
t_rgba		separate_color_rgba(uint32_t color);
t_rgba		rgba_add(t_rgba a, t_rgba b);
t_rgba		remove_excess(t_rgba c);
/*-------------------------Controls--------------------------*/
//update.c
void		update_trigger(t_vars *vars);
void		update_ambient_light(t_vars *vars);
void		update_intensity(t_vars *vars);
void		preset_ambient(t_vars *vars);
void		reset_position(t_vector3d *point);
//camera.c
void		change_fov(t_vars *vars);
void		camera_position(t_vars *vars);
void		orient_camera(t_vars *vars);
//init.c
void		init_trigger(t_vars *vars);
t_vars		*init_vars(void);
void		reinit_triggers(t_vars *vars, t_ray_hit hit);
//keybinding.c
void		mouse_hook(mouse_key_t button, action_t action,
				modifier_key_t mods, void *param);
void		process_key_actions(mlx_key_data_t keydata, void *param);
int			are_useful_keys_down(t_vars *vars);
//trigger.c
void		check_trigger_xyz(t_vars *vars);
void		check_trigger_orientation(t_vars *vars);
void		preset_ambient(t_vars *vars);
//norm_and_arrays
void		assign_keys_according_to_norm_a(int *useful_keys);
void		assign_keys_according_to_norm_b(int *useful_keys);
void		print_trigger_ui(void);
/*--------------------------Math-------------------------*/
//math_other.c
double		deg2grad(double deg);
uint32_t	clamp(uint32_t value, uint32_t min, uint32_t max);
double		find_distance(t_vector3d A, t_vector3d B);
//quadratic.c
bool		solve_quadratic(t_vector3d abc, t_vector2d *t);
void		swap_quad(t_vector2d *t);
t_vector3d	assign_var_quad(t_vector3d d, t_vector3d e, const t_shape *c);
//fixed.c
void		set_value(t_fixed *fp, double value);
double		to_double(t_fixed fp);
t_fixed		fp_init(double value);
t_vector3d	point3d_to_vector3d(t_3dPoint point);
t_3dPoint	vec3d_to_point3d(t_vector3d vec);
/*-------------------------vectors---------------------------*/
//Vectors.ops,c
t_vector3d	vector3d_add(t_vector3d a, t_vector3d b);
t_vector3d	vector3d_sub(t_vector3d a, t_vector3d b);
t_vector3d	vector3d_mult(t_vector3d v, double b);
t_vector3d	vector3d_mult3d(t_vector3d v, t_vector3d b);
t_vector3d	vector3d_unit(t_vector3d v);
//Vectors.c
t_vector3d	vector3d_init(double x, double y, double z);
double		vector3d_dot(t_vector3d a, t_vector3d b);
t_vector3d	vector3d_cross(t_vector3d a, t_vector3d b);
double		vector3d_length(t_vector3d v);
t_vector3d	vector3d_norm(const t_vector3d v);
//ray.c
t_ray		ray_init(t_vector3d origin, t_vector3d direction);
t_ray		ray_init_to_screen(t_vars *v, int x, int y);
t_vector3d	ray_direction(t_vector3d from, t_vector3d to);
void		print_info_scene(void);
#endif