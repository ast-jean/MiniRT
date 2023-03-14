#include "../../include/miniRT.h"

t_shape   *object_A(char **elem)
{
    t_shape *S = malloc(sizeof(t_shape));
    S->id = elem[0];
    S->light_ratio = str_to_fixed(elem[1]);
	S->color = RGB_to_hex(elem[2]);
    return(S);
}

t_shape *object_C(char **elem)
{
    t_shape *S = malloc(sizeof(t_shape));
	S->id = elem[0];
	S->coord = str_to_3D(elem[1]);
	S->orientation = str_to_3D(elem[2]);
	S->FOV = ft_atoi(elem[3]);
	return (S);
}

t_shape *object_L(char **elem)
{
    t_shape *S = malloc(sizeof(t_shape));
	S->id = elem[0];
	S->coord = str_to_3D(elem[1]);
	S->light_ratio = str_to_fixed(elem[2]);
	if (elem[3])
		S->color = RGB_to_hex(elem[3]);
	return (S);
}