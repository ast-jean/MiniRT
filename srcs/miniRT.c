#include "../include/miniRT.h"
#include <time.h> //remove


#define WIDTH 1920
#define HEIGHT 1080

static mlx_image_t* img;

// void    my_mlx_pixel_put(mlx_image_t *img, int x, int y, uint32_t color)
// {
// 	img->pixels[((y * (img->width + 1)) + x) * sizeof(int32_t)] = color;
// 	// *(img->pixels++) = (uint32_t)(color >> 24);
// 	// *(img->pixels++) = (uint32_t)(color >> 16);
// 	// *(img->pixels++) = (uint32_t)(color >> 8);
// 	// *(img->pixels++) = (uint32_t)(color & 0xFF);
// }

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



int	main(void)
{
	t_Vars vars;
	mlx_t* mlx;

	clock_t start_time = clock(); //illegal: used to see optimisation
	//init
	vars.env3D = malloc(INT_MAX * INT_MAX * INT_MAX * sizeof(t_3dPoint)); //allocation of the 3D environnement (TODO: env3D to be put in t_Vars) Range xyz = -2147483647 , 2147483647



	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true)))
		return(EXIT_FAILURE);
	vars.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	// ft_memset(vars.img->pixels, 255, vars.img->width * vars.img->height * sizeof(int));

	mlx_image_to_window(mlx, vars.img, 0, 0);


	clock_t end_time = clock();												// illegal maybe using timer from philo
	double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; //
	printf("Render time: %f seconds\n", elapsed_time);						//


	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}