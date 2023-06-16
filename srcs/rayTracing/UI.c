/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UI.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 12:01:31 by ast-jean          #+#    #+#             */
/*   Updated: 2023/06/16 18:05:33 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	ui_enabled(t_vars *vars, char *str, mlx_image_t *img)
{
	char	*obj;

	if (vars->selected)
		obj = vars->selected->id;
	else
		obj = "null";
	img->enabled = true;
	sprintf(str, "ACTIVE TRIGGERS  Obj=%s\n", obj);
	img = mlx_img_put_string(img, str, 0, 0);
	sprintf(str, "R=%d, H=%d, O=%d, F=%d, L=%d\n", \
	vars->radius_trigger, vars->height_trigger, \
	vars->orientation_trigger, vars->fov_trigger, vars->light_trigger);
	img = mlx_img_put_string(img, str, 0, 25);
	sprintf(str, "C=%d, X=%d, Y=%d, Z=%d, A=%d\n", \
	vars->camera_trigger, vars->x_trigger, vars->y_trigger, \
	vars->z_trigger, vars->ambient_trigger);
	img = mlx_img_put_string(img, str, 0, 50);
}

void	print_trigger_ui(void)
{
	mlx_texture_t	*tx;
	mlx_image_t		*img;
	char			str[30];

	tx = mlx_load_png("srcs/rayTracing/black_UI.png");
	img = mlx_texture_to_image(init_vars()->mlx, tx);
	if (init_vars()->interface_trigger)
	{
		img = mlx_texture_to_image(init_vars()->mlx, tx);
		ui_enabled(init_vars(), str, img);
		mlx_image_to_window(init_vars()->mlx, img, 0, 0);
	}
	mlx_delete_texture(tx);
}
