#include "../../include/miniRT.h"




void print_trigger_UI()
{
	t_vars *vars;
	vars = init_vars();
	mlx_texture_t *img;
	img = mlx_load_png("/Users/slavoie/Desktop/MiniRT/srcs/rayTracing/black_UI.png");
	char str[30];
	mlx_image_to_window(vars->mlx, mlx_texture_to_image(vars->mlx, img), 0, 0);
	mlx_put_string(vars->mlx, "ACTIVE TRIGGER", 0, 0);	
	sprintf(str, "R=%d, H=%d, O=%d, F=%d, L=%d\n", vars->radius_trigger, vars->height_trigger, vars->orientation_trigger, vars->fov_trigger, vars->light_trigger);
	mlx_put_string(vars->mlx, str, 0, 15);
	sprintf(str, "C=%d, X=%d, Y=%d, Z=%d, A=%d\n", vars->camera_trigger, vars->x_trigger, vars->y_trigger, vars->z_trigger, vars->ambient_trigger);
	mlx_put_string(vars->mlx, str, 0, 30);
}