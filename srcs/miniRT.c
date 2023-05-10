#include "../include/miniRT.h"
#include <errno.h>

static mlx_image_t* img;

void hook(void* param)
{
	// t_Vars		*vars = param;
	// mlx_t		*mlx = vars->mlx;
	// mlx_image_t *img = vars->img;

	// if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	// 	mlx_close_window(mlx);
	// if (mlx_is_key_down(mlx, MLX_KEY_UP))
	// 	img->instances[0].y -= 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	// 	img->instances[0].y += 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	// 	img->instances[0].x -= 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	// 	img->instances[0].x += 5;

	t_Vars* vars = param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	// if (mlx_is_key_down(vars->mlx, MLX_KEY_UP)){
	// 	set_value(&vars->camera->orientation.y,to_double(vars->camera->orientation.y) - 1);
	// 	// img->instances[0].y -= 5;
	// }
	// if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
	// {
	// 	set_value(&vars->camera->orientation.y,to_double(vars->camera->orientation.y) + 1);
	// 	// img->instances[0].y += 5;
	// }
	// if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
	// {
	// 	set_value(&vars->camera->orientation.x,to_double(vars->camera->orientation.x) - 1);
	// 	// img->instances[0].x -= 5;
	// }
	// if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
	// {
	// 	set_value(&vars->camera->orientation.x,to_double(vars->camera->orientation.x) + 1);
	// 	// img->instances[0].x += 5;
	// }

}

void init_trigger(t_Vars *vars)
{
	vars->x_trigger = 0;
	vars->y_trigger = 0;
	vars->z_trigger = 0;
	vars->radius_trigger = 0;
	vars->camera_trigger = 0;
	vars->orientation_trigger = 0;
	vars->height_trigger = 0;
	vars->FOV_trigger = 0;
	vars->light_trigger = 0;
	vars->ambient_light = 0;
}

t_Vars	*init_vars()
{
	static t_Vars	*vars;

	if (!vars)
	{

		vars = malloc(sizeof(t_Vars));
		vars->camera = NULL;
		vars->light = NULL;
		vars->ambient_light = NULL;
		// vars->mlx = NULL;
		// vars->img = malloc(sizeof(mlx_image_t));
		vars->objs = malloc(sizeof(t_dlist));
		vars->objs->first = NULL;
		vars->objs->last = NULL;
		vars->error_message = NULL;
		vars->selected = NULL;
		vars->distance_to_screen = 0;
		vars->i = 0;
		vars->nbr_obj = 0;
		init_trigger(vars);
	}
	return (vars);
}

void	free_vars(t_Vars *vars)
{
	dlist_free_content(vars->objs);
	free(vars->objs);
	free(vars->ambient_light);
	free(vars->light);
	free(vars->camera);
	if (vars->error_message)
		free(vars->error_message);
	free(vars);
}

void  mouse_hook(mouse_key_t button, action_t action, modifier_key_t mods, void* param)
{
	t_Vars *vars;
	t_Ray ray;
	t_Ray_hit hit;

	vars = param;
	(void)action;
	(void)mods;
	// printf("%i\n", button);

	if (mlx_is_mouse_down(vars->mlx, button))
	{
		mlx_get_mouse_pos(vars->mlx, &vars->mouse_x, &vars->mouse_y);
		ray = ray_init_to_screen(vars, vars->mouse_x, vars->mouse_y);
		hit = ray_trace(ray, 999999.9, NULL);
		if (hit.shape)
			vars->selected = hit.shape;
		if (vars->light_trigger)
		{
			set_value(&vars->light->coord.z, hit.coord.z);
			set_value(&vars->light->coord.y, hit.coord.y);
		}

	

		
		
		// free(ray);
		// printf("mouse_x = %d  mouse_y = %d\n", vars->mouse_x, vars->mouse_y);
		// mlx_put_pixel(vars->img, vars->mouse_x, vars->mouse_y, RED);
	}
	else
	{
		mlx_get_mouse_pos(vars->mlx, &vars->mouse_x, &vars->mouse_y);

		ray = ray_init_to_screen(vars, vars->mouse_x, vars->mouse_y);
		hit = ray_trace(ray, 999999.9, NULL);
		// printf("mouse_x: %d mouse_y: %d\n", vars->mouse_x, vars->mouse_y);
		// printf("%d\n", mlx_is_mouse_down(vars->mlx, 0));
		set_value(&vars->selected->coord.z, hit.coord.z);
		set_value(&vars->selected->coord.y, hit.coord.y);
		ray_to_screen();
		// print_objects();
	}

}

