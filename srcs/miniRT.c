/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 15:38:26 by ast-jean          #+#    #+#             */
/*   Updated: 2023/02/27 13:21:19 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/miniRT.h"

#define WIDTH 1920
#define HEIGHT 1080


typedef struct {
    float x;
	float y;
} Point_t;

static mlx_image_t* img;

void    my_mlx_pixel_put(mlx_image_t *img, int x, int y, uint32_t color)
{
	img->pixels[((y * (img->width + 1)) + x) * sizeof(int32_t)] = color;
	*(img->pixels++) = (uint32_t)(color >> 24);
	*(img->pixels++) = (uint32_t)(color >> 16);
	*(img->pixels++) = (uint32_t)(color >> 8);
	*(img->pixels++) = (uint32_t)(color & 0xFF);
}

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


int	draw_line(Point_t p1, Point_t p2, uint32_t color){
	float sx = p1.x;
	float sy = p1.y;
	float a = (p2.y - p1.y) / (p2.x - p1.x); // if zero, dont
	printf("a = %f\n", a);
	//sx and sy start at p1.
	while (sx <= p2.x && p2.y)
	{
		mlx_put_pixel(img, sx, sy, color);
		sx += 0.001f;
		sy = sx * a;
	}
	return 0;
}

int	main(void)
{
	mlx_t* mlx;
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "MiniRT", true)))
		return(EXIT_FAILURE);
	img = mlx_new_image(mlx, 1000, 1000);
	ft_memset(img->pixels, 255, img->width * img->height * sizeof(int));


    Point_t p1 = {0.0f, 0};
    Point_t p2 = {670.0f, 420.0f};
    draw_line(p1, p2, 0x00FF00FF);

	// for(int i = 0; i <= 200; i++)
	// {
	// 	int j = 0;
	// 	for(; j <= 200; j++)			//  R G B T
	// 		mlx_put_pixel(img, j, i,  0x550f9dFF);

	// }
	
		// my_mlx_pixel_put(img, 10, i+1, 0xFF0000);

	mlx_image_to_window(mlx, img, 0, 0);

	mlx_loop_hook(mlx, &hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
