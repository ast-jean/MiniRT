
#pragma once
#ifndef _MINI_RT_H_
# define _MINI_RT_H_

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <limits.h>
# include <math.h>
# include <fcntl.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include "libft_dlist/dlist.h"

#define BLACK	0x000000FF
#define WHITE	0xFFFFFFFF
#define GRAY	0x888888FF
#define RED		0xFF0000FF
#define GREEN	0x00FF00FF
#define BLUE	0x0000FFFF

#define fp_scale 256 //fixed number definition: now at 0.00
#define WIDTH	800 //Width of screen
#define HEIGHT	500 //Height of screen

static mlx_image_t* img;

typedef struct s_Vector2d	t_Vector2d;
typedef struct s_Vector3d	t_Vector3d;
typedef struct s_Ray_hit	t_Ray_hit;
typedef struct s_Ray		t_Ray;
typedef struct s_shape		t_shape;


typedef struct s_Vector2d{
    int32_t x;
	int32_t y;
} t_Vector2d;

typedef struct s_Vector3d{
    float x;
	float y;
	float z;
} t_Vector3d;

typedef struct s_Ray{
    t_Vector3d o;
	t_Vector3d d;
} t_Ray;

typedef struct s_Ray_hit{
    float		distance;
	uint32_t	color;
	t_shape		*shape;
	t_Vector3d	*coord;
} t_Ray_hit;

typedef struct s_rgba{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
} t_rgba;

typedef struct s_shape
{
	char 		*id;
	uint8_t		light_ratio; //from 0.0 to 1.0
	uint32_t	color; //RGB from 0 to 255
	t_Vector3d	coord; //coords for center xyz
	t_Vector3d	orien; //from -1 to 1 for each xyz
	uint8_t		FOV; //FOV from 0 to 180
	float		radius; //size of sphere
	float		height; // height of cylinder
}	t_shape;

typedef struct s_Vars	// all of our values needed throught the program
{
	mlx_t		*mlx;
	t_dlist		*objs;
	t_shape		*camera;
	t_shape		*ambient_light;
	t_shape		*light;
	mlx_image_t	*img;
	float		distance_to_screen;
	t_Vector2d 	mouse_pos;
	t_shape		*selected;
	char		*error_message;
} t_Vars;


/*-------------------------Vectors_ops.c--------------------------*/
t_Vector3d Vector3d_add(t_Vector3d a, t_Vector3d b);
t_Vector3d Vector3d_sub(t_Vector3d a, t_Vector3d b);
t_Vector3d Vector3d_mult(t_Vector3d v, float b);
t_Vector3d Vector3d_div(t_Vector3d v, float b);
/*-------------------------Vectors.c--------------------------*/
t_Vector3d	Vector3d_init(float x, float y, float z);
float		Vector3d_dot(t_Vector3d a, t_Vector3d b);
t_Vector3d	Vector3d_cross(t_Vector3d a, t_Vector3d b);
float		Vector3d_length(t_Vector3d v);
t_Vector3d	Vector3d_unit(t_Vector3d v);
t_Vector3d Vector3d_norm(const t_Vector3d v);
/*-------------------------Ray.c--------------------------*/
t_Ray ray_init(t_Vector3d origin, t_Vector3d direction);
t_Ray ray_init_to_screen(t_Vars *v, int32_t x, int32_t y);
t_Ray bounce_light(t_Vars *vars, t_Ray_hit *hit);
bool light_is_visible(t_Vars *vars, t_Ray_hit *hit);
// float round_to_first_digit(float num);
// float trunc_to_first_digit(float num);


/*-------------------------Initialisation-------------------------*/
//miniRT.c
t_Vars	*init_vars();
void	free_vars(t_Vars *vars);
/*----------------------------parsing----------------------------*/
//parsing.c
void		parse(int argc, char **argv);
void		valid_file(char *file);
void		split(char *file);
void		free_split(char **args);
void		valid_element(char **elem);
// t_Fixed		str_to_fixed(char *elem);
t_Vector3d	str_to_3D(char *elem);
//scene.c
void		object_A(char **elem, t_Vars *vars);
void		object_C(char **elem, t_Vars *vars);
void		object_L(char **elem, t_Vars *vars);
//objects.c
t_shape 	*object_sp(char **elem, t_Vars *vars);
t_shape 	*object_pl(char **elem, t_Vars *vars);
t_shape 	*object_cy(char **elem, t_Vars *vars);
//colors.c
int			str_is_digit(char *color);
uint8_t		valid_uint8(char *elem, int range);
uint32_t	rgb_to_hex(char *elem);
//debug.c
void		print_objects();
// void		draw_ray(t_Ray *ray, double x, double y, double distance);
void		error_exit(int code, char *str);

