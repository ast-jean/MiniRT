/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MiniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:38:26 by ast-jean          #+#    #+#             */
/*   Updated: 2023/02/17 17:00:24 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

int	main(int argc, char **argv)
{
	(void)argv;
	(void)argc;

	t_vars	vars;

	vars.mlx = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx, 1920, 1080, "MiniRT");
	// mlx_hook(vars.mlx_win, 2, 0, &event_manager, &vars);
	// mlx_hook(vars.mlx_win, 17, 0, &exit_game, &vars);
	// mlx_loop_hook(vars.mlx, &animation, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
