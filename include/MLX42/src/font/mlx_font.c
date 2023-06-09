/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_font.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ast-jean <ast-jean@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 12:01:37 by W2Wizard          #+#    #+#             */
/*   Updated: 2023/06/09 11:44:50 by ast-jean         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"
#include "MLX42/MLX42_Int.h"

//= Private =//
static void mlx_img_draw_char(mlx_image_t* image, uint32_t yoffset, int32_t texoffset, int32_t imgoffset)
{
	if (texoffset < 0)
		return;

	uint8_t* pixelx;
	uint8_t* pixeli;
	for (uint32_t y = 0; y < FONT_HEIGHT; y++)
	{
		pixelx = &font_atlas.pixels[((y) * font_atlas.width + texoffset) * BPP];
		pixeli = image->pixels + (((y + yoffset) * (image->width) + imgoffset) * BPP);
		memcpy(pixeli, pixelx, FONT_WIDTH * BPP);
	}
}

/**
 * Does the actual copying of pixels form the atlas buffer to the
 * image buffer.
 * 
 * Skips any non-printable characters.
 * 
 * @param image The image to draw on.
 * @param texture The font_atlas.
 * @param texoffset The character texture X offset.
 * @param imgoffset The image X offset.
 */
static void mlx_draw_char(mlx_image_t* image, int32_t texoffset, int32_t imgoffset)
{
	if (texoffset < 0)
		return;

	uint8_t* pixelx;
	uint8_t* pixeli;
	for (uint32_t y = 0; y < FONT_HEIGHT; y++)
	{
		pixelx = &font_atlas.pixels[(y * font_atlas.width + texoffset) * BPP];
		pixeli = image->pixels + ((y * image->width + imgoffset) * BPP);
		memcpy(pixeli, pixelx, FONT_WIDTH * BPP);
	}
}

//= Public =//
const mlx_texture_t* mlx_get_font(void)
{
    return ((const mlx_texture_t*)&font_atlas);
}

int32_t mlx_get_texoffset(char c)
{
    const bool _isprint = isprint(c);

    // NOTE: Cheesy branchless operation :D
    // +2 To skip line separator in texture
    return (-1 * !_isprint + ((FONT_WIDTH + 2) * (c - 32)) * _isprint);
}

mlx_image_t* mlx_img_put_string(mlx_image_t* img, const char* str, int32_t x, int32_t y)
{
	MLX_NONNULL(img);
	MLX_NONNULL(str);

	// mlx_image_t* strimage = img;

	const size_t len = strlen(str);
	if (len > MLX_MAX_STRING)
		return ((void*)mlx_error(MLX_STRTOOBIG));	
	// if (!(img = mlx_new_image(mlx, len * FONT_WIDTH, FONT_HEIGHT)))
	// 	return (NULL);

	// Draw the text itself
	int32_t imgoffset = 0;
	for (size_t i = 0; i < len; i++, imgoffset += FONT_WIDTH)
		mlx_img_draw_char(img, y, mlx_get_texoffset(str[i]), imgoffset);
	// if (mlx_image_to_window(mlx, strimage, x, y) == -1)
	// 	return (mlx_delete_image(mlx, strimage), NULL);
	return (img);
}


mlx_image_t* mlx_put_string(mlx_t* mlx, const char* str, int32_t x, int32_t y)
{
	MLX_NONNULL(mlx);
	MLX_NONNULL(str);

	mlx_image_t* strimage;
	const size_t len = strlen(str);
	if (len > MLX_MAX_STRING)
		return ((void*)mlx_error(MLX_STRTOOBIG));	
	if (!(strimage = mlx_new_image(mlx, len * FONT_WIDTH, FONT_HEIGHT)))
		return (NULL);

	// Draw the text itself
	int32_t imgoffset = 0;
	for (size_t i = 0; i < len; i++, imgoffset += FONT_WIDTH)
		mlx_draw_char(strimage, mlx_get_texoffset(str[i]), imgoffset);

	if (mlx_image_to_window(mlx, strimage, x, y) == -1)
		return (mlx_delete_image(mlx, strimage), NULL);
	return (strimage);
}
