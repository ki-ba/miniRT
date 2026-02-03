/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 09:56:38 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/17 12:00:44 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <X11/X.h>
#include "miniRT.h"
#include "graphics.h"
#include "mlx.h"
#include "hooks.h"

static void	init_mouse(t_mini_rt *mini_rt)
{
	mlx_mouse_move(mini_rt->mlx.mlx, mini_rt->mlx.win, W >> 1, H >> 1);
	mlx_mouse_hide(mini_rt->mlx.mlx, mini_rt->mlx.win);
}

void	ft_init_mlx(t_mini_rt *mini_rt)
{
	t_data		*img;
	void		*win;

	img = &mini_rt->mlx.img;
	mini_rt->mlx.mlx = mlx_init();
	mini_rt->mlx.win = mlx_new_window(mini_rt->mlx.mlx, W, H, "miniRT");
	win = mini_rt->mlx.win;
	mini_rt->mlx.img.img = mlx_new_image(mini_rt->mlx.mlx, W, H);
	mini_rt->mlx.img.addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	init_mouse(mini_rt);
	mlx_key_hook(mini_rt->mlx.win, handle_keypress, mini_rt);
	mlx_mouse_hook(mini_rt->mlx.win, handle_mouse_scroll, mini_rt);
	mlx_hook(win, MotionNotify, PointerMotionMask, handle_mouse_move, mini_rt);
	mlx_hook(win, ON_DESTROY, 0, handle_window_close, mini_rt);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr;
	dst += (y * data->line_length + x * (data->bits_per_pixel >> 3));
	*(unsigned int *) dst = color;
}

void	draw_upscaled(t_data *img, int i, t_color c, int scale)
{
	int		rw;
	int		w_x0;
	int		w_y0;
	int		dx;
	int		dy;

	rw = (W / scale);
	w_x0 = (i % rw) * scale;
	w_y0 = (i / rw) * scale;
	dx = 0;
	while (dx < scale)
	{
		dy = 0;
		while (dy < scale)
		{
			my_mlx_pixel_put(img, w_x0 + dx, w_y0 + dy, c.trgb);
			++dy;
		}
		++dx;
	}
}