void print_trigger_state()
{
	t_Vars *vars;

	vars = init_vars();
	printf("\033[32m");
	printf("--------------------\n");
	printf("|Active trigger     |\n");
	printf("|R=%d, H=%d, O=%d, F=%d |\n|C=%d, X=%d, Y=%d, Z=%d |\n|L=%d A=%d		    |\n", \
	vars->radius_trigger, vars->height_trigger, vars->orientation_trigger, \
	vars->FOV_trigger, vars->camera_trigger, vars->x_trigger,vars->y_trigger, vars->z_trigger, vars->light_trigger, vars->ambient_trigger);
	printf("--------------------\n");
	printf("\033[0m\n");

}

void update_trigger()
{
	t_Vars *vars;

	vars = init_vars();

	if (mlx_is_key_down(vars->mlx, MLX_KEY_O))
		vars->orientation_trigger = !vars->orientation_trigger;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_C))
		vars->camera_trigger = !vars->camera_trigger;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_X))
		vars->x_trigger = !vars->x_trigger;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_Y))
		vars->y_trigger = !vars->y_trigger;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_Z))
		vars->z_trigger = !vars->z_trigger;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_R))
		vars->radius_trigger = !vars->radius_trigger;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_H))
		vars->height_trigger = !vars->height_trigger;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_F))
		vars->FOV_trigger = !vars->FOV_trigger;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_L))
		vars->light_trigger = !vars->light_trigger;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		vars->ambient_trigger = !vars->ambient_trigger;
	print_trigger_state();
}

void check_trigger_xyz()
{
	t_Vars *vars;

	vars = init_vars();

	if (mlx_is_key_down(vars->mlx, 61) ||  mlx_is_key_down(vars->mlx, 334))
	{
		if (vars->selected && vars->radius_trigger)
			vars->selected->radius.value += 50;
		if (vars->selected && vars->height_trigger)
			vars->selected->height.value += 50;
		if (!vars->orientation_trigger)
		{
			if (vars->selected && vars->x_trigger)
				set_value(&vars->selected->coord.x, to_double(vars->selected->coord.x) + 1);
			if (vars->selected && vars->y_trigger)
				set_value(&vars->selected->coord.y, to_double(vars->selected->coord.y) + 1);
			if (vars->selected && vars->z_trigger)
				set_value(&vars->selected->coord.z, to_double(vars->selected->coord.z) + 1);
		}
	}
	if (mlx_is_key_down(vars->mlx, 45) || mlx_is_key_down(vars->mlx, 333))
	{
		if (vars->selected && vars->radius_trigger)
			vars->selected->radius.value -= 50;
		if (vars->selected && vars->height_trigger)
			vars->selected->height.value -= 50;
		if (!vars->orientation_trigger)
		{
			if (vars->selected && vars->x_trigger)
				set_value(&vars->selected->coord.x, to_double(vars->selected->coord.x) - 1);
			if (vars->selected && vars->y_trigger)
				set_value(&vars->selected->coord.y, to_double(vars->selected->coord.y) - 1);
			if (vars->selected && vars->z_trigger)
				set_value(&vars->selected->coord.z, to_double(vars->selected->coord.z) - 1);
		}
	}

}
void reset_position(t_Fixed *point)
{
	if (to_double(*point) > 1)
		set_value(point, -1);
	if (to_double(*point) < -1)
		set_value(point, 1);
}

