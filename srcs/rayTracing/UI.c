/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UI.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:01:31 by ast-jean          #+#    #+#             */
/*   Updated: 2023/06/09 12:06:44 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	ui_enabled(t_vars *vars, char *str, mlx_image_t *img)
{
	printf("UI \033[32mEnable\033[0m\n");
	img->enabled = true;
	img = mlx_img_put_string(img, "ACTIVE TRIGGER", 0, 0);
	sprintf(str, "R=%d, H=%d, O=%d, F=%d, L=%d\n", \
	vars->radius_trigger, vars->height_trigger, \
	vars->orientation_trigger, vars->fov_trigger, vars->light_trigger);
	img = mlx_img_put_string(img, str, 0, 15);
	sprintf(str, "C=%d, X=%d, Y=%d, Z=%d, A=%d\n", \
	vars->camera_trigger, vars->x_trigger, vars->y_trigger, \
	vars->z_trigger, vars->ambient_trigger);
	img = mlx_img_put_string(img, str, 0, 30);
}

void	print_trigger_ui(void)
{
	static t_vars			*vars;
	static mlx_texture_t	*tx;
	static mlx_image_t		*img;
	static int				init;
	char					str[30];

	if (!init++)
	{
		vars = init_vars();
		tx = mlx_load_png("srcs/rayTracing/black_UI.png");
		img = mlx_texture_to_image(vars->mlx, tx);
	}
	if (img && mlx_is_key_down(vars->mlx, MLX_KEY_I))
	{
		if (vars->interface_trigger)
			ui_enabled(vars, str, img);
		else
		{
			printf("UI \033[31mDisable\033[0m\n");
			img->enabled = false;
		}
		mlx_image_to_window(vars->mlx, img, 0, 0);
	}
}
