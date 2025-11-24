/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:04:24 by kbarru            #+#    #+#             */
/*   Updated: 2025/11/24 15:33:56 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "parsing.h"

int	main(int argc, char *argv[])
{
	ft_printf("main file\n");
	while (--argc)
		ft_printf("%d\n", has_correct_extension(argv[argc]));
	return (0);
}
