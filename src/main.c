/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:04:24 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/17 15:54:05 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "parsing.h"
#include <fcntl.h>
#include "debug.h"
#include "objects.h"
#include "core.h"

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
	if (!mini_rt.camera.is_defined || !mini_rt.ambient_light.is_defined)
	{
		write(2, MISSING_PROPERTY_MSG, ft_strlen(MISSING_PROPERTY_MSG));
		clean_exit(&mini_rt, GENERIC_ERR);
	}
	print_mini_rt(mini_rt);
	mlx_loop(mini_rt.mlx);
	destroy_mini_rt(&mini_rt);
	return (0);
}
