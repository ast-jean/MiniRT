/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:58:16 by ast-jean          #+#    #+#             */
/*   Updated: 2023/03/01 11:49:00 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef _MINI_RT_H_
# define _MINI_RT_H_

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <limits.h>
# include  <fcntl.h>
# include  <math.h>
# include "MLX42/include/MLX42/MLX42.h"

# include "libft/libft.h"



#define BLACK	0x00000000
#define WHITE	0xFFFFFFFF
#define GRAY	0x00000088
#define RED		0xFF0000FF
#define GREEN	0x00FF00FF
#define BLUE	0x0000FFFF

typedef struct s_vars
{
	void	*mlx;
	void	*mlx_win;
}			t_vars;

typedef struct s_point{
    float x;
	float y;
} t_Point;


#endif