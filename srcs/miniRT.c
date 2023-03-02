#include "../include/miniRT.h"
#include <time.h>

#define WIDTH 1920
#define HEIGHT 1080

void hook(void *param)
{
	t_Vars *vars = param;

	if (mlx_is_key_down(vars->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(vars->mlx);
	if (mlx_is_key_down(vars->mlx, MLX_KEY_UP))
		vars->img->instances[0].y -= 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_DOWN))
		vars->img->instances[0].y += 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_LEFT))
		vars->img->instances[0].x -= 5;
	if (mlx_is_key_down(vars->mlx, MLX_KEY_RIGHT))
		vars->img->instances[0].x += 5;
}

void makeBlack(mlx_image_t *img)
{
	uint32_t y = 0;
	uint32_t x;
	while(y < img->height)
	{
		x = 0;
		while (x < img->width){
			mlx_put_pixel(img, x++, y, BLACK);
		}
		y++;
	}	
}

int	main(void)
{
	t_Vars vars;


	if (!(vars.mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true)))
		return(EXIT_FAILURE);
	
	// clock_t start_time = clock(); //illegal: used to see optimisation
	
	
	vars.img = mlx_new_image(vars.mlx, 1920, 1080); //(TODO: img to be put in t_Vars)
	// ft_memset(img->pixels, 255, img->width * img->height * sizeof(int)); //Setting white pixels in the windows img 
	// makeBlack(img); //useless cause pixel will get replaced
	
	
	// vars.env3D = malloc(INT_MAX * INT_MAX * INT_MAX * sizeof(t_3dPoint)); //allocation of the 3D environnement (TODO: env3D to be put in t_Vars) Range xyz = -2147483647 , 2147483647
	
	
	// clock_t end_time = clock();												// illegal maybe using timer from philo
	// double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC; //
	// printf("Render time: %f seconds\n", elapsed_time);						//



	mlx_image_to_window(vars.mlx, vars.img, 0, 0);
	mlx_loop_hook(vars.mlx, &hook, vars.mlx);
	mlx_loop(vars.mlx);
	mlx_terminate(vars.mlx);
	return (EXIT_SUCCESS);
}
