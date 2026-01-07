/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:02:57 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/07 09:43:14 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

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

#endif
