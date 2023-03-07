/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:58:16 by ast-jean          #+#    #+#             */
/*   Updated: 2023/03/06 11:19:01 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef _MINI_RT_H_
# define _MINI_RT_H_

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <fcntl.h>
# include <math.h>
# include "MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"

#define BLACK	0x000000FF
#define WHITE	0xFFFFFFFF
#define GRAY	0x888888FF
#define RED		0xFF0000FF
#define GREEN	0x00FF00FF
#define BLUE	0x0000FFFF

typedef struct s_Fixed{
	int	value;
	//slavoie
}	t_Fixed;

typedef struct s_2dPoint{
    t_Fixed x;
	t_Fixed y;
} t_2dPoint;

typedef struct s_3dPoint{
    t_Fixed x;
	t_Fixed y;
	t_Fixed z;
	int32_t		color;
} t_3dPoint;

typedef struct s_Vars	// all of our values needed throught the program
{
	t_3dPoint	*env3D;
	mlx_image_t* img;
	mlx_t		*mlx;
	void		*objs;
} t_Vars;

typedef struct s_AmbientLight
{
	char	*id; // always 'A'
	t_Fixed	light_ratio; //from 0.0 to 1.0
	uint32_t	color; //RGB from 0 to 255    
	//ex: 182,60,60 -> 0xB63C3CFF 
	//ex: 45,45,200 -> 0x2D2DC8FF
}	t_AmbientLight;

typedef struct s_Camera
{
	char		*id;		 // always 'C'
	t_3dPoint	orientation; //from -1 to 1 for each xyz
	uint32_t		FOV;		 //FOV from 0 to 180
}	t_Camera;

typedef struct s_Light
{
	char		*id; // always 'L'
	t_Fixed		light_ratio; //from 0.0 to 1.0
	uint32_t	color; //RGB from 0 to 255
}	t_Light;

typedef struct s_Sphere
{
	char		*id; // always 'sp'
	t_3dPoint	center; //coords for center xyz
	t_Fixed		diameter; //size of sphere
	uint32_t		color; //RGB from 0 to 255
}	t_Sphere;

typedef struct s_Plane
{
	char		*id; // always 'pl'
	t_3dPoint	coords; //coords for center xyz
	t_3dPoint	orientation; //from -1 to 1 for each xyz
	uint32_t		color; //RGB from 0 to 255
}	t_Plane;

typedef struct s_Cylinder
{
	char		*id; // always 'cy'
	t_3dPoint	coords; //coords for center xyz
	t_3dPoint	orientation; //from -1 to 1 for each xyz
	t_Fixed		dia; //diameter of cercles
	t_Fixed		height; // height of cylinder
	uint32_t		color; //RGB from 0 to 255
}	t_Cylinder;

typedef struct s_Cone
{
	char		*id; // always 'co'
	t_3dPoint	coords; //coords for center xyz
	t_3dPoint	orientation; //from -1 to 1 for each xyz
	t_Fixed		dia; //diameter of cercle
	t_Fixed		height; // height of cylinder
	uint32_t	color; //RGB from 0 to 255 for each 
}	t_Cone;

//parsing
void	parse(int argc, char **argv);
void	error_exit(char *str);
void	valid_file(char *file);
void	something(char *file);
#endif