/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abetemps <abetemps@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:06:14 by abetemps          #+#    #+#             */
/*   Updated: 2025/12/23 10:55:53 by abetemps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "unity.h"
#include "rendering.h"

void	test_render(void)
{
	t_mini_rt *mini_rt = &((t_mini_rt) {0});

	TEST_ASSERT_EQUAL(1, render_scene(NULL));
	TEST_ASSERT_EQUAL(0, render_scene(mini_rt));
}

