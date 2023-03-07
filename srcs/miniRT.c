#include "../include/miniRT.h"

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



int	main(int argc, char **argv)
{
	t_Vars vars;
	mlx_t* mlx;
	
	parse(argc, argv);
	// if (!(mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true)))
	// 	return(EXIT_FAILURE);
	// img = mlx_new_image(mlx, 1000, 1000);
	// ft_memset(img->pixels, 255, img->width * img->height * sizeof(int));

	// mlx_image_to_window(mlx, img, 0, 0);

	// mlx_loop_hook(mlx, &hook, mlx);
	// mlx_loop(mlx);
	// mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

//trying forks