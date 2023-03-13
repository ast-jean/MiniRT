
#pragma once
#ifndef _MINI_RT_H_
# define _MINI_RT_H_

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdarg.h>
# include <limits.h>
# include <fcntl.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include "libft_dlist/dlist.h"
# include "objects.h"

#define BLACK	0x000000FF
#define WHITE	0xFFFFFFFF
#define GRAY	0x888888FF
#define RED		0xFF0000FF
#define GREEN	0x00FF00FF
#define BLUE	0x0000FFFF

typedef struct s_Vars	// all of our values needed throught the program
{
	t_3dPoint	*env3D;
	mlx_image_t* img;
	mlx_t		*mlx;
	void		*objs;
} t_Vars;


//parsing
void	parse(int argc, char **argv, t_dlist *l);
void	error_exit(char *str);
void	valid_file(char *file);
void	split(char *file, t_dlist *l);
void	valid_element(char **elem, t_dlist *l);
//objects
t_shape	*object_A(char **elem);
t_shape *object_C(char **elem);
t_shape *object_L(char **elem);
t_shape *object_sp(char **elem);
t_shape *object_pl(char **elem);
t_shape *object_cy(char **elem);
uint32_t RGB_to_hex(char *elem);
void	print_objects(t_dlist *l);
t_Fixed	str_to_fixed(char *elem);
t_3dPoint str_to_3D(char *elem);
#endif