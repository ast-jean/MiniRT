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

	mlx_image_to_window(vars->mlx, img, 0, 0);

	printf("FOV = %d\n",vars->camera->FOV);
	
	ray_to_screen();

	clock_t end_time = clock();												// illegal maybe using timer from philo
	double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; //
	printf("Render time: %f seconds\n", elapsed_time);						//
	mlx_loop_hook(vars->mlx, &hook, vars->mlx);
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