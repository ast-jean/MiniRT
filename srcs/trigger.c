/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trigger.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:35:27 by slavoie           #+#    #+#             */
/*   Updated: 2023/05/18 20:47:28 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

void	check_trigger_xyz(t_Vars *vars)
{
	if (mlx_is_key_down(vars->mlx, 61) || mlx_is_key_down(vars->mlx, 334))
	{
		if (vars->selected && vars->radius_trigger)
			vars->selected->radius.value += 50;
		if (vars->selected && vars->height_trigger)
			vars->selected->height.value += 50;
		if (!vars->orientation_trigger)
		{
			if (vars->selected && vars->x_trigger)
				set_value(&vars->selected->coord.x, \
				to_double(vars->selected->coord.x) + 1);
			if (vars->selected && vars->y_trigger)
				set_value(&vars->selected->coord.y, \
				to_double(vars->selected->coord.y) + 1);
			if (vars->selected && vars->z_trigger)
				set_value(&vars->selected->coord.z, \
				to_double(vars->selected->coord.z) + 1);
		}
	}
	if (mlx_is_key_down(vars->mlx, 45) || mlx_is_key_down(vars->mlx, 333))
	{
		if (vars->selected && vars->radius_trigger)
			vars->selected->radius.value -= 50;
		if (vars->selected && vars->height_trigger)
			vars->selected->height.value -= 50;
		if (!vars->orientation_trigger)
		{
			if (vars->selected && vars->x_trigger)
				set_value(&vars->selected->coord.x, \
				to_double(vars->selected->coord.x) - 1);
			if (vars->selected && vars->y_trigger)
				set_value(&vars->selected->coord.y, \
				to_double(vars->selected->coord.y) - 1);
			if (vars->selected && vars->z_trigger)
				set_value(&vars->selected->coord.z, \
				to_double(vars->selected->coord.z) - 1);
		}
	}
}

void rotate_vector(t_Vector3d *vec, double angle, char axis) {
    // Convert the angle to radians
    angle = angle * (M_PI / 180.0);

    // Temp variables to hold the original components of the vector
    double orig_x = vec->x;
    double orig_y = vec->y;
    double orig_z = vec->z;

    // Depending on the axis, rotate the vector accordingly
    switch(axis) {
        case 'x':
        case 'X':
            vec->y = orig_y * cos(angle) - orig_z * sin(angle);
            vec->z = orig_y * sin(angle) + orig_z * cos(angle);
            break;
        case 'y':
        case 'Y':
            vec->z = orig_z * cos(angle) - orig_x * sin(angle);
            vec->x = orig_z * sin(angle) + orig_x * cos(angle);
            break;
        case 'z':
        case 'Z':
            vec->x = orig_x * cos(angle) - orig_y * sin(angle);
            vec->y = orig_x * sin(angle) + orig_y * cos(angle);
            break;
        default:
            printf("Invalid rotation axis. Use 'x', 'y', or 'z'.\n");
    }
}

void	check_trigger_orientation(t_Vars *vars)
{
	t_Vector3d	orientation;

	orientation = point3d_to_vector3d(vars->selected->orientation);

	if (mlx_is_key_down(vars->mlx, 61) || mlx_is_key_down(vars->mlx, 334))
	{
		if (vars->orientation_trigger && vars->selected)
		{
			if (vars->x_trigger)
			{
				rotate_vector(&orientation, 10, 'x');
				vars->selected->orientation = Vec3D_to_point3D(orientation);
				// set_value(&vars->selected->orientation.x, \
				// to_double(vars->selected->orientation.x) + 0.2);
				// reset_position(&vars->selected->orientation.x, 'x');
				// vars->selected->orientation = Vec3D_to_point3D(vector3d_norm(point3d_to_vector3d(vars->selected->orientation)));
			}
			if (vars->y_trigger)
			{
				rotate_vector(&orientation, 10,  'y');
				vars->selected->orientation = Vec3D_to_point3D(orientation);
				// set_value(&vars->selected->orientation.y, \
				// to_double(vars->selected->orientation.y) + 0.2);
				// reset_position(&vars->selected->orientation.y, 'y');
				// vars->selected->orientation = Vec3D_to_point3D(vector3d_norm(point3d_to_vector3d(vars->selected->orientation)));

			}
			if (vars->z_trigger)
			{
				rotate_vector(&orientation, 10,  'z');
				vars->selected->orientation = Vec3D_to_point3D(orientation);
				// set_value(&vars->selected->orientation.z, \
				// to_double(vars->selected->orientation.z) + 0.2);
				// reset_position(&vars->selected->orientation.z, 'z');
				// vars->selected->orientation = Vec3D_to_point3D(vector3d_norm(point3d_to_vector3d(vars->selected->orientation)));

			}
		}
	}
	if (mlx_is_key_down(vars->mlx, 45) || mlx_is_key_down(vars->mlx, 333))
	{
		if (vars->orientation_trigger && vars->selected)
		{
			if (vars->x_trigger)
			{
				rotate_vector(&orientation, -10,  'x');
				vars->selected->orientation = Vec3D_to_point3D(orientation);
				// set_value(&vars->selected->orientation.x, \
				// to_double(vars->selected->orientation.x) - 0.2);
				// reset_position(&vars->selected->orientation.x, 'x');
				// vars->selected->orientation = Vec3D_to_point3D(vector3d_norm(point3d_to_vector3d(vars->selected->orientation)));

			}
			if (vars->y_trigger)
			{
				rotate_vector(&orientation, -10,  'y');
				vars->selected->orientation = Vec3D_to_point3D(orientation);
				// set_value(&vars->selected->orientation.y, \
				// to_double(vars->selected->orientation.y) - 0.2);
				// reset_position(&vars->selected->orientation.y, 'y');
				// vars->selected->orientation = Vec3D_to_point3D(vector3d_norm(point3d_to_vector3d(vars->selected->orientation)));

			}
			if (vars->z_trigger)
			{
				rotate_vector(&orientation, -10,  'z');
				vars->selected->orientation = Vec3D_to_point3D(orientation);
				// set_value(&vars->selected->orientation.z, \
				// to_double(vars->selected->orientation.z) - 0.2);
				// reset_position(&vars->selected->orientation.z, 'z');
				// vars->selected->orientation = Vec3D_to_point3D(vector3d_norm(point3d_to_vector3d(vars->selected->orientation)));

			}
		}
	}
	reset_position(&vars->selected->orientation.x, 'x');

	printf("x = %f, y = %f, z = %f\n", to_double(vars->selected->orientation.x), to_double(vars->selected->orientation.y), to_double(vars->selected->orientation.z) );
}