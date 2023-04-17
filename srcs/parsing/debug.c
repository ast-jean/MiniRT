#include "../../include/miniRT.h"

void	error_exit(int code, char *str)
{
	t_Vars *vars = init_vars();
	char *temp;
	
	if (code == 1)
	{
		printf("%s", str);
		free_vars(vars);
		exit(0);
	}
	if (code == 2)
	{
		temp = vars->error_message;
		vars->error_message = ft_strjoin(str, vars->error_message);
		free(temp);
	}
	if (code == 3)
		vars->error_message = ft_strjoin(str, vars->error_message);
	if (code == 4)
		vars->error_message = ft_strjoin("Invalid element: ", str);
	if (code == 180)
		vars->error_message = ft_strjoin("Invalid FOV -> ", str);
	if (code == 255)
		vars->error_message = ft_strjoin("Invalid RGB -> ", str);
}

/*
New error exit with code for each type of info
ex:
error_exit(int code, char *invalid_info)
{
if (code == 1)
vars->error_message = ft_strjoin("Invalid RGB -> ", invalid_info);
code 2 = FOV
error_message = ft_strjoin("Invalid FOV -> ", invalid_info);
...
}

back to object function: 
error_message = strjoin("Object '..': ", error_message)

final message example:
Object A: Invalid FOV -> 256
>%
*/

void	print_objects()
{
	t_Vars *vars = init_vars();
	t_node *aff = vars->objs->first;
	printf("------------Struct-------------\n");
	printf("ID:\t%s\n", vars->camera->id);
	printf("Coord:\t(%f),(%f),(%f)\n", to_double(vars->camera->coord.x), to_double(vars->camera->coord.y), to_double(vars->camera->coord.z));
    printf("Ori.:\t(%f),(%f),(%f)\n", to_double(vars->camera->orientation.x), to_double(vars->camera->orientation.y), to_double(vars->camera->orientation.z));
    printf("FOV:\t%d\n", vars->camera->FOV);
	printf("-------------------------------\n");
	printf("ID:\t%s\n", vars->ambient_light->id);
	printf("LRatio:\t%f\n", to_double(vars->ambient_light->light_ratio));
	printf("Color:\t%X\n", vars->ambient_light->color);
	printf("-------------------------------\n");
	printf("ID:\t%s\n", vars->light->id);
	printf("Coord:\t(%f),(%f),(%f)\n", to_double(vars->light->coord.x), to_double(vars->light->coord.y), to_double(vars->light->coord.z));
	printf("LRatio:\t%f\n", to_double(vars->light->light_ratio));
	printf("Color:\t%X\n", vars->light->color);
	printf("------------t_dlist------------\n");
	while(aff)
	{
		t_shape *s = aff->content;

		if (ft_strcmp(s->id, "sp")){
			printf("ID:\t%s\n", s->id);
			printf("Coord:\t(%f),(%f),(%f)\n", to_double(s->coord.x), to_double(s->coord.y), to_double(s->coord.z));
			printf("Dia.:\t%f\n", to_double(s->radius));
			printf("Color:\t%X\n", s->color);
		}
		else if (ft_strcmp(s->id, "pl")){
			printf("ID:\t%s\n", s->id);
            printf("Coord:\t(%f),(%f),(%f)\n", to_double(s->coord.x), to_double(s->coord.y), to_double(s->coord.z));
            printf("Ori.:\t(%f),(%f),(%f)\n", to_double(s->orientation.x), to_double(s->orientation.y), to_double(s->orientation.z));
			printf("Color:\t%X\n", s->color);
		}
		else if (ft_strcmp(s->id, "cy")){
			printf("ID:\t%s\n", s->id);
            printf("Coord:\t(%f),(%f),(%f)\n", to_double(s->coord.x), to_double(s->coord.y), to_double(s->coord.z));
            printf("Ori.:\t(%f),(%f),(%f)\n", to_double(s->orientation.x), to_double(s->orientation.y), to_double(s->orientation.z));
			printf("Dia.:\t%f\n", to_double(s->radius));
			printf("Height:\t%f\n", to_double(s->height));
			printf("Color:\t%X\n", s->color);
		}
		printf("------------------------------\n");
		aff = aff->next;
	}
}

		// if (ft_strcmp(s->id, "A")){
		// 	printf("ID:\t%s\n", s->id);
		// 	printf("LRatio:\t%f\n", to_double(s->light_ratio));
		// 	printf("Color:\t%X\n", s->color);
		// }
		// else if (ft_strcmp(s->id, "C")){
		// 	printf("ID:\t%s\n", s->id);
		// 	printf("Coord:\t(%f),(%f),(%f)\n", to_double(s->coord.x), to_double(s->coord.y), to_double(s->coord.z));
        //     printf("Ori.:\t(%f),(%f),(%f)\n", to_double(s->orientation.x), to_double(s->orientation.y), to_double(s->orientation.z));
        //     printf("FOV:\t%d\n", s->FOV);
		// }
		// else if (ft_strcmp(s->id, "L")){
		// 	printf("ID:\t%s\n", s->id);
		// 	printf("Coord:\t(%f),(%f),(%f)\n", to_double(s->coord.x), to_double(s->coord.y), to_double(s->coord.z));
		// 	printf("LRatio:\t%f\n", to_double(s->light_ratio));
		// 	printf("Color:\t%X\n", s->color);
		// }

