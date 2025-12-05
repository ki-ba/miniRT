/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 14:23:41 by kbarru            #+#    #+#             */
/*   Updated: 2025/12/04 14:26:11 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "unity.h"
#include "objects.h"

// TODO: Add more tests for object creation functions

void	test_create_light_success(void)
{
	char	*light_arr[] = { "L", "10,20,30", "0.5", "255,255,255", NULL };
	t_light	*light;

	light = create_light(light_arr);
	TEST_ASSERT_NOT_NULL(light);
	free(light);
}
