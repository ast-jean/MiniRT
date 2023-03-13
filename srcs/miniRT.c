#include "../include/miniRT.h"
#include <time.h> //remove before sending project


#define WIDTH 1920
#define HEIGHT 1080

static mlx_image_t* img;

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
	// t_Vars vars;
	// mlx_t* mlx;
	t_dlist *objects = malloc(sizeof(t_dlist));

	
	parse(argc, argv, objects);
	// if (!(mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true)))
	// 	return(EXIT_FAILURE);
	// vars.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	// ft_memset(vars.img->pixels, 255, vars.img->width * vars.img->height * sizeof(int));

	// mlx_image_to_window(mlx, vars.img, 0, 0);


	// clock_t end_time = clock();												// illegal maybe using timer from philo
	// double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; //
	// printf("Render time: %f seconds\n", elapsed_time);						//


	// mlx_loop_hook(mlx, &hook, mlx);
	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	free(objects);
	return (EXIT_SUCCESS);
}