// /*----------------------------fixed------------------------------*/
// void		set_value(t_Fixed *fp, double value);
// double		to_double(t_Fixed fp);
// int			to_int(t_Fixed fp);
// t_Fixed		fp_init(double value);
// t_Vector3d	Point3d_to_Vector3d(t_3dPoint point);
// t_3dPoint	Vector3d_to_Point3d(t_Vector3d vec);
// double		fp_cal(char operand, int num_args, ...);
/*-------------------------ray_tracing-------------------------*/
// ray_tracing.c
void		ray_to_screen();
int32_t		ray_tracing(const t_Ray ray);
t_Ray_hit	ray_trace(const t_Ray ray, float dist);
// check.c
void	ray_checkhit(const t_Ray ray, t_Ray_hit *rh, float *distance);
bool	check_cy(const t_shape *s,const t_Ray ray, t_Ray_hit *rh);
bool	check_pl(const t_shape *s,const t_Ray ray, t_Ray_hit *rh);
bool	check_sp(const t_shape *s,const t_Ray ray, t_Ray_hit *rh);

/*---------------------------colors-------------------------*/
float	remap(float a, float b, float t);
int32_t	brightness(int32_t color, float scale);
t_rgba	separate_color_rgba(int32_t color);
int32_t mix_colors(int32_t colorA, int32_t colorB, float ratio);

/*---------------------------Math-------------------------*/
//math_other.c
float		deg2grad(float deg);
uint32_t	clamp(uint32_t value, uint32_t min, uint32_t max);
float		find_distance(t_Vector3d A, t_Vector3d B);
float		intToFloat(int value);

#endif



// typedef struct s_AmbientLight
// {
// 	char	*id; // always 'A'
// 	t_Fixed	light_ratio; //from 0.0 to 1.0
// 	uint32_t	color; //RGB from 0 to 255    
// 	// //ex: 182,60,60 -> 0xB63C3CFF 
// 	// //ex: 45,45,200 -> 0x2D2DC8FF

// }	t_AmbientLight;

// typedef struct s_Camera
// {
// 	char		*id;		 // always 'C'
// 	t_3dPoint	orientation; //from -1 to 1 for each xyz
// 	uint32_t		FOV;		 //FOV from 0 to 180
// }	t_Camera;

// typedef struct s_Light
// {
// 	char		*id; // always 'L'
// 	t_Fixed		light_ratio; //from 0.0 to 1.0
// 	uint32_t	color; //RGB from 0 to 255
// }	t_Light;

// typedef struct s_Sphere
// {
// 	char		*id; // always 'sp'
// 	t_3dPoint	center; //coords for center xyz
// 	t_Fixed		diameter; //size of sphere
// 	uint32_t		color; //RGB from 0 to 255
// }	t_Sphere;

// typedef struct s_Plane
// {
// 	char		*id; // always 'pl'
// 	t_3dPoint	coords; //coords for center xyz
// 	t_3dPoint	orientation; //from -1 to 1 for each xyz
// 	uint32_t		color; //RGB from 0 to 255
// }	t_Plane;

// typedef struct s_Cylinder
// {
// 	char		*id; // always 'cy'
// 	t_3dPoint	coords; //coords for center xyz
// 	t_3dPoint	orientation; //from -1 to 1 for each xyz
// 	t_Fixed		dia; //diameter of cercles
// 	t_Fixed		height; // height of cylinder
// 	uint32_t		color; //RGB from 0 to 255
// }	t_Cylinder;

// typedef struct s_Cone
// {
// 	char		*id; // always 'co'
// 	t_3dPoint	coords; //coords for center xyz
// 	t_3dPoint	orientation; //from -1 to 1 for each xyz
// 	t_Fixed		dia; //diameter of cercle
// 	t_Fixed		height; // height of cylinder
// 	uint32_t	color; //RGB from 0 to 255 for each 
// }	t_Cone;
