#include "../include/miniRT.h"
#include <time.h> //remove before sending project
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
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
		img->instances[0].y -= 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
		img->instances[0].y += 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		img->instances[0].x -= 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		img->instances[0].x += 5;

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
		vars->img = NULL;
		vars->objs = malloc(sizeof(t_dlist));
		vars->objs->first = NULL;
		vars->objs->last = NULL;
		vars->selected = NULL;
		vars->error_message = 0;
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

	vars = param;

	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(vars->mlx);
	if (keydata.key == MLX_KEY_UP)
		img->instances[0].y -= 5;
	if (keydata.key == MLX_KEY_DOWN)
		img->instances[0].y += 5;
	if (keydata.key == MLX_KEY_LEFT)
		img->instances[0].x -= 5;
	if (keydata.key == MLX_KEY_RIGHT)
		img->instances[0].x += 5;
	else if (mlx_is_key_down(vars->mlx, 61) || mlx_is_key_down(vars->mlx, 334))
		if (vars->selected)
			{
				vars->selected->diameter.value += 50;
				ray_to_screen();
			}
	if (mlx_is_key_down(vars->mlx, 45) || mlx_is_key_down(vars->mlx, 333))
		if (vars->selected)
		{
			vars->selected->diameter.value -= 50;
			ray_to_screen();
		}
	
	// usleep(500);
	// printf("key= %d\n", keydata.key);
	//Changes the FOV
	if (mlx_is_key_down(vars->mlx, 70))
	{
		if ((int)vars->camera->FOV <= (int)180)
		{
			vars->camera->FOV += 5;
			vars->distance_to_screen = (0.5 * WIDTH) / tan((vars->camera->FOV * (M_PI / 180.0)) * 0.5);
			ray_to_screen();
		}
	}
	if (mlx_is_key_down(vars->mlx, 71))
	{

		if (vars->camera->FOV >= 0)
		{
			vars->camera->FOV -= 6;
			vars->distance_to_screen = (0.5 * WIDTH) / tan((vars->camera->FOV * (M_PI / 180.0)) * 0.5);
			ray_to_screen();
		}
	}
}

int	main(int argc, char **argv)
{
	t_Vars	*vars = init_vars();
	parse(argc, argv);

	if (!vars->error_message)
	{
	clock_t start_time = clock();
	// // mlx_t		*mlx;
	
	vars->mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	// // mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true);
	// // vars->mlx = mlx;
	// // if (!(vars->mlx))
	// // 	return(EXIT_FAILURE);
	// // vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	vars->img = img;
	ft_memset(img->pixels, 255, img->width * img->height * sizeof(int));
	// // ft_memset(vars->img->pixels, 255, vars->img->width * vars->img->height * sizeof(int));
	
	ray_to_screen();
	mlx_image_to_window(vars->mlx, img, 0, 0);	

	clock_t end_time = clock();												// illegal maybe using timer from philo
	double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; //
	printf("Render time: %f seconds\n", elapsed_time);
	mlx_mouse_hook(vars->mlx, mouse_hook, vars);
	mlx_key_hook(vars->mlx, shape_modifier, vars);					//
	// mlx_loop_hook(vars->mlx, &hook, vars);
	mlx_loop(vars->mlx);
	mlx_terminate(vars->mlx);
	}

	if (!vars->error_message)
		printf("\n\nGOOD\n\n");
	if (errno)
		printf("\n\nNO GOOD: %d\n\n", errno);

	free_vars(vars);
	return (EXIT_SUCCESS);
}


/*static mlx_image_t* img;

void hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		img->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		img->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		img->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		img->instances[0].x += 5;
}

int	main(int argc, char **argv)
{
	t_dlist *objects = malloc(sizeof(t_dlist));
	parse(argc, argv, objects);

	t_Vars vars;
	mlx_t* mlx;
	clock_t start_time = clock();
	
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true)))
		return(EXIT_FAILURE);
	vars.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	ft_memset(vars.img->pixels, 255, vars.img->width * vars.img->height * sizeof(int));

	mlx_image_to_window(mlx, vars.img, 0, 0);


	clock_t end_time = clock();												// illegal maybe using timer from philo
	double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; //
	printf("Render time: %f seconds\n", elapsed_time);						//


	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	dlist_free_content(objects);
	free(objects);
	return (EXIT_SUCCESS);
}
*/