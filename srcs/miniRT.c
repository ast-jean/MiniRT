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
		mlx_get_mouse_pos(vars->mlx, &vars->mouse_x, &vars->mouse_y);
		ray = ray_init_to_screen(vars, vars->mouse_x, vars->mouse_y);
		hit = ray_trace(ray, 999999.9, NULL);
		if (hit.shape)
			vars->selected = hit.shape;
		// free(ray);
		// printf("mouse_x = %d  mouse_y = %d\n", vars->mouse_x, vars->mouse_y);
		// mlx_put_pixel(vars->img, vars->mouse_x, vars->mouse_y, RED);
	}
}

void shape_modifier(mlx_key_data_t keydata, void *param)
{
	t_Vars *vars;

	
	printf("%d\n", keydata.key);
	// (void)keydata;
	vars = param;

	if(mlx_is_key_down(vars->mlx, 61) || mlx_is_key_down(vars->mlx, MLX_KEY_PAGE_UP) \
	|| mlx_is_key_down(vars->mlx, MLX_KEY_PAGE_DOWN) || mlx_is_key_down(vars->mlx, 334) \
	|| mlx_is_key_down(vars->mlx, 333) || mlx_is_key_down(vars->mlx, 45) \
	|| mlx_is_key_down(vars->mlx, MLX_KEY_UP) || mlx_is_key_down(vars->mlx, MLX_KEY_DOWN) \
	|| mlx_is_key_down(vars->mlx, MLX_KEY_LEFT) || mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT) \
	|| mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE) || mlx_is_key_down(vars->mlx, MLX_KEY_A) \
	|| mlx_is_key_down(vars->mlx, MLX_KEY_W) || mlx_is_key_down(vars->mlx, MLX_KEY_D) \
	|| mlx_is_key_down(vars->mlx, MLX_KEY_S) || mlx_is_key_down(vars->mlx, MLX_KEY_Q) || mlx_is_key_down(vars->mlx, MLX_KEY_E)|| mlx_is_key_down(vars->mlx, MLX_KEY_7) || mlx_is_key_down(vars->mlx, MLX_KEY_8))
	{
		if (mlx_is_key_down(vars->mlx, 61) ||  mlx_is_key_down(vars->mlx, 334))
			if (vars->selected)
				vars->selected->radius.value += 50;
		if (mlx_is_key_down(vars->mlx, 45) || mlx_is_key_down(vars->mlx, 333))
			if (vars->selected)
				vars->selected->radius.value -= 50;
		//Changes the FOV
		if (mlx_is_key_down(vars->mlx, MLX_KEY_PAGE_DOWN))
			if ((int)vars->camera->FOV <= (int)180){
				vars->camera->FOV = clamp(vars->camera->FOV + 3, 0 , 180);
				vars->distance_to_screen = (0.5 * WIDTH) / tan(deg2grad(vars->camera->FOV) * 0.5);
				printf("FOV= %d\n", vars->camera->FOV);
			}
		if (mlx_is_key_down(vars->mlx, MLX_KEY_PAGE_UP))
			if (vars->camera->FOV >= 0){
				vars->camera->FOV = clamp(vars->camera->FOV - 3, 0 , 180);
				vars->distance_to_screen = (0.5 * WIDTH) / tan(deg2grad(vars->camera->FOV) * 0.5);
				printf("FOV= %d\n", vars->camera->FOV);
			}
		if (mlx_is_key_down(vars->mlx, MLX_KEY_8))
		{
			if (to_double(vars->ambient_light->light_ratio) + 0.1 >= 1)
				set_value(&vars->ambient_light->light_ratio, 1);
			else
				set_value(&vars->ambient_light->light_ratio,to_double(vars->ambient_light->light_ratio) + 0.1);
				printf("Ambient light = %f\n", (to_double(vars->ambient_light->light_ratio)));
		}
		if (mlx_is_key_down(vars->mlx, MLX_KEY_7))
		{
			if (to_double(vars->ambient_light->light_ratio) - 0.1 <= 0)
				set_value(&vars->ambient_light->light_ratio, 0);
			else
				set_value(&vars->ambient_light->light_ratio, to_double(vars->ambient_light->light_ratio) - 0.01);
			printf("Ambient light = %f\n", (to_double(vars->ambient_light->light_ratio)));
		}
		if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		{
			// set_value(&vars->camera->orientation.z, to_double(vars->camera->orientation.z) - 0.015);
			// vars->camera->orientation.x.value -= 46;
			if (to_double(vars->camera->orientation.z) - 0.15 <= -1.0)
				set_value(&vars->camera->orientation.z, -1);
			else
				set_value(&vars->camera->orientation.z, to_double(vars->camera->orientation.z) - 0.007);

			printf("z = %f\n", to_double(vars->camera->orientation.z));
			// img->instances[0].x -= 5;
		}
		if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		{
			// set_value(&vars->camera->orientation.z, to_double(vars->camera->orientation.z) + 0.015);
			if (to_double(vars->camera->orientation.z) + 0.15 >= 2.0)
				set_value(&vars->camera->orientation.z, 2);
			else
				set_value(&vars->camera->orientation.z, to_double(vars->camera->orientation.z) + 0.007);
			// vars->camera->orientation.x.value += 46;
			printf("z = %f\n", to_double(vars->camera->orientation.z));

			// img->instances[0].x += 5;
		}
				if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
		{
			// set_value(&vars->camera->orientation.z, to_double(vars->camera->orientation.z) - 0.015);
			// vars->camera->orientation.x.value -= 46;
			if (to_double(vars->camera->orientation.y) - 0.15 <= -1.0)
				set_value(&vars->camera->orientation.y, -1);
			else
				set_value(&vars->camera->orientation.y, to_double(vars->camera->orientation.y) - 0.007);

			printf("y = %f\n", to_double(vars->camera->orientation.y));
			// img->instances[0].x -= 5;
		}
		if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
		{
			// set_value(&vars->camera->orientation.y, to_double(vars->camera->orientation.y) + 0.015);
			if (to_double(vars->camera->orientation.y) + 0.15 >= 2.0)
				set_value(&vars->camera->orientation.y, 2);
			else
				set_value(&vars->camera->orientation.y, to_double(vars->camera->orientation.y) + 0.007);
			// vars->camera->orientation.x.value += 46;
			printf("y = %f\n", to_double(vars->camera->orientation.y));

			// img->instances[0].x += 5;
		}

		if (mlx_is_key_down(vars->mlx, MLX_KEY_A))
		{
			// set_value(&vars->camera->orientation.y, to_double(vars->camera->orientation.y) + 0.015);
			set_value(&vars->camera->coord.z, to_double(vars->camera->coord.z) - 1.0);
			// vars->camera->orientation.x.value += 46;
			printf("CZ = %f\n", to_double(vars->camera->coord.z));

			// img->instances[0].x += 5;
		}

		if (mlx_is_key_down(vars->mlx, MLX_KEY_D))
		{
			// set_value(&vars->camera->orientation.y, to_double(vars->camera->orientation.y) + 0.015);
			set_value(&vars->camera->coord.z, to_double(vars->camera->coord.z) + 1.0);
			// vars->camera->orientation.x.value += 46;
			printf("CZ = %f\n", to_double(vars->camera->coord.z));

			// img->instances[0].x += 5;
		}
		if (mlx_is_key_down(vars->mlx, MLX_KEY_S))
		{
			// set_value(&vars->camera->orientation.y, to_double(vars->camera->orientation.y) + 0.015);
			set_value(&vars->camera->coord.x, to_double(vars->camera->coord.x) - 10.0);
			// vars->camera->orientation.x.value += 46;
			printf("CX = %f\n", to_double(vars->camera->coord.x));

			// img->instances[0].x += 5;
		}
		if (mlx_is_key_down(vars->mlx, MLX_KEY_W))
		{
			// set_value(&vars->camera->orientation.y, to_double(vars->camera->orientation.y) + 0.015);
			set_value(&vars->camera->coord.x, to_double(vars->camera->coord.x) + 10.0);
			// vars->camera->orientation.x.value += 46;
			printf("CX = %f\n", to_double(vars->camera->coord.x));

			// img->instances[0].x += 5;
		}
		if (mlx_is_key_down(vars->mlx, MLX_KEY_Q))
		{
			// set_value(&vars->camera->orientation.y, to_double(vars->camera->orientation.y) + 0.015);
			set_value(&vars->camera->coord.y, to_double(vars->camera->coord.y) - 1.0);
			// vars->camera->orientation.x.value += 46;
			printf("CY = %f\n", to_double(vars->camera->coord.y));

			// img->instances[0].x += 5;
		}
		if (mlx_is_key_down(vars->mlx, MLX_KEY_E))
		{
			// set_value(&vars->camera->orientation.y, to_double(vars->camera->orientation.y) + 0.015);
			set_value(&vars->camera->coord.y, to_double(vars->camera->coord.y) + 1.0);
			// vars->camera->orientation.y.value += 46;
			printf("Cy = %f\n", to_double(vars->camera->coord.y));

			// img->instances[0].x += 5;
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
		vars->img = img; //remove global variable
		// print_objects();
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