void check_trigger_orientation()
{

	t_Vars *vars;

	vars = init_vars();

	if (mlx_is_key_down(vars->mlx, 61) ||  mlx_is_key_down(vars->mlx, 334))
	{

		if (vars->orientation_trigger && vars->selected)
		{
			if (vars->x_trigger)
			{
				set_value(&vars->selected->orientation.x, to_double(vars->selected->orientation.x) + 0.1);
				reset_position(&vars->selected->orientation.x);

			}
			if (vars->y_trigger)
			{
				set_value(&vars->selected->orientation.y, to_double(vars->selected->orientation.y) + 0.1);
				reset_position(&vars->selected->orientation.y);	
			}
			if (vars->z_trigger)
			{
				set_value(&vars->selected->orientation.z, to_double(vars->selected->orientation.z) + 0.1);
				reset_position(&vars->selected->orientation.z);
			}
		}
	}
	if (mlx_is_key_down(vars->mlx, 45) || mlx_is_key_down(vars->mlx, 333))
	{

		if (vars->orientation_trigger && vars->selected)
		{
			if (vars->x_trigger)
			{
				set_value(&vars->selected->orientation.x, to_double(vars->selected->orientation.x) - 0.1);
				reset_position(&vars->selected->orientation.x);

			}
			if (vars->y_trigger)
			{
				set_value(&vars->selected->orientation.y, to_double(vars->selected->orientation.y) - 0.1);
				reset_position(&vars->selected->orientation.y);
			
			}
			if (vars->z_trigger)
			{
				set_value(&vars->selected->orientation.z, to_double(vars->selected->orientation.z) - 0.1);
				reset_position(&vars->selected->orientation.z);

			}
		}
	}
	if (vars->selected)
		printf("orientation x,y,z: %f, %f, %f\n", to_double(vars->selected->orientation.x),to_double(vars->selected->orientation.y),to_double(vars->selected->orientation.z));
}

void change_FOV()
{
	t_Vars *vars;

	vars = init_vars();

	if(vars->FOV_trigger)
	{

		if (mlx_is_key_down(vars->mlx, 61) ||  mlx_is_key_down(vars->mlx, 334))
			if ((int)vars->camera->FOV <= (int)180)
			{
				vars->camera->FOV = clamp(vars->camera->FOV + 3, 0 , 180);
				vars->distance_to_screen = (0.5 * WIDTH) / tan(deg2grad(vars->camera->FOV) * 0.5);
				// printf("FOV= %d\n", vars->camera->FOV);
			}
		if (mlx_is_key_down(vars->mlx, 45) || mlx_is_key_down(vars->mlx, 333))
			if (vars->camera->FOV >= 0)
			{
				vars->camera->FOV = clamp(vars->camera->FOV - 3, 0 , 180);
				vars->distance_to_screen = (0.5 * WIDTH) / tan(deg2grad(vars->camera->FOV) * 0.5);
				// printf("FOV= %d\n", vars->camera->FOV);
			}
	}
}

void camera_position()
{
	t_Vars *vars;

	vars = init_vars();
	if (mlx_is_key_down(vars->mlx, 61) ||  mlx_is_key_down(vars->mlx, 334))
	{
		if (vars->camera_trigger)
		{
			if (vars->x_trigger)
				set_value(&vars->camera->coord.x, to_double(vars->camera->coord.x) + 100);
			if (vars->y_trigger)
				set_value(&vars->camera->coord.y, to_double(vars->camera->coord.y) + 10);
			if (vars->z_trigger)
				set_value(&vars->camera->coord.z, to_double(vars->camera->coord.z) + 10);
		}
	}
	if (mlx_is_key_down(vars->mlx, 45) || mlx_is_key_down(vars->mlx, 333))
	{
		if (vars->camera_trigger && !vars->orientation_trigger)
		{
			if (vars->x_trigger)
				set_value(&vars->camera->coord.x, to_double(vars->camera->coord.x) - 100);
			if (vars->y_trigger)
				set_value(&vars->camera->coord.y, to_double(vars->camera->coord.y) - 10);
			if (vars->z_trigger)
				set_value(&vars->camera->coord.z, to_double(vars->camera->coord.z) - 10);
		}
	}


}


