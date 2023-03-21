
#ifndef VECTORS_H
# define VECTORS_H

#include "miniRT.h"

typedef struct s_Vector2d{
    double x;
	double y;
} t_Vector2d;

typedef struct s_Vector3d{
    double x;
	double y;
	double z;
} t_Vector3d;

typedef struct s_Ray{
    t_Vector3d origin;
	t_Vector3d direction;
} t_Ray;

/*-------------------------Vectors_ops.c--------------------------*/
t_Vector3d Vector3d_add(t_Vector3d a, t_Vector3d b);
t_Vector3d Vector3d_sub(t_Vector3d a, t_Vector3d b);
t_Vector3d Vector3d_mult(t_Vector3d v, double b);
t_Vector3d Vector3d_div(t_Vector3d v, double b);
/*-------------------------Vectors.c--------------------------*/
t_Vector3d Vector3d_init(double x, double y, double z);
double Vector3d_dot(t_Vector3d a, t_Vector3d b);
t_Vector3d Vector3d_cross(t_Vector3d a, t_Vector3d b);
double Vector3d_length(t_Vector3d v);
t_Vector3d Vector3d_unit(t_Vector3d v);
/*-------------------------Ray.c--------------------------*/
t_Ray ray_init(t_Vector3d origin, t_Vector3d direction);
t_Ray ray_makeForPixel(t_Vars vars, int x, int y);
int32_t ray_trace(const t_Ray *ray, t_Vars vars);

#endif