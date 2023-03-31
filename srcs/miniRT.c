#include "../include/miniRT.h"
#include <errno.h>

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
	t_Ray *ray;
	t_Ray_hit hit;

	vars = param;
	(void)action;
	(void)mods;

	if (mlx_is_mouse_down(vars->mlx, button))
	{
		mlx_get_mouse_pos(vars->mlx, &vars->mouse_x, &vars->mouse_y);
		ray = ray_init_to_screen(vars, vars->mouse_x, vars->mouse_y);
		hit = ray_trace(ray);
		if (hit.shape)
			vars->selected = hit.shape;
		free(ray);
		// printf("mouse_x = %d  mouse_y = %d\n", vars->mouse_x, vars->mouse_y);
		// mlx_put_pixel(vars->img, vars->mouse_x, vars->mouse_y, RED);
	}
}

void shape_modifier(mlx_key_data_t keydata, void *param)
{
	t_Vars *vars;


	(void)keydata;
	vars = param;
	
	if(mlx_is_key_down(vars->mlx, 61) || mlx_is_key_down(vars->mlx, 70) || mlx_is_key_down(vars->mlx, 71) || \
	mlx_is_key_down(vars->mlx, 334)||mlx_is_key_down(vars->mlx, 333)||mlx_is_key_down(vars->mlx, 45)||
	mlx_is_key_down(vars->mlx, MLX_KEY_UP) || mlx_is_key_down(vars->mlx, MLX_KEY_DOWN) ||\
	mlx_is_key_down(vars->mlx,  MLX_KEY_LEFT) || mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT) ||
	mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
	{
		if (mlx_is_key_down(vars->mlx, 61) || mlx_is_key_down(vars->mlx, 334))
			if (vars->selected)
				vars->selected->diameter.value += 50;
		if (mlx_is_key_down(vars->mlx, 45) || mlx_is_key_down(vars->mlx, 333))
			if (vars->selected)
				vars->selected->diameter.value -= 50;
		
		//Changes the FOV
		if (mlx_is_key_down(vars->mlx, MLX_KEY_G))
			if ((int)vars->camera->FOV <= (int)180){
				vars->camera->FOV += 5;
				vars->distance_to_screen = (0.5 * WIDTH) / tan((vars->camera->FOV * (M_PI / 180.0)) * 0.5);
			}
		if (mlx_is_key_down(vars->mlx, MLX_KEY_F))
			if (vars->camera->FOV >= 0){
				vars->camera->FOV -= 6;
				vars->distance_to_screen = (0.5 * WIDTH) / tan((vars->camera->FOV * (M_PI / 180.0)) * 0.5);
			}
		if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
		{
			if (to_double(vars->ambient_light->light_ratio) + 0.1 >= 1)
				set_value(&vars->ambient_light->light_ratio, 1);
			else
				set_value(&vars->ambient_light->light_ratio,to_double(vars->ambient_light->light_ratio) + 0.1);
			printf("Ambient light = %f\n", to_double(vars->ambient_light->light_ratio));
		}
		if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
		{
			if (to_double(vars->ambient_light->light_ratio) - 0.1 <= 0)
				set_value(&vars->ambient_light->light_ratio, 0);
			else
				set_value(&vars->ambient_light->light_ratio, to_double(vars->ambient_light->light_ratio) - 0.1);
			printf("Ambient light = %f\n", to_double(vars->ambient_light->light_ratio));
		}
		// if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		// {
		// 	set_value(&vars->camera->orientation.z,to_double(vars->camera->orientation.x) - 0.01);
		// 	// img->instances[0].x -= 5;
		// }
		// if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		// {
		// 	set_value(&vars->camera->orientation.z,to_double(vars->camera->orientation.x) + 0.01);
		// 	// img->instances[0].x += 5;
		// }
		if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
			mlx_close_window(vars->mlx);
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
		// mlx_put_pixel(vars->img, 1000000, 0, RED);
		ray_to_screen();
		mlx_image_to_window(vars->mlx, img, 0, 0);	
		mlx_mouse_hook(vars->mlx, mouse_hook, vars);
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
