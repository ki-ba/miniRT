/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:49:44 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/17 15:52:30 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "objects.h"
#include "debug.h"
#include "core.h"

void	destroy_mini_rt(t_mini_rt *mini_rt)
{
	ft_lstclear(&mini_rt->objects, destroy_shape);
	ft_lstclear(&mini_rt->lights, destroy_shape);
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
	mini_rt->mlx.img = (t_data){0};
	mini_rt->lights = NULL;
	mini_rt->objects = NULL;
	mini_rt->camera = (t_camera){0};
	mini_rt->ambient_light = (t_ambient){0};
	ft_init_mlx(mini_rt);
}

void	print_mini_rt(t_mini_rt mini_rt)
{
	print_properties(mini_rt);
	print_item_lst(mini_rt.objects);
	print_item_lst(mini_rt.lights);
}

void	clean_exit(t_mini_rt *mini_rt, int exit_code)
{
	destroy_mini_rt(mini_rt);
	exit(exit_code);
}
