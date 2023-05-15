
#pragma once
#ifndef _MINI_RT_H_
# define _MINI_RT_H_

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
# include "objects.h"
# include "Vectors.h"

#define BLACK	0x000000FF
#define WHITE	0xFFFFFFFF
#define GRAY	0x888888FF
#define RED		0xFF0000FF
#define GREEN	0x00FF00FF
#define BLUE	0x0000FFFF

#define fp_scale 256 //fixed number definition: now at 0.00
#define WIDTH	500 //Width of screen
#define HEIGHT	500 //Height of screen



typedef struct s_Vector3d t_Vector3d;
typedef struct s_Vector2d t_Vector2d;
typedef struct s_Ray_hit t_Ray_hit;
typedef struct s_Ray t_Ray;


typedef struct s_Vars	// all of our values needed throught the program
{
	mlx_t		*mlx;
	t_dlist		*objs;
	t_shape		*camera;
	t_shape		*ambient_light;
	t_shape		*light;
	mlx_image_t	*img;
	bool		orientation_trigger;
	bool 		x_trigger;
	bool		y_trigger;
	bool		z_trigger;
	bool		camera_trigger;
	bool		radius_trigger;
	bool		height_trigger;
	bool		FOV_trigger;
	bool	    light_trigger;
	bool		ambient_trigger;
	double		distance_to_screen;
	int 		mouse_x;
	int 		mouse_y;
	t_shape		*selected;
	char		*error_message;
	int			i;
	int			nbr_obj;
} t_Vars;

typedef struct s_matrice3x3
{
	double m[3][3];
} t_matrice3x3;

typedef struct s_matrice4x4
{
	double m[4][4];
} t_matrice4x4;

typedef struct s_rotation
{
	double phi;
	double theta;
	double psi;
}	t_rotation;

/*-------------------------Initialisation-------------------------*/
//miniRT.c
t_Vars	*init_vars();
void	free_vars(t_Vars *vars);
/*----------------------------parsing----------------------------*/
//colors.c
int			str_is_digit(char *color);
uint8_t		valid_uint8(char *elem);
uint32_t	rgb_to_hex(char *elem);
//converter.c
t_Fixed		str_to_fixed(char *elem);
t_3dPoint	str_to_3d(char *elem);
double		atod(char *str);
//debug.c
void		error_exit(int code, char *str);
int			info_count(char **elem);
void		print_objects();
//objects.c
t_shape 	*object_sp(char **elem, t_Vars *vars);
t_shape 	*object_pl(char **elem, t_Vars *vars);
t_shape 	*object_cy(char **elem, t_Vars *vars);
t_Fixed		parse_size(char *elem);
t_Fixed		parse_radius(char *elem);
//parsing.c
void		parse(int argc, char **argv);
void		valid_file(char *file);
void		split(char *file);
void		valid_element(char **elem);
//scene.c
void		object_a(char **elem, t_Vars *vars);
void		object_c(char **elem, t_Vars *vars);
void		object_l(char **elem, t_Vars *vars);
t_Fixed		parse_light_ratio(char *elem);
t_3dPoint	parse_coordinates(char *elem);
t_3dPoint	parse_orientation(char *elem);
uint8_t 	parse_fov(char *elem);
//utils.c
void		free_split(char **args);
int			range(double elem, int low, int high);
int			char_isdigit(char c);
int			is_number(char *str);
void		valid_scene();
// void 		draw_ray(t_Ray *ray, double x, double y, double distance);

/*----------------------------fixed------------------------------*/
void		set_value(t_Fixed *fp, double value);
double		to_double(t_Fixed fp);
int			to_int(t_Fixed fp);
t_Fixed		fp_init(double value);
t_Vector3d	Point3d_to_Vector3d(t_3dPoint point);
t_3dPoint Vec3D_to_point3D(t_Vector3d vec); //use?
double		fp_cal(char operand, int num_args, ...);
/*-------------------------ray_tracing-------------------------*/
// ray_tracing.c
void		ray_to_screen();
uint32_t	ray_tracing(const t_Ray ray);
t_Ray_hit	ray_trace(t_Ray ray, double dist, t_shape *shape);
// check.c
bool	check_side(const t_Ray ray, const t_shape shape);
void	ray_checkhit(const t_Ray ray, t_Ray_hit *rh, double *distance, t_shape *shape_o);
double	check_cy(const t_shape *s,const t_Ray ray, t_Ray_hit *rh, double dist);
double	check_pl(const t_shape *s,const t_Ray ray, t_Ray_hit *rh, double dist);
double	check_sp(const t_shape *s,const t_Ray ray, t_Ray_hit *rh, double dist);
bool	check_dot_sign(t_Vector3d shape_pos, t_Vector3d Vec1, t_Vector3d Vec2);
/*---------------------------Normal-------------------------*/
t_Vector3d	light_normal(t_Vector3d coords, t_Vector3d obj_coord);
t_Vector3d	cylinder_normal(t_Vector3d intersection, t_Vector3d C, t_Vector3d V);
t_Vector3d	plane_normal(t_Vector3d hit_coords, t_Vector3d orientation);
t_Vector3d	find_normal(t_Vector3d coords, t_Vector3d obj_coord, t_shape shape);
double		find_angle_normals(t_Vector3d Norm1, t_Vector3d Norm2);
/*---------------------------Shading-------------------------*/
t_rgba		shading(t_Ray_hit *hit);
t_Vector3d	find_normal(t_Vector3d coords, t_Vector3d obj_coord, t_shape shape);
// t_rgba		shading_sp(t_Ray ray, t_Ray_hit *hit);
/*---------------------------colors-------------------------*/
//colors.c
t_rgba		brightness(t_rgba color, double scale);
t_rgba		mix_colors(t_rgba colorA, t_rgba colorB, double mix_factor);
t_rgba		ambient(t_rgba color);
t_rgba		mix_colors_light(t_Ray_hit hit, t_shape shape, double coeff);
//colors_utils.c
int32_t		rgba_to_int32_t(t_rgba rgba);
t_rgba		rgba_init(int r, int g, int b);
t_rgba		separate_color_rgba(uint32_t color);
t_rgba		rgba_add(t_rgba a, t_rgba b);
t_rgba		remove_excess(t_rgba c);

/*--------------------------Math-------------------------*/
//math_other.c
double		deg2grad(double deg);
uint32_t	clamp(uint32_t value, uint32_t min, uint32_t max);
double		clampd(double value, double min, double max);
double		find_distance(t_Vector3d A, t_Vector3d B);
bool		solveQuadratic(t_Vector3d abc, t_Vector2d *t, double *disc);
double		max(double value1, double value2);

//matrice.c
t_matrice3x3 matrice_rotation_x(double alpha);
t_matrice3x3 matrice_rotation_y(double beta);
t_matrice3x3 matrice_rotation_z(double gamma);
t_matrice3x3 multiplier_matrices(t_matrice3x3 A, t_matrice3x3 B);
t_3dPoint rotation_point(t_matrice3x3 M, t_3dPoint P);
t_rotation vector_to_rotation_angles(t_Vector3d orientation);
t_matrice3x3 combine_matrice(t_matrice3x3 rx, t_matrice3x3 ry, t_matrice3x3 rz);

t_rgba calculate_lighting(t_Ray_hit *rh, const t_Vector3d *normal);
t_Vector3d cylinder_normal(t_Vector3d intersection, t_Vector3d C, t_Vector3d V);


#endif