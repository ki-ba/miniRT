/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:04:24 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/18 13:34:43 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "libft.h"
#include "miniRT.h"
#include "parsing.h"
#include <fcntl.h>
#include "core.h"

#include <math.h>

void	set_point_color(t_mini_rt *mini_rt, t_point vp_point)
{
	t_vec3	ray;

	ray.x = vp_point.x - mini_rt->camera.origin.x;
	ray.y = vp_point.y - mini_rt->camera.origin.y;
	ray.z = vp_point.z - mini_rt->camera.origin.z;
}

void	shoot_rays(t_mini_rt *mini_rt)
{
	size_t	i;
	t_point	*viewport;
	t_point	vp_point;

	(void)mini_rt;
	(void)viewport;
	(void)vp_point;
	i = 0;
	viewport = ft_calloc(WIDTH * HEIGHT, sizeof(t_color));
	while (i < (double)(WIDTH * HEIGHT) / SAMPLE_SIZE)
	{
		vp_point = (t_point){(double)i / WIDTH, i % WIDTH, VP_DISTANCE};
		set_point_color(mini_rt, vp_point);
		++i;
	}
}

int	check_properties(t_mini_rt *mini_rt)
{
	if (!mini_rt->camera.is_defined || !mini_rt->ambient_light.is_defined)
	{
		write(2, MISSING_PROPERTY_MSG, ft_strlen(MISSING_PROPERTY_MSG));
		return (GENERIC_ERR);
	}
	if (ft_lstsize(mini_rt->lights) > 1)
	{
		write(2, TOO_MUCH_ELEMENTS_MSG, ft_strlen(TOO_MUCH_ELEMENTS_MSG));
		return (GENERIC_ERR);
	}
	return (0);
}
int	main(int argc, char *argv[])

{
	t_mini_rt	mini_rt;
	int			fd;

	init_mini_rt(&mini_rt);
	if (argc != 2 || !has_correct_extension(argv[1]))
	{
		write(2, USAGE_ERR_MSG, ft_strlen(USAGE_ERR_MSG));
		clean_exit(&mini_rt, GENERIC_ERR);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (write(2, FILE_ERR_MSG, ft_strlen(FILE_ERR_MSG)));
	if (parse_items_in_file(&mini_rt, fd))
		clean_exit(&mini_rt, GENERIC_ERR);
	if (check_properties(&mini_rt))
		clean_exit(&mini_rt, GENERIC_ERR);
	ft_init_mlx(&mini_rt);
	print_mini_rt(mini_rt);
	mlx_loop(mini_rt.mlx.mlx);
	destroy_mini_rt(&mini_rt);
	return (0);
}