void orient_camera()
{
	t_Vars *vars = init_vars();

	if (mlx_is_key_down(vars->mlx, 61) ||  mlx_is_key_down(vars->mlx, 334))
	{
		if (vars->camera_trigger && vars->orientation_trigger)
		{
			if (vars->x_trigger)
				set_value(&vars->camera->orientation.x, to_double(vars->camera->orientation.x) + 0.007);
			if (vars->y_trigger)
				set_value(&vars->camera->orientation.y, to_double(vars->camera->orientation.y) + 0.007);
			if (vars->z_trigger)
				set_value(&vars->camera->orientation.z, to_double(vars->camera->orientation.z) + 0.007);
		}
	}
	if (mlx_is_key_down(vars->mlx, 45) || mlx_is_key_down(vars->mlx, 333))
	{
		if (vars->camera_trigger && vars->orientation_trigger)
			{
				if (vars->x_trigger)
					set_value(&vars->camera->orientation.x, to_double(vars->camera->orientation.x) - 0.007);
				if (vars->y_trigger)
					set_value(&vars->camera->orientation.y, to_double(vars->camera->orientation.y) - 0.007);
				if (vars->z_trigger)
					set_value(&vars->camera->orientation.z, to_double(vars->camera->orientation.z) - 0.007);
			}
	}
}

 int are_useful_keys_down(t_Vars *vars)
{
	int useful_keys[] = {61, 334, 333, 45, MLX_KEY_PAGE_UP, MLX_KEY_PAGE_DOWN, MLX_KEY_UP, MLX_KEY_DOWN,
	                     MLX_KEY_LEFT, MLX_KEY_RIGHT, MLX_KEY_ESCAPE, MLX_KEY_1, MLX_KEY_2, MLX_KEY_3,
	                     MLX_KEY_4, MLX_KEY_5, MLX_KEY_6, MLX_KEY_7, MLX_KEY_8, MLX_KEY_O, MLX_KEY_X,
	                     MLX_KEY_Y, MLX_KEY_Z, MLX_KEY_C, MLX_KEY_R, MLX_KEY_H, MLX_KEY_F, MLX_KEY_L};
	int num_keys = sizeof(useful_keys) / sizeof(int);
	int i = 0;

	while (i < num_keys)
	{
		if (mlx_is_key_down(vars->mlx, useful_keys[i]))
			return 1;
		i++;
	}

	return 0;
}

void light_x()
{
	t_Vars *vars = init_vars();

	if(vars->light_trigger && !vars->radius_trigger)
	{
		if (mlx_is_key_down(vars->mlx, 61) ||  mlx_is_key_down(vars->mlx, 334))
			set_value(&vars->light->coord.x, to_double(vars->light->coord.x) + 5);
		if (mlx_is_key_down(vars->mlx, 45) ||  mlx_is_key_down(vars->mlx, 333))
			set_value(&vars->light->coord.x, to_double(vars->light->coord.x) - 5);
	}
}

void update_ambient_light()
{
	t_Vars *vars = init_vars();

	if (vars->ambient_trigger)
	{
		if ((mlx_is_key_down(vars->mlx, 61) ||  mlx_is_key_down(vars->mlx, 334)) && (to_double(vars->ambient_light->light_ratio) + 0.1) < 1)
			set_value(&vars->ambient_light->light_ratio, to_double(vars->ambient_light->light_ratio) + 0.1);

		if ((mlx_is_key_down(vars->mlx, 45) ||  mlx_is_key_down(vars->mlx, 333)) && (to_double(vars->ambient_light->light_ratio) - 0.1) > 0)
			set_value(&vars->ambient_light->light_ratio, to_double(vars->ambient_light->light_ratio) - 0.1);
	}
}

