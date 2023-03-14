#include "../../include/miniRT.h"

t_shape *object_sp(char **elem)
{
    t_shape *S = malloc(sizeof(t_shape));
	S->id = elem[0];
	S->coord = str_to_3D(elem[1]);
	S->diameter = str_to_fixed(elem[2]);
	S->color = RGB_to_hex(elem[3]);
	return (S);
}

t_shape *object_pl(char **elem)
{
    t_shape *S = malloc(sizeof(t_shape));
	S->id = elem[0];
	S->coord = str_to_3D(elem[1]);
	S->orientation = str_to_3D(elem[2]);
	S->color = RGB_to_hex(elem[3]);
	return (S);
}

t_shape *object_cy(char **elem)
{
    t_shape *S = malloc(sizeof(t_shape));
	S->id = elem[0];
    S->coord = str_to_3D(elem[1]);
	S->orientation = str_to_3D(elem[2]);
	S->diameter = str_to_fixed(elem[3]);
	S->height = str_to_fixed(elem[4]);
	S->color = RGB_to_hex(elem[5]);
	return (S);
}
