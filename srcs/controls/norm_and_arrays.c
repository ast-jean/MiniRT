/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_and_arrays.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:33:42 by slavoie           #+#    #+#             */
/*   Updated: 2023/06/12 15:37:21 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void	assign_keys_according_to_norm_a(int *useful_keys)
{
	useful_keys[0] = 61;
	useful_keys[1] = 45;
	useful_keys[2] = 334;
	useful_keys[3] = 333;
	useful_keys[4] = MLX_KEY_PAGE_UP;
	useful_keys[5] = MLX_KEY_PAGE_DOWN;
	useful_keys[6] = MLX_KEY_UP;
	useful_keys[7] = MLX_KEY_DOWN;
	useful_keys[8] = MLX_KEY_LEFT;
	useful_keys[9] = MLX_KEY_RIGHT;
	useful_keys[10] = MLX_KEY_ESCAPE;
	useful_keys[11] = MLX_KEY_1;
	useful_keys[12] = MLX_KEY_2;
	useful_keys[13] = MLX_KEY_3;
	useful_keys[14] = MLX_KEY_4;
	useful_keys[15] = MLX_KEY_5;
	useful_keys[16] = MLX_KEY_6;
	useful_keys[17] = MLX_KEY_7;
	useful_keys[18] = MLX_KEY_8;
	useful_keys[19] = MLX_KEY_O;
}

void	assign_keys_according_to_norm_b(int *useful_keys)
{
	useful_keys[20] = MLX_KEY_X;
	useful_keys[21] = MLX_KEY_Y;
	useful_keys[22] = MLX_KEY_Z;
	useful_keys[23] = MLX_KEY_C;
	useful_keys[24] = MLX_KEY_R;
	useful_keys[25] = MLX_KEY_H;
	useful_keys[26] = MLX_KEY_F;
	useful_keys[27] = MLX_KEY_L;
	useful_keys[28] = MLX_KEY_I;
	useful_keys[29] = MLX_KEY_A;
	useful_keys[30] = MLX_KEY_P;
}
