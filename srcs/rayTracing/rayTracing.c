#include "../../include/miniRT.h"


// Define a virtual camera with a position, orientation, and field of view.
void save_camera(t_dlist *l, t_Vars *vars){
	t_node *aff = l->first;

	while(aff)
	{
		t_shape *s = aff->content;
		if (ft_strcmp(s->id, "C"))
		{
			vars->camera->id = s->id;
			vars->camera->orientation = s->orientation;
			vars->camera->coord = s->coord;
			vars->camera->FOV = s->FOV;
			dlist_remove_node(l, aff);
			return ;
		}
		aff = aff->next;
	}
	printf("Not Camera found : save_camera()\n");
	return ;
}


// Define a scene with one or more objects, each with a position, orientation, and geometry (e.g., a sphere, a plane, etc.).

// For each pixel in the image plane, compute a ray that starts from the camera position and passes through that pixel. The direction of the ray is given by the camera orientation and the field of view.

// For each ray, test it for intersection with each object in the scene. This can typically be done using an algorithm like ray-object intersection.

// If the ray intersects an object, compute the color of the corresponding pixel in the image using a shading model that takes into account the lighting and material properties of the object.

// Repeat steps 3-5 for each pixel in the image to obtain a complete rendering.







/*
	       ____
	    ,dP9CGG88@b,
	  ,IPIYYICCG888@@b,
	 dIiIIIIIICGG8888@b
	dCIIIIIIICCGG8888@@b
____GCCIIIICCCGGG8888@@@__________________
	GGCCCCCCCGGG88888@@@
	GGGGCCCGGGG88888@@@@...
	Y8GGGGGG8888888@@@@P.....
	 Y88888888888@@@@@P......
	 `Y8888888@@@@@@@P'......
	    `@@@@@@@@@P'.......
		   """"........
*/


