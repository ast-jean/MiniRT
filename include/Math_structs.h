
#ifndef MATHSTRUCT_H
# define MATHSTRUCT_H

# include <math.h>

#include "miniRT.h"

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

#endif