// void	print_objects(t_dlist *l)
// {
// 	t_node *aff = l->first;

// 	while(aff)
// 	{
// 		t_shape *s = aff->content;

// 		if (ft_strcmp(s->id, "A")){
// 			printf("ID:\t%s\n", s->id);
// 			printf("LRatio:\t%d,%d\n", s->light_ratio.entier, s->light_ratio.decimal);
// 			printf("Color:\t%X\n", s->color);
// 		}
// 		else if (ft_strcmp(s->id, "C")){
// 			printf("ID:\t%s\n", s->id);
//             printf("Coord:\t%d.%d,", s->coord.x.entier, s->coord.x.decimal);
//             printf("%d.%d,", s->coord.y.entier, s->coord.y.decimal);
//             printf("%d.%d\n", s->coord.z.entier, s->coord.z.decimal);
//             printf("Ori.:\t%d.%d,", s->orientation.x.entier, s->orientation.x.decimal);
//             printf("%d.%d,", s->orientation.y.entier, s->orientation.y.decimal);
//             printf("%d.%d\n", s->orientation.z.entier, s->orientation.z.decimal);
//             printf("FOV:\t%d\n", s->FOV);
// 		}
// 		else if (ft_strcmp(s->id, "L")){
// 			printf("ID:\t%s\n", s->id);
//             printf("Coord:\t%d.%d,", s->coord.x.entier, s->coord.x.decimal);
//             printf("%d.%d,", s->coord.y.entier, s->coord.y.decimal);
//             printf("%d.%d\n", s->coord.z.entier, s->coord.z.decimal);
// 			printf("LRatio:\t%d,%d\n", s->light_ratio.entier, s->light_ratio.decimal);
// 			printf("Color:\t%X\n", s->color);
// 		}
// 		else if (ft_strcmp(s->id, "sp")){
// 			printf("ID:\t%s\n", s->id);
//             printf("Coord:\t%d.%d,", s->coord.x.entier, s->coord.x.decimal);
//             printf("%d.%d,", s->coord.y.entier, s->coord.y.decimal);
//             printf("%d.%d\n", s->coord.z.entier, s->coord.z.decimal);
// 			printf("Dia.:\t%d,%d\n", s->diameter.entier, s->diameter.decimal);
// 			printf("Color:\t%X\n", s->color);
// 		}
// 		else if (ft_strcmp(s->id, "pl")){
// 			printf("ID:\t%s\n", s->id);
//             printf("Coord:\t%d.%d,", s->coord.x.entier, s->coord.x.decimal);
//             printf("%d.%d,", s->coord.y.entier, s->coord.y.decimal);
//             printf("%d.%d\n", s->coord.z.entier, s->coord.z.decimal);
//             printf("Ori.:\t%d.%d,", s->orientation.x.entier, s->orientation.x.decimal);
//             printf("%d.%d,", s->orientation.y.entier, s->orientation.y.decimal);
//             printf("%d.%d\n", s->orientation.z.entier, s->orientation.z.decimal);
// 			printf("Color:\t%X\n", s->color);
// 		}
// 		else if (ft_strcmp(s->id, "cy")){
// 			printf("ID:\t%s\n", s->id);
//             printf("Coord:\t%d.%d,", s->coord.x.entier, s->coord.x.decimal);
//             printf("%d.%d,", s->coord.y.entier, s->coord.y.decimal);
//             printf("%d.%d\n", s->coord.z.entier, s->coord.z.decimal);
//             printf("Ori.:\t%d.%d,", s->orientation.x.entier, s->orientation.x.decimal);
//             printf("%d.%d,", s->orientation.y.entier, s->orientation.y.decimal);
//             printf("%d.%d\n", s->orientation.z.entier, s->orientation.z.decimal);
// 			printf("Dia.:\t%d,%d\n", s->diameter.entier, s->diameter.decimal);
// 			printf("Height:\t%d,%d\n", s->height.entier, s->height.decimal);
// 			printf("Color:\t%X\n", s->color);
// 		}
// 		printf("------------------------------\n");
// 		aff = aff->next;
// 	}

