
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
# include "objects.h"
# include "Vectors.h"

#define BLACK	0x000000FF
#define WHITE	0xFFFFFFFF
#define GRAY	0x888888FF
#define RED		0xFF0000FF
#define GREEN	0x00FF00FF
#define BLUE	0x0000FFFF

#define fp_scale 256 //fixed number definition: now at 0.00
#define WIDTH	1000 //Width of screen
#define HEIGHT	1000 //Height of screen

static mlx_image_t* img;

typedef struct s_Vector3d t_Vector3d;
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
	double		distance_to_screen;
	int 		mouse_x;
	int 		mouse_y;
	t_shape		*selected;
	int			error_message;
} t_Vars;



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
t_Fixed		str_to_fixed(char *elem);
t_3dPoint	str_to_3D(char *elem);
//scene.c
void		object_A(char **elem, t_Vars *vars);
void		object_C(char **elem, t_Vars *vars);
void		object_L(char **elem, t_Vars *vars);
//objects.c
t_shape 	*object_sp(char **elem);
t_shape 	*object_pl(char **elem);
t_shape 	*object_cy(char **elem);
//colors.c
int			RGB_digit(char *color);
uint8_t		valid_RGB(char *color);
uint32_t	RGB_to_hex(char *elem);
//debug.c
void		print_objects();
void		error_exit(int code, char *str);
/*---------------------------------------------------------------*/
/*----------------------------fixed------------------------------*/
void		set_value(t_Fixed *fp, double value);
double		to_double(t_Fixed fp);
int			to_int(t_Fixed fp);
t_Vector3d	Point3d_to_Vector3d(t_3dPoint point);
/*---------------------------------------------------------------*/
/*---------------------------ray_tracing-------------------------*/
// ray_tracing.c
void		ray_to_screen();
int32_t		ray_tracing(const t_Ray *ray, t_Vars *vars);
t_Ray_hit	ray_trace(const t_Ray *ray);
// check.c
void	ray_checkhit(const t_Ray *ray, t_Ray_hit *rh, double *distance);
bool	check_cy(const t_shape *s,const  t_Ray ray, t_Ray_hit *rh);
bool	check_pl(const t_shape *s,const t_Ray ray, t_Ray_hit *rh);
bool	check_sp(const t_shape *s,const t_Ray *ray, t_Ray_hit *rh);

#endif