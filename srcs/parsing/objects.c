#include "../../include/miniRT.h"

t_AmbientLight    *object_A(char **elem)
{
    t_AmbientLight *A = NULL;
    A->id = elem[0];
    A->light_ratio = elem[1];
    A->color = elem[2];
    return(A);
}