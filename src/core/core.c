/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:49:44 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/11 11:58:08 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "vectors.h"
#include "debug.h"
#include "mlx.h"

void	destroy_mini_rt(t_mini_rt *mini_rt)
{
	clear_vector(&mini_rt->objects);
	clear_vector(&mini_rt->lights);
	if (mini_rt->mlx.img.img)
		mlx_destroy_image(mini_rt->mlx.mlx, mini_rt->mlx.img.img);
	if (mini_rt->mlx.win)
		mlx_destroy_window(mini_rt->mlx.mlx, mini_rt->mlx.win);
	if (mini_rt->mlx.mlx)
	{
		mlx_destroy_display(mini_rt->mlx.mlx);
		free(mini_rt->mlx.mlx);
	}
}

void	init_mini_rt(t_mini_rt *mini_rt)
{
	mini_rt->mlx.mlx = NULL;
	mini_rt->mlx.win = NULL;
	mini_rt->mlx.img = (t_data){0};
	mini_rt->lights = create_vector(1, sizeof(t_light), NULL);
	mini_rt->objects = create_vector(1, sizeof(t_object), NULL);
	mini_rt->cam = (t_camera){0};
	mini_rt->amb = (t_ambient){0};
}

void	print_mini_rt(t_mini_rt *mini_rt)
{
	print_properties(*mini_rt);
	print_item_lst(mini_rt->objects);
	print_lights(mini_rt->lights);
}

void	clean_exit(t_mini_rt *mini_rt, int exit_code)
{
	destroy_mini_rt(mini_rt);
	exit(exit_code);
}
