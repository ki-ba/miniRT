/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:04:24 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/05 17:59:39 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "parsing.h"
#include <fcntl.h>
#include "debug.h"

void	destroy_mini_rt(t_miniRT *miniRT)
{
	ft_lstclear(&miniRT->objects, destroy_shape);
	ft_lstclear(&miniRT->lights, destroy_shape);
}

int	main(int argc, char *argv[])
{
	t_miniRT	mini_rt;
	int			fd;

	mini_rt.lights = NULL;
	mini_rt.objects = NULL;
	(void)argc;
	if (!has_correct_extension(argv[1]))
	{
		write(2, USAGE_ERR_MSG, ft_strlen(USAGE_ERR_MSG));
		return (1);
	}
	fd = open(argv[1], O_RDONLY);
	if (parse_items_in_file(&mini_rt, fd))
		return (write(2, FILE_ERR_MSG, ft_strlen(FILE_ERR_MSG)));
	print_properties(mini_rt);
	print_item_lst(mini_rt.objects);
	print_item_lst(mini_rt.lights);
	destroy_mini_rt(&mini_rt);
	return (0);
}
