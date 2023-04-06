#include "../include/miniRT.h"
#include <errno.h>

void hook(void* param)
{
	t_Vars* vars = param;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
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
		vars->mlx = NULL;
		vars->img = malloc(sizeof(mlx_image_t));
		vars->objs = malloc(sizeof(t_dlist));
		vars->objs->first = NULL;
		vars->objs->last = NULL;
		vars->error_message = NULL;
		vars->selected = NULL;
		vars->distance_to_screen = 0;
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

	if (mlx_is_mouse_down(vars->mlx, button))
	{
		mlx_get_mouse_pos(vars->mlx, &vars->mouse_pos.x, &vars->mouse_pos.y);
		ray = ray_init_to_screen(vars, vars->mouse_pos.x, vars->mouse_pos.y);
		hit = ray_trace(ray, INFINITY);
		if (hit.shape)
			vars->selected = hit.shape;
		// free(ray);
		// printf("mouse_x = %d  mouse_y = %d\n", vars->mouse_x, vars->mouse_y);
		// mlx_put_pixel(vars->img, vars->mouse_x, vars->mouse_y, RED);
	}
}
t_Vector3d getMovementVector(const t_Vector3d camera, float movementSpeed) {
    t_Vector3d movementVector;
    float pitch_rad = camera.x * M_PI / 180.0f;
    float yaw_rad = camera.y * M_PI / 180.0f;
	printf("camera.x = %f | .y = %f| .z = %f\n", camera.x, camera.y, camera.z);
    movementVector.x = cosf(yaw_rad) * cosf(pitch_rad) * movementSpeed;
    // movementVector.y = sin(pitch_rad) * movementSpeed;
    // movementVector.z = sin(yaw_rad) * cos(pitch_rad) * movementSpeed;
    return movementVector;
}
t_Vector3d getStrafeVector(const t_Vector3d camera, float strafeSpeed) {
    t_Vector3d strafeVector;
    float yaw_rad = camera.y * M_PI / 180.0f;

    strafeVector.x = -sinf(yaw_rad) * strafeSpeed;
    strafeVector.y = 0;
    strafeVector.z = cosf(yaw_rad) * strafeSpeed;

    return strafeVector;
}



