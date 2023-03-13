
#ifndef OBJECTS_H
# define OBJECTS_H


#include "miniRT.h"


typedef struct s_Fixed{
	int	value;
	int scale;
}	t_Fixed;

typedef struct s_2dPoint{
    t_Fixed x;
	t_Fixed y;
} t_2dPoint;

typedef struct s_3dPoint{
    t_Fixed x;
	t_Fixed y;
	t_Fixed z;
} t_3dPoint;

typedef struct s_shape
{
	char 		*id;
	t_Fixed		light_ratio; //from 0.0 to 1.0
	uint32_t	color; //RGB from 0 to 255
	t_3dPoint	orientation; //from -1 to 1 for each xyz
	uint32_t	FOV;		 //FOV from 0 to 180
	t_3dPoint	coord; //coords for center xyz
	t_Fixed		diameter; //size of sphere
	t_Fixed		height; // height of cylinder
}	t_shape;

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
