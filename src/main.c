/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:04:24 by kbarru            #+#    #+#             */
/*   Updated: 2026/01/07 14:50:00 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "core.h"
#include "render.h"
#include "mlx.h"
#include "vectors.h"
#include <fcntl.h>

int	check_properties(t_mini_rt *mini_rt)
{
	if (!mini_rt->cam.is_defined || !mini_rt->cam.is_defined)
	{
		write(2, MISSING_PROPERTY_MSG, ft_strlen(MISSING_PROPERTY_MSG));
		return (GENERIC_ERR);
	}
		return (0);
}

int	main(int argc, char *argv[])

{
	t_mini_rt	mini_rt;
	int			fd;

	init_mini_rt(&mini_rt);
	if (argc != 2 || !check_extension(argv[1], EXTENSION))
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
	print_mini_rt(&mini_rt);
	shoot_rays(&mini_rt);
	mlx_loop(mini_rt.mlx.mlx);
	destroy_mini_rt(&mini_rt);
	return (0);
}