void camera_move(mlx_key_data_t keydata, void *param)
{
	t_Vars *vars;

	(void)keydata;
	vars = param;

	// t_Vector3d cc = Point3d_to_Vector3d(vars->camera->coord);
	// t_Vector3d co = Point3d_to_Vector3d(vars->camera->orientation);

	if(mlx_is_key_down(vars->mlx, MLX_KEY_UP) || mlx_is_key_down(vars->mlx, MLX_KEY_DOWN) \
	|| mlx_is_key_down(vars->mlx, MLX_KEY_LEFT) || mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT) \
	|| mlx_is_key_down(vars->mlx, MLX_KEY_W) || mlx_is_key_down(vars->mlx, MLX_KEY_A) \
	|| mlx_is_key_down(vars->mlx, MLX_KEY_S) || mlx_is_key_down(vars->mlx, MLX_KEY_D))
	{
		// if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
		// {
		// 	// if (to_double(vars->camera->orientation.y)< 1)
		// 		set_value(&vars->camera->orien.y, to_double(vars->camera->orien.y) + 0.01);
		// }	
		// if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
		// {
		// 	set_value(&vars->camera->orien.y, to_double(vars->camera->orien.y) - 0.01);

		// }
		// if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		// {
		// 	set_value(&vars->camera->orien.x, to_double(vars->camera->orien.x) + 0.01);

		// }
		// if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		// {
		// 	set_value(&vars->camera->orien.x, to_double(vars->camera->orien.x) - 0.01);
		// }
		// if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
		// {
		// 	t_Vector3d movementVector = getMovementVector(Point3d_to_Vector3d(vars->camera->coord), 100);
		// 	set_value(&vars->camera->coord.x, to_double(vars->camera->coord.x) + movementVector.x);
		// 	set_value(&vars->camera->coord.y, to_double(vars->camera->coord.y) + movementVector.y);
		// 	set_value(&vars->camera->coord.z, to_double(vars->camera->coord.z) + movementVector.z);
		// }
		// if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
		// {
		// 	t_Vector3d movementVector = getMovementVector(Point3d_to_Vector3d(vars->camera->coord), -100);
		// 	set_value(&vars->camera->coord.x, to_double(vars->camera->coord.x) + movementVector.x);
		// 	set_value(&vars->camera->coord.y, to_double(vars->camera->coord.y) + movementVector.y);
		// 	set_value(&vars->camera->coord.z, to_double(vars->camera->coord.z) + movementVector.z);
		// }
		// if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		// {
		// 	t_Vector3d movementVector = getStrafeVector(Point3d_to_Vector3d(vars->camera->coord), -1);
		// 	set_value(&vars->camera->coord.x, to_double(vars->camera->coord.x) + movementVector.x);
		// 	set_value(&vars->camera->coord.y, to_double(vars->camera->coord.y) + movementVector.y);
		// 	set_value(&vars->camera->coord.z, to_double(vars->camera->coord.z) + movementVector.z);
		// }
		// if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
		// {
		// 	t_Vector3d movementVector = getStrafeVector(Point3d_to_Vector3d(vars->camera->coord), 1);
		// 	set_value(&vars->camera->coord.x, to_double(vars->camera->coord.x) + movementVector.x);
		// 	set_value(&vars->camera->coord.y, to_double(vars->camera->coord.y) + movementVector.y);
		// 	set_value(&vars->camera->coord.z, to_double(vars->camera->coord.z) + movementVector.z);
		// }
		if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		{
			mlx_close_window(vars->mlx);
			return ;
		}
		ray_to_screen();
	}
}
void shape_modifier(mlx_key_data_t keydata, void *param)
{
	t_Vars *vars;
	camera_move(keydata, param);
	vars = param;
	if(mlx_is_key_down(vars->mlx, 61) || mlx_is_key_down(vars->mlx, MLX_KEY_PAGE_UP) \
	|| mlx_is_key_down(vars->mlx, MLX_KEY_PAGE_DOWN) || mlx_is_key_down(vars->mlx, 334) \
	|| mlx_is_key_down(vars->mlx, 333) || mlx_is_key_down(vars->mlx, 45) \
	|| mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE) || mlx_is_key_down(vars->mlx, 268)\
	|| mlx_is_key_down(vars->mlx, 269))
	{
		if (mlx_is_key_down(vars->mlx, 61) ||  mlx_is_key_down(vars->mlx, 334))
			if (vars->selected)
				vars->selected->radius += 1;
		if (mlx_is_key_down(vars->mlx, 45) || mlx_is_key_down(vars->mlx, 333))
			if (vars->selected)
				vars->selected->radius -= 1;
		//Changes the FOV
		if (mlx_is_key_down(vars->mlx, MLX_KEY_PAGE_DOWN))
			if ((int)vars->camera->FOV <= (int)180){
				vars->camera->FOV = clamp(vars->camera->FOV + 6, 0 , 180);
				vars->distance_to_screen = (0.5f * WIDTH) / tan(deg2grad(vars->camera->FOV) * 0.5f);
				printf("FOV= %d\n", vars->camera->FOV);
			}
		if (mlx_is_key_down(vars->mlx, MLX_KEY_PAGE_UP))
			if (vars->camera->FOV >= 0)
			{
				vars->camera->FOV = clamp(vars->camera->FOV - 6, 0 , 180);
				vars->distance_to_screen = (0.5f * WIDTH) / tan(deg2grad(vars->camera->FOV) * 0.5f);
				printf("FOV= %d\n", vars->camera->FOV);
			}
		if (mlx_is_key_down(vars->mlx, 268))
		{
			vars->ambient_light->light_ratio = clamp(vars->ambient_light->light_ratio + 10, 0, 100);

			printf("Ambient light = %f\n", (float) vars->ambient_light->light_ratio);
		}
		if (mlx_is_key_down(vars->mlx, 269))
		{
			vars->ambient_light->light_ratio = clamp(vars->ambient_light->light_ratio - 10, 0, 100);

			printf("Ambient light = %f\n", (float) vars->ambient_light->light_ratio);
		}
		if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		{
			mlx_close_window(vars->mlx);
			return ;
		}
		ray_to_screen();
	}

}

int	main(int argc, char **argv)
{
	t_Vars	*vars = init_vars();
	parse(argc, argv);
	if (!vars->error_message)
	{
		vars->mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
		img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
		vars->img = img;

		// print_objects();


		ray_to_screen();
		mlx_image_to_window(vars->mlx, img, 0, 0);	
		mlx_mouse_hook(vars->mlx, mouse_hook, vars);
		mlx_key_hook(vars->mlx, camera_move, vars);
		mlx_key_hook(vars->mlx, shape_modifier, vars);
		mlx_loop_hook(vars->mlx, &hook, vars);
		mlx_loop(vars->mlx);
		mlx_terminate(vars->mlx);
	}
	if (!vars->error_message)
		printf("\n\nGOOD\n\n");
	else
		printf("%s\n", vars->error_message);

	free_vars(vars);
	return (EXIT_SUCCESS);
}