void preset_ambient(t_Vars *vars)
{
	if (mlx_is_key_down(vars->mlx, MLX_KEY_1))
		vars->ambient_light->color = GREEN;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_2))
		vars->ambient_light->color = RED;	
	if (mlx_is_key_down(vars->mlx, MLX_KEY_3))
		vars->ambient_light->color = BLUE;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_4))
		vars->ambient_light->color = GRAY;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_5))
		vars->ambient_light->color = WHITE;
	// if (mlx_is_key_down(vars->mlx, MLX_KEY_6))

}

void update_intensity(t_Vars *vars)
{
	if (vars->light_trigger && vars->radius_trigger)	
	{
		if ((mlx_is_key_down(vars->mlx, 61) ||  mlx_is_key_down(vars->mlx, 334)) && (to_double(vars->light->light_ratio) + 0.1) < 1)
			set_value(&vars->light->light_ratio, to_double(vars->light->light_ratio) + 0.1);

		if ((mlx_is_key_down(vars->mlx, 45) ||  mlx_is_key_down(vars->mlx, 333)) && (to_double(vars->light->light_ratio) - 0.1) > 0)
			set_value(&vars->light->light_ratio, to_double(vars->light->light_ratio) - 0.1);
	}

}

void process_key_actions(mlx_key_data_t keydata, void *param)
{
    t_Vars *vars = param;

	(void)keydata;

    if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
    {
        mlx_close_window(vars->mlx);
        return;
    }

    update_trigger();
	preset_ambient(vars);

    if (are_useful_keys_down(vars))
    {
        check_trigger_xyz();
        check_trigger_orientation();
        change_FOV();
        camera_position();
        orient_camera();
		light_x();
        update_ambient_light();
		update_intensity(vars);
	    ray_to_screen();
    }

}

// void shape_modifier(mlx_key_data_t keydata, void *param)
// {
// 	t_Vars *vars;

	
// 	// printf("%d\n", keydata.key);
// 	(void)keydata;
// 	vars = param;

// 	if(mlx_is_key_down(vars->mlx, 61) || mlx_is_key_down(vars->mlx, MLX_KEY_PAGE_UP) \
// 	|| mlx_is_key_down(vars->mlx, MLX_KEY_PAGE_DOWN) || mlx_is_key_down(vars->mlx, 334) \
// 	|| mlx_is_key_down(vars->mlx, 333) || mlx_is_key_down(vars->mlx, 45) \
// 	|| mlx_is_key_down(vars->mlx, MLX_KEY_UP) || mlx_is_key_down(vars->mlx, MLX_KEY_DOWN) \
// 	|| mlx_is_key_down(vars->mlx, MLX_KEY_LEFT) || mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT) \
// 	|| mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE) || mlx_is_key_down(vars->mlx, MLX_KEY_A) \
// 	|| mlx_is_key_down(vars->mlx, MLX_KEY_W) || mlx_is_key_down(vars->mlx, MLX_KEY_D) \
// 	|| mlx_is_key_down(vars->mlx, MLX_KEY_S) || mlx_is_key_down(vars->mlx, MLX_KEY_Q) \
// 	|| mlx_is_key_down(vars->mlx, MLX_KEY_E)|| mlx_is_key_down(vars->mlx, MLX_KEY_7) \
// 	|| mlx_is_key_down(vars->mlx, MLX_KEY_8) || mlx_is_key_down(vars->mlx, MLX_KEY_O) \
// 	|| mlx_is_key_down(vars->mlx, MLX_KEY_X)|| mlx_is_key_down(vars->mlx, MLX_KEY_Y) \
// 	|| mlx_is_key_down(vars->mlx, MLX_KEY_Z)|| mlx_is_key_down(vars->mlx, MLX_KEY_C) \
// 	||mlx_is_key_down(vars->mlx, MLX_KEY_R)|| mlx_is_key_down(vars->mlx, MLX_KEY_H) \
// 	|| mlx_is_key_down(vars->mlx, MLX_KEY_F))
// 	{

// 		update_trigger();
// 		check_trigger_xyz();
// 		check_trigger_orientation();
// 		change_FOV();
// 		camera_position();
// 		orient_camera();