// }

double Vector3d_distance(t_Vector3d point, t_Vector3d end_point)
{
    double dx = end_point.x - point.x;
    double dy = end_point.y - point.y;
    double dz = end_point.z - point.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}


void draw_ray(t_Ray *ray, double x, double y, double distance)
{
    int i;
    int x2, y2;
    int color = 0xFFFFFF; // couleur du rayon (blanc)

    // On calcule les coordonnées du deuxième point du rayon
    x2 = x + (ray->d.x * distance);
    y2 = y + (ray->d.y * distance);

    // On vérifie que les coordonnées ne dépassent pas les limites de l'écran
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return;
    if (x2 < 0 || x2 >= WIDTH || y2 < 0 || y2 >= HEIGHT)
        return;

    // On dessine une ligne entre les deux points en ajoutant un effet de profondeur
    for (i = 0; i < distance; i++)
    {
        double depth = remap(0.0, distance, i); // effet de profondeur
        int r = (color >> 16) & 0xFF;
        int g = (color >> 8) & 0xFF;
        int b = color & 0xFF;
        r = (int)(r * depth);
        g = (int)(g * depth);
        b = (int)(b * depth);
        int new_color = (r << 16) | (g << 8) | b;
        mlx_put_pixel(init_vars()->img, x + (ray->d.x * i), y + (ray->d.y * i), new_color);
    }
}


// void draw_ray(t_Ray *ray)
// {
//     int i;
//     int color = 0xFFFFFF; // couleur du rayon (blanc)
//     double distance = 2000; // distance maximale de propagation du rayon
// 	t_Vars *vars = init_vars();
//     t_Vector3d origin =  Point3d_to_Vector3d(init_vars()->camera->coord); // origine du rayon (position de la caméra)
//     t_Vector3d direction = Vector3d_unit(Vector3d_sub(Vector3d_add(ray->origin, ray->direction), origin)); // direction du rayon à partir de la caméra
//     t_Vector3d point = origin; // point actuel du rayon
    
//     // On calcule les coordonnées du deuxième point du rayon en fonction de la distance maximale
//     t_Vector3d end_point = Vector3d_add(point, Vector3d_mult(direction, distance));

//     // On dessine une ligne entre les deux points avec une couleur réduite pour l'effet de profondeur
//     int color_depth = color & 0x00FFFFFF; // couleur sans la composante alpha
//     double depth_scale = 0.7; // échelle de la réduction de la couleur en fonction de la distance
//     double dist = Vector3d_distance(point, end_point); // distance entre les deux points
//     double depth = 0; // profondeur actuelle du rayon
//     for (i = 0; i < dist; i++)
//     {
//         depth = remap(0, dist, i); // on calcule la profondeur actuelle en fonction de la distance
//         mlx_put_pixel(vars->img, point.x, point.y, brightness(color_depth, 1 - depth_scale * depth)); // on dessine le pixel avec une couleur réduite
//         point = Vector3d_add(point, direction); // on passe au point suivant du rayon
//     }
	
// }






// void draw_ray(t_Ray *ray, double x, double y, double distance)
// {
//     int i;
//     int x2, y2;
//     int color = 0xFFFFFF; // couleur du rayon (blanc)
// 	t_Vars *vars = init_vars();

//     // On calcule les coordonnées du deuxième point du rayon
//     x2 = (int)(x + (ray->direction.x * distance));
//     y2 = (int)(y + (ray->direction.y * distance));

//     // On dessine une ligne entre les deux points
//     mlx_put_pixel(vars->img, (int)x, (int)y, color);
//     mlx_put_pixel(vars->img, (int)x2, (int)y2, color);
//     for (i = 1; i < distance; i++)
//     {
//         mlx_put_pixel(vars->img,  (int)(x + (ray->direction.x * i)), (int)(y + (ray->direction.y * i)), color);
//     }
// }