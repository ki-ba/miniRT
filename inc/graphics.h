/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:02:57 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/23 14:59:36 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "color.h"

# define WIDTH 1920
# define HEIGHT 1080

# define W WIDTH
# define H HEIGHT

# define LQ_SCALE 30
# define HQ_SCALE 1

// Common factors betweeen 1920 and 1080 are :
// 1, 2, 3, 4, 5, 6, 8, 10, 12, 15, 20, 24, 30, 40, 60, 120

typedef struct s_mini_rt	t_mini_rt;
typedef struct s_data		t_data;
typedef struct s_mlx		t_mlx;

struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
};

struct s_mlx
{
	void		*mlx;
	void		*win;
	t_data		img;
};

void	ft_init_mlx(t_mini_rt *mini_rt);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
void	draw_upscaled(t_data *img, int i, t_color c, int scale);

#endif
