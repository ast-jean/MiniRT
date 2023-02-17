/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:58:16 by ast-jean          #+#    #+#             */
/*   Updated: 2023/02/17 16:59:28 by ast-jean         ###   ########.fr       */
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
# include "mlx.h"
# include "libft/libft.h"
# include  <math.h>



typedef struct s_vars
{
	void	*mlx;
	void	*mlx_win;
}			t_vars;


#endif