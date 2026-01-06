/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 09:56:38 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/06 11:02:47 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "graphics.h"
#include "mlx.h"
#include "hooks.h"

void	ft_init_mlx(t_mini_rt *mini_rt)
{
	t_data		*img;

	img = &mini_rt->mlx.img;
	mini_rt->mlx.mlx = mlx_init();
	mini_rt->mlx.win = mlx_new_window(mini_rt->mlx.mlx, WIDTH, HEIGHT, "miniRT");
	mini_rt->mlx.img.img = mlx_new_image(mini_rt->mlx.mlx, WIDTH, HEIGHT);
	mini_rt->mlx.img.addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	mlx_key_hook(mini_rt->mlx.win, handle_keypress, mini_rt);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel >> 3));
	*(unsigned int *) dst = color;
}