// 		if (mlx_is_key_down(vars->mlx, MLX_KEY_8))
// 		{
// 			if (to_double(vars->ambient_light->light_ratio) + 0.1 >= 1)
// 				set_value(&vars->ambient_light->light_ratio, 1);
// 			else
// 				set_value(&vars->ambient_light->light_ratio,to_double(vars->ambient_light->light_ratio) + 0.1);
// 			// printf("Ambient light = %f\n", (to_double(vars->ambient_light->light_ratio)));
// 		}
// 		if (mlx_is_key_down(vars->mlx, MLX_KEY_7))
// 		{
// 			if (to_double(vars->ambient_light->light_ratio) - 0.1 <= 0)
// 				set_value(&vars->ambient_light->light_ratio, 0);
// 			else
// 				set_value(&vars->ambient_light->light_ratio, to_double(vars->ambient_light->light_ratio) - 0.1);
// 			// printf("Ambient light = %f\n", (to_double(vars->ambient_light->light_ratio)));
// 		}

// 		if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
// 		{
// 			mlx_close_window(vars->mlx);
// 			return ;
// 		}
// 		printf("%i\n", keydata.key);
// 		ray_to_screen();
// 	}
// }

// t_3dPoint *cy_rotation(t_shape *cy)
// {
// 	int num_points;
// 	double angle;
// 	int index;
// 	num_points = 12;


// 	t_3dPoint points[num_points];

	


// 	index = 0;

// 	// t_Vars vars = init_vars();


// 	while(index < num_points)
// 	{
// 		angle = 2 * M_PI * index/num_points;

// 		points[index].x = fp_init(to_double(cy->radius) * cos(angle));
// 		points[index].y = fp_init(to_double(cy->radius) * sin(angle));

// 		index++;
// 	}

// 	index = 0;

// 	while(index < num_points)
// 	{
// 		points[index].x = fp_init(to_double(points[index].x) + to_double(cy->coord.x));
// 		points[index].y = fp_init(to_double(points[index].y) + to_double(cy->coord.y));
// 		points[index].z = fp_init(0.0 + to_double(cy->coord.z));

// 		index++;
// 	}

// 	t_rotation rotation = vector_to_rotation_angles(Point3d_to_Vector3d(cy->orientation));


// 	t_matrice3x3 rx = matrice_rotation_x(rotation.phi);
// 	t_matrice3x3 ry = matrice_rotation_y(rotation.theta);
// 	t_matrice3x3 rz = matrice_rotation_z(rotation.psi);

// 	t_matrice3x3 combined_matrix = combine_matrice(rx,ry,rz);

// 	index = 0;

// 	while(index < num_points)
// 	{
// 		t_Vector3d vec = Point3d_to_Vector3d(points[index]);
// 		t_Vector3d rotated_point; 
		

// 		rotated_point = Point3d_to_Vector3d(rotation_point(combined_matrix, Vec3D_to_point3D(vec)));

// 		points[index] = Vec3D_to_point3D(rotated_point);
// 		index++;
// 	}

// 	index = 0;

// 	return (points);
// }







int	main(int argc, char **argv)
{
	t_Vars	*vars = init_vars();
	parse(argc, argv);

	if (!vars->error_message)
	{
		vars->mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
		img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
		vars->img = img; //remove global variable
		// print_objects();
		ray_to_screen();
		mlx_image_to_window(vars->mlx, img, 0, 0);	
		mlx_mouse_hook(vars->mlx, mouse_hook, vars);
		mlx_key_hook(vars->mlx, process_key_actions, vars);
		mlx_loop_hook(vars->mlx, &hook, vars);
		mlx_loop(vars->mlx);
		mlx_terminate(vars->mlx);
	}
	if (!vars->error_message)
		printf("\n\nGOOD\n\n");
	else
		printf("Error\n%s\n", vars->error_message);

	free_vars(vars);
	return (EXIT_SUCCESS);
}

